/*
 * Copyright (c) 2009, Google Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#pragma once

#include <stdint.h>

typedef struct udc_request udc_request_t;
typedef struct udc_gadget udc_gadget_t;
typedef struct udc_device udc_device_t;

/* endpoints are opaque handles specific to the particular device controller */
typedef struct udc_endpoint udc_endpoint_t;

/* USB Device Controller Transfer Request */
struct udc_request {
    void *buffer;
    unsigned length;
    void (*complete)(udc_request_t *req, unsigned actual, int status);
    void *context;
};

udc_request_t *udc_request_alloc(void);
void udc_request_free(udc_request_t *req);
int udc_request_queue(udc_endpoint_t *ept, udc_request_t *req);
int udc_request_cancel(udc_endpoint_t *ept, udc_request_t *req);

#define UDC_BULK_IN    0x82
#define UDC_BULK_OUT   0x02

udc_endpoint_t *udc_endpoint_alloc(unsigned type, unsigned maxpkt);
void udc_endpoint_free(udc_endpoint_t *ept);

#define UDC_EVENT_ONLINE    1
#define UDC_EVENT_OFFLINE   2

struct udc_gadget {
    void (*notify)(udc_gadget_t *gadget, unsigned event);
    void *context;

    struct udc_gadget *next; // do not modify

    uint8_t ifc_class;
    uint8_t ifc_subclass;
    uint8_t ifc_protocol;
    uint8_t ifc_endpoints;
    const char *ifc_string;
    unsigned flags;

    udc_endpoint_t **ept;
};

struct udc_device {
    uint16_t vendor_id;
    uint16_t product_id;
    uint16_t version_id;

    const char *manufacturer;
    const char *product;
    const char *serialno;
};

int udc_init(udc_device_t *devinfo);
int udc_register_gadget(udc_gadget_t *gadget);
int udc_start(void);
int udc_stop(void);


// +MSM8916 HACK+
#define UDC_TYPE_BULK_IN	1
#define UDC_TYPE_BULK_OUT	2
#define UDC_TYPE_INTR_IN	3
#define UDC_TYPE_INTR_OUT	4

/* these should probably go elsewhere */
#define GET_STATUS           0
#define CLEAR_FEATURE        1
#define SET_FEATURE          3
#define SET_ADDRESS          5
#define GET_DESCRIPTOR       6
#define SET_DESCRIPTOR       7
#define GET_CONFIGURATION    8
#define SET_CONFIGURATION    9
#define GET_INTERFACE        10
#define SET_INTERFACE        11
#define SYNCH_FRAME          12
#define SET_SEL              48
#define SET_ISOCH_DELAY      49

#define TYPE_DEVICE          1
#define TYPE_CONFIGURATION   2
#define TYPE_STRING          3
#define TYPE_INTERFACE       4
#define TYPE_ENDPOINT        5
#define TYPE_DEVICE_QUALIFIER          6
#define TYPE_OTHER_SPEED_CONFIG        7
#define TYPE_BOS             15
#define TYPE_DEVICE_CAP      16
#define TYPE_SS_EP_COMP      48

#define DEVICE_READ          0x80
#define DEVICE_WRITE         0x00
#define INTERFACE_READ       0x81
#define INTERFACE_WRITE      0x01
#define ENDPOINT_READ        0x82
#define ENDPOINT_WRITE       0x02
#define TEST_MODE            0x02

#define TEST_J               0x0100
#define TEST_K               0x0200
#define TEST_SE0_NAK		 0x0300
#define TEST_PACKET          0x0400
#define TEST_FORCE_ENABLE    0x0500

#define PORTSC_PTC           (0xF << 16)
#define PORTSC_PTC_SE0_NAK	 (0x03 << 16)
#define PORTSC_PTC_TST_PKT   (0x4 << 16)

#define USB_EP_NUM_MASK      0x0f
#define USB_EP_DIR_MASK      0x80
#define USB_EP_DIR_IN        0x80

struct setup_packet {
	unsigned char type;
	unsigned char request;
	unsigned short value;
	unsigned short index;
	unsigned short length;
} __attribute__ ((packed));

unsigned ulpi_read(unsigned reg);
void ulpi_write(unsigned val, unsigned reg);

// -MSM8916 HACK-
