/*
 * spi_vamp.c - SPI interface for SD/MMC card driver on SAGA core
 *
 * Copyright (C) 2019 The EmuTOS development team
 *
 * Authors:
 *  Christian Zietz
 *  RFB   Roger Burrows
 *
 * This file is distributed under the GPL, version 2 or at your
 * option any later version.  See doc/license.txt for details.
 */

#include "emutos.h"
#include "spi.h"

#if CONF_WITH_STEJOY_SPI

#define JOY_ADRS_OUTPUT 0xFFFF9202UL
#define JOY_ADRS_INPUT  0xFFFF9201UL

/*
 *  initialise spi for memory card
 */
void spi_initialise(void)
{
    spi_cs_unassert();
}

void spi_clock_sd(void)
{
    ;
}

void spi_clock_mmc(void)
{
    ;
}

void spi_clock_ident(void)
{
    ;
}

/* when we assert or unassert, we send a dummy byte to
 * force a write to the register
 */

static UWORD cs_status = 0;

void spi_cs_assert(void)
{
    cs_status = (UWORD)~6;
    *(volatile UWORD*)(JOY_ADRS_OUTPUT) = cs_status;
}

void spi_cs_unassert(void)
{
    cs_status = (UWORD)~2;
    *(volatile UWORD*)(JOY_ADRS_OUTPUT) = cs_status;
}

void spi_send_byte(UBYTE c)
{
    __asm volatile(
    "ROXL.B #1,%1      | 8  MSB in X\n\t"
    ".REPT 8\n\t"
    "MOVE.W %3,D0      | 4  CS low, CLK low\n\t"
    "ROXL.B #1,D0      | 8  MSB to MOSI\n\t"
    "MOVE.W D0,(%2)    | 8  ... and onto line\n\t"
    "ADDQ   #2,D0      | 4  CLK high\n\t"
    "ROXL.B #1,%1      | 8  MSB in X\n\t"
    "MOVE.W D0,(%2)    | 8  ... and onto line\n\t"
    ".ENDR\n\t" : "=d"(c) : "0"(c), "a"(JOY_ADRS_OUTPUT), "d"(cs_status >> 1) : "d0");
}

UBYTE spi_recv_byte(void)
{
    UBYTE retval;
    __asm volatile(
    ".REPT 8\n\t"
    "MOVE.W %3,(%1)    | 8  CS low CLK low MOSI high onto line\n\t"
    "ROXL.B #1,%0      | 8  previous MISO into Dn LSB\n\t"
    "MOVE.W %4,(%1)    | 8  CS low CLK high MOSI high onto line\n\t"
    "MOVE.B (%2),D0    | 8  MISO from line\n\t"
    "ROXR.B #1,D0      | 8  ... and into X\n\t"
    ".ENDR\n\t"
    "ROXL.B #1,%0      | 8  final MISO into Dn LSB\n\t"
    : "=&d"(retval) : "a"(JOY_ADRS_OUTPUT), "a"(JOY_ADRS_INPUT), "d"(cs_status), "d"(cs_status + 2) : "d0");
    return retval;
}
#endif /* CONF_WITH_STEJOY_SPI */
