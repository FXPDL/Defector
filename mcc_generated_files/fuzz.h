/* 
 * File:   fuzz.h
 * Author: Nancy
 *
 * Created on August 1, 2016, 7:51 PM
 */

#ifndef FUZZ_H
#define	FUZZ_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* FUZZ_H */

#define Fuzz_LED LATAbits.LATA2
#define Feedback_LED LATCbits.LATC3

#define Fuzz_Stomp PORTAbits.RA4

#define Relay_Fuzz10 LATCbits.LATC1
#define Relay_Fuzz1 LATCbits.LATC2
#define Relay_Feedback10 LATAbits.LATA1
#define Relay_Feedback1 LATAbits.LATA0


void initFuzz(void);
void updateFuzz(int);
void setFuzzState(int);
void setFeedbackState(int);