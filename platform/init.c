/*
 * Copyright (c) 2008 Travis Geiselbrecht
 *
 * Use of this source code is governed by a MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT
 */
#include <lk/err.h>
#include <lk/debug.h>
#include <platform.h>

/*
 * default implementations of these routines, if the platform code
 * chooses not to implement.
 */

__WEAK void platform_init_mmu_mappings(void) {
}

__WEAK void platform_early_init(void) {
}

__WEAK void platform_init(void) {
}

__WEAK void platform_quiesce(void) {
}

// +MSM8916 HACK+
#include <sdhci_msm.h>
#if PON_VIB_SUPPORT
#include <smem.h>
#include <vibrator.h>
#include <board.h>
#endif

__WEAK uint32_t platform_get_max_periph(void)
{
	return 128;
}
__WEAK uint32_t platform_detect_panel(void)
{
	return 0;
}
__WEAK uint32_t platform_get_boot_dev(void)
{
        return 0;
}
__WEAK void clock_config_cdc(uint32_t slot)
{

}
/* Default CFG delay value */
__WEAK uint32_t target_ddr_cfg_val(void)
{
	return DDR_CONFIG_VAL;
}
/* Default CFG register value */
uint32_t target_ddr_cfg_reg(void)
{
	uint32_t platform = board_platform_id();
	uint32_t ret = SDCC_HC_REG_DDR_CONFIG;

	switch(platform)
	{
		case MSM8937:
		case MSM8940:
		case APQ8037:
		case MSM8917:
		case MSM8920:
		case MSM8217:
		case MSM8617:
		case APQ8017:
		case MSM8953:
		case APQ8053:
		case SDM450:
		case SDA450:
		case SDM632:
		case SDA632:
		case SDM429:
		case SDM439:
		case SDA429:
		case SDA439:
		case QM215:
		case QCM2150:
		/* SDCC HC DDR CONFIG has shifted by 4 bytes for these platform */
			ret += 4;
			break;
		default:
			break;
	}
	return ret;
}
// -MSM8916 HACK-
