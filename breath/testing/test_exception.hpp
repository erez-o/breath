// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A test exception.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_8msuVkqs5IBc3s7j1mDOtGC97uqTUGg0
#define BREATH_GUARD_8msuVkqs5IBc3s7j1mDOtGC97uqTUGg0

#include "breath/top_level_namespace.hpp"
#include <iosfwd>
#include <stdexcept>

namespace breath_ns {

class test_exception
    :   public std::logic_error
{
public:
                        test_exception( std::string const & message,
                                        char const * file_name,
                                        long line ) ;
    char const *        file_name() const noexcept ;
    long                line_number() const noexcept ;

private:
    char const *        m_file_name ;
    long                m_line ;
} ;

std::ostream &      operator <<( std::ostream &, test_exception const & ) ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
