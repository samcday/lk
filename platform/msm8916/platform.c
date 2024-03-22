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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON-INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <lk/debug.h>
#include <lk/reg.h>
#include <platform/iomap.h>
#include <platform/irqs.h>
#include <platform/clock.h>
#include <qgic.h>
#include <qtimer.h>
#include <mmu.h>
#include <arch/arm/mmu.h>
#include <smem.h>
#include <board.h>
#include <boot_stats.h>
#include <platform.h>
#include <target/display.h>
#include <kernel/vm.h>


/* Peripherals - non-shared device */
#define IOMAP_MEMORY      (MMU_MEMORY_L1_TYPE_DEVICE_SHARED | \
			MMU_MEMORY_L1_AP_P_RW_U_RW | MMU_MEMORY_L1_SECTION_XN)

/* IMEM memory - cacheable, write through */
#define COMMON_MEMORY       (MMU_MEMORY_L1_TYPE_NORMAL_WRITE_THROUGH | \
                           MMU_MEMORY_L1_AP_P_RW_U_RW | MMU_MEMORY_L1_SECTION_XN)

#define SCRATCH_MEMORY       (MMU_MEMORY_L1_TYPE_NORMAL_WRITE_BACK_ALLOCATE | \
                           MMU_MEMORY_L1_AP_P_RW_U_RW | MMU_MEMORY_L1_SECTION_XN)

/* initial memory mappings. parsed by start.S */
struct mmu_initial_mapping mmu_initial_mappings[] = {
    {
        .phys = MEMBASE,
        .virt = MEMBASE,
        .size = MEMSIZE,
        .flags = 0,
        .name = "lk"
    },
    {
        .phys = MSM_IOMAP_BASE,
        .virt = MSM_IOMAP_BASE,
        .size = MSM_IOMAP_END - MSM_IOMAP_BASE,
        .flags = MMU_INITIAL_MAPPING_FLAG_DEVICE,
    },
    {
        .phys = A53_SS_BASE,
        .virt = A53_SS_BASE,
        .size = A53_SS_END - A53_SS_BASE,
        .flags = MMU_INITIAL_MAPPING_FLAG_DEVICE,
    },
    {
        .phys = SYSTEM_IMEM_BASE,
        .virt = SYSTEM_IMEM_BASE,
        .size = MB,
        .flags = 0,
    },
    {
        .phys = MSM_SHARED_BASE,
        .virt = MSM_SHARED_BASE,
        .size = MB,
        .flags = 0,
    },
    {
        .phys = SCRATCH_ADDR,
        .virt = SCRATCH_ADDR,
        .size = 256*MB,
        .flags = 0,
    },
    {
        .phys = MIPI_FB_ADDR,
        .virt = MIPI_FB_ADDR,
        .size = 10*MB,
        .flags = 0,
    },
    /* null entry to terminate the list */
    { 0 }
};

int platform_is_msm8939(void);
int platform_is_msm8929(void);

void platform_early_init(void)
{
	board_init();
	platform_clock_init();
	qgic_init();
	qtimer_init();
	scm_init();
}

int qtmr_irq(void)
{
	if (platform_is_msm8939() || platform_is_msm8929())
		return INT_QTMR_FRM_0_PHYSICAL_TIMER_EXP_8x39;
	else
		return INT_QTMR_FRM_0_PHYSICAL_TIMER_EXP_8x16;
}

void platform_init(void)
{
	dprintf(INFO, "platform_init()\n");
}

void platform_uninit(void)
{
	qtimer_uninit();
}

uint32_t platform_get_sclk_count(void)
{
	return readl(MPM2_MPM_SLEEP_TIMETICK_COUNT_VAL);
}

addr_t get_bs_info_addr(void)
{
	return ((addr_t)BS_INFO_ADDR);
}

int platform_use_identity_mmu_mappings(void)
{
	/* Use only the mappings specified in this file. */
	return 0;
}
/* Setup memory for this platform */
void platform_init_mmu_mappings(void)
{
}

addr_t platform_get_virt_to_phys_mapping(addr_t virt_addr)
{
	/* Using 1-1 mapping on this platform. */
	return virt_addr;
}

addr_t platform_get_phys_to_virt_mapping(addr_t phys_addr)
{
	/* Using 1-1 mapping on this platform. */
	return phys_addr;
}

int platform_is_msm8939(void)
{
	uint32_t platform = board_platform_id();
	uint32_t ret = 0;

	switch(platform)
	{
		case MSM8939:
		case APQ8036:
		case APQ8039:
		case MSM8236:
		case MSM8636:
		case MSM8936:
		case MSM8239:
			ret = 1;
			break;
		default:
			ret = 0;
	};

	return ret;
}

int platform_is_msm8929(void)
{
	uint32_t platform = board_platform_id();
	uint32_t ret = 0;

	switch(platform)
	{
		case MSM8929:
		case MSM8629:
		case MSM8229:
		case APQ8029:
			ret = 1;
			break;
		default:
			ret = 0;
	};

	return ret;
}

int platform_is_apq8016(void)
{
	return board_platform_id() == APQ8016 ? 1 : 0;
}

/* DYNAMIC SMEM REGION feature enables LK to dynamically
 * read the SMEM addr info from TCSR_TZ_WONCE register.
 * The first word read, if indicates a MAGIC number, then
 * Dynamic SMEM is assumed to be enabled. Read the remaining
 * SMEM info for SMEM Size and Phy_addr from the other bytes.
 */
uint32_t platform_get_smem_base_addr(void)
{
	struct smem_addr_info *smem_info = NULL;

	smem_info = (struct smem_addr_info *)readl(TCSR_TZ_WONCE);
	if(smem_info && (smem_info->identifier == SMEM_TARGET_INFO_IDENTIFIER))
		return smem_info->phy_addr;
	else
		return MSM_SHARED_BASE;
}
