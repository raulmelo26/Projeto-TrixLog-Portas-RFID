/**
 * \file rfid_driver.c
 * \brief
 * \author Thiago - thiagosilva@trixlog.com
 * \copyright Trixlog
 * \date 22/04/2013
 * \version 1.0
 */

#include "rfid_driver.h"

ISR(RFID_READER_INT_vect) {

	uint8_t dataInputState = (PINC & 0b00001100) >> 2;
	static uint8_t count = 0;
	
	switch (rfidReader.state) {
		case startBitLow:
			rfidReader.state = startBitHigh;
		break;
		
		case startBitHigh:
			rfidReader.id.value = 0; // clear last id received;
			count = 0; // init bit counter
			rfidReader.state = fall;
		break;
		
		case fall:
			rfidReader.id.value = (rfidReader.id.value << 1);
			if (dataInputState == 0b00000010) {
				rfidReader.id.value |= 0x01;
			} else if (dataInputState == 0b00000000) {
				rfidReader.id.value |= 0x00;
			}
			rfidReader.state = rise;
		break;
		
		case rise:
			count++;
			if(count < ID_NUMBER_OF_BYTES) {
				rfidReader.state =  fall;
			} else {
				rfidReader.state = stopBitLow;
			}
		break;
		
		case stopBitLow:
			rfidReader.state = stopBitHigh;
		break;
		
		case stopBitHigh:
			rfidReader.dataReceived = 1;
		break;
		
	}
}

