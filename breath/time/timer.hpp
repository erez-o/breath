// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A policy-based timer class (class template).
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_Jr0D8xlNtWxnToeomoet20V4lz0qIYDd
#define BREATH_GUARD_Jr0D8xlNtWxnToeomoet20V4lz0qIYDd

#include "breath/top_level_namespace.hpp"

namespace breath_ns {

//      timer:
//      ======
//
//!     \copybrief timer.hpp
//!
//!     A policy-based timer which allows the user to retrieve the
//!     amount of time elapsed from its start (i.e. a "stopwatch").
//!
//!     \c Device is a policy modeling the "clock device" concept: this
//!     can be a hardware device, a network time provider, a GPS system
//!     or pretty much anything else. It must be <tt>
//!     DefaultConstructible</tt> and provide the member functions:
//!
//!      - \c %start(),
//!            which must start or restart the \c Device
//!
//!      - \c %elapsed(),
//!            which must return the amount of time elapsed from the
//!            last call to \c %start()
//!
//!      - \c %resolution(),
//!            which must return the resolution of the \c Device or an
//!            estimate of it; note that the resolution is the smallest
//!            amount of time that the \c Device can measure and
//!            doesn't, in itself, tell anything about the \e accuracy
//!
//!     and the typedef:
//!
//!      - \c duration_type,
//!            which is the return type of \c %elapsed() and
//!            \c %resolution(); it must be a \c std::chrono::duration
// ---------------------------------------------------------------------------
template< class Device >
class timer
{
public:
    //!\{
    //!     Copy members are deleted.
    //!
    //!     Specifying copy semantics for a timer is a bit difficult
    //!     and, although it can probably be done, is not worth it, as
    //!     who would copy a timer or a timer policy, anyway? (A timer
    //!     will, in practice, always be used like a Python context.)
    // -----------------------------------------------------------------------
                        timer(      timer const & ) = delete ;
    timer &             operator =( timer const & ) = delete ;
    //!\}

    typedef typename Device::duration_type
                        duration_type ;

    enum start_mode { auto_start, manual_start } ;

    //!     Initializes the underlying device by calling the default
    //!     constructor and, if (and only if) <code>mode == auto_start
    //!     </code>, calls start().
    // -----------------------------------------------------------------------
    explicit            timer( start_mode mode = auto_start ) ;

    //!     Calls \c Device::start().
    // -----------------------------------------------------------------------
    void                start() ;

    //!     \return
    //!         The result of calling %elapsed() on the underlying \c
    //!         Device.
    // -----------------------------------------------------------------------
    duration_type       elapsed() const ;

    //!     \return
    //!         The result of calling \c Device::resolution().
    // -----------------------------------------------------------------------
    duration_type       resolution() const ;

private:
    Device              m_device ;
} ;

}

#include "brt/timer.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
