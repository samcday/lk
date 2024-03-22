// SPDX-License-Identifier: BSD-3-Clause
/* Copyright (c) 2021-2022, Stephan Gerhold <stephan@gerhold.net> */

#include <arch/defines.h>
#include <lk/bits.h>
#include <lk/debug.h>
#include <kernel/thread.h>
#include <platform/timer.h>
#include <lk/reg.h>
#include <arch/arm.h>

#include "cpu-boot.h"

#define CPU_PWR_CTL			0x4
#define APC_PWR_GATE_CTL		0x14

#define CPU_PWR_CTL_CLAMP		MSM8916_BIT(0)
#define CPU_PWR_CTL_CORE_MEM_CLAMP	MSM8916_BIT(1)
#define CPU_PWR_CTL_L1_RST_DIS		MSM8916_BIT(2)
#define CPU_PWR_CTL_CORE_MEM_HS		MSM8916_BIT(3)
#define CPU_PWR_CTL_CORE_RST		MSM8916_BIT(4)
#define CPU_PWR_CTL_COREPOR_RST		MSM8916_BIT(5)
#define CPU_PWR_CTL_GATE_CLK		MSM8916_BIT(6)
#define CPU_PWR_CTL_CORE_PWRD_UP	MSM8916_BIT(7)

#define APC_PWR_GATE_CTL_GHDS_EN	MSM8916_BIT(0)
#define APC_PWR_GATE_CTL_GHDS_CNT(cnt)	((cnt) << 24)

#define PWR_CTL_OVERRIDE		0xc
#define L2_PWR_CTL			0x14
#define L2_PWR_STATUS			0x18
#define CORE_CBCR			0x58

#define PWR_CTL_OVERRIDE_PRESETDBG	MSM8916_BIT(22)

#define L2_PWR_CTL_L2_ARRAY_HS		MSM8916_BIT(0)
#define L2_PWR_CTL_SCU_ARRAY_HS		MSM8916_BIT(1)
#define L2_PWR_CTL_L2_RST_DIS		MSM8916_BIT(2)
#define L2_PWR_CTL_L2_HS_CLAMP		MSM8916_BIT(8)
#define L2_PWR_CTL_L2_HS_EN		MSM8916_BIT(9)
#define L2_PWR_CTL_L2_HS_RST		MSM8916_BIT(10)
#define L2_PWR_CTL_L2_SLEEP_STATE	MSM8916_BIT(11)
#define L2_PWR_CTL_SYS_RESET		MSM8916_BIT(12)
#define L2_PWR_CTL_L2_RET_SLP		MSM8916_BIT(13)
#define L2_PWR_CTL_SCU_ARRAY_HS_CLAMP	MSM8916_BIT(14)
#define L2_PWR_CTL_L2_ARRAY_HS_CLAMP	MSM8916_BIT(15)
#define L2_PWR_CTL_L2_HS_CNT(cnt)	((cnt) << 16)
#define L2_PWR_CTL_PMIC_APC_ON		MSM8916_BIT(28)

#define L2_PWR_STATUS_L2_HS_STS		MSM8916_BIT(9)

#define CORE_CBCR_CLK_ENABLE		MSM8916_BIT(0)
#define CORE_CBCR_HW_CTL		MSM8916_BIT(1)

static void power_on_l2_cache(uint32_t base)
{
	uint32_t pwr_ctl, cbcr, ovr;

	/* Skip if cluster L2 is already powered on */
	if (readl(base + L2_PWR_STATUS) & L2_PWR_STATUS_L2_HS_STS)
		return;

	dprintf(INFO, "Powering on L2 cache @ %#08x\n", base);

	enter_critical_section();

	pwr_ctl = L2_PWR_CTL_L2_HS_CLAMP | L2_PWR_CTL_L2_HS_EN |
		  L2_PWR_CTL_L2_HS_RST | L2_PWR_CTL_SYS_RESET |
		  L2_PWR_CTL_SCU_ARRAY_HS_CLAMP | L2_PWR_CTL_L2_ARRAY_HS_CLAMP |
		  L2_PWR_CTL_L2_HS_CNT(16);
	writel(pwr_ctl, base + L2_PWR_CTL);

	ovr = PWR_CTL_OVERRIDE_PRESETDBG;
	writel(ovr, base + PWR_CTL_OVERRIDE);
	DSB;
	udelay(2);

	pwr_ctl &= ~(L2_PWR_CTL_SCU_ARRAY_HS_CLAMP |
		     L2_PWR_CTL_L2_ARRAY_HS_CLAMP);
	writel(pwr_ctl, base + L2_PWR_CTL);

	pwr_ctl |= (L2_PWR_CTL_L2_ARRAY_HS | L2_PWR_CTL_SCU_ARRAY_HS);
	writel(pwr_ctl, base + L2_PWR_CTL);
	DSB;
	udelay(2);

	cbcr = CORE_CBCR_CLK_ENABLE;
	writel(cbcr, base + CORE_CBCR);

	pwr_ctl &= ~L2_PWR_CTL_L2_HS_CLAMP;
	writel(pwr_ctl, base + L2_PWR_CTL);
	DSB;
	udelay(2);

	ovr &= ~PWR_CTL_OVERRIDE_PRESETDBG;
	writel(ovr, base + PWR_CTL_OVERRIDE);

	pwr_ctl &= ~(L2_PWR_CTL_L2_HS_RST | L2_PWR_CTL_SYS_RESET);
	writel(pwr_ctl, base + L2_PWR_CTL);
	DSB;
	udelay(54);

	pwr_ctl |= L2_PWR_CTL_PMIC_APC_ON;
	writel(pwr_ctl, base + L2_PWR_CTL);

	cbcr |= CORE_CBCR_HW_CTL;
	writel(cbcr, base + CORE_CBCR);
	DSB;

	exit_critical_section();
}

void cpu_boot_cortex_a(uint32_t base, uint32_t apcs_base)
{
	uint32_t pwr_ctl;

	if (apcs_base)
		power_on_l2_cache(apcs_base);

	enter_critical_section();

	pwr_ctl = CPU_PWR_CTL_CLAMP | CPU_PWR_CTL_CORE_MEM_CLAMP |
		  CPU_PWR_CTL_CORE_RST | CPU_PWR_CTL_COREPOR_RST;
	writel(pwr_ctl, base + CPU_PWR_CTL);
	DSB;

	writel(APC_PWR_GATE_CTL_GHDS_EN | APC_PWR_GATE_CTL_GHDS_CNT(16),
	       base + APC_PWR_GATE_CTL);
	DSB;
	udelay(2);

	pwr_ctl &= ~CPU_PWR_CTL_CORE_MEM_CLAMP;
	writel(pwr_ctl, base + CPU_PWR_CTL);
	DSB;

	pwr_ctl |= CPU_PWR_CTL_CORE_MEM_HS;
	writel(pwr_ctl, base + CPU_PWR_CTL);
	DSB;
	udelay(2);

	pwr_ctl &= ~CPU_PWR_CTL_CLAMP;
	writel(pwr_ctl, base + CPU_PWR_CTL);
	DSB;
	udelay(2);

	pwr_ctl &= ~(CPU_PWR_CTL_CORE_RST | CPU_PWR_CTL_COREPOR_RST);
	writel(pwr_ctl, base + CPU_PWR_CTL);
	DSB;

	pwr_ctl |= CPU_PWR_CTL_CORE_PWRD_UP;
	writel(pwr_ctl, base + CPU_PWR_CTL);
	DSB;

	exit_critical_section();
}
