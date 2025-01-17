/*
 * Use of this source code is governed by a MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT
 */
#include <platform.h>
#include <platform/clock.h>
#include <uart_dm.h>
#include <arch/arm.h>
#include <arch/arm/mmu.h>
#include <dev/interrupt/arm_gic.h>
//#include <dev/timer/arm_generic.h>
#include <qtimer.h>
#include <kernel/vm.h>
#include <platform/irqs.h>
#include <dev/uart.h>

#include <lk/console_cmd.h>
#include <lk/reg.h>
#include <kernel/timer.h>

struct mmu_initial_mapping mmu_initial_mappings[] = {
    {
        .phys = MEMBASE,
        .virt = MEMBASE,
        .size = MEMSIZE,
        .flags = 0,
        .name = "memory"
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
    /* null entry to terminate the list */
    { 0 }
};

static pmm_arena_t arena = {
    .name = "sdram",
    .base = MEMBASE,
    .size = MEMSIZE,
    .flags = PMM_ARENA_FLAG_KMAP,
};

void platform_early_init(void) {
    msm8916_clock_init();
    uart_dm_init(2, BLSP1_UART1_BASE);
    arm_gic_init();
//    arm_generic_timer_init(ARM_GENERIC_TIMER_PHYSICAL_INT, 19200000);
    qtimer_init();
    pmm_add_arena(&arena);
}

int platform_dgetc(char *c, bool wait)
{
    int n;
    n = uart_getc(0, 0);
    if (n < 0) {
        return -1;
    } else {
        *c = n;
        return 0;
    }
}

void platform_dputc(char c)
{
    uart_putc(0, c);
}

static int cmd_readl(int argc, const console_cmd_args *argv) {
    if (argc != 2) {
        return -1;
    }

    printf("0x%08x val: %d\n", argv[1].u, readl(argv[1].u));
    return 0;
}

STATIC_COMMAND_START
STATIC_COMMAND("readl", "read register", &cmd_readl)
STATIC_COMMAND_END(msm8916);

int qtmr_irq(void)
{
    return INT_QTMR_FRM_0_PHYSICAL_TIMER_EXP_8x16;
}
