/*****************************************************************************
 *   Mytemp.c:  Driver for the ISL29003 Mytemp-to-Digital Output Sensor
 *
 *   Copyright(C) 2009, Embedded Artists AB
 *   All rights reserved.
 *
 ******************************************************************************/

/*
 * NOTE: I2C must have been initialized before calling any functions in this
 * file.
 */

/******************************************************************************
 * Includes
 *****************************************************************************/

#include "../inc/myTemp.h"



/******************************************************************************
 * Defines and typedefs
 *****************************************************************************/

#define I2CDEV LPC_I2C2

#define Mytemp_I2C_ADDR    (0x4C)

/******************************************************************************
 * Local Functions
 *****************************************************************************/

static int I2CRead(uint8_t addr, uint8_t* buf, uint32_t len)
{
	I2C_M_SETUP_Type rxsetup;

	rxsetup.sl_addr7bit = addr;
	rxsetup.tx_data = NULL;	// Get address to read at writing address
	rxsetup.tx_length = 0;
	rxsetup.rx_data = buf;
	rxsetup.rx_length = len;
	rxsetup.retransmissions_max = 3;

	if (I2C_MasterTransferData(I2CDEV, &rxsetup, I2C_TRANSFER_POLLING) == SUCCESS){
		return (0);
	} else {
		return (-1);
	}
}




/******************************************************************************
 * Public Functions
 *****************************************************************************/

/******************************************************************************
 *
 * Description:
 *    Initialize the ISL29003 Device
 *
 *****************************************************************************/
void Mytemp_init (void)
{
    /* nothing to initialize. Mytemp_enable enables the sensor */
}



/******************************************************************************
 *
 * Description:
 *    Read sensor value
 *
 * Returns:
 *      Read Mytemp sensor value (in units of Lux)
 *
 *****************************************************************************/
uint32_t Mytemp_read(void)
{
    uint32_t data = 0;
    uint8_t buf[2];


    I2CRead(Mytemp_I2C_ADDR, buf, 2);

    data = (buf[0]<<1);
    data+=(buf[1]>>7);

    return (data);
}

