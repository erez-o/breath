# ============================================================================
#                         Copyright 2013 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________
#
#       Breath Library - Root makefile (for GNU Make)
# ----------------------------------------------------------------------------

subdirs := breath   \
           test     \
           tool

root := .
include $(root)/makefile/main.mk

ruler := \
------------------------------------------------------------------------------

#       Common targets
# ----------------------------------------------------------------------------

##      Builds the library, runs the unit tests and builds the tools,
##      for a given architecture/system/compiler triplet. This is the
##      default target, and requires 'system' and 'compiler' to be
##      defined.
##
.PHONY: all
all: $(bin_dir)
	@$(require_triplet)
	$(info $(ruler))
	$(info Using $(compiler_display_name) $(compiler_version))
	@printf '%s\n' "Running on: ` uname -m ` "
	$(do_for_all_subdirs)

##      Deletes the build artifacts for a given triplet (see 'all').
##      Requires 'system' and 'compiler' to be defined.
##
.PHONY: clean
clean:
	@$(require_triplet)
	$(do_for_all_subdirs)

$(bin_dir):
	mkdir -p $@

.PHONY: test-run
test-run:
	@$(require_triplet)
	$(do_for_all_subdirs)

# Local Variables:
# mode: makefile
# indent-tabs-mode: nil
# End:
# vim: set ft=make et sts=4 sw=4:
