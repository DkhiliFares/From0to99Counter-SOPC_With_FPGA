#include <stdio.h>
#include <unistd.h>
#include "system.h"
#include "io.h"

// 7-segment encoding for COMMON ANODE displays (active-low)
const unsigned char seg_code[10] = {
    0xC0, // 0
    0xF9, // 1
    0xA4, // 2
    0xB0, // 3
    0x99, // 4
    0x92, // 5
    0x82, // 6
    0xF8, // 7
    0x80, // 8
    0x90  // 9
};

void delay_ms(int ms)
{
    volatile int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 5000; j++);
}

int main()
{
    int counter = 0;

    while(1)
    {
        int d0 = (counter % 10);
        int d1 = (counter / 10) % 10;
        int d2 = (counter / 100) % 10;
        int d3 = (counter / 1000) % 10;

        // Write to displays
        IOWR_8DIRECT(DISPLAY7SEGMENT1_BASE, 0, seg_code[d0]);
        IOWR_8DIRECT(DISPLAY7SEGMENT2_BASE, 0, seg_code[d1]);
        IOWR_8DIRECT(DISPLAY7SEGMENT3_BASE, 0, seg_code[d2]);
        IOWR_8DIRECT(DISPLAY7SEGMENT4_BASE, 0, seg_code[d3]);

        delay_ms(10);
        counter++;
        if(counter > 9999)
            counter = 0;
    }

    return 0;
}
