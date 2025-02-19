#include <stdio.h>
#include <avr/io.h>

#include "HD44780.hpp"
#include "libADC.hpp"
#include "uart_buffer.hpp"

#include "Arduino.h"

int main() {
  LCD_Initalize();
  LCD_Clear();
  LCD_GoTo(0, 0);
  LCD_WriteText((char*)"tamagotchi ON ");
  _delay_ms(2000);
  LCD_Clear();

  ADC_Init();

  int health = 100;
  int counter = 0;
  char buffer[10];  // Asegúrate de que el tamaño del buffer sea suficiente

  // initialize Serial (UART) communication
  uart_init(9600,0);
  sei();

  uint8_t data;
  uart_send_string((uint8_t*)"0.Status; 1.Feed; 2.Play \n");
  while (1) {
    LCD_GoTo(0,0);
    LCD_WriteText("TAMA ");
    LCD_GoTo(1,1);
    sprintf(buffer, "Health: %d  ", health);  // Convierte el entero en una cadena
    LCD_WriteText(buffer);  // Muestra el número en el LCD
    _delay_ms(1000);
    counter++;

    // LAB 3
    if (uart_read_count() > 0) {
      data = uart_read();
      // when key '0' is pressed
      if (data == '0') {
        // do something
        uart_send_string((uint8_t*)buffer);
      }
      // when key '1' is pressed
      else if (data == '1') {
        // do something else
        uart_send_string((uint8_t*)"Tamagotchi fed.\n");
        health+=10;

      }
      else if (data == '2') {
        //do something else
        uart_send_string((uint8_t*)"Played with Tamagotchi.\n");
        health+=5;

      }
    }

    if (counter%2==0){
      health--;
    }
    if (health>100){
      health=100;
    }
    _delay_ms(1000);
  }
  _delay_ms(1000);
  return 0;
}
