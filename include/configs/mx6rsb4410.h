/*
 * Copyright (C) 2012 Freescale Semiconductor, Inc.
 * Copyright 2017-2018 NXP
 *
 * Configuration settings for the Freescale i.MX6Q SabreSD board.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __MX6SABRESD_CONFIG_H
#define __MX6SABRESD_CONFIG_H

#ifdef CONFIG_SPL
#include "imx6_spl_advantech.h"
#endif

#define CONFIG_MACH_TYPE	3980
#define CONFIG_MXC_UART_BASE	UART1_BASE
#define CONSOLE_DEV		"ttymxc0"
#define CONFIG_MMCROOT			"/dev/mmcblk0p2"  /* SDHC3 */

#if defined(CONFIG_DEFAULT_FDT_FILE)
#undef CONFIG_DEFAULT_FDT_FILE
#endif

#if defined(CONFIG_TARGET_MX6QRSB4410A1_512M) || defined(CONFIG_TARGET_MX6QRSB4410A2_512M)
#define PHYS_SDRAM_SIZE         (512u * 1024 * 1024)
#elif defined(CONFIG_TARGET_MX6QRSB4410A1_1G) || defined(CONFIG_TARGET_MX6QRSB4410A2_1G)
#define PHYS_SDRAM_SIZE         (1u * 1024 * 1024 * 1024)
#elif defined(CONFIG_TARGET_MX6QRSB4410A1_2G) || defined(CONFIG_TARGET_MX6QRSB4410A2_2G)
#define PHYS_SDRAM_SIZE         (2u * 1024 * 1024 * 1024)
#endif

#if defined(CONFIG_TARGET_MX6QRSB4410A1_1G)
#if defined(CONFIG_MX6QP)
#define CONFIG_DEFAULT_FDT_FILE	"imx6qp-rsb4410-a1.dtb"
#elif defined(CONFIG_MX6Q)
#define CONFIG_DEFAULT_FDT_FILE	"imx6q-rsb4410-a1.dtb"
#elif defined(CONFIG_MX6DL)
#define CONFIG_DEFAULT_FDT_FILE	"imx6dl-rsb4410-a1.dtb"
#elif defined(CONFIG_MX6S)
#define CONFIG_DEFAULT_FDT_FILE	"imx6dl-rsb4410-a1.dtb"
#endif
#elif defined(CONFIG_TARGET_MX6QRSB4410A2_1G)
#if defined(CONFIG_MX6QP)
#define CONFIG_DEFAULT_FDT_FILE "imx6qp-rsb4410-a2.dtb"
#elif defined(CONFIG_MX6Q)
#define CONFIG_DEFAULT_FDT_FILE "imx6q-rsb4410-a2.dtb"
#elif defined(CONFIG_MX6DL)
#define CONFIG_DEFAULT_FDT_FILE "imx6dl-rsb4410-a2.dtb"
#elif defined(CONFIG_MX6S)
#define CONFIG_DEFAULT_FDT_FILE "imx6dl-rsb4410-a2.dtb"
#endif
#endif

#include "mx6advantech_common.h"
/* don't use pmic */
#undef CONFIG_LDO_BYPASS_CHECK

/* Falcon Mode */
#define CONFIG_SPL_FS_LOAD_ARGS_NAME	"args"
#define CONFIG_SPL_FS_LOAD_KERNEL_NAME	"uImage"
#define CONFIG_SYS_SPL_ARGS_ADDR       0x18000000

/* Falcon Mode - MMC support: args@1MB kernel@2MB */
#define CONFIG_SYS_MMCSD_RAW_MODE_ARGS_SECTOR  0x800   /* 1MB */
#define CONFIG_SYS_MMCSD_RAW_MODE_ARGS_SECTORS (CONFIG_CMD_SPL_WRITE_SIZE / 512)
#define CONFIG_SYS_MMCSD_RAW_MODE_KERNEL_SECTOR        0x1000  /* 2MB */

#define CONFIG_SYS_FSL_USDHC_NUM	3
#if defined(CONFIG_ENV_IS_IN_MMC)
#define CONFIG_SYS_MMC_ENV_DEV		1	/* SDHC3 */
#ifndef CONFIG_SYS_MMC_ENV_PART
#define CONFIG_SYS_MMC_ENV_PART                0       /* user partition */
#endif
#endif

#ifdef CONFIG_CMD_SF
#define CONFIG_SF_DEFAULT_CS   0
#endif

/*
 * imx6 q/dl/solo pcie would be failed to work properly in kernel, if
 * the pcie module is iniialized/enumerated both in uboot and linux
 * kernel.
 * rootcause:imx6 q/dl/solo pcie don't have the reset mechanism.
 * it is only be RESET by the POR. So, the pcie module only be
 * initialized/enumerated once in one POR.
 * Set to use pcie in kernel defaultly, mask the pcie config here.
 * Remove the mask freely, if the uboot pcie functions, rather than
 * the kernel's, are required.
 */
#ifdef CONFIG_CMD_PCI
#define CONFIG_PCI_SCAN_SHOW
#define CONFIG_PCIE_IMX
#define CONFIG_PCIE_IMX_PERST_GPIO	IMX_GPIO_NR(7, 12)
#define CONFIG_PCIE_IMX_POWER_GPIO	IMX_GPIO_NR(3, 19)
#endif

/* USB Configs */
#ifdef CONFIG_CMD_USB
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET
#define CONFIG_USB_HOST_ETHER
#define CONFIG_USB_ETHER_ASIX
#define CONFIG_MXC_USB_PORTSC		(PORT_PTS_UTMI | PORT_PTS_PTW)
#define CONFIG_MXC_USB_FLAGS		0
#define CONFIG_USB_MAX_CONTROLLER_COUNT	1 /* Enabled USB controller number */
#endif

/*#define CONFIG_SPLASH_SCREEN*/
/*#define CONFIG_MXC_EPDC*/

/*
 * SPLASH SCREEN Configs
 */
#ifndef CONFIG_ADVANTECH
#if defined(CONFIG_SPLASH_SCREEN) && defined(CONFIG_MXC_EPDC)
	/*
	 * Framebuffer and LCD
	 */
	#define CONFIG_CMD_BMP
	#undef LCD_TEST_PATTERN
	/* #define CONFIG_SPLASH_IS_IN_MMC			1 */
	#define LCD_BPP					LCD_MONOCHROME
	/* #define CONFIG_SPLASH_SCREEN_ALIGN		1 */

	#define CONFIG_WAVEFORM_BUF_SIZE		0x400000
#endif /* CONFIG_SPLASH_SCREEN && CONFIG_MXC_EPDC */
#endif

/* uncomment for SECURE mode support */
/* #define CONFIG_SECURE_BOOT */

#ifdef CONFIG_SECURE_BOOT
#ifndef CONFIG_CSF_SIZE
#define CONFIG_CSF_SIZE 0x4000
#endif
#endif

/* #define CONFIG_MFG_IGNORE_CHECK_SECURE_BOOT */

#define CONFIG_SUPPORT_LVDS
#ifdef CONFIG_SUPPORT_LVDS
#define IOMUX_LCD_BKLT_PWM 	MX6_PAD_GPIO_1__GPIO1_IO01
#define IOMUX_LCD_BKLT_EN	MX6_PAD_KEY_COL0__GPIO4_IO06
#define IOMUX_LCD_VDD_EN	MX6_PAD_KEY_ROW0__GPIO4_IO07
#define LCD_BKLT_PWM 		IMX_GPIO_NR(1, 1)
#define LCD_BKLT_EN 		IMX_GPIO_NR(4, 6)
#define LCD_VDD_EN 		IMX_GPIO_NR(4, 7)	
#endif

#define SPI1_CS0                IMX_GPIO_NR(2,30)
#define IOMUX_SPI_SCLK          MX6_PAD_EIM_D16__ECSPI1_SCLK
#define IOMUX_SPI_MISO          MX6_PAD_EIM_D17__ECSPI1_MISO
#define IOMUX_SPI_MOSI          MX6_PAD_EIM_D18__ECSPI1_MOSI
#define IOMUX_SPI_CS0           MX6_PAD_EIM_EB2__ECSPI1_SS0

#define USDHC2_CD_GPIO          IMX_GPIO_NR(2, 2)
#endif                         /* __MX6SABRESD_CONFIG_H */