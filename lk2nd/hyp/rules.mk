# SPDX-License-Identifier: BSD-3-Clause
LOCAL_DIR := $(GET_LOCAL_DIR)

ifneq ($(filter msm8916 msm8952, $(PLATFORM)),)
	MODULE_SRCS += \
		$(LOCAL_DIR)/takeover.c \
		$(LOCAL_DIR)/remapper.c
endif
