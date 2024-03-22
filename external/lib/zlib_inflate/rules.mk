LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

MODULE_SRCS += \
	$(LOCAL_DIR)/zutil.c \
	$(LOCAL_DIR)/adler32.c \
	$(LOCAL_DIR)/inftrees.c \
	$(LOCAL_DIR)/inflate.c \
	$(LOCAL_DIR)/inffast.c \
	$(LOCAL_DIR)/uncompr.c \
	$(LOCAL_DIR)/decompress.c

include make/module.mk
