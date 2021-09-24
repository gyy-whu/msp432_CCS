#include "stdint.h"
#include "msp.h"
#include "CortexM.h"
#include "PWM.h"

// *******Lab 13 solution*******

// ------------Motor_Init------------
// Initialize GPIO pins for output, which will be
// used to control the direction of the motors and
// to enable or disable the drivers.
// The motors are initially stopped, the drivers
// are initially powered down, and the PWM speed
// control is uninitialized.
// Input: none
// Output: none
void Motor_Init(void){
  // write this as part of Lab 13
    P1->SEL0 &= ~0xC0;
    P1->SEL1 &= ~0xC0;  // configure as GPIO
    P1->DIR |= 0xC0;    // make P1.6 & P1.7 out
    P1->OUT &= ~0xC0;

    P3->SEL0 &= ~0xC0;
    P3->SEL1 &= ~0xC0;  // configure as GPIO
    P3->DIR |= 0xC0;    // make P3.6 & P3.7 out
    P3->OUT &= ~0xC0;   // low current sleep mode
}

// ------------Motor_Stop------------
// Stop the motors, power down the drivers, and
// set the PWM speed control to 0% duty cycle.
// Input: none
// Output: none
void Motor_Stop(void){
  // write this as part of Lab 13
    P1->OUT &= ~0xC0;
    P2->OUT &= ~0xC0;   // off
    P3->OUT &= ~0xC0;   // low current sleep mode
}

// ------------Motor_Forward------------
// Drive the robot forward by running left and
// right wheels forward with the given duty
// cycles.
// Input: leftDuty  duty cycle of left wheel (0 to 14,998)
//        rightDuty duty cycle of right wheel (0 to 14,998)
// Output: none
// Assumes: Motor_Init() has been called
void Motor_Backward(uint16_t leftDuty, uint16_t rightDuty){
  // write this as part of Lab 13
    P1->OUT &= ~0xC0;   // set direction of motors
    PWM_Init34(15000, rightDuty, leftDuty);
    P3->OUT |= 0xC0;    // activate motors
}

// ------------Motor_Right------------
// Turn the robot to the right by running the
// left wheel forward and the right wheel
// backward with the given duty cycles.
// Input: leftDuty  duty cycle of left wheel (0 to 14,998)
//        rightDuty duty cycle of right wheel (0 to 14,998)
// Output: none
// Assumes: Motor_Init() has been called
void Motor_Left(uint16_t leftDuty, uint16_t rightDuty){
  // write this as part of Lab 13
    P1->OUT &= ~0x80;   // left wheel forward
    P1->OUT |= 0x40;    // right wheel backward
    PWM_Init34(15000, rightDuty, leftDuty);
    P3->OUT |= 0xC0;    // activate motors
}

// ------------Motor_Left------------
// Turn the robot to the left by running the
// left wheel backward and the right wheel
// forward with the given duty cycles.
// Input: leftDuty  duty cycle of left wheel (0 to 14,998)
//        rightDuty duty cycle of right wheel (0 to 14,998)
// Output: none
// Assumes: Motor_Init() has been called
void Motor_Right(uint16_t leftDuty, uint16_t rightDuty){
  // write this as part of Lab 13
    P1->OUT &= ~0x40;   // right wheel forward
    P1->OUT |= 0x80;    // left wheel backward
    PWM_Init34(15000, rightDuty, leftDuty);
    P3->OUT |= 0xC0;    // activate motors
}

// ------------Motor_Backward------------
// Drive the robot backward by running left and
// right wheels backward with the given duty
// cycles.
// Input: leftDuty  duty cycle of left wheel (0 to 14,998)
//        rightDuty duty cycle of right wheel (0 to 14,998)
// Output: none
// Assumes: Motor_Init() has been called
void Motor_Forward(uint16_t leftDuty, uint16_t rightDuty){
  // write this as part of Lab 13
    P1->OUT |= 0xC0;   // set direction of motors
    if(leftDuty>=14999)
        leftDuty=14999;
    if(rightDuty>=14999)
        rightDuty=14999;
    PWM_Init34(15000, rightDuty, leftDuty);
    P3->OUT |= 0xC0;    // activate motors
}
