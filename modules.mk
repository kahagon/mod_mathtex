mathtex.o: mathtex.c
	$(SH_COMPILE)
mod_mathtex.la: mathtex.o mod_mathtex.slo
	$(SH_LINK) mathtex.o -rpath $(libexecdir) -module -avoid-version  mod_mathtex.lo
DISTCLEAN_TARGETS = modules.mk
shared =  mod_mathtex.la