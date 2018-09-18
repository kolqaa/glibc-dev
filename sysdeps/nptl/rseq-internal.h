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

#ifndef RSEQ_INTERNAL_H
#define RSEQ_INTERNAL_H

static inline int
sysdep_rseq_register_current_thread (void)
{
  return -1;
}

static inline int
sysdep_rseq_unregister_current_thread (void)
{
  return -1;
}

#endif	/* rseq-internal.h */
