#==============================================================================
# Copyright 2020 Daniel Boals & Michael Boals
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
# THE SOFTWARE.
#==============================================================================


# eventually these variables should be passed in 
BUILDDIR=.
BUILDROOT=../../

ASRC=startup.s
CSRC=boot.c

include $(BUILDROOT)/MAKE/RULES.MAK

OUTPUT_FILE=

INC+='-I../include'

#------------------------------------------------------------------------------
#  default rule.  Make the bootloader.bin file
#------------------------------------------------------------------------------
bootloader.bin: boot.o startup.o bootloader.ld
	$(LD) $(LINK_FLAGS) -o $(BUILDDIR)/bootloader.elf -T $(BUILDDIR)/bootloader.ld
	$(OBJCOPY) -O binary $(BUILDDIR)/bootloader.elf $(BUILDDIR)/bootloader.bin


#------------------------------------------------------------------------------
#  clean remove all the object and binary files. 
#------------------------------------------------------------------------------
clean:
	-@rm -f $(BUILDDIR)/bootloader.bin
	-@rm -f $(BUILDDIR)/bootloader.elf
	-@rm -f $(BUILDDIR)/startup.o
	-@rm -f $(BUILDDIR)/boot.o
