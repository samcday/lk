# SPDX-License-Identifier: BSD-3-Clause
LOCAL_DIR := $(GET_LOCAL_DIR)

# Filter out original display implementation
MODULE_SRCS := $(filter-out target/$(TARGET)/target_display.c, $(MODULE_SRCS))

GLOBAL_DEFINES += \
	$(if $(filter %/mdp3.c, $(MODULE_SRCS)), MDP3=1) \
	$(if $(filter %/mdp4.c, $(MODULE_SRCS)), MDP4=1) \
	$(if $(filter %/mdp5.c, $(MODULE_SRCS)), MDP5=1) \

MODULE_SRCS += \
	$(if $(filter MDP3=1 MDP4=1, $(GLOBAL_DEFINES)), $(LOCAL_DIR)/dma.c) \
	$(if $(filter MDP4=1 MDP5=1, $(GLOBAL_DEFINES)), $(LOCAL_DIR)/pipe.c) \
	$(LOCAL_DIR)/refresh.c \
	$(LOCAL_DIR)/target_display.c \
