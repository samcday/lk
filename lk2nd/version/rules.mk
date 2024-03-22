# SPDX-License-Identifier: BSD-3-Clause
LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE_SRCS += \
	$(LOCAL_DIR)/version.c \

# Generate the version tag from VCS
LK2ND_VERSION := $(shell lk2nd/scripts/describe-version.sh)
VERSION_FILE := $(BUILDDIR)/$(LOCAL_DIR)/tag.c

.FORCE:

$(VERSION_FILE): .FORCE
	@$(MKDIR)
	@echo "const char* LK2ND_VERSION = \"$(LK2ND_VERSION)\";" > $@.tmp
	@if ! cmp -s $@.tmp $@; then				\
		echo generating $@ for lk2nd $(LK2ND_VERSION);	\
		mv $@.tmp $@;					\
	fi

MODULE_SRCS += \
	$(BUILDDIR)/$(LOCAL_DIR)/tag.c \
