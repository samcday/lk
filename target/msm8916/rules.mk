LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

GLOBAL_INCLUDES += $(LOCAL_DIR)/include $(LKROOT)/platform/msm_shared
GLOBAL_INCLUDES += $(LKROOT)/dev/gcdb/display $(LKROOT)/dev/gcdb/display/include

PLATFORM := msm8916

MEMBASE := 0x8F600000 # SDRAM
MEMSIZE := 0x00100000 # 1MB

BASE_ADDR        := 0x80000000
SCRATCH_ADDR     := 0x90000000

GLOBAL_DEFINES += DISPLAY_SPLASH_SCREEN=1
GLOBAL_DEFINES += DISPLAY_TYPE_MIPI=1
GLOBAL_DEFINES += DISPLAY_TYPE_DSI6G=1

MODULES += \
	dev/gcdb/display \
	dev/keys \
	dev/pmic/pm8x41 \
	dev/vib \
	lib/fdt \
	lib/ptable_android \

GLOBAL_DEFINES += \
	MEMSIZE=$(MEMSIZE) \
	MEMBASE=$(MEMBASE) \
	BASE_ADDR=$(BASE_ADDR) \
	SCRATCH_ADDR=$(SCRATCH_ADDR)


MODULE_SRCS += \
	$(LOCAL_DIR)/init.c \
	$(LOCAL_DIR)/meminfo.c \
	$(LOCAL_DIR)/target_display.c \
	$(LOCAL_DIR)/oem_panel.c

include make/module.mk
