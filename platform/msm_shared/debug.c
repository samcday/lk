/*
 * Copyright (c) 2009, Google Inc.
 * All rights reserved.
 * Copyright (c) 2009-2016, 2018-2019, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  * Neither the name of Google, Inc. nor the names of its contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <stdlib.h>
#include <lk/debug.h>
#include <printf.h>
#include <string.h>
#include <arch/arm/dcc.h>
#include <dev/fbcon.h>
#include <dev/uart.h>
#include <platform/timer.h>
#include <platform.h>
#include <arch/ops.h>

#if PON_VIB_SUPPORT
#include <vibrator.h>
#endif


static void write_dcc(char c)
{
	uint32_t timeout = 10;

	/* Note: Smallest sampling rate for DCC is 50us.
	 * This can be changed by SNOOPer.Rate on T32 window.
	 */
	while (timeout)
	{
		if (dcc_putc(c) == 0)
			break;
		udelay(50);
		timeout--;
	}
}

#if WITH_DEBUG_LOG_BUF

#ifndef LK_LOG_BUF_SIZE
#define LK_LOG_BUF_SIZE    (4096) /* align on 4k */
#endif

#define LK_LOG_COOKIE    0x474f4c52 /* "RLOG" in ASCII */

struct lk_log {
	struct lk_log_header {
		unsigned cookie;
		unsigned max_size;
		unsigned size_written;
		unsigned idx;
	} header;
	char data[LK_LOG_BUF_SIZE];
};

static struct lk_log log;

static void log_init(void)
{
	log.header.cookie = LK_LOG_COOKIE;
	log.header.max_size = sizeof(log.data);
}

static void log_putc(char c)
{
	log.data[log.header.idx++] = c;
	log.header.size_written++;
	if (unlikely(log.header.idx >= log.header.max_size))
		log.header.idx = 0;
}

unsigned log_copy(void *dst)
{
	if (log.header.size_written >= log.header.max_size) {
		unsigned tail = log.header.max_size - log.header.idx;

		memcpy(dst, &log.data[log.header.idx], tail);
		memcpy(dst + tail, log.data, log.header.idx);
		return log.header.max_size;
	} else {
		memcpy(dst, log.data, log.header.idx);
		return log.header.idx;
	}
}
#endif /* WITH_DEBUG_LOG_BUF */

void display_fbcon_message(char *str)
{
#if ENABLE_FBCON_LOGGING
	while(*str != 0) {
		fbcon_putc(*str++);
	}
#endif
}

void debug_init(void)
{
#if WITH_DEBUG_LOG_BUF
	log_init();
#endif
}

void platform_dputc(char c)
{
#if WITH_DEBUG_LOG_BUF
	log_putc(c);
#endif
#if WITH_DEBUG_DCC
	if (c == '\n') {
		write_dcc('\r');
	}
	write_dcc(c) ;
#endif
#if WITH_DEBUG_UART
	uart_putc(0, c);
#endif
#if WITH_DEBUG_FBCON && WITH_DEV_FBCON
	fbcon_putc(c);
#endif
#if WITH_DEBUG_JTAG
	jtag_dputc(c);
#endif
}

int platform_dgetc(char *c, bool wait)
{
	int n;
#if WITH_DEBUG_DCC
	n = dcc_getc();
#elif WITH_DEBUG_UART
	n = uart_getc(0, 0);
#else
	n = -1;
#endif
	if (n < 0) {
		return -1;
	} else {
		*c = n;
		return 0;
	}
}

// TODO(MSM8916):
// void platform_halt(void)
// {
// #if PON_VIB_SUPPORT
// 	vib_turn_off();
// #endif
// 	dprintf(CRITICAL, "HALT: reboot into dload mode...\n");
// 	arch_clean_cache_range(MEMBASE, MEMSIZE);
// 	reboot_device(NORMAL_DLOAD);

// 	dprintf(CRITICAL, "HALT: spinning forever...\n");
// 	for (;;) ;
// }