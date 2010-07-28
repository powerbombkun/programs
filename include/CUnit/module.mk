# module.mk
#
# author : Junsei Takahashi
# last update 2010-07-28 23:27:27
#

local_lib      := libcunit.a
local_src      := $(notdir $(wildcard $(subdirectory)/*.c))

$(eval $(call make-library,$(local_lib),$(local_src)))

LDLIBS += $(local_lib)
