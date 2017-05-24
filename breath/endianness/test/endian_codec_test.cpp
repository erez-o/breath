// =========================================================================
//                       Copyright 2017 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/endianness/endian_codec.hpp"
#include "breath/testing/testing.hpp"

#include <cstdint>
#include <iostream>
#include <ostream>

namespace {

void check()
{
    using               breath::big_endian_policy ;
    using               breath::little_endian_policy ;

    std::uint32_t const value = 0x01020304;
    std::uint8_t        array[ 4 ] ;
    breath::endian_store< little_endian_policy >( value, &array[ 0 ] ) ;
    BREATH_CHECK( array[ 0 ] == 4 ) ;
    BREATH_CHECK( array[ 1 ] == 3 ) ;
    BREATH_CHECK( array[ 2 ] == 2 ) ;
    BREATH_CHECK( array[ 3 ] == 1 ) ;
    std::uint32_t const u = breath::endian_load< little_endian_policy,
                                                 std::uint32_t >(
                                                            &array[ 0 ]
                                                            ) ;
    BREATH_CHECK( u == 0x01020304 ) ;

    breath::endian_store< big_endian_policy >( value, &array[ 0 ] ) ;
    BREATH_CHECK( array[ 0 ] == 1 ) ;
    BREATH_CHECK( array[ 1 ] == 2 ) ;
    BREATH_CHECK( array[ 2 ] == 3 ) ;
    BREATH_CHECK( array[ 3 ] == 4 ) ;

    std::uint32_t const u2 = breath::endian_load< big_endian_policy,
                                                  std::uint32_t >(
                                                        &array[ 0 ]
                                                        ) ;
    BREATH_CHECK( u2 == 0x01020304 ) ;

}

}

int
main()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( { check } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4: