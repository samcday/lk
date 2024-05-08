LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

ARCH    := arm

# When targetting cortex-a8 as lk2nd does, we run into a panic in fpu.c
# (the check in arm_fpu_undefined_instruction). So for now the target is a9
# which doesn't define ARM_WITH_VFP. Seems like there's a deeper issue that
# ought to be resolved ...
ARM_CPU := cortex-a9

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
