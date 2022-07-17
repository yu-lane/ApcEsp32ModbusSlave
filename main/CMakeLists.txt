set(PROJECT_NAME "ApcEsp32ModbusSlave")

idf_component_register(SRCS "apc_modbus_regs.c" "slave.c"
                    INCLUDE_DIRS ".")
