/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#endif


#include "./../state_manager.h"
#include "boost.h"


int boost_state = -1; //initialize to an invalid value so the initialize will run.

int boost_pressed = 0;  
int boost_up = 1;  
int boost_toggle = 0;

void initBoost() {
    int initState = getBoostState();
    setBoostState(initState);
}

void updateBoost(void) {

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
        if (boost_state == 1) {
            if (boost_up == 1) {
                boost_toggle = 1;
            }
        } else {
            //boost was off, so turn it on
            boost_toggle = 0;
            setBoostState(1);
        }

        
        boost_up = 0;
    } else if (boost_pressed >= debounce_limit) {
        if (boost_toggle == 1) {
            setBoostState(0);
        }
        boost_toggle = 0;
        boost_up = 1;
        boost_pressed = debounce_limit; /* defensive code if integrator got corrupted */
    }    
    
    
}


void setBoostState(int f_state) {
    if (boost_state == f_state) {return;}
    boost_state = f_state;
    Boost_LED = f_state;
    Relay_Boost1 = f_state;
    Relay_Boost10 = !f_state;

    wait_ms(relay_delay);

    Relay_Boost1 = 0;
    Relay_Boost10 = 0;

    updateBoostState(boost_state);  
    wait_ms(relay_delay);
}
