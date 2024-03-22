LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

GLOBAL_INCLUDES += $(LOCAL_DIR)/include

MODULE_SRCS += \
	$(LOCAL_DIR)/pm8x41.c \
	$(LOCAL_DIR)/pm8x41_adc.c \
	$(LOCAL_DIR)/pm8x41_wled.c

ifeq ($(ENABLE_WEAK_BATT_CHRG_SUPPORT),1)
MODULE_SRCS += \
	$(LOCAL_DIR)/qpnp-smb2.c \
	$(LOCAL_DIR)/qpnp-fg-gen3.c
endif

ifeq ($(ENABLE_PON_VIB_SUPPORT),true)
MODULE_SRCS += \
	$(LOCAL_DIR)/pm8x41_vib.c
endif

ifeq ($(ENABLE_PWM_SUPPORT),true)
MODULE_SRCS += \
	$(LOCAL_DIR)/pm_pwm.c
endif

ifeq ($(ENABLE_VADC_HC_SUPPORT),true)
MODULE_SRCS += \
	$(LOCAL_DIR)/pm_vadc_hc.c
endif

include make/module.mk
