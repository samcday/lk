OPENSSL_PATH := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

MODULES += \
	external/lib/openssl/crypto

include make/module.mk
