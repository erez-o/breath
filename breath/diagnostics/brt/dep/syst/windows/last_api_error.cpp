// =========================================================================
//                       Copyright 2015 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include <Windows.h>
#include <cstddef>
#include <cstring>
#include <ostream>

namespace breath {

last_api_error::last_api_error( char const * p ) noexcept
    : m_last_error( GetLastError() )
{
    int const           max_incipit_size = 512 ;
    static_assert( max_incipit_size < (sizeof m_message / 10 ), "" ) ;

    if ( p != nullptr ) {
        std::strncpy( m_message, p, max_incipit_size ) ;
    }
    char const          sep[] = ": " ;
    std::size_t const   offset = p == nullptr
                                    ? 0
                                    : strlen( p ) + sizeof sep - 1
                                    ;
    if ( p != nullptr ) {
        std::strcpy( m_message + (offset - sizeof sep + 1), sep ) ;
    }

    DWORD const         dw = ::FormatMessageA(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        // this cast silences a -Wconversion warning under Cygwin64
        // (which typedefs DWORD to unsigned int)
        static_cast< DWORD >( m_last_error ),
        0,
        m_message + offset,
        static_cast< DWORD >( sizeof m_message - offset ),
        nullptr
        ) ;
    if ( dw == 0 ) {
        strcpy( &m_message[ offset ], "FormatMessage failed: see error code") ;
    }
    // strip trailing \r\n
    if ( dw > 2 && m_message[ offset + dw - 2 ] == '\r' &&
                   m_message[ offset + dw - 1 ] == '\n' ) {
        m_message[ offset + dw - 2 ] = '\0' ;
    }
}

last_api_error::last_api_error( last_api_error const & other ) noexcept
    :   exception( other ), m_last_error( other.m_last_error )
{
    std::strcpy( &m_message[ 0 ], &other.m_message[ 0 ] ) ;
}

last_api_error::~last_api_error() noexcept
{
}

unsigned long
last_api_error::code() const noexcept
{
    return m_last_error ;
}

char const *
last_api_error::what() const noexcept
{
    return m_message ;
}

std::ostream &
operator <<( std::ostream & dest, last_api_error const & last )
{
    return dest << last.m_message << " [code: " << last.code() << ']' ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
