#==============================================================================
# Copyright 2020 Daniel Boals & Michael Boals
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
# THE SOFTWARE.
#==============================================================================

.PHONY: all boot init clean boot_clean

SUBDIRS := init

include ../MAKE/RULES.MAK

all: boot $(SUBDIRS)

include ../MAKE/TARGETS.MAK


boot:
	mkdir -p $(BUILDDIR)/$@
	$(MAKE) SRCDIR=$(SRCDIR)/boot BUILDROOT=$(BUILDDIR)/boot BUILDDIR=$(BUILDDIR)/boot -C $@ -f Makefile

boot_clean:
	$(MAKE) SRCDIR=$(SRCDIR)/boot BUILDROOT=$(BUILDDIR)/boot BUILDDIR=$(BUILDDIR)/boot -C boot -f Makefile clean

$(SUBDIRS):
	mkdir -p $(BUILDDIR)/$@
	$(MAKE) SRCDIR=$(SRCDIR)/$@ BUILDROOT=$(BUILDROOT) BUILDDIR=$(BUILDDIR)/$@ -C $@ -f Makefile

#------------------------------------------------------------------------------
#  clean remove all the object and binary files. 
#------------------------------------------------------------------------------
clean:  boot_clean subdir_clean

