####################################################################
# qkthings                                                      
####################################################################

QKPERIPHERAL_DIR = qkperipheral


####################################################################
# SOURCE                   
####################################################################

INCLUDE_DIRS += \
$(QKPERIPHERAL_DIR)/include \
$(QKPERIPHERAL_DIR)/src/include

C_SRC_DIRS += \
$(QKPERIPHERAL_DIR)/src

s_SRC += 
S_SRC += 


####################################################################
# TARGET
####################################################################

#include $(TARGET_GLOBAL)
include $(QKPERIPHERAL_DIR)/target/$(TARGET_CPU)/board/$(TARGET_BOARD).mk
include $(QKPERIPHERAL_DIR)/target/$(TARGET_CPU)/$(TARGET_CPU).mk





