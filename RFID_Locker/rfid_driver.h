/**
 * \file rfid_driver.h
 * \brief
 * \author Thiago - thiagosilva@trixlog.com
 * \copyright Trixlog
 * \date 22/04/2013
 * \version 1.0
 */

#ifndef RFID_DRIVER_H_
#define RFID_DRIVER_H_

#include <avr/io.h>
#include <avr/interrupt.h>

/**
 * Defines
 */
#define ID_NUMBER_OF_BYTES		24
#define RFID_READER_PORT		PORTC
#define RFID_READER_REG			PINC
#define RFID_READER_D0			PC3
#define RFID_READER_D1			PC2
#define RFID_READER_INT_vect	PCINT1_vect

/**
 * Enumerations
 */
enum rfidReader_state
{
	startBitLow,
	startBitHigh,
	fall,
	rise,
	stopBitLow,
	stopBitHigh
};

/**
 * \struct RFID_READER
 */
struct RFID_READER {
	uint8_t state;
	uint8_t dataReceived;
	union ID
	{
		uint32_t value;
		uint8_t byte[4];
	}id;
} rfidReader;

/**
 * Defines
 */
#define rfidReader_enable()		{ PCICR |= (1<<PCIE1); \
								  PCMSK1 = (1<<PCINT11 | 1<<PCINT10);\
								}
#define	rfidReader_disable()	{ PCICR &= ~(1<<PCIE1); }

#endif /* RFID_DRIVER_H_ */
