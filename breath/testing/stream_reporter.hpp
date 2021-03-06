// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A test_reporter to report unit test errors to a \c
//!            std::ostream.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_XgKxFi9sRq7YDgySOH2206PWX2ZxQrtB
#define BREATH_GUARD_XgKxFi9sRq7YDgySOH2206PWX2ZxQrtB

#include "breath/top_level_namespace.hpp"
#include "breath/testing/test_reporter.hpp"
#include <iosfwd>

namespace breath_ns {

//      stream_reporter:
//      ================
//
//!     \copybrief stream_reporter.hpp
//!
//!     \par Naming rationale
//!
//!     Not named \c output_stream_reporter because that made difficult
//!     to use our declaration style: with that name, declaring an
//!     object of type output_stream_reporter required to but the type
//!     name on one line and the variable name on the next line, which
//!     is ugly. Example:
//!
//!     <code>
//!                  1         2
//!         1234567890123456789012345
//!         {
//!             output_stream_reporter
//!                                 r ;
//!             ...
//!         }
//!     </code>
//!
//!     An alternative would have been \c ostream_reporter, but that's
//!     inconsistent with the rest of the library.
// ---------------------------------------------------------------------------
class stream_reporter
    :   public test_reporter
{
public:
    //      Declare this explicitly to avoid Visual C++ C4625.
    // -----------------------------------------------------------------------
                        stream_reporter( stream_reporter const & ) = delete ;

    //      Declare this explicitly to avoid Visual C++ C4626 (and
    //      C5027).
    // -----------------------------------------------------------------------
    stream_reporter &   operator =( stream_reporter const & ) = delete ;

    explicit            stream_reporter( std::ostream & os ) ;

private:
    virtual void        do_on_all_tests_begin( char const * group_description ) override ;
    virtual void        do_on_all_tests_end() override ;
    virtual void        do_on_test_begin( int test_number,
                                           char const * name ) override ;
    virtual void        do_on_test_passed( int test_number ) override ;
    virtual void        do_on_test_failed( int test_number,
                                           test_exception const & ) override ;
    virtual void        do_on_unexpected_exception( int test_number ) override ;
    virtual void        do_on_unexpected_exception( int test_number,
                                                     std::exception const & )
                                                                      override ;

    std::ostream &      m_stream ;
    int                 m_passed ;
    int                 m_failed ;
    int                 m_unexpected_exceptions ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
