/* Copyright (c) 2014-2015, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of The Linux Foundation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <lk/err.h>
#include <assert.h>
#include <lk/debug.h>
#include <lk/reg.h>
#include <qtimer.h>
#include <platform/iomap.h>
#include <clock.h>
#include <platform/clock.h>
#include <blsp_qup.h>
#include <platform.h>

#define MAX_LOOPS	500

/* Configure UART clock based on the UART block id*/
void clock_config_uart_dm(uint8_t id)
{
	int ret;
	char iclk[64];
	char cclk[64];

	snprintf(iclk, sizeof(iclk), "uart%u_iface_clk", id);
	snprintf(cclk, sizeof(cclk), "uart%u_core_clk", id);

	ret = clk_get_set_enable(iclk, 0, 1);
	if(ret)
	{
		dprintf(CRITICAL, "failed to set %s ret = %d\n", iclk, ret);
		ASSERT(0);
	}

	ret = clk_get_set_enable(cclk, 7372800, 1);
	if(ret)
	{
		dprintf(CRITICAL, "failed to set %s ret = %d\n", cclk, ret);
		ASSERT(0);
	}
}

static void rcg_update_config(uint32_t reg)
{
	int i;

	for (i = 0; i < MAX_LOOPS; i++) {
		if (!(readl(reg) & (1<<0)))
			return;
		udelay(1);
	}

	dprintf(CRITICAL, "failed to update rcg config for reg = 0x%x\n", reg);
	ASSERT(0);
}

static void branch_clk_halt_check(uint32_t reg)
{
	int i;

	for (i = 0; i < MAX_LOOPS; i++) {
		if (!(readl(reg) & (1<<31)))
			return;
		udelay(1);
	}

	dprintf(CRITICAL, "failed to enable branch for reg = 0x%x\n", reg);
	ASSERT(0);
}
