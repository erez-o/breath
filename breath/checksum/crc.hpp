// ===========================================================================
//                     Copyright 2016-2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A generic CRC calculator.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_QZFmJAcA8K3GPo0Y6IjGdVIsYqLTmz3C
#define BREATH_GUARD_QZFmJAcA8K3GPo0Y6IjGdVIsYqLTmz3C

#include "breath/top_level_namespace.hpp"
#include "breath/meta/has_sign.hpp"
#include "breath/meta/width.hpp"
#include <cstdint>
#include <iosfwd>

namespace breath_ns {

//!\cond implementation
namespace crc_private {

template< typename CrcTraits >
class crc_cache ;

}
//!\endcond


//      crc
//      ===
//
//!     This template is instantiated over a traits class which provides
//!     the characterizing parameters of the CRC. To the best of my
//!     knowledge, these parameters were first identified by Ross N.
//!     Williams in his paper "A painless guide to CRC error detection
//!     algorithms", available online (a copy of the version available
//!     on <ross.net> at the time of this writing---October 7, 2020---is
//!     in the same directory of this source file).
//!

// ---------------------------------------------------------------------------
template< typename Traits >
class crc
{
public:
    //!     The same as \c Traits::value_type.
    // -----------------------------------------------------------------------
    typedef typename Traits::value_type
                        value_type ;

    //!\name Initialization
    //!\{
    //!     Initializes the CRC calculator.
    // -----------------------------------------------------------------------
    constexpr           crc() noexcept ;

    //!     Calculates the CRC of the range <tt>[first, last)</tt>.
    // -----------------------------------------------------------------------
    template< typename InputIter >
    constexpr           crc( InputIter first, InputIter last ) ;
    //!\}

    //!     Appends the values in <tt>[first, last)</tt> to the
    //!     calculation, in order.
    // -----------------------------------------------------------------------
    template< typename InputIter >
    constexpr void      accumulate( InputIter first, InputIter last ) ;

    //!\name Reading the result
    //!\{
    //!     Returns the calculated CRC. This read may occur at any time,
    //!     and doesn't disturb the running sum.
    // -----------------------------------------------------------------------
    constexpr value_type
                        value() const noexcept ;
    //!\}

private:
    //      A repetition of some of the names in Traits, to make code
    //      less verbose (inherit privately from Traits, instead?).
    // -----------------------------------------------------------------------
    static int        const width       = Traits::width       ;
    static value_type const init        = Traits::init        ;
    static bool       const reflect_in  = Traits::reflect_in  ;
    static bool       const reflect_out = Traits::reflect_out ;
    static value_type const xor_out     = Traits::xor_out     ;


    value_type          m_current ;
    static constexpr    crc_private::crc_cache< Traits >
                        s_cache{} ;

    //      A few sanity checks on the traits class. These use
    //      "Traits::" to make things clearer for the user if an assert
    //      fails.
    // -----------------------------------------------------------------------
    static_assert( ! meta::has_sign< typename Traits::value_type >::value, "") ;
    static_assert( Traits::width > 0, "" ) ;
    static_assert( Traits::width <=
                       meta::width< typename Traits::value_type >::value,
                   "value_type does not have at least width value bits") ;
    static_assert( ( Traits::poly & 1 ) != 0,
                   "the constant term of the polynomial must be 1") ;
} ;

//!     \brief Stream inserter for crc objects.
//!
//!     Outputs \c crc to the stream \c dest. The output consists of
//!     <tt>n</tt> uppercase hexadecimal digits (since CRCs are usually
//!     presented in uppercase), where <tt>n</tt> is the ceiling of the
//!     quotient between \c Traits::width and <tt>4</tt>.
// ---------------------------------------------------------------------------
template< typename Traits >
std::ostream &      operator <<( std::ostream & dest,
                                 crc< Traits > const & crc ) ;

//      crc16:
//      ======
//
//!\brief
//!     Traits for CRC-16 (also known as CRC-16/ARC).
//!
//!     \see
//!         crc
// ---------------------------------------------------------------------------
struct crc16
{
    typedef std::uint16_t   value_type ;

    static int        const width       = 16     ;
    static value_type const poly        = 0x8005 ;
    static value_type const init        = 0      ;
    static bool       const reflect_in  = true   ;
    static bool       const reflect_out = true   ;
    static value_type const xor_out     = 0      ;

    static value_type const check       = 0xBB3D ;
} ;

//      crc32:
//      ======
//
//!\brief
//!     Traits for CRC-32, as used by Ethernet, Serial ATA, PKZIP, Gzip,
//!     Bzip2, PNG.
//!
//!     \see
//!         crc
// ---------------------------------------------------------------------------
struct crc32
{
    typedef std::uint32_t   value_type ;

    static int        const width       = 32         ;
    static value_type const poly        = 0x04C11DB7 ;
    static value_type const init        = 0xFFFFFFFF ;
    static bool       const reflect_in  = true       ;
    static bool       const reflect_out = true       ;
    static value_type const xor_out     = 0xFFFFFFFF ;

    static value_type const check       = 0xCBF43926 ;
} ;

//      crc16_ibm3740:
//      ==============
//
//!\brief
//!     Traits for CRC-16/IBM-3740. This CRC is often misidentified as
//!     CRC-CCITT and is thus also known as CRC-16/CCITT-FALSE.
//!
//!     \see
//!         crc
// ---------------------------------------------------------------------------
struct crc16_ibm3740
{
    typedef std::uint16_t   value_type ;

    static int        const width       = 16     ;
    static value_type const poly        = 0x1021 ;
    static value_type const init        = 0xFFFF ;
    static bool       const reflect_in  = false  ;
    static bool       const reflect_out = false  ;
    static value_type const xor_out     = 0      ;

    static value_type const check       = 0x29B1 ;
} ;

}

#include "brt/crc.tpp"
#include "brt/crc_io.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
