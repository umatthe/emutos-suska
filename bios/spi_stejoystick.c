/*
 * spi_stejoystick.c - SPI interface for SD/MMC card driver
 * on STE/Falcon/Suska-C Extended Joystick Port
 *
 * Copyright (C) 2021 The EmuTOS development team
 *
 * Authors:
 *  Udo Matthe
 *  Orion_ from atari-forum.com see:
 *  https://www.atari-forum.com/viewtopic.php?f=15&t=39022
 *
 * This file is distributed under the GPL, version 2 or at your
 * option any later version.  See doc/license.txt for details.
 */

/*
; Extended Joystick Port: Computer Side
;    _______________________________
;    \   5   4    3    2    1      /
;     \     10   9    8    7   6  /
;      \ 15  14   13  12   11    /
;       \_______________________/
;
; 4 - MOSI
; 3 - SCK
; 2 - CS
; 6 - MISO
; 7 - VCC
; 9 - GND
*/

#include "emutos.h"
#include "spi.h"

#if CONF_WITH_STEJOYSTICK_SPI
UBYTE spi_transmit_byte(UBYTE data);

#define _BV(bit) (1 << (bit))

#define JOY_OUTPUT      0xFF9202
#define JOY_INPUT       0xFF9201
#define SOFTSPI_CS      2
#define SOFTSPI_SCK     1
#define SOFTSPI_MOSI    0
#define SOFTSPI_MISO    0

UBYTE spiout;
UBYTE slowspi = 0;

volatile UWORD* joy_output;
UBYTE* joy_input;

void spi_initialise(void)
{
   joy_input=(UBYTE*)JOY_INPUT;
   joy_output=(UWORD*)JOY_OUTPUT;
   spiout=0;
   spi_cs_unassert();
}

void spi_clock_sd(void)
{
// not needed
}

void spi_clock_mmc(void)
{
// not needed
}

void spi_clock_ident(void)
{
// not needed
}

void spi_cs_assert(void)
{
    spiout&=~_BV(SOFTSPI_MOSI);
    *joy_output = spiout;
}

void spi_cs_unassert(void)
{
    spiout|=_BV(SOFTSPI_MOSI);
    *joy_output = spiout;
}

UBYTE spi_transmit_byte(UBYTE data)
{
        UBYTE rdata=0;
        UBYTE i=0;

        for (i=0; i<8; i++)
        {

                rdata<<=1;
                if (data&128)
                {
                        spiout|=_BV(SOFTSPI_MOSI);
                }
                else
                {
                        spiout&=~_BV(SOFTSPI_MOSI);
                }
                *joy_output = spiout;
                if ((*joy_input)&(1<<SOFTSPI_MISO))
                {
                        rdata|=1;
                }
                spiout|=_BV(SOFTSPI_SCK);
                *joy_output = spiout;
                spiout&=~_BV(SOFTSPI_SCK);
                *joy_output = spiout;
                data<<=1;
        }
        return rdata;
}

void spi_send_byte(UBYTE data)
{
// spi_transmit_byte(data);
//        UBYTE i=0;


        if (data>127)
        {
                spiout|=_BV(SOFTSPI_MOSI);
        }
        else
        {
                spiout&=~_BV(SOFTSPI_MOSI);
        }
        *joy_output = spiout;
        spiout|=_BV(SOFTSPI_SCK);
        *joy_output = spiout;
        spiout&=~_BV(SOFTSPI_SCK);
        *joy_output = spiout;
        data<<=1;

        if (data>127)
        {
                spiout|=_BV(SOFTSPI_MOSI);
        }
        else
        {
                spiout&=~_BV(SOFTSPI_MOSI);
        }
        *joy_output = spiout;
        spiout|=_BV(SOFTSPI_SCK);
        *joy_output = spiout;
        spiout&=~_BV(SOFTSPI_SCK);
        *joy_output = spiout;
        data<<=1;

        if (data>127)
        {
                spiout|=_BV(SOFTSPI_MOSI);
        }
        else
        {
                spiout&=~_BV(SOFTSPI_MOSI);
        }
        *joy_output = spiout;
        spiout|=_BV(SOFTSPI_SCK);
        *joy_output = spiout;
        spiout&=~_BV(SOFTSPI_SCK);
        *joy_output = spiout;
        data<<=1;

        if (data>127)
        {
                spiout|=_BV(SOFTSPI_MOSI);
        }
        else
        {
                spiout&=~_BV(SOFTSPI_MOSI);
        }
        *joy_output = spiout;
        spiout|=_BV(SOFTSPI_SCK);
        *joy_output = spiout;
        spiout&=~_BV(SOFTSPI_SCK);
        *joy_output = spiout;
        data<<=1;

        if (data>127)
        {
                spiout|=_BV(SOFTSPI_MOSI);
        }
        else
        {
                spiout&=~_BV(SOFTSPI_MOSI);
        }
        *joy_output = spiout;
        spiout|=_BV(SOFTSPI_SCK);
        *joy_output = spiout;
        spiout&=~_BV(SOFTSPI_SCK);
        *joy_output = spiout;
        data<<=1;

        if (data>127)
        {
                spiout|=_BV(SOFTSPI_MOSI);
        }
        else
        {
                spiout&=~_BV(SOFTSPI_MOSI);
        }
        *joy_output = spiout;
        spiout|=_BV(SOFTSPI_SCK);
        *joy_output = spiout;
        spiout&=~_BV(SOFTSPI_SCK);
        *joy_output = spiout;
        data<<=1;

        if (data>127)
        {
                spiout|=_BV(SOFTSPI_MOSI);
        }
        else
        {
                spiout&=~_BV(SOFTSPI_MOSI);
        }
        *joy_output = spiout;
        spiout|=_BV(SOFTSPI_SCK);
        *joy_output = spiout;
        spiout&=~_BV(SOFTSPI_SCK);
        *joy_output = spiout;
        data<<=1;

        if (data>127)
        {
                spiout|=_BV(SOFTSPI_MOSI);
        }
        else
        {
                spiout&=~_BV(SOFTSPI_MOSI);
        }
        *joy_output = spiout;
        spiout|=_BV(SOFTSPI_SCK);
        *joy_output = spiout;
        spiout&=~_BV(SOFTSPI_SCK);
        *joy_output = spiout;

/*
        for (i=0; i<8; i++)
        {

                if (data&128)
                {
                        spiout|=_BV(SOFTSPI_MOSI);
                }
                else
                {
                        spiout&=~_BV(SOFTSPI_MOSI);
                }
                *joy_output = spiout;
                spiout|=_BV(SOFTSPI_SCK);
                *joy_output = spiout;
                spiout&=~_BV(SOFTSPI_SCK);
                *joy_output = spiout;
                data<<=1;
        }
*/
}

UBYTE spi_recv_byte(void)
{
    /* send a byte to get one */
//    return spi_transmit_byte(0xff);
        UBYTE rdata=0;
//        UBYTE i=0;

        spiout|=_BV(SOFTSPI_MOSI);
        *joy_output = spiout;

        rdata=(rdata<<1)|((*joy_input)&1);
        spiout|=_BV(SOFTSPI_SCK);
        *joy_output = spiout;
        spiout&=~_BV(SOFTSPI_SCK);
        *joy_output = spiout;

        rdata=(rdata<<1)|((*joy_input)&1);
        spiout|=_BV(SOFTSPI_SCK);
        *joy_output = spiout;
        spiout&=~_BV(SOFTSPI_SCK);
        *joy_output = spiout;

        rdata=(rdata<<1)|((*joy_input)&1);
        spiout|=_BV(SOFTSPI_SCK);
        *joy_output = spiout;
        spiout&=~_BV(SOFTSPI_SCK);
        *joy_output = spiout;

        rdata=(rdata<<1)|((*joy_input)&1);
        spiout|=_BV(SOFTSPI_SCK);
        *joy_output = spiout;
        spiout&=~_BV(SOFTSPI_SCK);
        *joy_output = spiout;

        rdata=(rdata<<1)|((*joy_input)&1);
        spiout|=_BV(SOFTSPI_SCK);
        *joy_output = spiout;
        spiout&=~_BV(SOFTSPI_SCK);
        *joy_output = spiout;

        rdata=(rdata<<1)|((*joy_input)&1);
        spiout|=_BV(SOFTSPI_SCK);
        *joy_output = spiout;
        spiout&=~_BV(SOFTSPI_SCK);
        *joy_output = spiout;

        rdata=(rdata<<1)|((*joy_input)&1);
        spiout|=_BV(SOFTSPI_SCK);
        *joy_output = spiout;
        spiout&=~_BV(SOFTSPI_SCK);
        *joy_output = spiout;

        rdata=(rdata<<1)|((*joy_input)&1);
        spiout|=_BV(SOFTSPI_SCK);
        *joy_output = spiout;
        spiout&=~_BV(SOFTSPI_SCK);
        *joy_output = spiout;
/*
        for (i=0; i<8; i++)
        {
                rdata=(rdata<<1)|((*joy_input)&1);
                spiout|=_BV(SOFTSPI_SCK);
                *joy_output = spiout;
                spiout&=~_BV(SOFTSPI_SCK);
                *joy_output = spiout;
        }
*/
        return rdata;
}
#endif /* CONF_WITH_STEJOYSTICK_SPI */
