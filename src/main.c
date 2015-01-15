#include <msp430.h>
#include <driverlib.h>

int main (void)
{
        WDTCTL = WDTPW | WDTHOLD;

//        P1DIR |= 0x01;

        // Ustaw p1.0 jako wyjście, prąd duży i stan 1.
        PADIR |= 0x0001;
        PADS = 0x0001;

        while (1) {
                PAOUT = 0x0001;

                for (volatile uint16_t i = 0; i < 65535; ++i)
//                        for (volatile uint16_t j = 0; j < 65535; ++j)
                                asm ("nop");

                PAOUT = 0x0000;

                for (volatile uint16_t i = 0; i < 65535; ++i)
//                        for (volatile uint16_t j = 0; j < 65535; ++j)
                                asm ("nop");
        }



        return 0;
}


