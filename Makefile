#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := ApcEsp32ModbusSlave

EXTRA_COMPONENT_DIRS := $(IDF_PATH)/components/freemodbus

include $(IDF_PATH)/make/project.mk
