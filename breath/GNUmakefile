# ============================================================================
#                      Copyright 2019-2020 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________

root := ..

#       Using vpath is a temporary solution; it doesn't work in case
#       there exist homonym files.
#
#       But, for now, we have no homonyms.
# ----------------------------------------------------------------------------
vpath %.cpp     $(root)/breath/checksum/brt         \
                $(root)/breath/conversion/brt       \
                $(root)/breath/cryptography/brt     \
                $(root)/breath/diagnostics/brt      \
                $(root)/breath/environment/brt      \
                $(root)/breath/memory/brt           \
                $(root)/breath/metric/brt           \
                $(root)/breath/path/brt             \
                $(root)/breath/process/brt          \
                $(root)/breath/random/brt           \
                $(root)/breath/stream/brt           \
                $(root)/breath/testing/brt          \
                $(root)/breath/text/brt             \
                $(root)/breath/time/brt             \
                $(root)/breath/time/private/brt     \
                $(root)/breath/uuid/brt

ifeq ($(system),windows)
    vpath %.cpp $(root)/breath/environment/windows_only/brt \
                $(root)/breath/time/windows_only/brt
endif

vpath %.asm     $(root)/breath/cpu/brt

source_files := luhn.cpp                                    \
                                                            \
                roman.cpp                                   \
                                                            \
                hashing_count.cpp                           \
                md5_hasher.cpp                              \
                sha1_hasher.cpp                             \
                sha224_hasher.cpp                           \
                sha256_hasher.cpp                           \
                sha384_hasher.cpp                           \
                sha512_hasher.cpp                           \
                                                            \
                assert.cpp                                  \
                last_api_error.cpp                          \
                                                            \
                get_all_environment_variables.cpp           \
                get_environment_variable.cpp                \
                operating_system_name.cpp                   \
                                                            \
                amount_of_physical_memory.cpp               \
                                                            \
                damerau_levenshtein_distance.cpp            \
                levenshtein_distance.cpp                    \
                                                            \
                base_file_name.cpp                          \
                directory_separators.cpp                    \
                extension.cpp                               \
                                                            \
                command_line.cpp                            \
                current_directory.cpp                       \
                exit_code.cpp                               \
                program.cpp                                 \
                program_option.cpp                          \
                set_current_directory.cpp                   \
                                                            \
                entropy_source.cpp                          \
                subrange_max.cpp                            \
                                                            \
                inserter.cpp                                \
                null_stream.cpp                             \
                                                            \
                stream_reporter.cpp                         \
                test_descriptor.cpp                         \
                test_exception.cpp                          \
                test_reporter.cpp                           \
                test_runner.cpp                             \
                                                            \
                begins_with.cpp                             \
                ends_with.cpp                               \
                printable_string.cpp                        \
                remove_from_end.cpp                         \
                replace_all.cpp                             \
                set_of_chars.cpp                            \
                split.cpp                                   \
                string_constant.cpp                         \
                tail.cpp                                    \
                to_lowercase.cpp                            \
                to_uppercase.cpp                            \
                trim.cpp                                    \
                trim_head.cpp                               \
                trim_tail.cpp                               \
                                                            \
                c_clock_policy.cpp                          \
                steady_clock_timer.cpp                      \
                time_string.cpp                             \
                thread_safe_reentrant_time_functions.cpp    \
                                                            \
                uuid.cpp

ifeq ($(system),windows)
    source_files +=                                         \
                get_os.cpp                                  \
                os_id.cpp                                   \
                windows_version_info.cpp                    \
                                                            \
                performance_counter_policy.cpp
endif


include $(root)/makefile/main.mk

asm_source_files :=

ifeq ($(architecture),x86_64)
    asm_source_files := get_cpuid_info.asm
endif


target := $(bin_dir)/$(library_name_prefix)breath$(library_name_suffix)
object_files :=                                                             \
    $(patsubst %.cpp, $(bin_dir)/%$(object_file_suffix), $(source_files))   \
    $(patsubst %.asm, $(bin_dir)/%$(object_file_suffix), $(asm_source_files))


$(target): $(object_files)
	$(build_library)

define assemble_to_object
    as --warn --fatal-warnings -o $@ $<
endef

$(bin_dir)/%$(object_file_suffix): %.asm
	$(assemble_to_object)

.PHONY: all
all: $(target)

.PHONY: clean
clean:
	rm -fr $(dependency_dir)
	rm -f $(object_files)
	rm -f $(target)

# Local Variables:
# mode: makefile
# indent-tabs-mode: nil
# End:
# vim: set ft=make et sts=4 sw=4:
