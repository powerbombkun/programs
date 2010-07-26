# common.mk
#
# author : Junsei Takahashi
# last update 2010-07-27 01:44:49
#

#
# macro
#
# $(call source-to-object, souce-file-list)
source-to-object = $(subst .c,.o,$(filter %.c,$1))

# $(subdirectory)
subdirectory = $(dir $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST)))


# $(call make-library, library-name, source-file-list)
define make-library
 libraries += $1
 sources   += $2

 $1 : $(call source-to-object,$2)
	$(AR) $(ARFLAGS) $$@ $$^
	$(RANLIB) $$@
endef

# $(call make-app, app-name, source-file-list, library-list)
define make-app
 programs += $1
 sources  += $2

 $1 : $(call source-to-object,$2) $3
	$(LINK.o) $$^ $(LOADLIBES) $(LDLIBS) -o $$@
endef

# $(call make-test, test-name, source-file-list, library-list)
define make-test
 tests   += $1
 sources += $2
 $1 : $(call source-to-object,$2) $3
	$(LINK.o) $$^ $(LOADLIBES) $(LDLIBS) -o $$@
endef

# $(call make-depend,source-file,object-file,depend-file)
define make-depend
  $(CC)     -MM                 \
            -MF $3              \
            -MP                 \
            -MT $2              \
            $(CFLAGS)           \
            $(CPPFLAGS)         \
            $(TARGET_ARCH)      \
            $1
endef

CD        := cd
MV        := mv -f
RM        := rm -f
SED       := sed
TEE       := tee
AR        := ar
RANLIB    := ranlib
CC        := gcc

root_dir  ?= .

prgrams   :=
# library module
modules   := $(shell find $(root_dir) -name module.mk)
# app module
modules   += $(shell find $(root_dir) -name app.mk)
module_dirs   := $(dir $(modules))
libraries :=
sources   :=
tests     :=
doxyfile  := Doxyfile

objects      = $(call source-to-object,$(sources))
dependencies = $(subst .o,.d,$(objects))

include_dirs := . $(root_dir)/include $(module_dirs)
extra_clean ?=

all :

include $(modules)

CPPFLAGS += -DROOT_DIR="\"$(root_dir)\"" $(addprefix -I,$(include_dirs))

vpath %.c $(module_dirs)
vpath %.h $(include_dirs)

.PHONY : all run clean

all : $(programs)

run : $(programs)
	$(foreach p,$(programs),$(PWD)/$p;)

clean :
	$(RM) $(objects) $(tests) $(libraries) $(dependencies) $(programs) $(extra_clean)

ifneq "$(MAKECMDGOALS)" "clean"
  -include $(dependencies)
endif

%.o : %.c
	$(if $(findstring gcc,$(CC)), \
		$(call make-depend,$<,$@,$(subst .o,.d,$@)))
	$(COMPILE.c) $(OUTPUT_OPTION) $<

