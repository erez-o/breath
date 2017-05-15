// =========================================================================
//                       Copyright 2017 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief A simple bit counter.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_D5dKoDqQ2v7QNXhW1F8zF0ZKijovEPgp
#define BREATH_GUARD_D5dKoDqQ2v7QNXhW1F8zF0ZKijovEPgp

#include <cstddef>

namespace breath {

//!     \return The number of on bits in the value \c t. \p T must be
//!     an unsigned built-in type.
// -------------------------------------------------------------------------
template< typename T >
constexpr std::size_t
                    count_bits( T t ) noexcept ;

}

#include "brt/count_bits.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4: