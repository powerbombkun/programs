# module.mk
#
# author : Junsei Takahashi
# last update 2010-08-17 20:51:20
#

local_lib      := libutil.a
local_src      := $(notdir $(wildcard $(subdirectory)/*.c))

$(eval $(call make-library,$(local_lib),$(local_src)))

LDLIBS += $(local_lib)
