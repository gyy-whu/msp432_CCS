#include "msp.h"
#include "Clock.h"
void PWM_Init34(uint16_t period, uint16_t duty3, uint16_t duty4){

  // write this as part of Lab 13
  if(duty3 >= period) return; // bad input
  if(duty4 >= period) return; // bad input
  P2->DIR |= 0xC0;          // P2.6, P2.7 output
  P2->SEL0 |= 0xC0;         // P2.6, P2.7 Timer0A functions
  P2->SEL1 &= ~0xC0;        // P2.6, P2.7 Timer0A functions
  TIMER_A0->CCTL[0] = 0x0080;      // CCI0 toggle
  TIMER_A0->CCR[0] = period;       // Period is 2*period*8*83.33ns is 1.333*period
  TIMER_A0->EX0 = 0x0000;          // divide by 1
  TIMER_A0->CCTL[3] = 0x0040;      // CCR3 toggle/reset
  TIMER_A0->CCR[3] = duty3;        // CCR3 duty cycle is duty3/period
  TIMER_A0->CCTL[4] = 0x0040;      // CCR4 toggle/reset
  TIMER_A0->CCR[4] = duty4;        // CCR4 duty cycle is duty4/period
  TIMER_A0->CTL = 0x02F0;        // SMCLK=12MHz, divide by 8, up-down mode
  // bit  mode
  // 9-8  10    TASSEL, SMCLK=12MHz
  // 7-6  11    ID, divide by 8
  // 5-4  11    MC, up-down mode
  // 2    0     TACLR, no clear
  // 1    0     TAIE, no interrupt
  // 0          TAIFG
}

void main(void
)
{
    WDT_A->CTL = WDT_A_CTL_PW |             // Stop WDT
                    WDT_A_CTL_HOLD;
    Clock_Init48MHz();
    while(1){
    PWM_Init34(15000, 375,1875 );
    Clock_Delay1ms(200);
    PWM_Init34(15000, 0,0 );
    Clock_Delay1ms(2000);
    PWM_Init34(15000, 375,1875 );
    Clock_Delay1ms(100);
    PWM_Init34(15000, 0,0 );
    Clock_Delay1ms(2000);
    PWM_Init34(15000, 375,1875 );
    Clock_Delay1ms(50);
    PWM_Init34(15000, 0,0 );
    Clock_Delay1ms(2000);
    PWM_Init34(15000, 375,1875  );
    Clock_Delay1ms(10);
    PWM_Init34(15000, 0,0 );
    Clock_Delay1ms(2000);
}
}

