/* Copyright (C) 2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Mathieu Desnoyers <mathieu.desnoyers@efficios.com>, 2018.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include "pthreadP.h"

__attribute__((weak))
__thread volatile uint32_t __rseq_refcount;

#ifdef __NR_rseq
#include <sysdeps/unix/sysv/linux/rseq-internal.h>
#else
#include <sysdeps/nptl/rseq-internal.h>
#endif  /* __NR_rseq.  */

int
attribute_hidden
__rseq_register_current_thread (void)
{
  return sysdep_rseq_register_current_thread ();
}

int
attribute_hidden
__rseq_unregister_current_thread (void)
{
  return sysdep_rseq_register_current_thread ();
}
