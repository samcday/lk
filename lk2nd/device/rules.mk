# SPDX-License-Identifier: BSD-3-Clause
LOCAL_DIR := $(GET_LOCAL_DIR)

MODULES += \
	   lib/fdt \
	   lk2nd/hw/gpio \

LK2ND_DEVICE_SRCS := $(LOCAL_DIR)/device.c

# NOTE: The init functions are performed in the order of linking
# thus the order might be important here. Notably:
#
# - keys.o must be after device.o as device.o will (if needed) probe
#   the keys driver and the keys.o will then rely on the created data
#   to report the keys.

MODULE_SRCS += \
	$(LK2ND_DEVICE_SRCS) \
	$(LOCAL_DIR)/panel.c \
	$(LOCAL_DIR)/keys.c \

ifneq ($(LK2ND_COMPATIBLE),)
GLOBAL_DEFINES += LK2ND_COMPATIBLE="$(LK2ND_COMPATIBLE)"
endif

# TODO(MSM8916):
# include \
# 	$(if $(filter msm8916, $(TARGET)), $(LOCAL_DIR)/smb1360/rules.mk) \
# 	$(LOCAL_DIR)/dts/rules.mk \
