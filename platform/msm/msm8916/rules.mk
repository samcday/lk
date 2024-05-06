LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

ARCH    := arm
ARM_CPU := cortex-a8
CPU     := generic

MODULE_SRCS += \
	$(LOCAL_DIR)/acpuclock.c \
	$(LOCAL_DIR)/clock.c \
	$(LOCAL_DIR)/gpio.c \
	$(LOCAL_DIR)/platform.c

MEMBASE := 0x8F600000
MEMSIZE := 0x00100000
KERNEL_BASE = $(MEMBASE)

MODULE_DEPS += \
    dev/interrupt/arm_gic \
    dev/timer/arm_generic

include platform/msm/common/rules.mk
include make/module.mk
