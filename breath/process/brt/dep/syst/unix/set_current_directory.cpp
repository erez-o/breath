// =========================================================================
//                    Copyright 2015-2019 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/diagnostics/last_api_error.hpp"
#include <unistd.h>
#include <string>

namespace breath {

void
set_current_directory( std::string const & dir )
{
    int const           r = chdir( dir.c_str() ) ;
    if ( r == -1 ) {
        throw last_api_error( "chdir() failed" ) ;
    }
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4: