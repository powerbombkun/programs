# module.mk
#
# author : Junsei Takahashi
# last update 2010-07-23 01:54:27
#

local_app      := a.out
local_src      := $(notdir $(wildcard $(subdirectory)/*.c))

$(eval $(call make-app,$(local_app),$(local_src),$(libraries)))
