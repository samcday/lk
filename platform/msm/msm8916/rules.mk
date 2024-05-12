LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

ARCH    := arm
ARM_CPU := cortex-a8
WITH_SMP := 1

MODULE_SRCS += \
	$(LOCAL_DIR)/clock.c \
	$(LOCAL_DIR)/gpio.c \
	$(LOCAL_DIR)/platform.c

MEMBASE := 0x80000000
MEMSIZE := 0x00100000

MODULE_DEPS += \
    dev/interrupt/arm_gic \
    lib/debugcommands \
    app/tests

# dev/timer/arm_generic doesn't work on msm8916 - it reads platform time okay,
# but the interrupts never fire (I tried GIC_SPI_START+8 and GIC_PPI_START+2)
# So for now we use qtimer code pulled from downstream sources.
#    dev/timer/arm_generic \

include platform/msm/common/rules.mk
include make/module.mk
