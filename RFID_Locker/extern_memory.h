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

id EEMEM contributorsList[255] = {
	0x000034,	// variável de contagem inicial. O valor dessa variavel assume a quantidade de elementos nesta lista.
	0x006F51, //Thiago - 1
	0x008A95,  //Thiago - 2
	0x001218, //Leidson
	0x005411, //Eduardo Lopes
	0x00429b, //Marcos 1
	0x000061, //Marcos 2
	0x00bd9f, //raul 1
	0x009265, //Jonas 2
	0x001c4d, //Wanderson
	0x001a75, //Douglas
	0x00e98b, //Alan GOKU
	0x00429b, //Marcos Flávio
	0x005415, //Max Ribeiro
	0x00564b, //Iago
	0x0059ba, //Reginaldo
	0x0055af, //Isac
	0x00166c, //Atila
	0x00564e, //Gustavo
	0x0052cf, //rafael - 20
	0x004c1c, //Hayannah Pereira
	0x0055BA, //Daniel Martis
	0x0073ED, //Amanda Souto
	0x0046CD, //Amanda Vitoria
	0x0073ED, //Wesley
	0x0014c7, //Cintia Freitas
	0x0055AF, //Diana Mesquita
	0x0014c8, //Viviany Monteiro
	0x0053AD, //Gê Rodrigues
	0x005f51, //Germano Sampaio - 30
	0x0014C7, //Felipe oliveira
	0x005065, //Dirceu
	0x0055EE, //Jessica Ribeiro
	0x008fe9, //Rodrigo Costa
	0x00774f, //Suely Quintela
	0x0073ED, //italo rocha
	0x0014C8, //Aline
	0x004680, //Bruna Macedo
	0x005079, //Ricardo Araujo
	0x0059BA, //Carlos Eduardo - 40
	0x008FDC, //Rhavenna Barbosa
	0x000F83, //Walter Acompanhamento
	0x003A90, //Stafuza
	0x006343, //Heladio	
	0x00bd9f, // Will
	0x005e74, //Will - prov
	0x0055BE, //Natalia Lopes - 48
	//0x0061b1, //Provisório
	//0x001a5c, //Provisório
	//0x005e62, //Provisório
	//0x007299, //Provisório
	//0x0073fb, //Provisório
	//0x005e59, //Provisório tirado
	0x006219, //Provisório - 55
	0x00d713, //Provisório
	0x00516c, // Daniel
	0x005f5e, //JP
	0x00e98b //Solange
	
};

#endif /* EXTERN_MEMORY_H_ */