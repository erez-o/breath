// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A smart pointer to an array object.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_FvaoTt7c3pTltKsed1Av5CAvE3SvnVIn
#define BREATH_GUARD_FvaoTt7c3pTltKsed1Av5CAvE3SvnVIn

#include "breath/top_level_namespace.hpp"

namespace breath_ns {

//      auto_array:
//      ===========
//
//!     \copybrief auto_array.hpp
//!
//!     A smart pointer that retains sole ownership of an array through
//!     a pointer. An <code>auto_array< T ></code> is similar to a
//!     <code>unique_ptr< T[], std::default_delete< T[] > ></code> but
//!     this template was written way before C++11.
//!
//!     Like for \c unique_ptr, instances of this template satisfy the
//!     requirements of <tt>MoveConstructible</tt> and <tt>
//!     MoveAssignable</tt>, but not the requirements of either <tt>
//!     CopyConstructible</tt> or <tt>CopyAssignable</tt>.
// ---------------------------------------------------------------------------
template< typename T >
class auto_array
{
public:
    //!\{
    //!     Copy members are deleted.
    // -----------------------------------------------------------------------
                        auto_array( auto_array const & ) = delete ;
    auto_array &        operator =( auto_array const & ) = delete ;
    //!\}

                        auto_array() noexcept ;
    explicit            auto_array( T * ) noexcept ;
                        auto_array( auto_array && ) noexcept ;
                        ~auto_array() noexcept ;

    auto_array &        operator =( auto_array && ) noexcept ;
    T *                 get() const noexcept ;
    void                reset( T * ) noexcept ;

private:
    T *                 m_ptr ;
    void                do_delete() noexcept ;
} ;

}

#include "brt/auto_array.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
