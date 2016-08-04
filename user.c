/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/



#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */



#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */
//#define ACQ_US_DELAY 5

void InitApp(void) {
    TRISAbits.TRISA0 = 0; //output - Relay_Feedback2
    TRISAbits.TRISA1 = 0; //output - Relay_Feedback1
    
    TRISAbits.TRISA2 = 0; //output - Fuzz_LED
    TRISAbits.TRISA4 = 1; //input - Fuzz_Stomp
    TRISAbits.TRISA5 = 1; //input - Boost_Stomp
    ANSELAbits.ANSA4 = 0; //digital
    
    TRISCbits.TRISC0 = 0; //output - Relay_boost2
    TRISCbits.TRISC1 = 0; //output - Relay_fuzz1
    TRISCbits.TRISC2 = 0; //output - Relay_Fuzz2
    TRISCbits.TRISC3 = 0; //output - Feedback LED
    TRISCbits.TRISC4 = 0; //output - Relay_boost1
    TRISCbits.TRISC5 = 0; //output - Boost_LED
    
    LATCbits.LATC5 = 0; //Boost_LED
    
    LATAbits.LATA2 = 0; //Fuzz_LED
    LATCbits.LATC3 = 0; //Feedback_LED

    init_adc();

}


void init_timer2(void) {
    PIR1bits.ADIF = 0;
    T2CONbits.T2CKPS = 0b00;
    T2CONbits.T2OUTPS = 0b0000;
    T2CONbits.TMR2ON = 1;
}

void init_adc(void) {
    ADCON1bits.ADFM = 0b1; // right justify the output
    ADCON1bits.ADCS = 0b110; // use Fosc/64 for clock source
    ADCON1bits.ADPREF = 0b00; // Vref = Vdd
    ADCON0bits.ADON = 0b1; // turn on the ADC
}

uint16_t adc_convert(uint8_t channel) {
    ADCON0bits.CHS = channel; // select the given channel
    ADCON0bits.GO = 0b1; // start the conversion
    while (ADCON0bits.GO_nDONE); // wait for the conversion to finish
    return (ADRESH << 8) | ADRESL; // return the result 
}

