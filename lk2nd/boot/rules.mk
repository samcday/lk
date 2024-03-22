# SPDX-License-Identifier: BSD-3-Clause
LOCAL_DIR := $(GET_LOCAL_DIR)

MODULES += \
	lib/bio \
	lib/fs \
	# lk2nd/hw/bdev \
	# TODO(MSM8916):

MODULE_SRCS += \
	$(LOCAL_DIR)/boot.c \
	$(LOCAL_DIR)/extlinux.c \
	$(LOCAL_DIR)/util.c \
