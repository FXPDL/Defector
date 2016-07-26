/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#endif

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */

#define Fuzz_LED LATAbits.LATA2
#define Boost_LED LATCbits.LATC5
#define Feedback_LED LATCbits.LATC3

#define Fuzz_Stomp PORTAbits.RA4
#define Boost_Stomp PORTAbits.RA5

#define Relay_Boost1 LATCbits.LATC4
#define Relay_Boost2 LATCbits.LATC0
#define Relay_Fuzz1 LATCbits.LATC1
#define Relay_Fuzz2 LATCbits.LATC2
#define Relay_Feedback1 LATAbits.LATA0
#define Relay_Feedback2 LATAbits.LATA1

int debounce_count_fuzz = 0;
int debounce_count_boost = 0;

int fuzz_state = 0; //off
int boost_state = 0; //off
int feedback_state = 0; //off


/******************************************************************************/
/* Main Program                                                               */

/******************************************************************************/
void main(void) {
    ConfigureOscillator();
    InitApp();

    Relay_Boost1 = 0;
    Relay_Boost2 = 0;
    Relay_Fuzz1 = 0;
    Relay_Fuzz2 = 0;

    //load startup conditions
    Relay_Boost1 = !boost_state;
    Relay_Boost2 = boost_state;
    Boost_LED = boost_state;

    Relay_Fuzz1 = !fuzz_state;
    Relay_Fuzz2 = fuzz_state;
    Fuzz_LED = fuzz_state;

   // Relay_Feedback1 = 0;
   // Relay_Feedback2 = 1;

    /* Relay_Feedback1 = feedback_state;
     Relay_Feedback2 = feedback_state;
     Feedback_LED = feedback_state;*/

    while (1) {
        if (Fuzz_Stomp == 0) {
            debounce_count_fuzz++;
            if (debounce_count_fuzz > 25) {
                fuzz_state = !fuzz_state;
                Fuzz_LED = !fuzz_state;
                Relay_Fuzz1 = fuzz_state;
                Relay_Fuzz2 = !fuzz_state;
                while (Fuzz_Stomp == 0) {
                    wait_ms(20);
                }
            }
        } else {
            debounce_count_fuzz = 0;
        }
        /* if (Fuzz_Stomp == 0) {
                 fuzz_state = !fuzz_state;
                 Fuzz_LED = fuzz_state;
                 Relay_Fuzz1 = fuzz_state;
                 Relay_Fuzz2 = !fuzz_state;
                 while (Fuzz_Stomp == 0){
                 wait_ms(20);
                 }
            
              
         } */

        if (Boost_Stomp == 0) {
            debounce_count_boost++;
            if (debounce_count_boost > 25) {
                boost_state = !boost_state;
                Boost_LED = !boost_state;
                Relay_Boost1 = boost_state;
                Relay_Boost2 = !boost_state;
                while (Boost_Stomp == 0) {
                    wait_ms(20);
                }
            }
        } else {
            debounce_count_boost = 0;
        }
    }

}