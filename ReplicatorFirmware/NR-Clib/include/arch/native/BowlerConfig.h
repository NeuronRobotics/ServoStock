/**
 * @file BowlerConfig.h
 *
 * Created on: May 27, 2010
 * @author hephaestus
 */

#ifndef BOWLERCONFIG_H_
#define BOWLERCONFIG_H_
#include <stdio.h>
#include <stdlib.h>
#define USE_DYN_RPC

#define StartCritical()
#define EndCritical()

void Linux_Bowler_HAL_Init(void);
#define Bowler_HAL_Init Linux_Bowler_HAL_Init
#define SetColor(a,b,c)
#endif /* BOWLERCONFIG_H_ */
