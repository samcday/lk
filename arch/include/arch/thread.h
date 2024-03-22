/*
 * Copyright (c) 2008 Travis Geiselbrecht
 *
 * Use of this source code is governed by a MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT
 */
#pragma once

// give the arch code a chance to declare the arch_thread struct
#include <arch/arch_thread.h>
#include <lk/compiler.h>

__BEGIN_CDECLS

struct thread;

void arch_thread_initialize(struct thread *);
void arch_context_switch(struct thread *oldthread, struct thread *newthread);

__END_CDECLS

// +MSM8916 HACK+
/* critical sections */
extern int critical_section_count;

static inline __ALWAYS_INLINE void enter_critical_section(void)
{
	critical_section_count++;
	if (critical_section_count == 1)
		arch_disable_ints();
}

static inline __ALWAYS_INLINE void exit_critical_section(void)
{
	critical_section_count--;
	if (critical_section_count == 0)
		arch_enable_ints();
}

static inline __ALWAYS_INLINE bool in_critical_section(void)
{
	return critical_section_count > 0;
}
// -MSM8916 HACK-
