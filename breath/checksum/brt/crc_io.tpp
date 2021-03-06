// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//                         Copyright 2004 James Kanze
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/iteration/begin_end.hpp"
#include "breath/mathematics/rounded_up_quotient.hpp"
#include "breath/stream/inserter.hpp"
#include <ostream>

namespace breath_ns {

template< typename Traits >
std::ostream &
operator <<( std::ostream & dest, crc< Traits > const & crc )
{
    inserter            ins( dest ) ;
    try {
        if ( ins.sentry_is_ok() ) {
            int const       digit_count =
                rounded_up_quotient( Traits::width, 4 ) ;
            auto            pad = dest.width() - digit_count ;

            if ( ( dest.flags() & std::ios::adjustfield ) != std::ios::left ) {
                ins.pad( pad ) ;
                pad = 0 ;
            }
            char            buffer[ digit_count ] ;
            auto const      start = breath::begin( buffer ) ;
            auto            iter  = breath::end( buffer ) ;
            typename Traits::value_type
                            value = crc.value() ;
            while ( iter != start ) {
                -- iter ;
                *iter = "0123456789ABCDEF"[ value & 0x0f ] ;
                value >>= 4 ;
            }

            ins.put( buffer, digit_count ) ;
            ins.pad( pad ) ;
        }
    } catch ( ... ) {
        bool                rethrow = false ;
        try { dest.setstate( std::ios::badbit ) ; }
        catch ( ... ) { rethrow = true ; }
        if ( rethrow ) {
            throw ;
        }
    }

    return dest ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
