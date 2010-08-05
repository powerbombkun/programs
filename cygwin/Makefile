# Makefile
#
# author : Junsei Takahashi
# last update 2010-07-30 21:01:04
#
root_dir := ..

# optimize level
CFLAGS  += -O0 -Wstrict-aliasing=2

CPPFLAGS+=  -D_FORTIFY_SORCE=2
# warning level
CFLAGS  += -g -ffloat-store -Wall -Wextra -Wformat=2
# ak
LDLIBS += -lm

LDLIBS += libcunit.a

include $(root_dir)/common.mk

