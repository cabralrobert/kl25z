#include <stdio.h>
#include "freedom.h"
#include "common.h"
#include "adc.h"
#include "gpio.h"

extern char *_sbrk(int len);
uint16_t adc = 0;

void initPulsioximeter(){

	gpio_direction(PORT_D,1,INPUT,NO_PULL_RESISTOR);	//13
	gpio_direction(PORT_D,3,INPUT,NO_PULL_RESISTOR);	//12
	gpio_direction(PORT_D,2,INPUT,NO_PULL_RESISTOR);	//11
	gpio_direction(PORT_D,0,INPUT,NO_PULL_RESISTOR);	//10
	gpio_direction(PORT_D,5,INPUT,NO_PULL_RESISTOR);	//9
	gpio_direction(PORT_A,13,INPUT,NO_PULL_RESISTOR);	//8
	gpio_direction(PORT_C,9,INPUT,NO_PULL_RESISTOR);	//7
	gpio_direction(PORT_C,8,INPUT,NO_PULL_RESISTOR);	//6

} 

// Main program
int main(void)
{

	
//	uint32_t i = 0;
//	uint8_t led = 0;

	gpio_direction(PORT_A,13,INPUT,NO_PULL_RESISTOR);	
	gpio_direction(PORT_B,19,OUTPUT,NO_PULL_RESISTOR);	
	gpio_direction(PORT_B,18,OUTPUT,NO_PULL_RESISTOR);	

	uart_init(115200);
	setvbuf(stdin, NULL, _IONBF, 0);        // No buffering

	tests();

	for(;;)    
    {     
      // Tecla está pressionada?   
      if(gpio_read(PORT_A,13))   
      {   
         // Não, liga o LED Vermeho e desliga o Verde.   
         gpio_set(PORT_B,19,HIGH);     // Desliga LED Verde.   
         gpio_set(PORT_B,18,LOW);     // Liga LED Vermelho.   
      }   
      else   
      {   
         gpio_set(PORT_B,19,LOW);     // Desliga LED Verde.   
         gpio_set(PORT_B,18,HIGH);     // Liga LED Vermelho.   
        // Sim, liga o LED Verde e desliga o Vermelho.   
      }
		printf("%d\n\r", gpio_read(PORT_A,13));   
    }   

}
