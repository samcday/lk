LOCAL_DIR := $(GET_LOCAL_DIR)

GLOBAL_INCLUDES += $(LKROOT)/platform/msm_shared/include $(LKROOT)/lib/zlib_inflate

GLOBAL_DEFINES += ASSERT_ON_TAMPER=1

# TODO(MSM8916): can use miniz?
MODULES += external/lib/zlib_inflate

MODULE_SRCS += \
	$(LOCAL_DIR)/aboot.c \
	$(LOCAL_DIR)/fastboot.c \
	$(LOCAL_DIR)/recovery.c

ifeq ($(ABOOT_STANDALONE), 1)
GLOBAL_DEFINES += ABOOT_STANDALONE=1
MODULE_SRCS := $(filter-out $(LOCAL_DIR)/recovery.c, $(MODULE_SRCS))
GLOBAL_DEFINES := $(filter-out SSD_ENABLE TZ_SAVE_KERNEL_HASH TZ_TAMPER_FUSE, $(GLOBAL_DEFINES))
endif

ifeq ($(ENABLE_UNITTEST_FW), 1)
MODULE_SRCS += \
	$(LOCAL_DIR)/fastboot_test.c
	ifeq ($(ENABLE_MDTP_SUPPORT),1)
		MODULE_SRCS += \
			$(LOCAL_DIR)/mdtp_lk_ut.c
	endif
endif

ifeq ($(ENABLE_MDTP_SUPPORT),1)
MODULE_SRCS += \
	$(LOCAL_DIR)/mdtp.c \
	$(LOCAL_DIR)/mdtp_ui.c \
	$(LOCAL_DIR)/mdtp_fuse.c \
	$(LOCAL_DIR)/mdtp_defs.c \
	$(LOCAL_DIR)/mdtp_fs.c
endif
