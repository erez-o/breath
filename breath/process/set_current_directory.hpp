// ===========================================================================
//                        Copyright 2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Sets the current directory of the calling process.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_E6f26R6Om6D3dxAUPssS2yROHiV0L8sv
#define BREATH_GUARD_E6f26R6Om6D3dxAUPssS2yROHiV0L8sv

#include "breath/top_level_namespace.hpp"
#include <string>

namespace breath_ns {

//      set_current_directory():
//      ========================
//
//!     Sets the current directory of the calling process to \c dir; \c
//!     dir must be a valid directory path.
//!
//!     \throw
//!         A \c std::runtime_error (which may be a \c last_api_error)
//!         if it fails.
// ---------------------------------------------------------------------------
void                set_current_directory( std::string const & dir ) ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
