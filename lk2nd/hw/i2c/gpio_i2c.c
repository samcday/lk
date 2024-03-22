/* vim: set expandtab ts=4 sw=4 tw=100: */
/*
 * Copyright (c) 2013 Google Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <assert.h>
#include <lk/compiler.h>
#include <lk/debug.h>
#include <printf.h>
#include <lk/err.h>

#include <kernel/mutex.h>
#include <platform/timer.h>

#include <lk2nd/hw/gpio_i2c.h>

/******************************************************************************
 *
 * Internal implementation.
 *
 ******************************************************************************/
static inline void send_start(const gpio_i2c_info_t* i)
{
    gpiol_direction_output(i->sda, 0);
    udelay(i->qcd);
    gpiol_direction_output(i->scl, 0);
    udelay(i->hcd);
}

static inline void send_stop(const gpio_i2c_info_t* i)
{
    gpiol_direction_output(i->sda, 0);
    gpiol_direction_input(i->scl);
    udelay(i->qcd);
    gpiol_direction_input(i->sda);
}

static inline void send_restart(const gpio_i2c_info_t* i)
{
    gpiol_direction_input(i->scl);
    udelay(i->qcd);
    send_start(i);
}

static inline void send_nack(const gpio_i2c_info_t* i)
{
    udelay(i->hcd);
    gpiol_direction_input(i->scl);
    udelay(i->hcd);
    gpiol_direction_output(i->scl, 0);
    gpiol_direction_input(i->sda);
    udelay(i->hcd);
}

static inline void send_ack(const gpio_i2c_info_t* i)
{
    gpiol_direction_output(i->sda, 0);
    send_nack(i);
}

static inline bool send_byte(const gpio_i2c_info_t* i, uint32_t b)
{
    bool ret;

    for (size_t j = 0; j < 8; ++j) {
        if (b & 0x80)
            gpiol_direction_input(i->sda);
        else
            gpiol_direction_output(i->sda, 0);
        b <<= 1;
        /* setup time for data (the time between when data becomes stable and
         * clock becomes a stable high) is spec'ed to be 250ns for 100KHz i2c
         * and 100nsec for 400KHz i2c.  If any micro running LK needs to spin
         * here in order to hit that timing, they are welcome to add a spin
         * right here.
         */
        udelay(i->hcd);
        gpiol_direction_input(i->scl);
        udelay(i->hcd);
        gpiol_direction_output(i->scl, 0);
    }

    gpiol_direction_input(i->sda);
    udelay(i->hcd);
    gpiol_direction_input(i->scl);
    udelay(i->hcd);
    ret = (0 == gpiol_is_asserted(i->sda));
    gpiol_direction_output(i->scl, 0);
    udelay(i->hcd);

    return ret;
}

static inline void recv_byte(const gpio_i2c_info_t* i, uint8_t* b)
{
    uint32_t tmp = 0;

    for (size_t j = 0; j < 7; ++j) {
        gpiol_direction_input(i->scl);
        udelay(i->hcd);
        if (gpiol_is_asserted(i->sda))
            tmp |= 1;
        tmp <<= 1;
        gpiol_direction_output(i->scl, 0);
        udelay(i->hcd);
    }

    gpiol_direction_input(i->scl);
    udelay(i->hcd);
    if (gpiol_is_asserted(i->sda))
        tmp |= 1;
    gpiol_direction_output(i->scl, 0);

    *b = (uint8_t)tmp;
}

static status_t gpio_i2c_tx_common(const gpio_i2c_info_t* i,
                                   uint8_t address,
                                   const uint8_t* reg,
                                   const void* buf,
                                   size_t cnt)
{
    status_t ret = ERR_I2C_NACK;

    DEBUG_ASSERT(buf || !cnt);

    enter_critical_section();
    send_start(i);
    if (!send_byte(i, address << 1))
        goto finished;

    if ((NULL != reg) && !send_byte(i, *reg))
        goto finished;

    for (size_t j = 0; j < cnt; ++j)
        if (!send_byte(i, ((const uint8_t*)buf)[j]))
            goto finished;

    ret = NO_ERROR;

finished:
    send_stop(i);
    exit_critical_section();
    return ret;
}

static status_t gpio_i2c_rx_common(const gpio_i2c_info_t* i,
                                   uint8_t address,
                                   const uint8_t* reg,
                                   void* buf,
                                   size_t cnt)
{
    status_t ret = ERR_I2C_NACK;

    DEBUG_ASSERT(buf && cnt);

    address <<= 1;

    enter_critical_section();
    send_start(i);
    if (!send_byte(i, address | (!reg ? 0x1 : 0x0)))
        goto finished;

    if (NULL != reg) {
        if (!send_byte(i, *reg))
            goto finished;

        send_restart(i);

        if (!send_byte(i, address | 0x1))
            goto finished;
    }

    recv_byte(i, buf++);
    for (size_t j = 0; j < (cnt - 1); ++j) {
        send_ack(i);
        recv_byte(i, buf++);
    }
    send_nack(i);
    ret = NO_ERROR;

finished:
    send_stop(i);
    exit_critical_section();
    return ret;
}

/******************************************************************************
*
*  LK facing API
*
* *****************************************************************************/
status_t gpio_i2c_transmit(const gpio_i2c_info_t* i, uint8_t address, const void* buf, size_t cnt)
{
    return gpio_i2c_tx_common(i, address, NULL, buf, cnt);
}

status_t gpio_i2c_receive(const gpio_i2c_info_t* i, uint8_t address, void* buf, size_t cnt)
{
    return gpio_i2c_rx_common(i, address, NULL, buf, cnt);
}

status_t gpio_i2c_write_reg_bytes(const gpio_i2c_info_t* i, uint8_t address, uint8_t reg, const uint8_t* buf, size_t cnt)
{
    return gpio_i2c_tx_common(i, address, &reg, buf, cnt);
}

status_t gpio_i2c_read_reg_bytes(const gpio_i2c_info_t* i, uint8_t address, uint8_t reg, uint8_t* buf, size_t cnt)
{
    return gpio_i2c_rx_common(i, address, &reg, buf, cnt);
}
