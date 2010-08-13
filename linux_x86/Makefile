# Makefile
#
# author : Junsei Takahashi
# last update 2010-08-14 02:46:02
#
root_dir := ..

# optimize level
CFLAGS  += -O0 -Wstrict-aliasing=2

CPPFLAGS+=  -D_FORTIFY_SORCE=2
# warning level
CFLAGS  += -g -ffloat-store -fstack-protector -Wall -Wextra -Wformat=2
# ak
LDLIBS += -lm

LDLIBS += libcunit.a

include $(root_dir)/common.mk

