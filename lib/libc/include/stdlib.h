/*
 * Copyright (c) 2008-2014 Travis Geiselbrecht
 *
 * Use of this source code is governed by a MIT-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/MIT
 */
#pragma once

#include <lk/compiler.h>
#include <sys/types.h>
#include <stddef.h>
#include <malloc.h>
#include <endian.h>
#include <rand.h>
#include <arch/defines.h>

__BEGIN_CDECLS

int atoi(const char *num);
double atof(const char *num);
unsigned int atoui(const char *num);
long atol(const char *num);
unsigned long atoul(const char *num);
unsigned long long atoull(const char *num);

long strtol(const char *nptr, char **endptr, int base);
long long strtoll(const char *nptr, char **endptr, int base);

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define ROUNDUP(a, b) (((a) + ((b)-1)) & ~((b)-1))
#define ROUNDDOWN(a, b) ((a) & ~((b)-1))

#define ALIGN(a, b) ROUNDUP(a, b)
#define IS_ALIGNED(a, b) (!(((uintptr_t)(a)) & (((uintptr_t)(b))-1)))

/* allocate a buffer on the stack aligned and padded to the cpu's cache line size */
#define STACKBUF_DMA_ALIGN(var, size) \
    uint8_t var[ROUNDUP(size, CACHE_LINE)] __ALIGNED(CACHE_LINE);
void abort(void) __attribute__((noreturn));
void qsort(void *aa, size_t n, size_t es, int (*cmp)(const void *, const void *));
void *bsearch(const void *key, const void *base, size_t num_elems, size_t size,
              int (*compare)(const void *, const void *));
unsigned long int strtoul(const char *nptr, char **endptr, int base);
char *getenv(const char *name);
int atexit(void (*func)(void));

__END_CDECLS


// +MSM8916 HACK+
void        strrev(unsigned char *str); 
int itoa(int num, unsigned char* str, int len, int base);
unsigned gcd(unsigned m, unsigned n);
unsigned lcm(unsigned m, unsigned n);

#define ROUNDUP(a, b) (((a) + ((b)-1)) & ~((b)-1))
#define ROUNDDOWN(a, b) ((a) & ~((b)-1))

/* Macro returns UINT_MAX in case of overflow */
#define ROUND_TO_PAGE(x,y) ((ROUNDUP((x),((y)+1)) < (x))?UINT_MAX:ROUNDUP((x),((y)+1)))

/* Macro to allocate buffer in both local & global space, the STACKBUF_DMA_ALIGN cannot
 * be used for global space.
 * If we use STACKBUF_DMA_ALIGN 'C' compiler throws the error "Initializer element
 * is not constant", since global variable need to be initialized with a constant value.
 */
#define BUF_DMA_ALIGN(var, size) \
	static uint8_t var[ROUNDUP(size, CACHE_LINE)] __attribute__((aligned(CACHE_LINE)));
// -MSM8916 HACK-
