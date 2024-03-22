# SPDX-License-Identifier: BSD-3-Clause
LOCAL_DIR := $(GET_LOCAL_DIR)

MODULES += \
	   lib/bio \
	   lib/partition \

MODULE_SRCS += \
	$(LOCAL_DIR)/bdev.c \
	$(LOCAL_DIR)/util.c \
	$(LOCAL_DIR)/wrapper.c \

# Not all targets have the same mmc controller.
ifeq ($(ENABLE_SDHCI_SUPPORT),1)
MODULE_SRCS += \
	$(LOCAL_DIR)/mmc_sdhci.c
endif
