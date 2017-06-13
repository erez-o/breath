// =========================================================================
//                       Copyright 2017 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/preprocessing/stringize_delayed.hpp"
#include "breath/testing/testing.hpp"
#include <cstring>
#include <iostream>
#include <ostream>

#define FOO 1
#define FOO2 FOO

#define BAR "a"
#define BAR2 BAR

namespace {

void
do_tests()
{
    BREATH_CHECK( std::strcmp( BREATH_STRINGIZE_DELAYED( FOO2 ), "1" )  == 0 ) ;
    BREATH_CHECK( std::strcmp( BREATH_STRINGIZE_DELAYED( BAR2 ), "\"a\"" )  == 0 ) ;
}

}

int
main()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( { do_tests } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4: