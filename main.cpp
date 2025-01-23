#include <stdio.h>
#include <avr/io.h>

#include "HD44780.hpp"
#include "libADC.hpp"
#include "uart_buffer.hpp"

#include "Arduino.h"

int ledPin = 13;

int main() {
  LCD_Initalize();
  LCD_Clear();
  LCD_GoTo(0, 0);
  LCD_WriteText((char*)"tamagotchi ON:");
  _delay_ms(2000);


  ADC_Init();

  pinMode(ledPin, OUTPUT);
  int health = 100;
  int counter = 0;

  LCD_Initalize();
  LCD_Clear();
  LCD_GoTo(0,0);
  char buffer[10];  // Asegúrate de que el tamaño del buffer sea suficiente
  sprintf(buffer, "Health: %d  ", health);  // Convierte el entero en una cadena
  LCD_WriteText(buffer);  // Muestra el número en el LCD
  // initialize Serial (UART) communication
  uart_init(9600,0);
  sei();

  uint8_t data;
  uart_send_string((uint8_t*)"0.Status; 1.Feed; 2.Play \n");
  while (1) {
    LCD_Initalize();
    LCD_Clear();
    LCD_GoTo(0,0);
    LCD_WriteText("Tamagotchi. ");
    sprintf(buffer, "Health: %d \n ", health); 
    counter++;

    // LAB 3
    if (uart_read_count() > 0) {
      data = uart_read();
      // when key '0' is pressed
      if (data == '0') {
        // do something
        uart_send_string((uint8_t*)buffer);
        LCD_Initalize();
        LCD_Clear();
        LCD_GoTo(0,0);        
        LCD_WriteText(buffer);
      }
      // when key '1' is pressed
      else if (data == '1') {
        // do something else
        uart_send_string((uint8_t*)"Tamagotchi fed.\n");
        LCD_Initalize();
        LCD_Clear();
        LCD_GoTo(0,0);
        LCD_WriteText(buffer);
        health+=10;
        LCD_Initalize();
        LCD_Clear();
        LCD_GoTo(0,0);
        LCD_WriteText(buffer);
      }
      else if (data == '2') {
        //do something else
        uart_send_string((uint8_t*)"Played with Tamagotchi.\n");
        LCD_Initalize();
        LCD_Clear();
        LCD_GoTo(0,0);
        LCD_WriteText(buffer);
        health+=5;
        LCD_Initalize();
        LCD_Clear();
        LCD_GoTo(0,0);
        LCD_WriteText(buffer);
      }
    }

    if (counter%2==0){
      health--;
    }
    if (health>=50){
      digitalWrite(ledPin, HIGH);
    }
    if (health<50){
      digitalWrite(ledPin, LOW);
    }
    _delay_ms(1000);
  }
  _delay_ms(1000);
  return 0;
}
