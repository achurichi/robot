#ifndef utils_h
#define utils_h

#include "Arduino.h"

// Initialize timer 3 with the selected 'time' in seconds
void timer3_init(float time){
    cli(); // stop interrupts
    TCCR3A = 0;  // set entire TCCR3A register to 0
    TCCR3B = 0;  // same for TCCR3B
    TCNT3  = 0;  // initialize counter value to 0
    OCR3A = (uint16_t)(time*15624); // set time
    TCCR3B |= (1 << WGM12); // turn on CTC mode
    TCCR3B |= (1 << CS12) | (1 << CS10); // Set CS12 and CS10 bits for 1024 prescaler
    TIMSK3 |= (1 << OCIE3A); // enable timer compare interrupt
    sei();//allow interrupts
}

// Initialize timer 4 with the selected 'time' in seconds
void timer4_init(float time){
    cli(); // stop interrupts
    TCCR4A = 0;  // set entire TCCR4A register to 0
    TCCR4B = 0;  // same for TCCR4B
    TCNT4  = 0;  // initialize counter value to 0
    OCR4A = (uint16_t)(time*15624); // set time
    TCCR4B |= (1 << WGM12); // turn on CTC mode
    TCCR4B |= (1 << CS12) | (1 << CS10); // Set CS12 and CS10 bits for 1024 prescaler
    TIMSK4 |= (1 << OCIE4A); // enable timer compare interrupt
    sei();//allow interrupts
}

// Data struct
typedef struct data
{
    uint16_t motor[12];          
    bool state;           

} data;

#endif