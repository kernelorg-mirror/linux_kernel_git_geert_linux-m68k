# SPDX-License-Identifier: GPL-2.0
#
# Makefile for the Zorro bus specific drivers.
#

obj-$(CONFIG_ZORRO)	+= zorro.o zorro-driver.o zorro-sysfs.o
obj-$(CONFIG_PROC_FS)	+= proc.o
obj-$(CONFIG_ZORRO_NAMES) +=  names.o

obj-$(CONFIG_ARIADNE_MFD) += ariadne-mfd.o
obj-$(CONFIG_ARIADNE2_MFD) += ariadne2-mfd.o
obj-$(CONFIG_BUDDHA_MFD) += buddha-mfd.o
obj-$(CONFIG_CATWEASEL_MFD) += catweasel-mfd.o
obj-$(CONFIG_XSURF_MFD) += xsurf-mfd.o

obj-$(CONFIG_ARIADNE_NET) += ariadne-net.o
obj-$(CONFIG_ARIADNE_PAR) += ariadne-par.o
obj-$(CONFIG_BUDDHA_IDE) += buddha-ide.o
obj-$(CONFIG_CATWEASEL_FLOPPY) += catweasel-floppy.o
obj-$(CONFIG_8390_CELL) += 8390-cell.o

hostprogs		:= gen-devlist

# Files generated that shall be removed upon make clean
clean-files := devlist.h

# Dependencies on generated files need to be listed explicitly
$(obj)/names.o: $(obj)/devlist.h

# And that's how to generate them
quiet_cmd_devlist = DEVLIST $@
      cmd_devlist = ( cd $(obj); ./gen-devlist ) < $<
$(obj)/devlist.h: $(src)/zorro.ids $(obj)/gen-devlist
	$(call cmd,devlist)

