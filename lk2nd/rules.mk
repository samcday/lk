# SPDX-License-Identifier: BSD-3-Clause
LOCAL_DIR := $(GET_LOCAL_DIR)

GLOBAL_INCLUDES += $(LOCAL_DIR)/include

GPL ?= 0
GLOBAL_DEFINES += GPL=$(GPL)
ifeq ($(GPL), 1)
BUILD_GPL := 1
ifeq ($(CRYPTO_BACKEND), openssl)
$(warning WARNING: OpenSSL License is not compatible with \
	  GPL-2.0-only used for some parts of the lk2nd module. \
	  Set GPL=0 to exclude GPL-licensed code.)
endif
ifeq ($(DTBO_BACKEND), libufdt)
$(warning WARNING: Apache-2.0 license of libufdt is not compatible with \
	  GPL-2.0-only used for some parts of the lk2nd module. \
	  Set GPL=0 to exclude GPL-licensed code.)
endif
endif

$(BUILDDIR)/$(LOCAL_DIR)/%.o: CFLAGS := $(CFLAGS) -Wmissing-prototypes

MODULE_SRCS += $(LOCAL_DIR)/init.o
include $(LOCAL_DIR)/util/rules.mk
