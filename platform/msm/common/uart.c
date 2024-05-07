/* Copyright (c) 2010-2012, 2014, The Linux Foundation. All rights reserved.
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

#include <string.h>
#include <stdlib.h>
#include <kernel/thread.h>
#include <lk/debug.h>
#include <lk/reg.h>
#include <lk/utils.h>
#include <sys/types.h>
#include <platform/iomap.h>
#include <platform/irqs.h>
#include <platform/interrupts.h>
#include <platform/clock.h>
#include <platform/gpio.h>
#include <uart_dm.h>
#include <arch/arm.h>

/* Note:
 * This is a basic implementation of UART_DM protocol. More focus has been
 * given on simplicity than efficiency. Few of the things to be noted are:
 * - RX path may not be suitable for multi-threaded scenaraio because of the
 *   use of static variables. TX path shouldn't have any problem though. If
 *   multi-threaded support is required, a simple data-structure can
 *   be maintained for each thread.
 * - Right now we are using polling method than interrupt based.
 * - We are using legacy UART protocol without Data Mover.
 * - Not all interrupts and error events are handled.
 * - While waiting Watchdog hasn't been taken into consideration.
 */

#define NON_PRINTABLE_ASCII_CHAR      128

static uint8_t pack_chars_into_words(uint8_t *buffer, uint8_t cnt, uint32_t *word)
{
	uint8_t num_chars_writtten = 0;

	*word = 0;

	 for(int j=0; j < cnt; j++)
	 {
		 if (buffer[num_chars_writtten] == '\n')
		 {
			/* replace '\n' by the NON_PRINTABLE_ASCII_CHAR and print '\r'.
			 * While printing the NON_PRINTABLE_ASCII_CHAR, we will print '\n'.
			 * Thus successfully replacing '\n' by '\r' '\n'.
			 */
			*word |= ('\r' & 0xff) << (j * 8);
			buffer[num_chars_writtten] = NON_PRINTABLE_ASCII_CHAR;
		 }
		 else
		 {
			if (buffer[num_chars_writtten] == NON_PRINTABLE_ASCII_CHAR)
			{
				buffer[num_chars_writtten] = '\n';
			}

			 *word |= (buffer[num_chars_writtten] & 0xff) << (j * 8);

			 num_chars_writtten++;
		 }
	 }

	 return num_chars_writtten;
}

/* Static Function Prototype Declarations */
static unsigned int msm_boot_uart_calculate_num_chars_to_write(char *data_in,
							       uint32_t *num_of_chars);
static unsigned int msm_boot_uart_dm_init(uint32_t base);
static unsigned int msm_boot_uart_dm_read(uint32_t base,
	unsigned int *data, int wait);
static unsigned int msm_boot_uart_dm_write(uint32_t base, char *data,
	unsigned int num_of_chars);
static unsigned int msm_boot_uart_dm_init_rx_transfer(uint32_t base);
static unsigned int msm_boot_uart_dm_reset(uint32_t base);

/* Keep track of uart block vs port mapping.
 */
static uint32_t port_lookup[4];

/*
 * Helper function to keep track of Line Feed char "\n" with
 * Carriage Return "\r\n".
 */
static unsigned int
msm_boot_uart_calculate_num_chars_to_write(char *data_in,
				uint32_t *num_of_chars)
{
	uint32_t i = 0, j = 0;

	if ((data_in == NULL)) {
		return MSM_BOOT_UART_DM_E_INVAL;
	}

	for (i = 0, j = 0; i < *num_of_chars; i++, j++) {
		if (data_in[i] == '\n') {
			j++;
		}

	}

	*num_of_chars = j;

	return MSM_BOOT_UART_DM_E_SUCCESS;
}

/*
 * Initialize Receive Path
 */
static unsigned int msm_boot_uart_dm_init_rx_transfer(uint32_t uart_dm_base)
{
	writel(MSM_BOOT_UART_DM_GCMD_DIS_STALE_EVT, MSM_BOOT_UART_DM_CR(uart_dm_base));
	writel(MSM_BOOT_UART_DM_CMD_RES_STALE_INT, MSM_BOOT_UART_DM_CR(uart_dm_base));
	writel(MSM_BOOT_UART_DM_DMRX_DEF_VALUE, MSM_BOOT_UART_DM_DMRX(uart_dm_base));
	writel(MSM_BOOT_UART_DM_GCMD_ENA_STALE_EVT, MSM_BOOT_UART_DM_CR(uart_dm_base));

	return MSM_BOOT_UART_DM_E_SUCCESS;
}

/*
 * UART Receive operation
 * Reads a word from the RX FIFO.
 */
static unsigned int
msm_boot_uart_dm_read(uint32_t base, unsigned int *data, int wait)
{
    unsigned int sr;
    unsigned int count;

    if (data == NULL) {
        return MSM_BOOT_UART_DM_E_INVAL;
    }

    /* Check for Overrun error. We'll just reset Error Status */
    if (readl(MSM_BOOT_UART_DM_SR(base)) & MSM_BOOT_UART_DM_SR_UART_OVERRUN) {
        writel(MSM_BOOT_UART_DM_CMD_RESET_ERR_STAT, MSM_BOOT_UART_DM_CR(base));
    }

    sr = readl(MSM_BOOT_UART_DM_SR(base));
    if (sr & MSM_BOOT_UART_DM_SR_RXRDY) {
        /* There are at least 4 bytes in fifo */
        *data = readl(MSM_BOOT_UART_DM_RF(base, 0));
    } else {
        /* Check if there is anything in fifo */
        count = readl(MSM_BOOT_UART_DM_RXFS(base)) >> 0x7 & 0x7;
        if (!count) {
            return MSM_BOOT_UART_DM_E_RX_NOT_READY;
        }
        /* There is at least one character, move it to fifo */
        writel(MSM_BOOT_UART_DM_GCMD_SW_FORCE_STALE, MSM_BOOT_UART_DM_CR(base));
        *data = readl(MSM_BOOT_UART_DM_RF(base, 0));
        writel(MSM_BOOT_UART_DM_GCMD_RESET_STALE_INT, MSM_BOOT_UART_DM_CR(base));
        writel(0x7, MSM_BOOT_UART_DM_DMRX(base));
    }

    return MSM_BOOT_UART_DM_E_SUCCESS;
}

/*
 * UART transmit operation
 */
static unsigned int
msm_boot_uart_dm_write(uint32_t base, char *data, unsigned int num_of_chars)
{
	unsigned int tx_word_count = 0;
	unsigned int tx_char_left = 0, tx_char = 0;
	unsigned int tx_word = 0;
	int i = 0;
	char *tx_data = NULL;
	uint8_t num_chars_written;

	if ((data == NULL) || (num_of_chars <= 0)) {
		return MSM_BOOT_UART_DM_E_INVAL;
	}

	msm_boot_uart_calculate_num_chars_to_write(data, &num_of_chars);

	tx_data = data;

	/* Write to NO_CHARS_FOR_TX register number of characters
	 * to be transmitted. However, before writing TX_FIFO must
	 * be empty as indicated by TX_READY interrupt in IMR register
	 */

	/* Check if transmit FIFO is empty.
	 * If not we'll wait for TX_READY interrupt. */
	if (!(readl(MSM_BOOT_UART_DM_SR(base)) & MSM_BOOT_UART_DM_SR_TXEMT)) {
		while (!(readl(MSM_BOOT_UART_DM_ISR(base)) & MSM_BOOT_UART_DM_TX_READY)) {
            // TODO(msm8916): shouldn't be using debug spin here I think. What else?
            spin(1);
			/* Kick watchdog? */
		}
	}

	//We need to make sure the DM_NO_CHARS_FOR_TX&DM_TF are are programmed atmoically.
	THREAD_LOCK(state);
	/* We are here. FIFO is ready to be written. */
	/* Write number of characters to be written */
	writel(num_of_chars, MSM_BOOT_UART_DM_NO_CHARS_FOR_TX(base));

	/* Clear TX_READY interrupt */
	writel(MSM_BOOT_UART_DM_GCMD_RES_TX_RDY_INT, MSM_BOOT_UART_DM_CR(base));

	/* We use four-character word FIFO. So we need to divide data into
	 * four characters and write in UART_DM_TF register */
	tx_word_count = (num_of_chars % 4) ? ((num_of_chars / 4) + 1) :
	    (num_of_chars / 4);
	tx_char_left = num_of_chars;

	for (i = 0; i < (int)tx_word_count; i++) {
		tx_char = (tx_char_left < 4) ? tx_char_left : 4;
		num_chars_written = pack_chars_into_words((uint8_t *)tx_data, tx_char, &tx_word);

		/* Wait till TX FIFO has space */
		while (!(readl(MSM_BOOT_UART_DM_SR(base)) & MSM_BOOT_UART_DM_SR_TXRDY)) {
            // TODO(msm8916): shouldn't be using debug spin here I think. What else?
            spin(1);
		}

		/* TX FIFO has space. Write the chars */
		writel(tx_word, MSM_BOOT_UART_DM_TF(base, 0));
		tx_char_left = num_of_chars - (i + 1) * 4;
		tx_data = tx_data + num_chars_written;
	}
	THREAD_UNLOCK(state);

	return MSM_BOOT_UART_DM_E_SUCCESS;
}


/* Configure UART clock based on the UART block id*/
static void clock_config_uart_dm(uint8_t id)
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

/* Defining functions that's exposed to outside world and in coformance to
 * existing uart implemention. These functions are being called to initialize
 * UART and print debug messages in bootloader.
 */
void uart_dm_init(uint8_t id, uint32_t uart_dm_base)
{
	static uint8_t port = 0;

	/* Configure the uart clock */
	clock_config_uart_dm(id);
	DSB;

	/* Configure GPIO to provide connectivity between UART block
	   product ports and chip pads */
	gpio_config_uart_dm(id);
	DSB;

	/* Configure clock selection register for tx and rx rates.
	 * Selecting 115.2k for both RX and TX.
	 */
	writel(UART_DM_CLK_RX_TX_BIT_RATE, MSM_BOOT_UART_DM_CSR(uart_dm_base));
	DSB;

    /* Enable RS232 flow control to support RS232 db9 connector */
    writel(1 << 7, MSM_BOOT_UART_DM_MR1(uart_dm_base));
    /* 8-N-1 configuration: 8 data bits - No parity - 1 stop bit */
    writel(MSM_BOOT_UART_DM_8_N_1_MODE, MSM_BOOT_UART_DM_MR2(uart_dm_base));

    writel(MSM_BOOT_UART_DM_CMD_RESET_RX, MSM_BOOT_UART_DM_CR(uart_dm_base));
    writel(MSM_BOOT_UART_DM_CMD_RESET_TX, MSM_BOOT_UART_DM_CR(uart_dm_base));

	ASSERT(port < ARRAY_SIZE(port_lookup));
	port_lookup[port++] = uart_dm_base;
}

/* UART_DM uses four character word FIFO where as UART core
 * uses a character FIFO. so it's really inefficient to try
 * to write single character. But that's how dprintf has been
 * implemented.
 */
int uart_putc(int port, char c)
{
	uint32_t uart_base = port_lookup[port];

	msm_boot_uart_dm_write(uart_base, &c, 1);

	return 0;
}

/* UART_DM uses four character word FIFO whereas uart_getc
 * is supposed to read only one character. So we need to
 * read a word and keep track of each character in the word.
 */
int uart_getc(int port, bool wait)
{
	int byte;
	static unsigned int word = 0;
	uint32_t uart_base = port_lookup[port];

	if (!word) {
		/* Read from FIFO only if it's a first read or all the four
		 * characters out of a word have been read */
		if (msm_boot_uart_dm_read(uart_base, &word, wait) != MSM_BOOT_UART_DM_E_SUCCESS) {
			return -1;
		}

	}

	byte = (int)word & 0xff;
	word = word >> 8;

	return byte;
}
