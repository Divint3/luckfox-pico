ifeq ($(SYSDRV_PARAM), )
	SYSDRV_PARAM:=../../Makefile.param
	include $(SYSDRV_PARAM)
endif

HELLO_CURRENT_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
ifeq ($(RK_PROJECT_OUTPUT),)
-include $(HELLO_CURRENT_DIR)/../../../.BoardConfig.mk
endif

M_OUT_DIR ?= $(HELLO_CURRENT_DIR)/../out
MODULE_NAME := hello

# 内核以 O=objs_kernel 方式构建时，外部模块构建也必须带 O=,
# 否则会命中未配置的内核源码树导致报错
ifneq ($(SYSDRV_KERNEL_OBJS_OUTPUT_DIR),)
__HELLO_KERNEL_O__ := O=$(SYSDRV_KERNEL_OBJS_OUTPUT_DIR)
endif

obj-m := $(MODULE_NAME).o

all: modules
	@echo "build $(MODULE_NAME) done"

.PHONY: modules clean

modules:
	$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) $(__HELLO_KERNEL_O__) \
		-C $(KERNEL_DIR) M=$(HELLO_CURRENT_DIR) modules -j$(SYSDRV_JOBS)
	cp -v $(HELLO_CURRENT_DIR)/$(MODULE_NAME).ko $(M_OUT_DIR)
	@rm -rf *.o *~ .depend .*.cmd .tmp_versions *.symvers modules.order *.mod

clean:
	@rm -rf *.o *~ .depend .*.cmd .tmp_versions *.ko *.symvers modules.order *.mod
