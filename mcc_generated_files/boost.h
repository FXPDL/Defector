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

#define Boost_LED LATCbits.LATC5
#define Boost_Stomp PORTAbits.RA5

#define Relay_Boost1 LATCbits.LATC4
#define Relay_Boost2 LATCbits.LATC0

void initBoost(void);
void updateBoost(int);
void setBoostState(int);
