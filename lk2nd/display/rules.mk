# SPDX-License-Identifier: BSD-3-Clause
LOCAL_DIR := $(GET_LOCAL_DIR)

# Filter out original panel implementation
MODULE_SRCS := $(filter-out target/$(TARGET)/oem_panel.c, $(MODULE_SRCS))

MODULE_SRCS += \
	$(LOCAL_DIR)/simplefb.c

ifeq ($(LK2ND_DISPLAY), cont-splash)
include $(LOCAL_DIR)/cont-splash/rules.mk
else
$(error Display '$(LK2ND_DISPLAY)' is not supported yet)
endif
