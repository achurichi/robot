#ifndef utils_h
#define utils_h

#include "Arduino.h"

// Initialize timer 3 with the selected 'time' in seconds
void timer3_init(float time){
    cli(); // stop interrupts

    TCCR3A = 0;  // set entire TCCR3A register to 0

    TCCR3B = 0;  // same for TCCR3B
    TCCR3B |= (1 << WGM32); // turn on CTC mode
    TCCR3B |= (1 << CS32) | (1 << CS30); // Set CS32 and CS30 bits for 1024 prescaler

    TCNT3  = 0;  // initialize counter value to 0

    OCR3A = (uint16_t)(time*15624); // set time

    TIMSK3 |= (1 << OCIE3A); // enable timer compare interrupt

    sei(); // allow interrupts
}

// Initialize timer 4 with the selected 'time' in seconds
void timer4_init(float time){
    cli(); // stop interrupts

    TCCR4A = 0;  // set entire TCCR4A register to 0

    TCCR4B = 0;  // same for TCCR4B
    TCCR4B |= (1 << WGM42); // turn on CTC mode
    TCCR4B |= (1 << CS42) | (1 << CS40); // Set CS42 and CS40 bits for 1024 prescaler
    
    TCNT4  = 0;  // initialize counter value to 0
    
    OCR4A = (uint16_t)(time*15624); // set time

    TIMSK4 |= (1 << OCIE4A); // enable timer compare interrupt
    
    sei(); // allow interrupts
}

// Data struct
typedef struct data
{
    uint16_t motor[12];          
    bool state;           

} data;

#endif