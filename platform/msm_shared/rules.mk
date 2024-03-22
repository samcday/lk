LOCAL_DIR := $(GET_LOCAL_DIR)

GLOBAL_INCLUDES += \
			$(LOCAL_DIR)/include $(LKROOT)/dev/panel/msm $(LKROOT)/app/aboot

GLOBAL_DEFINES += $(TARGET_XRES)
GLOBAL_DEFINES += $(TARGET_YRES)

MODULE_SRCS += \
	$(LOCAL_DIR)/debug.c \
	$(LOCAL_DIR)/smem.c \
	$(LOCAL_DIR)/smem_ptable.c \
	$(LOCAL_DIR)/partition_parser.c \
	$(LOCAL_DIR)/ab_partition_parser.c \
	$(LOCAL_DIR)/hsusb.c \
	$(LOCAL_DIR)/boot_stats.c \
	$(LOCAL_DIR)/qgic_common.c

ifneq ($(filter $(GLOBAL_DEFINES), WITH_DEBUG_JTAG=1),)
MODULE_SRCS += \
	$(LOCAL_DIR)/jtag_hook.c \
	$(LOCAL_DIR)/jtag.c
endif

ifeq ($(ENABLE_WDOG_SUPPORT),1)
MODULE_SRCS += \
	$(LOCAL_DIR)/wdog.c
endif

ifeq ($(ENABLE_SECAPP_LOADER), 1)
MODULE_SRCS += $(LOCAL_DIR)/secapp_loader.c
endif

ifeq ($(ENABLE_QGIC3), 1)
MODULE_SRCS += $(LOCAL_DIR)/qgic_v3.c
endif

ifeq ($(ENABLE_SMD_SUPPORT),1)
MODULE_SRCS += \
	$(LOCAL_DIR)/rpm-ipc.c \
	$(LOCAL_DIR)/rpm-smd.c \
	$(LOCAL_DIR)/smd.c
endif

ifeq ($(ENABLE_SDHCI_SUPPORT),1)
MODULE_SRCS += \
	$(LOCAL_DIR)/sdhci.c \
	$(LOCAL_DIR)/sdhci_msm.c \
	$(LOCAL_DIR)/mmc_sdhci.c \
	$(LOCAL_DIR)/mmc_wrapper.c
else
MODULE_SRCS += \
	$(LOCAL_DIR)/mmc.c
endif

ifeq ($(VERIFIED_BOOT),1)
MODULE_SRCS += \
	$(LOCAL_DIR)/boot_verifier.c
endif

ifeq ($(ENABLE_DISPLAY),0)
GLOBAL_DEFINES := $(filter-out DISPLAY_SPLASH_SCREEN=1, $(GLOBAL_DEFINES))
endif

ifeq ($(ENABLE_FBCON_DISPLAY_MSG),1)
GLOBAL_DEFINES += FBCON_DISPLAY_MSG=1
MODULE_SRCS += \
	$(LOCAL_DIR)/menu_keys_detect.c \
	$(LOCAL_DIR)/display_menu.c
endif

ifeq ($(ENABLE_GLINK_SUPPORT),1)
MODULE_SRCS += \
		$(LOCAL_DIR)/glink/glink_api.c \
		$(LOCAL_DIR)/glink/glink_core_if.c \
		$(LOCAL_DIR)/glink/glink_core_internal.c \
		$(LOCAL_DIR)/glink/glink_rpmcore_setup.c \
		$(LOCAL_DIR)/glink/glink_core_intentless_xport.c \
		$(LOCAL_DIR)/glink/glink_os_utils_dal.c \
		$(LOCAL_DIR)/glink/glink_vector.c \
		$(LOCAL_DIR)/glink/xport_rpm.c \
		$(LOCAL_DIR)/glink/xport_rpm_config.c \
		$(LOCAL_DIR)/smem_list.c \
		$(LOCAL_DIR)/rpm-glink.c
endif

ifneq ($(ENABLE_SMD_SUPPORT),1)
MODULE_SRCS += \
	$(LOCAL_DIR)/rpm-ipc.c
endif

ifeq ($(PLATFORM),msm8x60)
	MODULE_SRCS += $(LOCAL_DIR)/mipi_dsi.c \
			$(LOCAL_DIR)/i2c_qup.c \
			$(LOCAL_DIR)/uart_dm.c \
			$(LOCAL_DIR)/board.c \
			$(LOCAL_DIR)/crypto_eng.c \
			$(LOCAL_DIR)/crypto_hash.c \
			$(LOCAL_DIR)/scm.c \
			$(LOCAL_DIR)/lcdc.c \
			$(LOCAL_DIR)/mddi.c \
			$(LOCAL_DIR)/qgic.c \
			$(LOCAL_DIR)/mdp4.c \
			$(LOCAL_DIR)/certificate.c \
			$(LOCAL_DIR)/image_verify.c \
			$(LOCAL_DIR)/hdmi.c \
			$(LOCAL_DIR)/interrupts.c \
			$(LOCAL_DIR)/timer.c \
			$(LOCAL_DIR)/nand.c
endif

ifeq ($(PLATFORM),msm8960)
	MODULE_SRCS += $(LOCAL_DIR)/hdmi.c \
			$(LOCAL_DIR)/mipi_dsi.c \
			$(LOCAL_DIR)/i2c_qup.c \
			$(LOCAL_DIR)/uart_dm.c \
			$(LOCAL_DIR)/qgic.c \
			$(LOCAL_DIR)/mdp4.c \
			$(LOCAL_DIR)/crypto4_eng.c \
			$(LOCAL_DIR)/crypto_hash.c \
			$(LOCAL_DIR)/certificate.c \
			$(LOCAL_DIR)/image_verify.c \
			$(LOCAL_DIR)/scm.c \
			$(LOCAL_DIR)/interrupts.c \
			$(LOCAL_DIR)/clock-local.c \
			$(LOCAL_DIR)/clock.c \
			$(LOCAL_DIR)/clock_pll.c \
			$(LOCAL_DIR)/board.c \
			$(LOCAL_DIR)/display.c \
			$(LOCAL_DIR)/lvds.c \
			$(LOCAL_DIR)/mipi_dsi_phy.c \
			$(LOCAL_DIR)/timer.c \
			$(LOCAL_DIR)/mdp_lcdc.c \
			$(LOCAL_DIR)/nand.c
endif

ifeq ($(PLATFORM),msm8974)
GLOBAL_DEFINES += DISPLAY_TYPE_MDSS=1
	MODULE_SRCS += $(LOCAL_DIR)/qgic.c \
			$(LOCAL_DIR)/qtimer.c \
			$(LOCAL_DIR)/qtimer_mmap.c \
			$(LOCAL_DIR)/interrupts.c \
			$(LOCAL_DIR)/clock.c \
			$(LOCAL_DIR)/clock_pll.c \
			$(LOCAL_DIR)/clock_lib2.c \
			$(LOCAL_DIR)/uart_dm.c \
			$(LOCAL_DIR)/board.c \
			$(LOCAL_DIR)/scm.c \
			$(LOCAL_DIR)/mdp5.c \
			$(LOCAL_DIR)/display.c \
			$(LOCAL_DIR)/mipi_dsi.c \
			$(LOCAL_DIR)/mipi_dsi_phy.c \
			$(LOCAL_DIR)/mipi_dsi_autopll.c \
			$(LOCAL_DIR)/spmi.c \
			$(LOCAL_DIR)/bam.c \
			$(LOCAL_DIR)/dev_tree.c \
			$(LOCAL_DIR)/certificate.c \
			$(LOCAL_DIR)/image_verify.c \
			$(LOCAL_DIR)/crypto_hash.c \
			$(LOCAL_DIR)/crypto5_eng.c \
			$(LOCAL_DIR)/crypto5_wrapper.c \
			$(LOCAL_DIR)/i2c_qup.c \
			$(LOCAL_DIR)/gpio.c \
			$(LOCAL_DIR)/dload_util.c \
			$(LOCAL_DIR)/edp.c \
			$(LOCAL_DIR)/edp_util.c \
			$(LOCAL_DIR)/edp_aux.c \
			$(LOCAL_DIR)/edp_phy.c
endif

ifeq ($(PLATFORM),msm8226)
GLOBAL_DEFINES += DISPLAY_TYPE_MDSS=1
	MODULE_SRCS += $(LOCAL_DIR)/qgic.c \
			$(LOCAL_DIR)/qtimer.c \
			$(LOCAL_DIR)/qtimer_mmap.c \
			$(LOCAL_DIR)/interrupts.c \
			$(LOCAL_DIR)/clock.c \
			$(LOCAL_DIR)/clock_pll.c \
			$(LOCAL_DIR)/clock_lib2.c \
			$(LOCAL_DIR)/uart_dm.c \
			$(LOCAL_DIR)/board.c \
			$(LOCAL_DIR)/scm.c \
			$(LOCAL_DIR)/mdp5.c \
			$(LOCAL_DIR)/display.c \
			$(LOCAL_DIR)/mipi_dsi.c \
			$(LOCAL_DIR)/mipi_dsi_phy.c \
			$(LOCAL_DIR)/mipi_dsi_autopll.c \
			$(LOCAL_DIR)/spmi.c \
			$(LOCAL_DIR)/bam.c \
            $(LOCAL_DIR)/certificate.c \
            $(LOCAL_DIR)/image_verify.c \
            $(LOCAL_DIR)/crypto_hash.c \
            $(LOCAL_DIR)/crypto5_eng.c \
            $(LOCAL_DIR)/crypto5_wrapper.c \
			$(LOCAL_DIR)/dev_tree.c \
			$(LOCAL_DIR)/gpio.c \
			$(LOCAL_DIR)/dload_util.c \
			$(LOCAL_DIR)/shutdown_detect.c
endif

ifeq ($(PLATFORM),msm8916)
GLOBAL_DEFINES += DISPLAY_TYPE_MDSS=1
	MODULE_SRCS += $(LOCAL_DIR)/qgic.c \
		$(LOCAL_DIR)/qtimer.c \
		$(LOCAL_DIR)/qtimer_mmap.c \
		$(LOCAL_DIR)/interrupts.c \
		$(LOCAL_DIR)/clock.c \
		$(LOCAL_DIR)/clock_pll.c \
		$(LOCAL_DIR)/clock_lib2.c \
		$(LOCAL_DIR)/uart_dm.c \
		$(LOCAL_DIR)/board.c \
		$(LOCAL_DIR)/spmi.c \
		$(LOCAL_DIR)/bam.c \
		$(LOCAL_DIR)/scm.c \
		$(LOCAL_DIR)/dload_util.c \
		$(LOCAL_DIR)/gpio.c \
		$(LOCAL_DIR)/dev_tree.c \
		$(LOCAL_DIR)/mdp5.c \
		$(LOCAL_DIR)/display.c \
		$(LOCAL_DIR)/mipi_dsi.c \
		$(LOCAL_DIR)/mipi_dsi_phy.c \
		$(LOCAL_DIR)/mipi_dsi_autopll.c \
		$(LOCAL_DIR)/shutdown_detect.c \
		$(LOCAL_DIR)/certificate.c \
		$(LOCAL_DIR)/image_verify.c \
		$(LOCAL_DIR)/crypto_hash.c \
		$(LOCAL_DIR)/crypto5_eng.c \
		$(LOCAL_DIR)/crypto5_wrapper.c \
		$(LOCAL_DIR)/i2c_qup.c \
		$(LOCAL_DIR)/mipi_dsi_i2c.c

endif


ifeq ($(PLATFORM),msm8610)
GLOBAL_DEFINES += DISPLAY_TYPE_MDSS=1
    MODULE_SRCS += $(LOCAL_DIR)/qgic.c \
            $(LOCAL_DIR)/qtimer.c \
            $(LOCAL_DIR)/qtimer_mmap.c \
            $(LOCAL_DIR)/interrupts.c \
            $(LOCAL_DIR)/clock.c \
            $(LOCAL_DIR)/clock_pll.c \
            $(LOCAL_DIR)/clock_lib2.c \
            $(LOCAL_DIR)/uart_dm.c \
            $(LOCAL_DIR)/board.c \
            $(LOCAL_DIR)/display.c \
            $(LOCAL_DIR)/mipi_dsi.c \
            $(LOCAL_DIR)/mipi_dsi_phy.c \
            $(LOCAL_DIR)/mdp3.c \
            $(LOCAL_DIR)/spmi.c \
            $(LOCAL_DIR)/bam.c \
            $(LOCAL_DIR)/dev_tree.c \
            $(LOCAL_DIR)/scm.c \
            $(LOCAL_DIR)/gpio.c \
            $(LOCAL_DIR)/certificate.c \
            $(LOCAL_DIR)/image_verify.c \
            $(LOCAL_DIR)/crypto_hash.c \
            $(LOCAL_DIR)/crypto5_eng.c \
            $(LOCAL_DIR)/crypto5_wrapper.c \
            $(LOCAL_DIR)/dload_util.c \
            $(LOCAL_DIR)/shutdown_detect.c
endif

ifeq ($(PLATFORM),apq8084)
GLOBAL_DEFINES += DISPLAY_TYPE_MDSS=1
    MODULE_SRCS += $(LOCAL_DIR)/qgic.c \
            $(LOCAL_DIR)/qtimer.c \
            $(LOCAL_DIR)/qtimer_mmap.c \
            $(LOCAL_DIR)/interrupts.c \
            $(LOCAL_DIR)/clock.c \
            $(LOCAL_DIR)/clock_pll.c \
            $(LOCAL_DIR)/clock_lib2.c \
            $(LOCAL_DIR)/uart_dm.c \
            $(LOCAL_DIR)/board.c \
            $(LOCAL_DIR)/mdp5.c \
            $(LOCAL_DIR)/display.c \
            $(LOCAL_DIR)/mipi_dsi.c \
            $(LOCAL_DIR)/mipi_dsi_phy.c \
            $(LOCAL_DIR)/mipi_dsi_autopll.c \
            $(LOCAL_DIR)/mdss_hdmi.c \
            $(LOCAL_DIR)/hdmi_pll_28nm.c \
            $(LOCAL_DIR)/spmi.c \
            $(LOCAL_DIR)/bam.c \
            $(LOCAL_DIR)/dev_tree.c \
            $(LOCAL_DIR)/gpio.c \
            $(LOCAL_DIR)/scm.c \
			$(LOCAL_DIR)/certificate.c \
			$(LOCAL_DIR)/image_verify.c \
			$(LOCAL_DIR)/crypto_hash.c \
			$(LOCAL_DIR)/crypto5_eng.c \
			$(LOCAL_DIR)/crypto5_wrapper.c \
			$(LOCAL_DIR)/edp.c \
			$(LOCAL_DIR)/edp_util.c \
			$(LOCAL_DIR)/edp_aux.c \
			$(LOCAL_DIR)/edp_phy.c

endif

ifeq ($(PLATFORM),msm7x27a)
	MODULE_SRCS += $(LOCAL_DIR)/uart.c \
			$(LOCAL_DIR)/nand.c \
			$(LOCAL_DIR)/proc_comm.c \
			$(LOCAL_DIR)/mdp3.c \
			$(LOCAL_DIR)/mipi_dsi.c \
			$(LOCAL_DIR)/crypto_eng.c \
			$(LOCAL_DIR)/crypto_hash.c \
			$(LOCAL_DIR)/certificate.c \
			$(LOCAL_DIR)/image_verify.c \
			$(LOCAL_DIR)/qgic.c \
			$(LOCAL_DIR)/interrupts.c \
			$(LOCAL_DIR)/timer.c \
			$(LOCAL_DIR)/display.c \
			$(LOCAL_DIR)/mipi_dsi_phy.c \
			$(LOCAL_DIR)/mdp_lcdc.c \
			$(LOCAL_DIR)/spi.c
endif

ifeq ($(PLATFORM),msm7k)
	MODULE_SRCS += $(LOCAL_DIR)/uart.c \
			$(LOCAL_DIR)/nand.c \
			$(LOCAL_DIR)/proc_comm.c \
			$(LOCAL_DIR)/lcdc.c \
			$(LOCAL_DIR)/mddi.c \
			$(LOCAL_DIR)/timer.c
endif

ifeq ($(PLATFORM),msm7x30)
	MODULE_SRCS += $(LOCAL_DIR)/crypto_eng.c \
			$(LOCAL_DIR)/crypto_hash.c \
			$(LOCAL_DIR)/uart.c \
			$(LOCAL_DIR)/nand.c \
			$(LOCAL_DIR)/proc_comm.c \
			$(LOCAL_DIR)/lcdc.c \
			$(LOCAL_DIR)/mddi.c \
			$(LOCAL_DIR)/certificate.c \
			$(LOCAL_DIR)/image_verify.c \
			$(LOCAL_DIR)/timer.c
endif

ifeq ($(PLATFORM),mdm9x15)
	MODULE_SRCS += $(LOCAL_DIR)/qgic.c \
			$(LOCAL_DIR)/nand.c \
			$(LOCAL_DIR)/uart_dm.c \
			$(LOCAL_DIR)/interrupts.c \
			$(LOCAL_DIR)/scm.c \
			$(LOCAL_DIR)/timer.c
endif

ifeq ($(PLATFORM),mdm9x25)
	MODULE_SRCS += $(LOCAL_DIR)/qgic.c \
			$(LOCAL_DIR)/uart_dm.c \
			$(LOCAL_DIR)/interrupts.c \
			$(LOCAL_DIR)/qtimer.c \
			$(LOCAL_DIR)/qtimer_mmap.c \
			$(LOCAL_DIR)/board.c \
			$(LOCAL_DIR)/spmi.c \
			$(LOCAL_DIR)/qpic_nand.c \
			$(LOCAL_DIR)/bam.c \
			$(LOCAL_DIR)/scm.c \
			$(LOCAL_DIR)/dev_tree.c \
			$(LOCAL_DIR)/clock.c \
			$(LOCAL_DIR)/clock_pll.c \
			$(LOCAL_DIR)/clock_lib2.c
endif

ifeq ($(PLATFORM),mdm9x35)
GLOBAL_DEFINES += DISPLAY_TYPE_QPIC=1
	MODULE_SRCS += $(LOCAL_DIR)/qgic.c \
			$(LOCAL_DIR)/uart_dm.c \
			$(LOCAL_DIR)/interrupts.c \
			$(LOCAL_DIR)/qtimer.c \
			$(LOCAL_DIR)/qtimer_mmap.c \
			$(LOCAL_DIR)/board.c \
			$(LOCAL_DIR)/spmi.c \
			$(LOCAL_DIR)/qpic_nand.c \
			$(LOCAL_DIR)/flash-ubi.c \
			$(LOCAL_DIR)/bam.c \
			$(LOCAL_DIR)/scm.c \
			$(LOCAL_DIR)/dev_tree.c \
			$(LOCAL_DIR)/clock.c \
			$(LOCAL_DIR)/clock_pll.c \
			$(LOCAL_DIR)/clock_lib2.c \
			$(LOCAL_DIR)/qmp_usb30_phy.c \
			$(LOCAL_DIR)/display.c \
			$(LOCAL_DIR)/qpic.c \
			$(LOCAL_DIR)/qpic_panel.c
endif

ifeq ($(PLATFORM),mdm9640)
GLOBAL_DEFINES += DISPLAY_TYPE_QPIC=1
	MODULE_SRCS += $(LOCAL_DIR)/qgic.c \
			$(LOCAL_DIR)/uart_dm.c \
			$(LOCAL_DIR)/interrupts.c \
			$(LOCAL_DIR)/qtimer.c \
			$(LOCAL_DIR)/qtimer_mmap.c \
			$(LOCAL_DIR)/board.c \
			$(LOCAL_DIR)/spmi.c \
			$(LOCAL_DIR)/qpic_nand.c \
			$(LOCAL_DIR)/flash-ubi.c \
			$(LOCAL_DIR)/bam.c \
			$(LOCAL_DIR)/dev_tree.c \
			$(LOCAL_DIR)/clock.c \
			$(LOCAL_DIR)/clock_pll.c \
			$(LOCAL_DIR)/clock_lib2.c \
			$(LOCAL_DIR)/gpio.c \
			$(LOCAL_DIR)/crypto_hash.c \
			$(LOCAL_DIR)/crypto5_eng.c \
			$(LOCAL_DIR)/crypto5_wrapper.c \
			$(LOCAL_DIR)/certificate.c \
			$(LOCAL_DIR)/image_verify.c \
			$(LOCAL_DIR)/scm.c \
			$(LOCAL_DIR)/qmp_usb30_phy.c \
			$(LOCAL_DIR)/qusb2_phy.c \
			$(LOCAL_DIR)/display.c \
			$(LOCAL_DIR)/qpic.c \
			$(LOCAL_DIR)/qpic_panel.c
endif

ifeq ($(PLATFORM),fsm9900)
	MODULE_SRCS += $(LOCAL_DIR)/qgic.c \
			$(LOCAL_DIR)/qtimer.c \
			$(LOCAL_DIR)/qtimer_mmap.c \
			$(LOCAL_DIR)/interrupts.c \
			$(LOCAL_DIR)/clock.c \
			$(LOCAL_DIR)/clock_pll.c \
			$(LOCAL_DIR)/clock_lib2.c \
			$(LOCAL_DIR)/uart_dm.c \
			$(LOCAL_DIR)/board.c \
			$(LOCAL_DIR)/scm.c \
			$(LOCAL_DIR)/spmi.c \
			$(LOCAL_DIR)/bam.c \
			$(LOCAL_DIR)/dev_tree.c \
			$(LOCAL_DIR)/certificate.c \
			$(LOCAL_DIR)/image_verify.c \
			$(LOCAL_DIR)/crypto_hash.c \
			$(LOCAL_DIR)/crypto5_eng.c \
			$(LOCAL_DIR)/crypto5_wrapper.c \
			$(LOCAL_DIR)/i2c_qup.c \
			$(LOCAL_DIR)/gpio.c \
			$(LOCAL_DIR)/dload_util.c
endif

ifeq ($(PLATFORM),fsm9010)
	MODULE_SRCS += $(LOCAL_DIR)/qgic.c \
			$(LOCAL_DIR)/qtimer.c \
			$(LOCAL_DIR)/qtimer_mmap.c \
			$(LOCAL_DIR)/interrupts.c \
			$(LOCAL_DIR)/clock.c \
			$(LOCAL_DIR)/clock_pll.c \
			$(LOCAL_DIR)/clock_lib2.c \
			$(LOCAL_DIR)/uart_dm.c \
			$(LOCAL_DIR)/board.c \
			$(LOCAL_DIR)/scm.c \
			$(LOCAL_DIR)/spmi.c \
			$(LOCAL_DIR)/bam.c \
			$(LOCAL_DIR)/dev_tree.c \
			$(LOCAL_DIR)/certificate.c \
			$(LOCAL_DIR)/image_verify.c \
			$(LOCAL_DIR)/crypto_hash.c \
			$(LOCAL_DIR)/crypto5_eng.c \
			$(LOCAL_DIR)/crypto5_wrapper.c \
			$(LOCAL_DIR)/i2c_qup.c \
			$(LOCAL_DIR)/gpio.c \
			$(LOCAL_DIR)/qmp_usb30_phy.c \
			$(LOCAL_DIR)/dload_util.c
endif

ifeq ($(PLATFORM),msm8994)
GLOBAL_DEFINES += DISPLAY_TYPE_MDSS=1
	MODULE_SRCS += $(LOCAL_DIR)/qgic.c \
			$(LOCAL_DIR)/qtimer.c \
			$(LOCAL_DIR)/qtimer_mmap.c \
			$(LOCAL_DIR)/interrupts.c \
			$(LOCAL_DIR)/clock.c \
			$(LOCAL_DIR)/clock_pll.c \
			$(LOCAL_DIR)/clock_lib2.c \
			$(LOCAL_DIR)/uart_dm.c \
			$(LOCAL_DIR)/board.c \
			$(LOCAL_DIR)/spmi.c \
			$(LOCAL_DIR)/bam.c \
			$(LOCAL_DIR)/dev_tree.c \
			$(LOCAL_DIR)/gpio.c \
			$(LOCAL_DIR)/scm.c \
			$(LOCAL_DIR)/qmp_usb30_phy.c \
			$(LOCAL_DIR)/certificate.c \
			$(LOCAL_DIR)/image_verify.c \
			$(LOCAL_DIR)/crypto_hash.c \
			$(LOCAL_DIR)/crypto5_eng.c \
			$(LOCAL_DIR)/crypto5_wrapper.c \
			$(LOCAL_DIR)/qusb2_phy.c \
			$(LOCAL_DIR)/qseecom_lk.c \
			$(LOCAL_DIR)/mdp5.c \
			$(LOCAL_DIR)/display.c \
			$(LOCAL_DIR)/mipi_dsi.c \
			$(LOCAL_DIR)/mipi_dsi_phy.c \
			$(LOCAL_DIR)/mipi_dsi_autopll.c \
			$(LOCAL_DIR)/mipi_dsi_autopll_20nm.c \
			$(LOCAL_DIR)/mdss_hdmi.c \
			$(LOCAL_DIR)/hdmi_pll_20nm.c \
			$(LOCAL_DIR)/dload_util.c
endif

ifeq ($(PLATFORM),msm8909)
GLOBAL_DEFINES += DISPLAY_TYPE_MDSS=1
	MODULE_SRCS += $(LOCAL_DIR)/qgic.c \
			$(LOCAL_DIR)/qtimer.c \
			$(LOCAL_DIR)/qtimer_mmap.c \
			$(LOCAL_DIR)/interrupts.c \
			$(LOCAL_DIR)/clock.c \
			$(LOCAL_DIR)/clock_pll.c \
			$(LOCAL_DIR)/clock_lib2.c \
			$(LOCAL_DIR)/uart_dm.c \
			$(LOCAL_DIR)/board.c \
			$(LOCAL_DIR)/spmi.c \
			$(LOCAL_DIR)/bam.c \
			$(LOCAL_DIR)/qpic_nand.c \
			$(LOCAL_DIR)/scm.c \
			$(LOCAL_DIR)/dev_tree.c \
			$(LOCAL_DIR)/gpio.c \
			$(LOCAL_DIR)/crypto_hash.c \
			$(LOCAL_DIR)/crypto5_eng.c \
			$(LOCAL_DIR)/crypto5_wrapper.c \
			$(LOCAL_DIR)/dload_util.c \
			$(LOCAL_DIR)/shutdown_detect.c \
			$(LOCAL_DIR)/certificate.c \
			$(LOCAL_DIR)/image_verify.c \
			$(LOCAL_DIR)/i2c_qup.c \
			$(LOCAL_DIR)/spi_qup.c \
            $(LOCAL_DIR)/qseecom_lk.c \
			$(LOCAL_DIR)/mdp3.c \
			$(LOCAL_DIR)/display.c \
			$(LOCAL_DIR)/mipi_dsi.c \
			$(LOCAL_DIR)/mipi_dsi_phy.c \
			$(LOCAL_DIR)/flash-ubi.c \
			$(LOCAL_DIR)/mipi_dsi_autopll.c\
			$(LOCAL_DIR)/mdss_spi.c
endif

ifeq ($(PLATFORM),mdm9607)
	MODULE_SRCS += $(LOCAL_DIR)/qgic.c \
			$(LOCAL_DIR)/qtimer.c \
			$(LOCAL_DIR)/qtimer_mmap.c \
			$(LOCAL_DIR)/interrupts.c \
			$(LOCAL_DIR)/clock.c \
			$(LOCAL_DIR)/clock_pll.c \
			$(LOCAL_DIR)/clock_lib2.c \
			$(LOCAL_DIR)/uart_dm.c \
			$(LOCAL_DIR)/board.c \
			$(LOCAL_DIR)/spmi.c \
			$(LOCAL_DIR)/bam.c \
			$(LOCAL_DIR)/qpic_nand.c \
			$(LOCAL_DIR)/crypto_hash.c \
			$(LOCAL_DIR)/crypto5_eng.c \
			$(LOCAL_DIR)/crypto5_wrapper.c \
			$(LOCAL_DIR)/certificate.c \
			$(LOCAL_DIR)/image_verify.c \
			$(LOCAL_DIR)/flash-ubi.c \
			$(LOCAL_DIR)/scm.c \
			$(LOCAL_DIR)/dev_tree.c
endif

ifeq ($(PLATFORM),msm8996)
GLOBAL_DEFINES += DISPLAY_TYPE_MDSS=1
	MODULE_SRCS += $(LOCAL_DIR)/qtimer.c \
			$(LOCAL_DIR)/qtimer_mmap.c \
			$(LOCAL_DIR)/interrupts.c \
			$(LOCAL_DIR)/clock.c \
			$(LOCAL_DIR)/clock_pll.c \
			$(LOCAL_DIR)/clock_alpha_pll.c \
			$(LOCAL_DIR)/clock_lib2.c \
			$(LOCAL_DIR)/uart_dm.c \
			$(LOCAL_DIR)/board.c \
			$(LOCAL_DIR)/spmi.c \
			$(LOCAL_DIR)/bam.c \
			$(LOCAL_DIR)/dev_tree.c \
			$(LOCAL_DIR)/gpio.c \
			$(LOCAL_DIR)/scm.c \
			$(LOCAL_DIR)/qseecom_lk.c \
			$(LOCAL_DIR)/qmp_usb30_phy.c \
			$(LOCAL_DIR)/qusb2_phy.c \
			$(LOCAL_DIR)/certificate.c \
			$(LOCAL_DIR)/image_verify.c \
			$(LOCAL_DIR)/crypto_hash.c \
			$(LOCAL_DIR)/crypto5_eng.c \
			$(LOCAL_DIR)/crypto5_wrapper.c \
			$(LOCAL_DIR)/mdp5.c \
			$(LOCAL_DIR)/display.c \
			$(LOCAL_DIR)/mipi_dsi.c \
			$(LOCAL_DIR)/mipi_dsc.c \
			$(LOCAL_DIR)/mipi_dsi_phy.c \
			$(LOCAL_DIR)/mipi_dsi_autopll_thulium.c \
			$(LOCAL_DIR)/shutdown_detect.c \
			$(LOCAL_DIR)/i2c_qup.c \
			$(LOCAL_DIR)/mipi_dsi_i2c.c \
			$(LOCAL_DIR)/mdss_hdmi.c \
			$(LOCAL_DIR)/mdss_hdmi_pll_8996.c
endif

ifeq ($(ENABLE_UFS_SUPPORT), 1)
	MODULE_SRCS += \
			$(LOCAL_DIR)/ufs.c \
			$(LOCAL_DIR)/utp.c \
			$(LOCAL_DIR)/uic.c \
			$(LOCAL_DIR)/ucs.c \
			$(LOCAL_DIR)/ufs_hci.c \
			$(LOCAL_DIR)/dme.c
endif

ifeq ($(PLATFORM),msm8952)
GLOBAL_DEFINES += DISPLAY_TYPE_MDSS=1
	MODULE_SRCS += $(LOCAL_DIR)/qgic.c \
			$(LOCAL_DIR)/qtimer.c \
			$(LOCAL_DIR)/qtimer_mmap.c \
			$(LOCAL_DIR)/interrupts.c \
			$(LOCAL_DIR)/clock.c \
			$(LOCAL_DIR)/clock_pll.c \
			$(LOCAL_DIR)/clock_lib2.c \
			$(LOCAL_DIR)/uart_dm.c \
			$(LOCAL_DIR)/board.c \
			$(LOCAL_DIR)/spmi.c \
			$(LOCAL_DIR)/bam.c \
			$(LOCAL_DIR)/scm.c \
			$(LOCAL_DIR)/qseecom_lk.c \
			$(LOCAL_DIR)/dev_tree.c \
			$(LOCAL_DIR)/gpio.c \
			$(LOCAL_DIR)/spi_qup.c \
			$(LOCAL_DIR)/mdss_spi.c \
			$(LOCAL_DIR)/dload_util.c \
			$(LOCAL_DIR)/shutdown_detect.c \
			$(LOCAL_DIR)/certificate.c \
			$(LOCAL_DIR)/image_verify.c \
			$(LOCAL_DIR)/crypto_hash.c \
			$(LOCAL_DIR)/crypto5_eng.c \
			$(LOCAL_DIR)/crypto5_wrapper.c \
			$(LOCAL_DIR)/mdp5.c \
			$(LOCAL_DIR)/display.c \
			$(LOCAL_DIR)/mipi_dsi.c \
			$(LOCAL_DIR)/mipi_dsc.c \
			$(LOCAL_DIR)/mipi_dsi_phy.c \
			$(LOCAL_DIR)/mipi_dsi_autopll.c \
			$(LOCAL_DIR)/mipi_dsi_autopll_12nm.c
endif

ifeq ($(PLATFORM),msm8953)
GLOBAL_DEFINES += DISPLAY_TYPE_MDSS=1
	MODULE_SRCS += $(LOCAL_DIR)/qgic.c \
			$(LOCAL_DIR)/qtimer.c \
			$(LOCAL_DIR)/qtimer_mmap.c \
			$(LOCAL_DIR)/interrupts.c \
			$(LOCAL_DIR)/clock.c \
			$(LOCAL_DIR)/clock_pll.c \
			$(LOCAL_DIR)/clock_lib2.c \
			$(LOCAL_DIR)/uart_dm.c \
			$(LOCAL_DIR)/board.c \
			$(LOCAL_DIR)/spmi.c \
			$(LOCAL_DIR)/bam.c \
			$(LOCAL_DIR)/scm.c \
			$(LOCAL_DIR)/qseecom_lk.c \
			$(LOCAL_DIR)/dev_tree.c \
			$(LOCAL_DIR)/gpio.c \
			$(LOCAL_DIR)/dload_util.c \
			$(LOCAL_DIR)/shutdown_detect.c \
			$(LOCAL_DIR)/certificate.c \
			$(LOCAL_DIR)/image_verify.c \
			$(LOCAL_DIR)/crypto_hash.c \
			$(LOCAL_DIR)/crypto5_eng.c \
			$(LOCAL_DIR)/qmp_usb30_phy.c \
			$(LOCAL_DIR)/qusb2_phy.c \
			$(LOCAL_DIR)/crypto5_wrapper.c \
			$(LOCAL_DIR)/mdp5.c \
			$(LOCAL_DIR)/display.c \
			$(LOCAL_DIR)/mipi_dsi.c \
			$(LOCAL_DIR)/mipi_dsc.c \
			$(LOCAL_DIR)/mipi_dsi_phy.c \
			$(LOCAL_DIR)/mipi_dsi_autopll_thulium.c
endif

ifneq ($(filter DEVICE_TREE=1, $(DEFINES)),)
# Add dev_tree.c if it is not already there
MODULE_SRCS += $(if $(filter $(LOCAL_DIR)/dev_tree.c,$(MODULE_SRCS)),,$(LOCAL_DIR)/dev_tree.c)
MODULES += lib/libfdt
endif

ifeq ($(ENABLE_BOOT_CONFIG_SUPPORT), 1)
	GLOBAL_DEFINES += BOOT_CONFIG_SUPPORT=1
	MODULE_SRCS += \
		$(LOCAL_DIR)/boot_device.c
endif

ifeq ($(ENABLE_USB30_SUPPORT),1)
	MODULE_SRCS += \
		$(LOCAL_DIR)/usb30_dwc.c \
		$(LOCAL_DIR)/usb30_dwc_hw.c \
		$(LOCAL_DIR)/usb30_udc.c \
		$(LOCAL_DIR)/usb30_wrapper.c
endif

ifeq ($(ENABLE_PARTIAL_GOODS_SUPPORT), 1)
	MODULE_SRCS += $(LOCAL_DIR)/partial_goods.c
endif

ifeq ($(ENABLE_REBOOT_MODULE), 1)
	MODULE_SRCS += $(LOCAL_DIR)/reboot.c
endif

# Default to libufdt for DTBOs if device tree is enabled
DTBO_BACKEND ?= $(if $(filter $(DEFINES), DEVICE_TREE=1),libufdt,none)
ifeq ($(DTBO_BACKEND), libufdt)
MODULES += lib/libufdt
else ifeq ($(DTBO_BACKEND), libfdt)
MODULES += lib/libfdt
else ifeq ($(DTBO_BACKEND), none)
GLOBAL_DEFINES += DTBO_DISABLED=1
else
$(error Unknown DTBO backend: $(DTBO_BACKEND))
endif

# CRYPTO_SW_BACKEND ?= openssl
# ifeq ($(CRYPTO_SW_BACKEND), openssl)
# MODULES += external/lib/openssl
# else ifeq ($(CRYPTO_SW_BACKEND), none)
# ifneq ($(SIGNED_KERNEL)$(VERIFIED_BOOT)$(VERIFIED_BOOT_2),)
# $(error Crypto software backend is required for secure boot)
# endif
# OBJS := $(filter-out $(LOCAL_DIR)/image_verify.c, $(OBJS))
# else
# $(error Unknown crypto software backend: $(CRYPTO_SW_BACKEND))
# endif

ifneq ($(filter MDP4=1, $(DEFINES)),)
ifeq ($(ENABLE_DISPLAY), 0)
MODULES := $(filter-out dev/panel/msm, $(MODULES))
DISPLAY_SOURCES := \
	$(LOCAL_DIR)/display.c \
	$(LOCAL_DIR)/hdmi.c \
	$(LOCAL_DIR)/lcdc.c \
	$(LOCAL_DIR)/lvds.c \
	$(LOCAL_DIR)/mddi.c \
	$(LOCAL_DIR)/mdp_lcdc.c \
	$(LOCAL_DIR)/mdp4.c \
	$(LOCAL_DIR)/mipi_dsi.c \
	$(LOCAL_DIR)/mipi_dsi_phy.c \
	platform/$(PLATFORM)/hdmi_core.c \
	platform/$(PLATFORM)/panel%.c \
	target/$(TARGET)/target_display.c
MODULE_SRCS := $(filter-out $(DISPLAY_SOURCES), $(MODULE_SRCS))
else
$(error Display support in $(TARGET) is currently broken)
endif
endif

ifeq ($(ENABLE_RPMB_SUPPORT), 1)
include platform/msm_shared/rpmb/rules.mk
endif

ifeq ($(VERIFIED_BOOT_2), 1)
MODULE_SRCS += platform/msm_shared/boot_verifier.c
include platform/msm_shared/avb/rules.mk
endif
