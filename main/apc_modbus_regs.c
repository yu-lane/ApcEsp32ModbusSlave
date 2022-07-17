#include "apc_modbus_regs.h"
#include <stdint.h>


#pragma pack(push, 1)
typedef struct ApcModbusRegStatus
{
    /**(0x0000 – 0x0007F)
     * Status and Alarm Registers. 
     */
    uint32_t UPSStatus_BF;                  //0
    uint16_t UPSStatusChangeCause_EN;       //2
    uint32_t MOG_OutletStatus_BF;           //3
    uint32_t SOG0_OutletStatus_BF;          //6
    uint32_t SOG1_OutletStatus_BF;          //9
    uint32_t SOG2_OutletStatus_BF;          //12
    uint32_t SOG3_OutletStatus_BF;          //15
    uint16_t SimpleSignalStatus_BF;         //18
    uint16_t GeneralError_BF;               //19
    uint32_t PowerSystemError_BF;           //20
    uint16_t BatterySystemError_BF;         //22
    uint16_t ReplaceBatteryTestStatus_BF;   //23
    uint16_t RunTimeCalibrationStatus_BF;   //24
    uint16_t Battery_LifeTimeStatus_BF;     //25
    uint16_t UserInterfaceStatus_BF;        //26
}ApcModbusRegStatus_t;

typedef struct ApcModbusRegDynamic
{
    /* (0x0080 – 0x01FF)
    The dynamic data consists of information 
    that changes during the operation and 
    consists of measurement information. */
    uint32_t RunTimeRemaining;                 //128
    uint16_t StateOfCharge_Pct;                //130
    uint16_t Battery_Positive_VoltageDC;       //131
    uint16_t _Reserve;                         //132
    uint16_t Battery_Date;                     //133
    uint16_t _Reserve1;                        //134
    uint16_t Battery_Temperature;              //135
    uint16_t Output0_RealPower_Pct;            //136
    uint16_t _Reserve2;                        //137
    uint16_t Output0_ApparentPower_Pct;        //138
    uint16_t _Reserve3;                        //139
    uint16_t Output0_CurrentAC;                //140
    uint16_t _Reserve4;                        //141
    uint16_t Output0_VoltageAC;                //142
    uint16_t _Reserve5;                        //143
    uint16_t Output_Frequency;                 //144
    uint32_t Output_Energy;                    //145
    uint16_t _Reserve6[4];                     //146
    uint16_t Input_InputStatus_BF;             //150
    uint16_t Input0_VoltageAC;                 //151
    uint16_t _Reserve7[2];                     //152
    uint16_t Input_Efficiency_EN;              //154
    uint16_t MOG_TurnOffCountdown_EN;          //155
    uint16_t MOG_TurnOnCountdown_EN;           //156
    uint32_t MOG_StayOffCountdown_EN;          //157
    uint16_t SOG0_TurnOffCountdown_EN;         //159
    uint16_t SOG0_TurnOnCountdown_EN;          //160
    uint32_t SOG0_StayOffCountdown_EN;         //161
    uint16_t SOG1_TurnOffCountdown_EN;         //163
    uint16_t SOG1_TurnOnCountdown_EN;          //164
    uint32_t SOG1_StayOffCountdown_EN;         //165
    uint16_t SOG2_TurnOffCountdown_EN;         //167
    uint16_t SOG2_TurnOnCountdown_EN;          //168
    uint32_t SOG2_StayOffCountdown_EN;         //169
    uint16_t SOG3_TurnOffCountdown_EN;         //171
    uint16_t SOG3_TurnOnCountdown_EN;          //172
    uint32_t SOG3_StayOffCountdown_EN;         //173

}ApcModbusRegDynamic_t;



typedef struct ApcModbusRegInventory
{
    /*  (0x0200 – 0x03FF)
    This is information about the particular 
    device, including SKU Name, Serial 
    Number, Firmware version, and 
    Manufacturing Date. User Configuration 
    strings will be in this region as well. 
    */
    uint16_t _Reserve01[2];                    //512,513
    uint32_t _Reserve4B;                       //514
    char FWVersion_STR[16];                    //516
    char _Reserve_STR[16];                     //524
    char Model_STR[32];                        //532
    char SKU_STR[32];                          //548
    char SerialNumber_STR[16];                 //564
    char Battery_SKU_STR[16];                  //572
    char Battery_ExternalBattery_SKU_STR[16];  //580
    uint16_t Output_ApparentPowerRating;       //588
    uint16_t Output_RealPowerRating;           //589
    uint16_t I_SOGRelayConfigSetting_BF;       //590
    uint16_t Date;                             //591
    uint16_t Output_VoltageACSetting_BF;       //592
    uint16_t _Reserve[2];                      //593,594
    uint16_t Battery_DateSetting;              //595
    char Name_STR[16];                         //596
    char MogName_STR[16];                      //604
    char SOG0Name_STR[16];                     //612
    char SOG1Name_STR[16];                     //620
    char SOG2Name_STR[16];                     //628
    char SOG3Name_STR[16];                     //636
    uint32_t VoltageACSetting_BF;              //644
}ApcModbusRegInventory_t;



typedef struct ApcModbusRegStatic
{
    /*  (0x0400 – 0x5FF)
    The static data consists of string 
    information, and configuration data that 
    does not change frequently.
    */
    uint16_t BatteryTestIntervalSetting_BF_Lookup;      //1024
    uint16_t PowerQualitySetting_BF;                    //1025
    uint16_t Output_UpperAcceptableVoltageSetting;      //1026
    uint16_t Output_LowerAcceptableVoltageSetting;      //1027
    uint16_t Output_SensitivitySetting_BF;              //1028
    uint16_t MOG_TurnOffCountdownSetting_EN;            //1029
    uint16_t MOG_TurnOnCountdownSetting_EN;             //1030
    uint32_t MOG_StayOffCountdownSetting_4B;            //1031
    uint16_t MOG_MinimumReturnRuntimeSetting;           //1033
    uint16_t SOG0_TurnOffCountdownSetting_EN;           //1034
    uint16_t SOG0_TurnOnCountdownSetting_EN;            //1035
    uint32_t SOG0_StayOffCountdownSetting_4B;           //1036
    uint16_t SOG0_MinimumReturnRuntimeSetting;           //1038
    uint16_t SOG1_TurnOffCountdownSetting_EN;           //1039
    uint16_t SOG1_TurnOnCountdownSetting_EN;            //1040
    uint32_t SOG1_StayOffCountdownSetting_4B;           //1041
    uint16_t SOG1_MinimumReturnRuntimeSetting;           //1043
    uint16_t SOG2_TurnOffCountdownSetting_EN;           //1044
    uint16_t SOG2_TurnOnCountdownSetting_EN;            //1045
    uint32_t SOG2_StayOffCountdownSetting_4B;           //1046
    uint16_t SOG2_MinimumReturnRuntimeSetting;           //1047
    uint16_t SOG3_TurnOffCountdownSetting_EN;           //1049
    uint16_t SOG3_TurnOnCountdownSetting_EN;            //1050
    uint32_t SOG3_StayOffCountdownSetting_4B;           //1051
    uint16_t SOG3_MinimumReturnRuntimeSetting;           //1053
}ApcModbusRegStatic_t;

typedef struct ApcModbusRegCommands
{
    /* s (0x0600 – 0x6FF)
    Write only commands that affect operation
    */
    uint32_t UPSCommand_BF;                   //1536
    uint32_t OutletCommand_BF;                //1538
    uint16_t SimpleSignalingCommand_BF;       //1540
    uint16_t ReplaceBatteryTestCommand_BF;    //1541
    uint16_t RunTimeCalibrationCommand_BF;    //1542
    uint16_t UserInterfaceCommand_BF;         //1543

}ApcModbusRegCommands_t;

typedef struct ApcModbusRegProtocolVerify
{
    /*  (0x0800 – 0x8FF)
    Read only data to verify protocol 
    communications. 
    */
    uint8_t ModbusMapID[4];                 //2048
    uint8_t TestString[8];                  //2050
    uint8_t Test4BNumber1[4];               //2054
    uint8_t Test4BNumber2[4];               //2056
    uint8_t Test2BNumber1[2];               //2058
    uint8_t Test2BNumber2[2];               //2059
    uint8_t TestBPINumber1[2];              //2060
    uint8_t TestBPINumber2[2];              //2061

}ApcModbusRegProtocolVerify_t;
#pragma pack(pop)


ApcModbusRegStatus_t apcModbusRegStatus;
ApcModbusRegDynamic_t apcModbusRegDynamic;
ApcModbusRegStatic_t apcModbusRegStatic;
ApcModbusRegInventory_t apcModbusRegInventory;
ApcModbusRegCommands_t apcModbusRegCommands;
ApcModbusRegProtocolVerify_t apcModbusRegProtocolVerify;

void ApcModbusReg_ProtocolVerifyInit(void)
{
    apcModbusRegProtocolVerify.ModbusMapID[0] = 0x30;
    apcModbusRegProtocolVerify.ModbusMapID[1] = 0x30;
    apcModbusRegProtocolVerify.ModbusMapID[2] = 0x2e;
    apcModbusRegProtocolVerify.ModbusMapID[3] = 0x35;

    apcModbusRegProtocolVerify.TestString[0] = 0x31;
    apcModbusRegProtocolVerify.TestString[1] = 0x32;
    apcModbusRegProtocolVerify.TestString[2] = 0x33;
    apcModbusRegProtocolVerify.TestString[3] = 0x34;
    apcModbusRegProtocolVerify.TestString[4] = 0x35;
    apcModbusRegProtocolVerify.TestString[5] = 0x36;
    apcModbusRegProtocolVerify.TestString[6] = 0x37;
    apcModbusRegProtocolVerify.TestString[7] = 0x38;

    apcModbusRegProtocolVerify.Test4BNumber1[0] = 0x12;
    apcModbusRegProtocolVerify.Test4BNumber1[1] = 0x34;
    apcModbusRegProtocolVerify.Test4BNumber1[2] = 0x56;
    apcModbusRegProtocolVerify.Test4BNumber1[3] = 0x78;

    apcModbusRegProtocolVerify.Test4BNumber2[0] = 0xff;
    apcModbusRegProtocolVerify.Test4BNumber2[1] = 0xff;
    apcModbusRegProtocolVerify.Test4BNumber2[2] = 0xff;
    apcModbusRegProtocolVerify.Test4BNumber2[3] = 0xfb;

    apcModbusRegProtocolVerify.Test2BNumber1[0] = 0x12;
    apcModbusRegProtocolVerify.Test2BNumber1[1] = 0x34;

    apcModbusRegProtocolVerify.Test2BNumber2[0] = 0xff;
    apcModbusRegProtocolVerify.Test2BNumber2[1] = 0xfb;

    apcModbusRegProtocolVerify.TestBPINumber1[0] = 0x20;
    apcModbusRegProtocolVerify.TestBPINumber1[1] = 0x20;

    apcModbusRegProtocolVerify.TestBPINumber2[0] = 0xdf;
    apcModbusRegProtocolVerify.TestBPINumber2[1] = 0xe0;

}

void APcModbusGetRegDescriptor(APcDataTypeAndOffset_t type, mb_register_area_descriptor_t *pDescriptor)
{
    switch (type)
    {
    case STATUS_DATA:
        pDescriptor->type = MB_PARAM_INPUT;
        pDescriptor->start_offset = STATUS_DATA;
        pDescriptor->address = &apcModbusRegStatus;
        pDescriptor->size = sizeof(apcModbusRegStatus);
        break;
    case DYNAMIC_DATA:
        pDescriptor->type = MB_PARAM_HOLDING;
        pDescriptor->start_offset = DYNAMIC_DATA;
        pDescriptor->address = &apcModbusRegDynamic;
        pDescriptor->size = sizeof(apcModbusRegDynamic);
        break;
    case STATIC_DATA:
        pDescriptor->type = MB_PARAM_HOLDING;
        pDescriptor->start_offset = STATIC_DATA;
        pDescriptor->address = &apcModbusRegStatic;
        pDescriptor->size = sizeof(apcModbusRegStatic);
        break;
    case INVENTORY_DATA:
        pDescriptor->type = MB_PARAM_HOLDING;
        pDescriptor->start_offset = INVENTORY_DATA;
        pDescriptor->address = &apcModbusRegInventory;
        pDescriptor->size = sizeof(apcModbusRegInventory);
        break;
    case COMMANDS:
        pDescriptor->type = MB_PARAM_HOLDING;
        pDescriptor->start_offset = COMMANDS;
        pDescriptor->address = &apcModbusRegCommands;
        pDescriptor->size = sizeof(apcModbusRegCommands);
        break;
    case PROTOCOL_VERIFY:
        pDescriptor->type = MB_PARAM_INPUT;
        pDescriptor->start_offset = PROTOCOL_VERIFY;
        pDescriptor->address = &apcModbusRegProtocolVerify;
        pDescriptor->size = sizeof(apcModbusRegProtocolVerify);
        break;
    
    default:
        break;
    }
}

