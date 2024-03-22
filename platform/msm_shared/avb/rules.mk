LOCAL_DIR := $(GET_LOCAL_DIR)

GLOBAL_INCLUDES += $(LKROOT)/include $(LKROOT)/app/aboot $(LKROOT)/platform/msm_shared $(LKROOT)/platform/msm_shared/avb $(LKROOT)/platform/msm_shared/include \

CFLAGS += -DAVB_COMPILATION

OBJS += $(LOCAL_DIR)/libavb/avb_chain_partition_descriptor.o \
		$(LOCAL_DIR)/libavb/avb_crc32.o \
		$(LOCAL_DIR)/libavb/avb_crypto.o \
		$(LOCAL_DIR)/libavb/avb_descriptor.o \
		$(LOCAL_DIR)/libavb/avb_footer.o \
		$(LOCAL_DIR)/libavb/avb_hash_descriptor.o \
		$(LOCAL_DIR)/libavb/avb_hashtree_descriptor.o \
		$(LOCAL_DIR)/libavb/avb_kernel_cmdline_descriptor.o \
		$(LOCAL_DIR)/libavb/avb_property_descriptor.o \
		$(LOCAL_DIR)/libavb/avb_ops.o \
		$(LOCAL_DIR)/libavb/avb_rsa.o \
		$(LOCAL_DIR)/libavb/avb_sha256.o \
		$(LOCAL_DIR)/libavb/avb_sha512.o \
		$(LOCAL_DIR)/libavb/avb_slot_verify.o \
		$(LOCAL_DIR)/libavb/avb_sysdeps_posix.o \
		$(LOCAL_DIR)/libavb/avb_vbmeta_image.o \
		$(LOCAL_DIR)/libavb/avb_util.o \
		$(LOCAL_DIR)/libavb/avb_version.o \
		$(LOCAL_DIR)/VerifiedBoot.o \
