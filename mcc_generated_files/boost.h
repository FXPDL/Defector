/* 
 * File:   boost.h
 * Author: Nancy
 *
 * Created on August 1, 2016, 8:16 PM
 */

#ifndef BOOST_H
#define	BOOST_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* BOOST_H */

#include <stdint.h>        /* For uint8_t definition */
#include "../system.h"
#include "hardware_controls.h"

#define Boost_LED  LATCbits.LATC5
#define Boost_Stomp PORTAbits.RA5
#define Relay_Boost1 LATCbits.LATC0
#define Relay_Boost10 LATCbits.LATC4

void initBoost(void);
void updateBoost(int);
void setBoostState(int);
