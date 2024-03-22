# SPDX-License-Identifier: BSD-3-Clause
LOCAL_DIR := $(GET_LOCAL_DIR)
MODULES += lib/fdt

MODULE_SRCS += \
	$(LOCAL_DIR)/mac.c \
	$(LOCAL_DIR)/serialno.c \
