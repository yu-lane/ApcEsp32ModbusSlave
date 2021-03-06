/* FreeModbus Slave Example ESP32

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <stdint.h>
#include "esp_err.h"
#include "mbcontroller.h"       // for mbcontroller defines and api
#include "esp_log.h"            // for log_write
#include "sdkconfig.h"

#include "apc_modbus_regs.h"


#define MB_PORT_NUM     (CONFIG_MB_UART_PORT_NUM)   // Number of UART port used for Modbus connection
#define MB_SLAVE_ADDR   (CONFIG_MB_SLAVE_ADDR)      // The address of device in Modbus network
#define MB_DEV_SPEED    (CONFIG_MB_UART_BAUD_RATE)  // The communication speed of the UART

// Note: Some pins on target chip cannot be assigned for UART communication.
// Please refer to documentation for selected board and target to configure pins using Kconfig.

// Defines below are used to define register start address for each type of Modbus registers
#define HOLD_OFFSET(field) ((uint16_t)(offsetof(holding_reg_params_t, field) >> 1))
#define INPUT_OFFSET(field) ((uint16_t)(offsetof(input_reg_params_t, field) >> 1))


#define MB_PAR_INFO_GET_TOUT                (10) // Timeout for get parameter info

// #define MB_CHAN_DATA_MAX_VAL                (6)
// #define MB_CHAN_DATA_OFFSET                 (0.2f)

#define MB_READ_MASK                        (MB_EVENT_INPUT_REG_RD \
                                                | MB_EVENT_HOLDING_REG_RD \
                                                | MB_EVENT_DISCRETE_RD \
                                                | MB_EVENT_COILS_RD)

#define MB_WRITE_MASK                       (MB_EVENT_HOLDING_REG_WR \
                                                | MB_EVENT_COILS_WR)

#define MB_READ_WRITE_MASK                  (MB_READ_MASK | MB_WRITE_MASK)

static const char *TAG = "SLAVE_TEST";

// static portMUX_TYPE param_lock = portMUX_INITIALIZER_UNLOCKED;

#pragma pack(push, 1)
typedef struct
{
    uint16_t test_regs[50];
} apc_holding_reg_t;
apc_holding_reg_t apc_holding_reg;


#pragma pack(pop)
// Set register values into known state
static void setup_reg_data(void)
{
    // Define initial state of parameters
    for(int i=0; i< 50; i++){
        apc_holding_reg.test_regs[i] = i;
    }
}

// An example application of Modbus slave. It is based on freemodbus stack.
// See deviceparams.h file for more information about assigned Modbus parameters.
// These parameters can be accessed from main application and also can be changed
// by external Modbus master host.
void app_main(void)
{
    mb_param_info_t reg_info; // keeps the Modbus registers access information
    mb_communication_info_t comm_info; // Modbus communication parameters
    mb_register_area_descriptor_t reg_area; // Modbus register area descriptor structure

    // Set UART log level
    esp_log_level_set(TAG, ESP_LOG_DEBUG);
    void* mbc_slave_handler = NULL;

    ESP_ERROR_CHECK(mbc_slave_init(MB_PORT_SERIAL_SLAVE, &mbc_slave_handler)); // Initialization of Modbus controller

    // Setup communication parameters and start stack
#if CONFIG_MB_COMM_MODE_ASCII
    comm_info.mode = MB_MODE_ASCII,
#elif CONFIG_MB_COMM_MODE_RTU
    comm_info.mode = MB_MODE_RTU,
#endif
    comm_info.slave_addr = MB_SLAVE_ADDR;
    comm_info.port = MB_PORT_NUM;
    comm_info.baudrate = MB_DEV_SPEED;
    comm_info.parity = MB_PARITY_NONE;
    ESP_ERROR_CHECK(mbc_slave_setup((void*)&comm_info));

    ApcModbusReg_ProtocolVerifyInit();
    // The code below initializes Modbus register area descriptors
    // for Modbus Holding Registers, Input Registers, Coils and Discrete Inputs
    // Initialization should be done for each supported Modbus register area according to register map.
    // When external master trying to access the register in the area that is not initialized
    // by mbc_slave_set_descriptor() API call then Modbus stack
    // will send exception response for this register area.

    APcModbusGetRegDescriptor(STATUS_DATA, &reg_area);
    ESP_ERROR_CHECK(mbc_slave_set_descriptor(reg_area));
    ESP_LOGI(TAG, "Modbus reg type:%d", reg_area.type);
    ESP_LOGI(TAG, "Modbus reg start:%d", reg_area.start_offset);
    ESP_LOGI(TAG, "Modbus reg address: %08x", (uint32_t)reg_area.address);
    ESP_LOGI(TAG, "Modbus reg size:%d", reg_area.size);


    APcModbusGetRegDescriptor(DYNAMIC_DATA, &reg_area);
    ESP_ERROR_CHECK(mbc_slave_set_descriptor(reg_area));
    ESP_LOGI(TAG, "Modbus reg type:%d", reg_area.type);
    ESP_LOGI(TAG, "Modbus reg start:%d", reg_area.start_offset);
    ESP_LOGI(TAG, "Modbus reg address: %08x", (uint32_t)reg_area.address);
    ESP_LOGI(TAG, "Modbus reg size:%d", reg_area.size);

    APcModbusGetRegDescriptor(STATIC_DATA, &reg_area);
    ESP_ERROR_CHECK(mbc_slave_set_descriptor(reg_area));
    ESP_LOGI(TAG, "Modbus reg type:%d", reg_area.type);
    ESP_LOGI(TAG, "Modbus reg start:%d", reg_area.start_offset);
    ESP_LOGI(TAG, "Modbus reg address: %08x", (uint32_t)reg_area.address);
    ESP_LOGI(TAG, "Modbus reg size:%d", reg_area.size);

    APcModbusGetRegDescriptor(COMMANDS, &reg_area);
    ESP_ERROR_CHECK(mbc_slave_set_descriptor(reg_area));
    ESP_LOGI(TAG, "Modbus reg type:%d", reg_area.type);
    ESP_LOGI(TAG, "Modbus reg start:%d", reg_area.start_offset);
    ESP_LOGI(TAG, "Modbus reg address: %08x", (uint32_t)reg_area.address);
    ESP_LOGI(TAG, "Modbus reg size:%d", reg_area.size);

    APcModbusGetRegDescriptor(PROTOCOL_VERIFY, &reg_area);
    ESP_ERROR_CHECK(mbc_slave_set_descriptor(reg_area));
    ESP_LOGI(TAG, "Modbus reg type:%d", reg_area.type);
    ESP_LOGI(TAG, "Modbus reg start:%d", reg_area.start_offset);
    ESP_LOGI(TAG, "Modbus reg address: %08x", (uint32_t)reg_area.address);
    ESP_LOGI(TAG, "Modbus reg size:%d", reg_area.size);

    setup_reg_data(); // Set values into known state

    // Starts of modbus controller and stack
    ESP_ERROR_CHECK(mbc_slave_start());

    // Set UART pin numbers
    ESP_ERROR_CHECK(uart_set_pin(MB_PORT_NUM, CONFIG_MB_UART_TXD,
                            CONFIG_MB_UART_RXD, CONFIG_MB_UART_RTS,
                            UART_PIN_NO_CHANGE));

    // Set UART driver mode to Half Duplex
    ESP_ERROR_CHECK(uart_set_mode(MB_PORT_NUM, UART_MODE_RS485_HALF_DUPLEX));

    ESP_LOGI(TAG, "Modbus slave stack initialized.");
    ESP_LOGI(TAG, "Start modbus test...");

    // The cycle below will be terminated when parameter holdingRegParams.dataChan0
    // incremented each access cycle reaches the CHAN_DATA_MAX_VAL value.
    while(apc_holding_reg.test_regs[0]!=100) {
        // Check for read/write events of Modbus master for certain events
        mb_event_group_t event = mbc_slave_check_event(MB_READ_WRITE_MASK);
        const char* rw_str = (event & MB_READ_MASK) ? "READ" : "WRITE";

        // Filter events and process them accordingly
        if(event & (MB_EVENT_HOLDING_REG_WR | MB_EVENT_HOLDING_REG_RD)) {
            // Get parameter information from parameter queue
            ESP_ERROR_CHECK(mbc_slave_get_param_info(&reg_info, MB_PAR_INFO_GET_TOUT));
            ESP_LOGI(TAG, "HOLDING %s (%u us), ADDR:%u, TYPE:%u, INST_ADDR:0x%.4x, SIZE:%u",
                    rw_str,
                    (uint32_t)reg_info.time_stamp,
                    (uint32_t)reg_info.mb_offset,
                    (uint32_t)reg_info.type,
                    (uint32_t)reg_info.address,
                    (uint32_t)reg_info.size);
            // if (reg_info.address == (uint8_t*)&holding_reg_params.holding_data0)
            // {
            //     portENTER_CRITICAL(&param_lock);
            //     holding_reg_params.holding_data0 += MB_CHAN_DATA_OFFSET;
            //     if (holding_reg_params.holding_data0 >= (MB_CHAN_DATA_MAX_VAL - MB_CHAN_DATA_OFFSET)) {
            //         coil_reg_params.coils_port1 = 0xFF;
            //     }
            //     portEXIT_CRITICAL(&param_lock);
            // }
        }
    }
    // Destroy of Modbus controller on alarm
    ESP_LOGI(TAG,"Modbus controller destroyed.");
    vTaskDelay(100);
    ESP_ERROR_CHECK(mbc_slave_destroy());
}
