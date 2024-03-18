/*
; Printer Port: Computer Side
;    _____________________________________________
;    \  13 12 11 10  9  8  7  6  5   4  3  2  1  /
;     \  25 24 23 22 21 20 19 18 17 16 15 14    /
;      \_______________________________________/
;
;  2 - MOSI PortB0
;  4 - SCK  PortB2
;  --UMA 1 - CS   PortA5 (Strobe)
;  3 - CS   PortB1
; 11 - MISO MFP0   (Busy)
; 13 - VCC
; 25 - GND
*/
#include "emutos.h"
#include "spi.h"
#if CONF_WITH_LPT_SPI
UBYTE spi_transmit_byte(UBYTE data);

#define _BV(bit) (1 << (bit))

#define AY_SELREG       0xFF8800
#define AY_WRITEREG     0xFF8802
#define CTRL_REG        7
#define PRTDAT_REG      15
#define PRT_INPUT       0xFFFA01
// Outputs
#define SOFTSPI_MOSI    0
#define SOFTSPI_CS      1
#define SOFTSPI_SCK     2
// Input
#define SOFTSPI_MISO    0

#include <stdio.h>

UBYTE spiout;

volatile UBYTE* aysel_output;
volatile UBYTE* aywrite_output;
volatile UBYTE* prt_input;


void spi_initialise(void)
{
  prt_input=(UBYTE*)PRT_INPUT;
  aysel_output=(UBYTE*)AY_SELREG;
  aywrite_output=(UBYTE*)AY_WRITEREG;

  *aysel_output = CTRL_REG;
  *aywrite_output= (*aysel_output) | 0x80;
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
    *aysel_output = PRTDAT_REG;
    spiout&=~_BV(SOFTSPI_CS);
    *aywrite_output=spiout;
}

void spi_cs_unassert(void)
{
    *aysel_output = PRTDAT_REG;
    spiout|=_BV(SOFTSPI_CS);
    *aywrite_output=spiout;
}

UBYTE spi_transmit_byte(UBYTE data)
{
        UBYTE rdata=0;
        UBYTE i;
        __asm__ __volatile__(
        "move.w #0x2700,sr\n\t"
        );

        *aysel_output = PRTDAT_REG;
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
                *aywrite_output=spiout;
                if ((*prt_input)&(1<<SOFTSPI_MISO))
                {
                        rdata|=1;
                }
                spiout|=_BV(SOFTSPI_SCK);
                *aywrite_output=spiout;
                spiout&=~_BV(SOFTSPI_SCK);
                *aywrite_output=spiout;
                data<<=1;
        }
        __asm__ __volatile__(
        "move.w #0x2300,sr\n\t"
        );

        return rdata;
}
void spi_send_byte(UBYTE data)
{
 spi_transmit_byte(data);
}

UBYTE spi_recv_byte(void)
{
    /* send a byte to get one */
    return spi_transmit_byte(0xff);
}

#endif /* CONF_WITH_LPT_SPI */
