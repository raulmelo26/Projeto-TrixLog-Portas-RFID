 /*
 * main
 *
 * Created: 02/04/2018
 *  Author: raulmelo-trix, thiagosilva-trix
 */ 
 #define STOP_TIMER1  TCCR1B &= 0B11111000
 #define START_TIMER1 TIMSK1 |= (1 << TOIE1);
 
 #define F_CPU 16000000UL
 #include <avr/io.h>
 #include <avr/interrupt.h>
 #include <avr/eeprom.h>
 #include <avr/delay.h>
 #include "usart.h"
 #include "rfid_driver.h"
 #include "extern_memory.h"
 
 #define DEBUG

uint8_t searchId(uint32_t id) {
	uint32_t authId;
	
	for (uint8_t index = 0; index < 255; index++) {
		authId = eeprom_read_dword(index*4);
		if (id == authId) {
			return 1;
		}
	}
	
	return 0;
}

ISR(TIMER1_OVF_vect)
{
	TCNT1 = 0xC2F7;
	rfidReader.state = startBitLow;
	STOP_TIMER1;
}

void memEstourada(int a){
	PORTD = 0b00100000;
	_delay_ms(a);
	PORTD = 0b00000000;
	_delay_ms(a);
	PORTD = 0b00100000;
	_delay_ms(a);
	PORTD = 0b00000000;
	_delay_ms(a);
	PORTD = 0b00100000;
	_delay_ms(a);
	PORTD = 0b00000000;
}

void unlock() {
	usart0_putString("Authorized Card!\n");
	PORTD = 0b00000100; 
	_delay_ms(1000);
	PORTD=  0b00000000; 
}

uint8_t str[5];
uint32_t count;
uint32_t rfidAux = 0xffff;
 
 int main() {
	 
	 DDRC &= ~(1<<PORTC3|1<<PORTC2); 
	 DDRC = DDRC & ~(1<<0);
	 PORTC |= (1<<PORTC3|1<<PORTC2|1<<PORTC0);
	 DDRD = 0xFF; 
		
	TCCR1A = 0;                        //confira timer para operação normal pinos OC1A e OC1B desconectados
	TCCR1B = 0;                        //limpa registrador
	TCCR1B |= (1<<CS10)|(1 << CS12);   // configura prescaler para 1024: CS12 = 1 e CS10 = 1
	
	//TIMSK1 |= (1 << TOIE1);	
		
	 // usart0 config
	 usart0_init((ASYNC|PARITY_DISABLE |STOP_BIT_1 |CHAR_SIZE_8),9600);
	 
	 // pin change interrupt for rfid reader
	 rfidReader_enable();
	 
	 sei(); //enable global interrupts
	 
	 usart0_putString("RFID_Lock started!\n");	
	 //QUANTIDADE DE CARTOES JA CADASTRADOS
	 count = eeprom_read_dword(0);
	 sprintf(&str,"Count: %.5u\r",count);
	 usart0_putString(str);
	 
	 while(1) {
		/*if(eeprom_read_dword(32) == 0x00bd9f){
			PORTD = 0b00000100; //Turns ON All LEDs
			_delay_ms(1000); //1 second delay
			PORTD=  0b00000000; //Turns OFF All LEDs
			_delay_ms(1000); //1 second delay
		}*/
		if (rfidReader.dataReceived == 1) {
			
			#ifdef DEBUG
			sprintf(&str,"%.5u\r",rfidReader.id.value);
			usart0_putString(str);
			
			#endif
			if (searchId(rfidReader.id.value) && (rfidReader.id.value != 0x0)) {
				unlock();
				} else {
				#ifdef DEBUG
				usart0_putString("Cartão não cadastrado!\n");
				//memEstourada(100);
				//unlock();
				#endif
			}
			rfidReader.dataReceived = 0;
			rfidReader.state = startBitLow;
			//MODO DE GRAVAÇÃO
			if((PINC & (1<<0)) == 0){ 
				//VERIFICA SE O CARD JÁ É CADASTRADO
				if(!searchId(rfidReader.id.value) && (rfidReader.id.value == rfidAux)){
					//MEMORIA ESGOTADA
					if(count>256){ 
						memEstourada(1000);
						usart0_putString("Estouro da memória eeprom!\n");
						}
					else{
						//GRAVA O NOVO CARD
						eeprom_write_dword (count*4, rfidReader.id.value);
						usart0_putString("Id gravado com sucesso");
						count++;
						eeprom_update_dword (0, count);
						unlock();
					}
				}
				rfidAux = rfidReader.id.value;
			}
		}
		// LED VERDE - INDICA QUE ENTROU NO MODO DE GRAVAÇÃO
		if((PINC & (1<<0)) == 0){
			PORTD = 0b00100000;	
		} else{
			PORTD = 0b00000000; 
		}
		
	 }

 }