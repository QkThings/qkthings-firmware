PROJECT_NAME = qkperipheral

LIB_BUILD_DIR = $(TARGET_CPU)/$(TARGET_BOARD)

LIB_INCLUDE_DIRS += \
/include \
/src/include

LIB_C_SRC_DIRS += \
/src

include $(LIB)/target/$(TARGET_CPU)/board/$(TARGET_BOARD).mk
include $(LIB)/target/$(TARGET_CPU)/$(TARGET_CPU).mk
