/*
 * Copyright (c) 2008 Travis Geiselbrecht
 *
 * Use of this source code is governed by a MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT
 */
#pragma once

#include <lk/compiler.h>
#include <sys/types.h>

/* TODO: move all callers to using time.h directly */
#include <platform/time.h>

__BEGIN_CDECLS

typedef enum {
    HALT_ACTION_HALT = 0,       // Spin forever.
    HALT_ACTION_REBOOT,         // Reset the CPU.
    HALT_ACTION_SHUTDOWN,       // Shutdown and power off.
} platform_halt_action;

typedef enum {
    HALT_REASON_UNKNOWN = 0,
    HALT_REASON_POR,            // Cold-boot
    HALT_REASON_HW_WATCHDOG,    // HW watchdog timer
    HALT_REASON_LOWVOLTAGE,     // LV/Brownout condition
    HALT_REASON_HIGHVOLTAGE,    // High voltage condition.
    HALT_REASON_THERMAL,        // Thermal reason (probably overtemp)
    HALT_REASON_OTHER_HW,       // Other hardware (platform) specific reason
    HALT_REASON_SW_RESET,       // Generic Software Initiated Reboot
    HALT_REASON_SW_WATCHDOG,    // Reboot triggered by a SW watchdog timer
    HALT_REASON_SW_PANIC,       // Reboot triggered by a SW panic or ASSERT
    HALT_REASON_SW_UPDATE,      // SW triggered reboot in order to begin firmware update
} platform_halt_reason;

/* super early platform initialization, before almost everything */
void platform_early_init(void);

/* later init, after the kernel has come up */
void platform_init(void);

/* called by the arch init code to get the platform to set up any mmu mappings it may need */
void platform_init_mmu_mappings(void);

/* if the platform has knowledge of what caused the latest reboot, it can report
 * it to applications with this function.  */
platform_halt_reason platform_get_reboot_reason(void);

/* platform_halt is a method which is called from various places in the LK
 * system, and may be implemented by platforms and called by applications.  This
 * call represents the end of the life of SW for a device; there is no returning
 * from this function.  Callers will provide a reason for the halt, and a
 * suggested action for the platform to take, but it is the platform's
 * responsibility to determine the final action taken.  For example, in the case
 * of a failed ASSERT or a panic, LK will call platform halt and suggest a Halt
 * action, but a release build on a platform with no debug channel may choose to
 * reboot instead as there is no one to tell about the ASSERT, and no one
 * waiting to debug the device in its halted state.  If not overloaded by the
 * platform, the default behavior of platform halt will be to dprintf the
 * reason, and then halt execution by turning off interrupts and spinning
 * forever.
 */
void platform_halt(platform_halt_action suggested_action,
                   platform_halt_reason reason) __NO_RETURN;

/* called during chain loading to make sure drivers and platform is put into a stopped state */
void platform_quiesce(void);

__END_CDECLS


// +MSM8916 HACK+
#include <dload_util.h>

#define PA(x) platform_get_virt_to_phys_mapping(x)
#define VA(x) platform_get_phys_to_virt_mapping(x)

/* called by the arch init code to get the platform to set up any mmu mappings it may need */
int platform_use_identity_mmu_mappings(void);
void platform_init_mmu_mappings(void);
addr_t platform_get_virt_to_phys_mapping(addr_t virt_addr);
addr_t platform_get_phys_to_virt_mapping(addr_t phys_addr);
addr_t get_bs_info_addr(void);

void display_init(void);
void display_shutdown(void);
void display_image_on_screen(void);
void display_fbcon_message(char *str);

unsigned board_machtype(void);
unsigned board_platform_id(void);
unsigned check_reboot_mode(void);
unsigned check_hard_reboot_mode(void);
uint32_t check_alarm_boot(void);
void platform_uninit_timer(void);
void reboot_device(unsigned);
int set_download_mode(enum reboot_reason mode);
uint32_t platform_get_smem_base_addr(void);
uint32_t platform_get_sclk_count(void);
void clock_config_cdc(uint32_t interface);
uint8_t platform_pmic_type(uint32_t pmic_type);
int platform_is_8974(void);
int platform_is_8974Pro(void);
int platform_is_8974ac(void);
int platform_is_apq8016(void);
int platform_is_msm8929(void);
int platform_is_msm8939(void);
int platform_is_msm8909(void);
int platform_is_msm8992(void);
int platform_is_msm8937(void);
int platform_is_msm8917(void);
int platform_is_qm215(void);
uint32_t platform_get_apcs_ipc_base(void);
int platform_is_msm8952(void);
int platform_is_msm8953(void);
int platform_is_msm8956(void);
int platform_is_sdm429(void);
int platform_is_sdm439(void);
int platform_is_sdm429w(void);
int platform_is_sda429w(void);
uint32_t platform_is_msm8976_v_1_1(void);
uint32_t platform_get_tz_app_add(void);
uint32_t platform_get_tz_app_size(void);
int boot_device_mask(int);
uint32_t platform_detect_panel(void);
uint32_t platform_get_max_periph(void);
int platform_is_msm8996(void);
int platform_is_apq8096_mediabox(void);
bool platform_use_qmp_misc_settings(void);
void set_device_unlock_value(int type, bool status);
void get_product_name(unsigned char *buf);
void get_bootloader_version(unsigned char *buf);
void get_baseband_version(unsigned char *buf);
bool is_device_locked(void);
bool platform_is_mdm9650(void);
bool platform_is_sdx20(void);
uint64_t platform_get_ddr_start(void);
bool platform_is_glink_enabled(void);
bool platform_is_mdm9206(void);
#if VERIFIED_BOOT_LE
int is_vb_le_enabled(void);
#else
static inline int is_vb_le_enabled(void) { return 0; }
#endif
void* get_rpmb_snd_rcv_buff(void);
int LoadImage(char *Pname, void **ImgBuf, uint32_t *ImgSzActual);
void boot_verifier_init(void);
uint32_t get_page_size(void);
int read_rollback_index(uint32_t loc, uint64_t *roll_back_index);
int write_rollback_index(uint32_t loc, uint64_t roll_back_index);
int get_userkey(uint8_t **user_key, uint32_t *user_key_size);
int erase_userkey(void);
int store_userkey(uint8_t *user_key, uint32_t user_key_size);
bool is_device_locked_critical(void);
bool is_verity_enforcing(void);
// -MSM8916 HACK-
