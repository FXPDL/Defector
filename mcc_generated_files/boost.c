/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#endif

#include "boost.h"


int boost_state = 0; //off

int boost_pressed = 0;  
int boost_up = 1;  
int boost_down = 0;  
int last_boost_state = 0;

void initBoost(void) {
    boost_state = 0;
    Boost_LED = 0;
    Relay_Boost1 = 1; //off
    Relay_Boost2 = 0; //off

}

void updateBoost(int debounce_limit) {

    //http://www.kennethkuhn.com/electronics/debounce.c
    /* Step 1: Update the integrator based on the input signal.  Note that the 
    integrator follows the input, decreasing or increasing towards the limits as 
    determined by the input state (0 or 1). */

    if (Boost_Stomp == 0) {
        if (boost_pressed > 0) {
            boost_pressed--;
        }
    } else if (boost_pressed < debounce_limit) {
        boost_pressed++;
    }

    /* Step 2: Update the output state based on the integrator.  Note that the
    output will only change states if the integrator has reached a limit, either
    0 or MAXIMUM. */

    if (boost_pressed == 0) {
        // Fuzz_LED = 0;
        boost_down = 1;
        if (boost_up == 1) {
            setBoostState(!boost_state);
        }
        boost_up = 0;
    } else if (boost_pressed >= debounce_limit) {
        boost_up = 1;
        boost_down = 0;
        boost_pressed = debounce_limit; /* defensive code if integrator got corrupted */
    }     
    
    
}


void setBoostState(int f_state) {
    boost_state = f_state;
    Boost_LED = f_state;
    Relay_Boost1 = !f_state;
    Relay_Boost2 = f_state;
}
