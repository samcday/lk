# SPDX-License-Identifier: BSD-3-Clause
LOCAL_DIR := $(GET_LOCAL_DIR)

MODULES += \
	lib/fdt \
	lk2nd/hw/gpio \

MODULE_SRCS += \
	$(LOCAL_DIR)/dt.c \
	$(LOCAL_DIR)/gpio_i2c.c \
