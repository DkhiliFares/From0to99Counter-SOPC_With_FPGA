#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "system.h"
#include "altera_avalon_pio_regs.h"

/* Table de segments 7-seg actifs-bas */
static const uint8_t SEG_LO[16] = {
    0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,
    0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E
};

static inline uint8_t seg_of(uint8_t x) {
    return SEG_LO[x & 0x0F];  // protection automatique (mod 16)
}

int main(void)
{
    printf("Nios II: Afficheur 7-segments (compteur 0..F)\n");

    uint8_t d = 0;

    while (1) {

        /* Afficher la valeur actuelle */
        IOWR_ALTERA_AVALON_PIO_DATA(DISPLAY7SEGMENT_BASE, seg_of(d));

        usleep(100000);  // demi seconde

        /* Mécanisme de comptage */
        d++;          // incremente
        d &= 0x0F;    // revient à 0 après 15 (0x0F)
    }

    return 0;
}
