# SPDX-License-Identifier: BSD-3-Clause
LOCAL_DIR := $(GET_LOCAL_DIR)
MODULES += lib/fdt

MODULE_SRCS += \
	$(LOCAL_DIR)/gpio.c \
	$(LOCAL_DIR)/tlmm.c \
	$(if $(filter dev/pmic/pm8x41, $(ALLMODULES)), $(LOCAL_DIR)/pm8x41.c) \
	$(if $(filter dev/pmic/pm8921, $(ALLMODULES)), $(LOCAL_DIR)/pm8921.c) \
