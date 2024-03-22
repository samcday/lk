// SPDX-License-Identifier: BSD-3-Clause

#include <lk/debug.h>
#include <lk/err.h>

#include <libfdt.h>
#include <lk2nd/hw/gpio_i2c.h>

status_t gpio_i2c_get(const void *dtb, int node, gpio_i2c_info_t *i, uint8_t *addr)
{
	status_t ret;

	ret = gpiol_get(dtb, node, "i2c-sda", &i->sda, GPIOL_FLAGS_IN);
	if (ret)
		return ret;
	ret = gpiol_get(dtb, node, "i2c-scl", &i->scl, GPIOL_FLAGS_IN);
	if (ret)
		return ret;

	/* Set to ~50 KHz, maybe this should be configurable? */
	i->hcd = 10;
	i->qcd = 5;

	if (addr) {
		const fdt32_t *prop;
		int len;

		prop = fdt_getprop(dtb, node, "i2c-reg", &len);
		if (len != sizeof(*prop)) {
			dprintf(CRITICAL, "Invalid i2c-reg property: %d\n", len);
			return ERR_GENERIC;
		}
		*addr = fdt32_to_cpu(*prop);
	}
	return NO_ERROR;
}
