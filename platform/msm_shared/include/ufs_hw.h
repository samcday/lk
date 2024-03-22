/* Copyright (c) 2013, The Linux Foundation. All rights reserved.
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

#ifndef _UFS_HW_H_
#define _UFS_HW_H_

#include <lk/bits.h>

#define UFS_CAP(_base)                             (_base + 0x00000000)
#define UFS_VER(_base)                             (_base + 0x00000008)
#define UFS_HCDDID(_base)                          (_base + 0x00000010)
#define UFS_HCPMID(_base)                          (_base + 0x00000014)
#define UFS_IS(_base)                              (_base + 0x00000020)
#define UFS_IE(_base)                              (_base + 0x00000024)
#define UFS_HCS(_base)                             (_base + 0x00000030)
#define UFS_HCE(_base)                             (_base + 0x00000034)
#define UFS_UECPA(_base)                           (_base + 0x00000038)
#define UFS_UECDL(_base)                           (_base + 0x0000003C)
#define UFS_UECN(_base)                            (_base + 0x00000040)
#define UFS_UECT(_base)                            (_base + 0x00000044)
#define UFS_UECDME(_base)                          (_base + 0x00000048)
#define UFS_UTRIACR(_base)                         (_base + 0x0000004C)
#define UFS_UTRLBA(_base)                          (_base + 0x00000050)
#define UFS_UTRLBAU(_base)                         (_base + 0x00000054)
#define UFS_UTRLDBR(_base)                         (_base + 0x00000058)
#define UFS_UTRLCLR(_base)                         (_base + 0x0000005C)
#define UFS_UTRLRSR(_base)                         (_base + 0x00000060)
#define UFS_UTMRLBA(_base)                         (_base + 0x00000070)
#define UFS_UTMRLBAU(_base)                        (_base + 0x00000074)
#define UFS_UTMRLRSR(_base)                        (_base + 0x00000080)
#define UFS_UICCMD(_base)                          (_base + 0x00000090)
#define UFS_UICCMDARG1(_base)                      (_base + 0x00000094)
#define UFS_UICCMDARG2(_base)                      (_base + 0x00000098)
#define UFS_UICCMDARG3(_base)                      (_base + 0x0000009C)
#define UFS_SYS1CLK_1US(_base)                     (_base + 0x000000C0)
#define UFS_TX_SYMBOL_CLK_NS_US(_base)             (_base + 0x000000C4)
#define UFS_REG_PA_LINK_STARTUP_TIMER(_base)       (_base + 0x000000D8)
#define UFS_CFG1(_base)                            (_base + 0x000000DC)

#define UFS_CFG1_PHY_SOFT_RESET             MSM8916_BIT(0)

/* Bit field of UFSHCI_HCS register */
#define UFS_HCS_DP                          MSM8916_BIT(0)
#define UFS_HCS_UTRLRDY                     MSM8916_BIT(1)
#define UFS_HCS_UTMRLRDY                    MSM8916_BIT(2)
#define UFS_HCS_UCRDY                       MSM8916_BIT(3)

/* Bit field of UFSHCI_IE register */
#define UFS_IE_UTRCE                        MSM8916_BIT(0)
#define UFS_IE_UDEPRIU                      MSM8916_BIT(1)
#define UFS_IE_UEE                          MSM8916_BIT(2)
#define UFS_IE_UTMSE                        MSM8916_BIT(3)
#define UFS_IE_UPMSE                        MSM8916_BIT(4)
#define UFS_IE_UHXSE                        MSM8916_BIT(5)
#define UFS_IE_UHESE                        MSM8916_BIT(6)
#define UFS_IE_ULLSE                        MSM8916_BIT(7)
#define UFS_IE_ULSSE                        MSM8916_BIT(8)
#define UFS_IE_UTMRCE                       MSM8916_BIT(9)
#define UFS_IE_UCCE                         MSM8916_BIT(10)
#define UFS_IE_DFEE                         MSM8916_BIT(11)
#define UFS_IE_UTPEE                        MSM8916_BIT(12)
#define UFS_IE_HCFEE                        MSM8916_BIT(16)
#define UFS_IE_SBFEE                        MSM8916_BIT(17)

/* Bit field of UFSHCI_IS register */
#define UFS_IS_UTRCS                        MSM8916_BIT(0)
#define UFS_IS_UDEPRI                       MSM8916_BIT(1)
#define UFS_IS_UE                           MSM8916_BIT(2)
#define UFS_IS_UTMS                         MSM8916_BIT(3)
#define UFS_IS_UPMS                         MSM8916_BIT(4)
#define UFS_IS_UHXS                         MSM8916_BIT(5)
#define UFS_IS_UHES                         MSM8916_BIT(6)
#define UFS_IS_ULLS                         MSM8916_BIT(7)
#define UFS_IS_ULSS                         MSM8916_BIT(8)
#define UFS_IS_UTMRCS                       MSM8916_BIT(9)
#define UFS_IS_UCCS                         MSM8916_BIT(10)
#define UFS_IS_DFES                         MSM8916_BIT(11)
#define UFS_IS_UTPES                        MSM8916_BIT(12)
#define UFS_IS_HCFES                        MSM8916_BIT(16)
#define UFS_IS_SBFES                        MSM8916_BIT(17)

/* Bit field for UIC Error decode */
#define UFS_IS_UECPA                        MSM8916_BIT(31)
#define UFS_IS_UECDL                        MSM8916_BIT(31)

/* Bit field for UFS_HCE register. */
#define UFS_HCE_ENABLE                      MSM8916_BIT(0)

#endif
