/*****************************************************************************
 *   eeprom.h:  Header file for the 24LC08 EEPROM
 *
 *   Copyright(C) 2009, Embedded Artists AB
 *   All rights reserved.
 *
******************************************************************************/
#ifndef __EEPROM_H
#define __EEPROM_H


void eeprom_init (void);
int16_t eeprom_read(uint8_t* buf, uint16_t offset, uint16_t len);
int16_t eeprom_write(uint8_t* buf, uint16_t offset, uint16_t len);
#define EEPROM_VERSION_ADDR 0x00  // Adres wersji danych w EEPROM
#define EEPROM_VERSION_ID 0x1234ABCD  // Unikalny identyfikator wersji
#define TEMP_MAX_ADDR 0x10
#define PRESS_MAX_ADDR 0x20


#endif /* end __EEPROM_H */
/****************************************************************************
**                            End Of File
*****************************************************************************/
