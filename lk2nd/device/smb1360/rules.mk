# SPDX-License-Identifier: BSD-3-Clause
LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE_SRCS += $(LOCAL_DIR)/smb1360.c
include $(if $(BUILD_GPL), $(LOCAL_DIR)/gpl/rules.mk)
