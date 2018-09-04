# =========================================================================
#                    Copyright 2007-2018 Gennaro Prota
#
#                 Licensed under the 3-Clause BSD License.
#            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#             <https://opensource.org/licenses/BSD-3-Clause>.)
# _________________________________________________________________________

#       As usual, the options are listed in two groups. The group
#       listed first relates mainly to standards conformance. The other
#       group contains other options in alphabetical order.
#
#       Special notes for some of the options:
#       ======================================
#
#       -ansi:
#
#           this one seemed to be the only way, with both gcc 4.7.3
#           under Cygwin and gcc 4.7.1 under Slackware 14.0 x86_64, to
#           prevent the compiler from pre-defining macros with names
#           that are in the user's name space;
#
#           particularly, the name "unix", which would bite us
#           immediately because it may appear when expanding our
#           BREATH_DEPENDENT_CODE_* macros.
#
#           TODO: add something like `g++ -E -dM - < /dev/null | grep...'
#           to the makefiles, as a form of pre-check?   --gps
#
#           If it wasn't for this reason I wouldn't use the option at
#           all (even if this was C++98), because I don't like using
#           the name "ansi" when in fact the standard is from ISO. (I
#           could have attempted to use it on affected systems only,
#           but it doesn't do any harm for the others (it seems), so
#           why adding further complexity...)
#
#           Note that it must appear *before* -std=..., or it will
#           revert things to an earlier standard (C++03 or C++98, I
#           haven't verified).
#
#       -D_GLIBCXX_USE_CXX11_ABI:
#
#           enables the new implementations of std::string and
#           std::list, which conform to C++11; for more details see:
#
#             <https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_dual_abi.html>
#
#       -pipe:
#
#           just an optimization, "but it can also allow compilations to
#           succeed even when the space on /tmp is tight.  (It's a very
#           important optimization on Unix systems, because it reduces
#           pressure on the disk cache.)
#
#           On a multi-core machine, -pipe also runs a lot faster, since
#           it allows the back end to generate code for one function
#           while the front end is parsing the next" (insights provided
#           by James Kanze).
#
#       Options to be added in the future:
#       ==================================
#
#       These options will be added when the minimum required gcc
#       version will support them:
#
#           -Waligned-new=all
#           -Wcast-align=strict
#           -Wduplicated-branches
# ----------------------------------------------------------------------------
cpp_basic_options =  -ansi                      \
                     -std=c++14                 \
                     -Wall                      \
                     -Wextra                    \
                     -pedantic                  \
                     -Werror                    \
                     -D_POSIX_C_SOURCE=200112L  \
                     -U_GNU_SOURCE              \
                     -D_GLIBCXX_USE_CXX11_ABI

cpp_basic_options += -pipe                      \
                     -Wabi                      \
                     -Wconversion               \
                     -Wdouble-promotion         \
                     -Wduplicated-cond          \
                     -Wfloat-equal              \
                     -Wformat=2                 \
                     -Winvalid-pch              \
                     -Wlogical-op               \
                     -Wnoexcept                 \
                     -Wnon-virtual-dtor         \
                     -Wold-style-cast           \
                     -Woverloaded-virtual       \
                     -Wplacement-new=2          \
                     -Wredundant-decls          \
                     -Wshadow                   \
                     -Wstrict-null-sentinel     \
                     -Wsuggest-override         \
                     -Wsync-nand                \
                     -Wundef                    \
                     -Wunused-macros

include_switch = -I
object_file_suffix = .o

# Note that this differs from the compiler name, which is in $(compiler)
#
compiler_command = g++


# gps mostly by James!
define compile_to_object
# gps controlla la riga seguente!!!
$(compiler_command) $(cpp_options) -c -o $@ $<
endef

# gps mostly by James!
#
define link_to_exec
$(compiler_command) $(cpp_options) -o $@ $+
endef

# Local Variables:
# mode: makefile
# indent-tabs-mode: t
# tab-width: 8
# End:
# vim: set ft=make noet ts=8 sts=0 sw=8:
