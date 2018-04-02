 
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

void unlock() {
	usart0_putString("Authorized Card!\n");
	PORTD = 0b00000100; 
	_delay_ms(1000);
	PORTD=  0b00000000;
	_delay_ms(1000); 
	
}

uint8_t str[5];
uint32_t count;
 
 int main() {
	 
	 DDRC &= ~(1<<PORTC3|1<<PORTC2); //(1<<PORTC3|1<<PORTC2|PORTC0);
	 DDRC = DDRC & ~(1<<0);
	 PORTC |= (1<<PORTC3|1<<PORTC2|1<<PORTC0);
	 DDRD = 0xFF; 
		
	 // usart0 config
	 usart0_init((ASYNC|PARITY_DISABLE |STOP_BIT_1 |CHAR_SIZE_8),9600);
	 
	 // pin change interrupt for rfid reader
	 rfidReader_enable();
	 
	 sei(); //enable global interrupts
	 
	 usart0_putString("RFID_Lock started!\n");	
	 
	 count = eeprom_read_dword(0);
	 
	 while(1) {
		 
		/*if(eeprom_read_dword(52) == 0x0000bd9f){
			PORTD = 0b00000100; //Turns ON All LEDs
			_delay_ms(1000); //1 second delay
			PORTD=  0b00000000; //Turns OFF All LEDs
			_delay_ms(1000); //1 second delay
		}*/
		if (rfidReader.dataReceived == 1) {
			
			#ifdef DEBUG
			sprintf(&str,"ID: %.5u\r",rfidReader.id.value);
			usart0_putString(str);
			
			#endif
			if (searchId(rfidReader.id.value)) {
				unlock();
				} else {
				#ifdef DEBUG
				usart0_putString("Cartão não cadastrado!\n");
				//unlock();
				#endif
			}
			rfidReader.dataReceived = 0;
			rfidReader.state = startBitLow;
			
			if((PINC & (1<<0)) == 0){ 
				if(!searchId(rfidReader.id.value)){
					if(count>256){ usart0_putString("Estouro da memória eeprom!\n");}
					else{
						eeprom_write_dword (count*4, rfidReader.id.value);
						usart0_putString("Id gravado com sucesso");
						count++;
						eeprom_update_dword (0, count);
					}
				}
			}
		}
		
		if((PINC & (1<<0)) == 0){
			PORTD = 0b00100000;	
		} else{
			PORTD = 0b00000000; 
		}
		
	 }

 }