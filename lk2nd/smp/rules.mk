# SPDX-License-Identifier: BSD-3-Clause
LOCAL_DIR := $(GET_LOCAL_DIR)
MODULES += lib/fdt

# Additional initialization for CPU clocks (if needed)
MODULE_SRCS += $(wildcard $(LOCAL_DIR)/clock-$(PLATFORM).c)

ifneq ($(filter msm8226 msm8610 msm8909 msm8916, $(PLATFORM)),)
CPU_BOOT_SRCS := $(LOCAL_DIR)/cortex-a.c
GLOBAL_DEFINES += CPU_BOOT_CORTEX_A=1
else ifneq ($(filter apq8084 msm8974, $(PLATFORM)),)
CPU_BOOT_SRCS := $(if $(BUILD_GPL), $(LOCAL_DIR)/gpl/krait.c)
GLOBAL_DEFINES += CPU_BOOT_KPSSV2=1
else ifneq ($(filter msm8960, $(PLATFORM)),)
CPU_BOOT_SRCS := $(if $(BUILD_GPL), $(LOCAL_DIR)/gpl/krait.c)
GLOBAL_DEFINES += CPU_BOOT_KPSSV1=1
endif

MODULE_SRCS += $(if $(CPU_BOOT_SRCS), $(LOCAL_DIR)/cpu-boot.c $(CPU_BOOT_SRCS))
