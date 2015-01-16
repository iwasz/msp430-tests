#include <msp430.h>
#include <driverlib.h>

int main (void)
{
        WDTCTL = WDTPW | WDTHOLD;

//        P1DIR |= 0x01;

        // Ustaw p1.0 jako wyjście, prąd duży i stan 1.
        P1DIR |= 0x01;
        P1DS = 0x01;

        // P2.1 jako wejście
        P2DIR &= ~GPIO_PIN1;
        // Włącz rezystor pull.
        P2REN |= GPIO_PIN1;
        // Pull up, bo guzik zwiera do masy.
        P2OUT |= GPIO_PIN1;
        //Włącz przerwania
        P2IE |= GPIO_PIN1;
        // Zbocze opadające.
        P2IES |= GPIO_PIN1;

        __enable_interrupt ();

        while (1) {
                P1OUT = 0x01;

                for (volatile uint16_t i = 0; i < 65535; ++i)
//                        for (volatile uint16_t j = 0; j < 65535; ++j)
                                asm ("nop");

                P1OUT = 0x00;

                for (volatile uint16_t i = 0; i < 65535; ++i)
//                        for (volatile uint16_t j = 0; j < 65535; ++j)
                                asm ("nop");
        }



        return 0;
}

__attribute__((interrupt (PORT2_VECTOR)))
void port2 (void)
{
        P1OUT = 0x01;
//        P2IFG &= ~GPIO_PIN1;
//        volatile uint16_t y = P2IV;
        P2IV = 0;
}
