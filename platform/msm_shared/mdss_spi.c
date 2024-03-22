/* Copyright (c) 2017-2018, 2020,  The Linux Foundation. All rights reserved.
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
 *
 */

#include <spi_qup.h>
#include <msm_panel.h>
#include <target/display.h>
#include <platform/gpio.h>
#include <dev/gpio.h>
#include <platform/timer.h>
#include "mdss_spi.h"

#define SUCCESS           0
#define FAIL              1

static struct qup_spi_dev *dev = NULL;

#if QM215_MDSS_SPI
static struct gpio_pin spi_dc_gpio = {
  "msmgpio", 64, 3, 1, 0, 1
};

#define SPI_BLSP_ID                  1
#define SPI_QUP_ID                   2
#endif
static int mdss_spi_write_cmd(const unsigned char *buf)
{
	int ret = 0;

	if (!dev) {
		dprintf(CRITICAL, "SPI has not been initialized\n");
		return -ENODEV;
	}

	dev->bytes_per_word = 1;
	dev->bit_shift_en = 1;

	gpio_set(spi_dc_gpio.pin_id, 0);
	ret = spi_qup_write(dev, buf, 1);
	gpio_set(spi_dc_gpio.pin_id, 2);
	if (ret)
		dprintf(CRITICAL, "Send SPI command to panel failed\n");

	return ret;
}

static int mdss_spi_write_data(const unsigned char *buf, size_t len)
{
	int ret = 0;

	if (!dev) {
		dprintf(CRITICAL, "SPI has not been initialized\n");
		return -ENODEV;
	}

	dev->bytes_per_word = 1;
	dev->bit_shift_en = 1;

	gpio_set(spi_dc_gpio.pin_id, 2);
	ret = spi_qup_write(dev, buf, len);
	if (ret)
		dprintf(CRITICAL, "Send SPI parameters to panel failed\n");

	return ret;
}

static int mdss_spi_write_frame(const unsigned char *buf, size_t len)
{
	int ret = 0;

	if (!dev) {
		dprintf(CRITICAL, "SPI has not been initialized\n");
		return -ENODEV;
	}

	dev->bytes_per_word = 2;
	dev->bit_shift_en = 1;
	dev->unpack_en = 0;

	gpio_set(spi_dc_gpio.pin_id, 2);
	ret = spi_qup_write(dev, buf, len);

	return ret;
}

void spi_read_panel_data(unsigned char *buf,  int len)
{
	int ret = 0;

	if (!dev) {
		dprintf(CRITICAL, "SPI has not been initialized\n");
		return;
	}
	dev->bytes_per_word = 1;
	dev->bit_shift_en = 1;

	gpio_set(spi_dc_gpio.pin_id, 0);
	ret = spi_qup_read(dev, buf, len);
	gpio_set(spi_dc_gpio.pin_id, 2);

	if (ret)
		dprintf(CRITICAL, "Send SPI command to panel failed\n");

	return;
}

int spi_check_panel_id(struct msm_panel_info *pinfo)
{
	int i = 0;
	int len;
	int ret = SUCCESS;
	unsigned char *buf;

	if (!pinfo->spi.signature || !pinfo->spi.signature_len)
		return ret;

	len = pinfo->spi.signature_len;
	buf = (unsigned char*) malloc(len + 1);

	mdss_spi_write_cmd(pinfo->spi.signature_addr);
	spi_read_panel_data(buf, len + 1);

	for (i = 0; i < len; i++) {
		/* left shift a bit to match SPI panel timming */
		if(pinfo->spi.signature[i] !=
			 (((buf[i] << 1) | (buf[i + 1] >> 7)) & 0xFF)) {
			ret = FAIL;
			break;
		}
	}

	free(buf);
	return ret;
}

int mdss_spi_init(void)
{
	if (!dev) {
		dev = qup_blsp_spi_init(SPI_BLSP_ID, SPI_QUP_ID);
		if (!dev) {
			dprintf(CRITICAL, "Failed initializing SPI\n");
			return -ENODEV;
		}
	}

	gpio_tlmm_config(spi_dc_gpio.pin_id, 0, spi_dc_gpio.pin_direction,
				spi_dc_gpio.pin_pull, spi_dc_gpio.pin_strength,
				spi_dc_gpio.pin_state);
	return SUCCESS;

}

int mdss_spi_panel_init(struct msm_panel_info *pinfo)
{
	int cmd_count = 0;

	while (cmd_count < pinfo->spi.num_of_panel_cmds) {

		if (pinfo->spi.panel_cmds[cmd_count].cmds_post_tg){
			cmd_count ++;
			continue;
		}

		mdss_spi_write_cmd((unsigned char *) pinfo->spi.panel_cmds[cmd_count].payload);
		if (pinfo->spi.panel_cmds[cmd_count].size > 1)
			mdss_spi_write_data(
				(unsigned char *) pinfo->spi.panel_cmds[cmd_count].payload + 1,
				pinfo->spi.panel_cmds[cmd_count].size - 1);

		if (pinfo->spi.panel_cmds[cmd_count].wait)
			mdelay(pinfo->spi.panel_cmds[cmd_count].wait);

		cmd_count ++;
	}

	return SUCCESS;
}

int mdss_spi_on(struct msm_panel_info *pinfo, struct fbcon_config *fb)
{
	int buf_size = 0;
	int ret = 0;

	buf_size =  fb->width * fb->height * (fb->bpp / 8);
	ret = mdss_spi_write_frame(fb->base, buf_size);
	if (ret)
		dprintf(CRITICAL, "Send SPI frame data to panel failed\n");

	return ret;
}

int mdss_spi_cmd_post_on(struct msm_panel_info *pinfo)
{
	int cmd_count = 0;
	char *payload;

	if (!dev) {
		dprintf(CRITICAL, "SPI has not been initialized\n");
		return -ENODEV;
	}

	while (cmd_count < pinfo->spi.num_of_panel_cmds) {
		if (pinfo->spi.panel_cmds[cmd_count].cmds_post_tg) {
			payload = pinfo->spi.panel_cmds[cmd_count].payload;
			mdss_spi_write_cmd((unsigned char *) payload);
			if (pinfo->spi.panel_cmds[cmd_count].size > 1)
				mdss_spi_write_data((unsigned char *) payload + 1,
					pinfo->spi.panel_cmds[cmd_count].size
						- 1);

			if (pinfo->spi.panel_cmds[cmd_count].wait)
				mdelay(pinfo->spi.panel_cmds[cmd_count].wait);
		}

		cmd_count ++;
	}

	return SUCCESS;
}
