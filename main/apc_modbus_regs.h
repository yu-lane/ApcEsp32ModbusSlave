#ifndef __APC_MODBUS_REGS_H__
#define __APC_MODBUS_REGS_H__


#include "mbcontroller.h"       // for mb_register_area_descriptor_t

typedef enum APcDataTypeAndOffset{
    STATUS_DATA = 0,
    DYNAMIC_DATA = 0x0080,
    INVENTORY_DATA = 0x0200,
    STATIC_DATA  = 0x0400,
    COMMANDS = 0x0600,
    PROTOCOL_VERIFY = 0x0800,
}APcDataTypeAndOffset_t;


void ApcModbusReg_ProtocolVerifyInit(void);
void APcModbusGetRegDescriptor(APcDataTypeAndOffset_t type, mb_register_area_descriptor_t *pDescriptor);

#endif
