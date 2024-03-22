# SPDX-License-Identifier: BSD-3-Clause
LOCAL_DIR := $(GET_LOCAL_DIR)

ifneq ($(CPU_BOOT_OBJ),)
MODULE_SRCS += $(LOCAL_DIR)/spin-table.c
else ifneq ($(LK2ND_SMP_OPTIONAL),)
$(warning NOTE: $(PLATFORM) not supported, disabling SMP spin table)
else
$(error $(PLATFORM) not supported)
endif
