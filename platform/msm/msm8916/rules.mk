LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

ARCH    := arm
ARM_CPU := cortex-a8

MODULE_SRCS += \
	$(LOCAL_DIR)/clock.c \
	$(LOCAL_DIR)/gpio.c \
	$(LOCAL_DIR)/platform.c

MEMBASE := 0x80000000
MEMSIZE := 0x00100000

MODULE_DEPS += \
    dev/interrupt/arm_gic \
    dev/timer/arm_generic \
    lib/debugcommands \
    app/tests

include platform/msm/common/rules.mk
include make/module.mk
