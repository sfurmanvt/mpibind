
#######################################################
# slurm plugin
#######################################################

# TODO guard with if have slurm
mpibindmod_LTLIBRARIES  = mpibind_slurm.la

mpibind_slurm_la_SOURCES = plugin.c
mpibind_slurm_la_CFLAGS  = -Wall -Werror -I$(top_srcdir)/src $(HWLOC_CFLAGS)
mpibind_slurm_la_LIBADD  = $(top_builddir)/src/libmpibind.la
mpibind_slurm_la_LDFLAGS = -module

# TODO How should install be handled if we dont have root privileges
# Install mpibind_flux.so into the flux shell
# plugin path so it is loaded by default with
# 'plugin.load("*.so")'. 
# plugin_name = ${mpibindmod_LTLIBRARIES:la=so}
# install-exec-hook: 
#	$(AM_V_at)echo Installing the mpibind flux plugin...
#	$(MKDIR_P) $(FLUX_SHELL_PLUGIN_DIR) && \
#	$(INSTALL) $(builddir)/.libs/$(plugin_name) $(FLUX_SHELL_PLUGIN_DIR)/

