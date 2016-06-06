// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________

#include "private/check_common_gcd_lcm_preconditions.hpp"
#include <cmath>

namespace breath {

template< typename M, typename N >
constexpr std::common_type_t< M, N >
gcd( M a, N b ) noexcept
{
    gcd_lcm_private::check_common_gcd_lcm_preconditions( a, b ) ;

    a = std::abs( a ) ;
    b = std::abs( b ) ;
    while ( true ) {

        if ( a == 0 ) {
            return b ;
        }
        b %= a ;

        if ( b == 0 ) {
            return a ;
        }
        a %= b ;
    }
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
