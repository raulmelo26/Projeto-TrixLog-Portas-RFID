/*
 * extern_memory.h
 *
 * Created: 06/06/2017 18:16:07
 *  Author: thiagosilva-trix
 */ 


#ifndef EXTERN_MEMORY_H_
#define EXTERN_MEMORY_H_

#include <avr/io.h>
#include <avr/eeprom.h>

typedef uint32_t id;

id EEMEM contributorsList[100] = {
	0x0000000D,	// variável de contagem inicial. O valor dessa variavel assume  .
	0x006F5148, //Thiago - 1
	0x008A950B,  //Thiago - 2
	0x00121896, //Leidson
	0x005411EC, //Eduardo Lopes
	0x001672fe, //Jose Alan
	0x00429b7d, //Marcos 1
	0x000061B1, //Marcos 2
	0x0000BD9F, //raul 1
	0x00926508, //Jonas 2
	0x001c4d04, //Wanderson
	0x001a758a, //Douglas
	0x00e98b8a  //Alan GOKU
};

#endif /* EXTERN_MEMORY_H_ */