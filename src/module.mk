# module.mk
#
# author : Junsei Takahashi
# last update 2010-07-23 01:48:33
#

local_lib      := libutil.a
local_src      := $(notdir $(wildcard $(subdirectory)/*.c))

$(eval $(call make-library,$(local_lib),$(local_src)))

LDLIBS += $(local_lib)
