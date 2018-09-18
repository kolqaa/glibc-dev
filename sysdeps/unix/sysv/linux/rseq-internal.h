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

#include <stdint.h>
#include <linux/rseq.h>

#define RSEQ_SIG 0x53053053

extern __thread volatile struct rseq __rseq_abi
__attribute__ ((tls_model ("initial-exec")));

extern __thread volatile uint32_t __rseq_refcount
__attribute__ ((tls_model ("initial-exec")));

static inline int
sysdep_rseq_register_current_thread (void)
{
  int rc, ret = 0;
  INTERNAL_SYSCALL_DECL (err);

  if (__rseq_abi.cpu_id == RSEQ_CPU_ID_REGISTRATION_FAILED)
    return -1;
  rc = INTERNAL_SYSCALL_CALL (rseq, err, &__rseq_abi, sizeof (struct rseq),
                              0, RSEQ_SIG);
  if (!rc)
    {
      __rseq_refcount = 1;
      goto end;
    }
  if (INTERNAL_SYSCALL_ERRNO (rc, err) != EBUSY)
    __rseq_abi.cpu_id = RSEQ_CPU_ID_REGISTRATION_FAILED;
  ret = -1;
end:
  return ret;
}

static inline int
sysdep_rseq_unregister_current_thread (void)
{
  int rc, ret = 0;
  INTERNAL_SYSCALL_DECL (err);

  __rseq_refcount = 0;
  rc = INTERNAL_SYSCALL_CALL (rseq, err, &__rseq_abi, sizeof (struct rseq),
                              RSEQ_FLAG_UNREGISTER, RSEQ_SIG);
  if (!rc)
    goto end;
  ret = -1;
end:
  return ret;
}

#endif	/* rseq-internal.h */
