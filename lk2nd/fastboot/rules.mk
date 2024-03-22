# SPDX-License-Identifier: BSD-3-Clause
LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE_SRCS += \
	$(LOCAL_DIR)/fetch.c \
	$(LOCAL_DIR)/hash.c \
	$(LOCAL_DIR)/misc.c \

ifneq ($(filter DISPLAY_SPLASH_SCREEN=1,$(GLOBAL_DEFINES)),)
MODULE_SRCS += \
	$(LOCAL_DIR)/screenshot.c \
	$(LOCAL_DIR)/screenshot-neon.c
endif