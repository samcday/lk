# SPDX-License-Identifier: BSD-3-Clause
LOCAL_DIR := $(GET_LOCAL_DIR)

MODULES += \
	lib/fdt \
	lk2nd/hw/gpio \
	lk2nd/hw/i2c \

MODULE_SRCS += \
	$(LOCAL_DIR)/device.c \
	$(LOCAL_DIR)/match.c \
	$(LOCAL_DIR)/parse-cmdline.c \
	$(LOCAL_DIR)/parse-tags.c \
	$(LOCAL_DIR)/partition.c \
	$(LOCAL_DIR)/samsung-muic-reset.c \
	$(if $(filter %/mdss_spi.c, $(MODULE_SRCS)), $(LOCAL_DIR)/spi-display.c) \

ifneq ($(LK2ND_PARTITION_SIZE),)
GLOBAL_DEFINES += \
	LK2ND_PARTITION_BASE="$(LK2ND_PARTITION_BASE)" \
	LK2ND_PARTITION_NAME="$(LK2ND_PARTITION_NAME)" \
	LK2ND_PARTITION_SIZE=($(LK2ND_PARTITION_SIZE))
endif

ifneq ($(QHYPSTUB_PARTITION_SIZE),)
GLOBAL_DEFINES += \
	QHYPSTUB_PARTITION_BASE="$(QHYPSTUB_PARTITION_BASE)" \
	QHYPSTUB_PARTITION_NAME="$(QHYPSTUB_PARTITION_NAME)" \
	QHYPSTUB_PARTITION_SIZE=($(QHYPSTUB_PARTITION_SIZE))
endif

include $(if $(BUILD_GPL),$(LOCAL_DIR)/gpl/rules.mk)

ifneq ($(OUTBOOTIMG),)
# Appended DTBs
OUTBINDTB := $(OUTBIN)
ifneq ($(ADTBS),)
OUTBINDTB := $(OUTBIN)-dtb
$(OUTBINDTB): $(OUTBIN) $(ADTBS)
	@echo generating image with $(words $(ADTBS)) appended DTBs: $@
	$(NOECHO)cat $^ > $@
endif

# QCDT image
ifneq ($(LK2ND_QCDT),)
OUTQCDT := $(LK2ND_QCDT)
$(warning WARNING: Using pre-built QCDT image from $(LK2ND_QCDT))
else ifneq ($(QCDTBS),)
OUTQCDT := $(BUILDDIR)/qcdt.img
$(OUTQCDT): $(QCDTBS)
	@echo generating QCDT image with $(words $(QCDTBS)) DTBs: $@
	$(NOECHO)lk2nd/scripts/dtbTool -o $@ $(QCDTBS)
endif

# Android boot image
MKBOOTIMG_BASE ?= $(BASE_ADDR)

ifeq ($(ENABLE_UFS_SUPPORT), 1)
MKBOOTIMG_PAGESIZE ?= 4096
endif

$(OUTBOOTIMG): $(OUTBINDTB) $(OUTQCDT)
	@echo generating Android boot image: $@
	$(NOECHO)lk2nd/scripts/mkbootimg \
		--kernel=$< \
		--output=$@ \
		--cmdline="$(MKBOOTIMG_CMDLINE)" \
		$(if $(OUTQCDT),--qcdt=$(OUTQCDT)) \
		$(if $(MKBOOTIMG_BASE),--base=$(MKBOOTIMG_BASE)) \
		$(if $(MKBOOTIMG_PAGESIZE),--pagesize=$(MKBOOTIMG_PAGESIZE)) \
		$(MKBOOTIMG_ARGS)
	$(NOECHO)echo -n SEANDROIDENFORCE >> $@

APPSBOOTHEADER: $(OUTBOOTIMG)
endif
