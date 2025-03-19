/*****************************************************************************
 *   Mytemp.h:  Header file for ISL29003 Mytemp-to-Digital Output Sensor
 *
 *   Copyright(C) 2009, Embedded Artists AB
 *   All rights reserved.
 *
******************************************************************************/
#ifndef __Mytemp_H
#define __Mytemp_H

#include "lpc17xx_i2c.h"

void Mytemp_init (void);
uint32_t Mytemp_read(void);



#endif /* end __Mytemp_H */
/****************************************************************************
**                            End Of File
*****************************************************************************/
