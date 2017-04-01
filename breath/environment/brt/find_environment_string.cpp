// =========================================================================
//                    Copyright 2006-2007 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/environment/find_environment_string.hpp"
#include "breath/idiom/maybe.hpp"

#include <cstdlib>

namespace breath {

maybe< std::string >
find_environment_string( std::string const & name )
{
    typedef maybe< std::string >
                        maybe_type;

    char const * const  p( std::getenv( name.c_str() ) );

    return p == nullptr
        ? maybe_type()
        : maybe_type( std::string( p ) )
        ;
    }
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
