//  This may look like C code, but it is really -*- C++ -*-

//  ------------------------------------------------------------------
//  The Goldware Library
//  Copyright (C) 1999 Alexander S. Aganichev
//  ------------------------------------------------------------------
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Library General Public
//  License as published by the Free Software Foundation; either
//  version 2 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Library General Public License for more details.
//
//  You should have received a copy of the GNU Library General Public
//  License along with this program; if not, write to the Free
//  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston,
//  MA 02111-1307, USA
//  ------------------------------------------------------------------
//  $Id$
//  ------------------------------------------------------------------
//  Portable NLS functions for ctype.
//  ------------------------------------------------------------------

#ifndef __gctype_h
#define __gctype_h


//  ------------------------------------------------------------------

#include <gdefs.h>
#include <gutlos.h>
#ifdef __BORLANDC__
#define __USELOCALES__
#elif defined(__EMX__)
#define _CTYPE_FUN
#endif
#include <ctype.h>
#if defined(__EMX__)
#include <sys/nls.h>
#define tolower(a) _nls_tolower((unsigned char)(a))
#define toupper(a) _nls_toupper((unsigned char)(a))
#elif defined(__WIN32__)
#ifdef __cplusplus
extern "C" {
#endif
extern char tl[256], tu[256];
inline int _nls_tolower(int c) { return tl[c]; }
inline int _nls_toupper(int c) { return tu[c]; }
#ifdef __MSVCRT__
inline int _nls_isspace(int c) { return (iscntrl(c) or (c == ' ')); }
#endif
#ifdef __cplusplus
}
#define tolower(a) _nls_tolower((unsigned char)(a))
#define toupper(a) _nls_toupper((unsigned char)(a))
#ifdef __MSVCRT__
#define isspace(a) _nls_isspace((unsigned char)(a))
#endif
#endif
#endif


//  ------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif
// NLS chars detected by converting to lower or upper case and in case they don't match they treated as characters
inline int isxalnum(char c) { return isascii(c) ? isalnum(c) : (c != tolower(c)) or (c != toupper(c)); }
#ifdef __cplusplus
}
#endif


//  ------------------------------------------------------------------

#endif

//  ------------------------------------------------------------------
