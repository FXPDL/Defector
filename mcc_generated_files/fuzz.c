/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
#include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
#include <htc.h>        /* HiTech General Include File */
#endif




#include "./../state_manager.h"
#include "fuzz.h"

int fuzz_state = -1; //initialize to an invalid value so the initialize will run.
int feedback_state = -1; //initialize to an invalid value so the initialize will run.

int fuzz_pressed = 0;  
int fuzz_up = 1;  
int fuzz_down = 0;  
int fuzz_toggle = 0;
int fuzz_turning_on = 0;

int long_press_limit = 20000000; 

void initFuzz() {
    int initState = getFuzzState();
    setFuzzState(initState);   
    setFeedbackState(0);

}

void updateFuzz(int debounce_limit) {

    //http://www.kennethkuhn.com/electronics/debounce.c
    /* Step 1: Update the integrator based on the input signal.  Note that the 
    integrator follows the input, decreasing or increasing towards the limits as 
    determined by the input state (0 or 1). */
    
    if (Fuzz_Stomp == 0) {
        if (fuzz_pressed > 0) {
            fuzz_pressed--;
        }
    } else if (fuzz_pressed < debounce_limit) {
        fuzz_pressed++;

    }

    /* Step 2: Update the output state based on the integrator.  Note that the
    output will only change states if the integrator has reached a limit, either
    0 or MAXIMUM. */

    if (fuzz_pressed == 0) {
        // Fuzz_LED = 0;
        fuzz_down++;
        if (fuzz_state == 1) {
            if (fuzz_up == 1) {
                fuzz_toggle = 1;
            }
            //Fuzz was on, so if it is long press then kick in feedback.  If it is short, then turn off the fuzz
            if (fuzz_down >= long_press_limit && feedback_state == 0 && fuzz_turning_on == 0) {

                fuzz_down = long_press_limit; //try and prevent overflow
                Fuzz_LED = 0;
                setFeedbackState(1);
            }
        } else {
            //Fuzz was off, so turn it on
            fuzz_turning_on = 1;
            fuzz_toggle = 0;
            setFuzzState(1);
            feedback_state = 0;
        }

        
        fuzz_up = 0;
    } else if (fuzz_pressed >= debounce_limit) {
        int fb_state = feedback_state;
        if (fuzz_toggle == 1 && fb_state == 0) {
            setFuzzState(0);
        }
        Fuzz_LED = fuzz_state;
        //when the switch is up, Feedback is definitely off.  If the toggle for fuzz is true, then turn the fuzz off.
        setFeedbackState(0);
        fuzz_turning_on = 0;
        fuzz_toggle = 0;
        fuzz_up = 1;
        fuzz_down = 0;
        fuzz_pressed = debounce_limit; /* defensive code if integrator got corrupted */
    }     
}

void setFuzzState(int f_state) {
    if (fuzz_state == f_state) {return;}
    fuzz_state = f_state;
    Fuzz_LED = f_state;
    Relay_Fuzz1 = f_state;
    Relay_Fuzz10 = !f_state;
    
    wait_ms(relay_delay);
    
    Relay_Fuzz1 = 0;
    Relay_Fuzz10 = 0;  
    
    updateFuzzState(fuzz_state);    
    wait_ms(relay_delay);
}

void setFeedbackState(int f_state) {
    if (feedback_state == f_state) {return;}
    feedback_state = f_state;
    Feedback_LED = f_state;
    Relay_Feedback1 = f_state;
    Relay_Feedback10 = !f_state;
    
    wait_ms(relay_delay);
    
    Relay_Feedback1 = 0;
    Relay_Feedback10 = 0;  
    
        
    wait_ms(relay_delay);
    
}
 