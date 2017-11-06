/* -*- C -*-
// -------------------------------------------------------------------
// Atomic primitives
// Copyright (c) 2008  Leon Bottou. All rights reserved
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// ------------------------------------------------------------------- */

#ifndef ATOMIC_H
#define ATOMIC_H

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/* This file defines macros or functions performing
// the following atomic operations with a full memory barrier.
//
//   void* atomicExchangePointer(void* volatile *var, int val);
//   { void* tmp = *var; *var = val; return tmp; }
*/

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(ATOMIC_MACROS) && defined(_WIN64)
# define ATOMIC_MACROS "WIN64"
# include <windows.h>
# define atomicExchangePointer(var,nv) \
  (void*)(InterlockedExchangePointer((PVOID volatile*)(var),(PVOID)(nv)))
#endif

#if !defined(ATOMIC_MACROS) && defined(_WIN32)
# define ATOMIC_MACROS "WIN32"
# include <windows.h>
# define atomicExchangePointer(var,nv) \
  (void*)(InterlockedExchange((LONG volatile*)(var),(LONG)(nv)))
#endif

#if !defined(ATOMIC_MACROS) && defined(HAVE_INTEL_ATOMIC_BUILTINS)
# define ATOMIC_MACROS "INTEL"
# if defined(__i386__) || defined(__x86_64__) || defined(__amd64__)
#  define atomicExchangePointer(var,nv) \
   (__sync_lock_test_and_set((void* volatile*)(var),(void*)(nv)))
# else
  static inline void* atomicExchangePointer(void* volatile *var, void* nv) {
    void *ov; do { ov = *var;  /* overkill */
    } while (! __sync_bool_compare_and_swap(var, ov, nv));
    return ov;
  }
# endif
#endif

#if !defined(ATOMIC_MACROS) && defined(__GNUC__)
# if defined(__i386__) || defined(__amd64__) || defined(__x86_64__)
#  define ATOMIC_MACROS "GNU86"
  static inline void *atomicExchangePointer(void * volatile *var, void *nv) {
    void *ov;  __asm__ __volatile__ (
#  if defined(__x86_64__) || defined(__amd64__)
         "xchgq %0, %1"
#  else
         "xchgl %0, %1"
#  endif
         : "=r" (ov), "=m" (*var) : "0" (nv), "m" (*var));
    return ov;
  }
# endif
#endif


#ifndef ATOMIC_MACROS
  /* emulation */
  extern void* atomicExchangePointer(void* volatile *var, void* nv);
#endif


# ifdef __cplusplus
}
# endif

#endif
