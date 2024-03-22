# SPDX-License-Identifier: BSD-3-Clause
LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE_SRCS += \
	$(LOCAL_DIR)/cpuid.c \
	$(LOCAL_DIR)/register.c \

# Currently the regulator fastboot debug code is only used for SPMI regulators
ifneq ($(filter dev/pmic/pm8x41, $(ALLMODULES)),)
ifneq ($(BUILD_GPL),)
MODULES += lk2nd/hw/regulator
MODULE_SRCS += $(LOCAL_DIR)/regulator.c
endif
endif
