#ifndef _MYLED_H_
#define _MYLED_H_

#include "main.h"

#define				CTU					1
#define				CTD					2
//mode_blink
#define				NO_MODE			0	//LED display normal, no LED blinking
#define				MODE_SS			1	//Minute adjustment mode (2 minute LEDs flash continuously for 0.5s);
#define				MODE_MM			2 	//Second adjustment mode (2 second LEDs flash continuously for 0.5s);

void SCK();
void LATCH();
void Data8_put(uint8_t d8); //send 1 byte
void Data16_put(uint16_t d16);
void LED_data(uint8_t n); //display number, n: corresponding number '0-9', 10: LED OFF, 11: '-'
void LED_put(uint8_t n, uint8_t p); //display number, n: corresponding number, p: point, '1-5'
void LED_putstring(char* s); //send string, index max: 5
void display_LED(int num, uint8_t start, uint8_t stop);
void blink_LED(int num,long long *last_blink, uint8_t start, uint8_t stop); //blink cycle: 0.5,main:last_blink= HAL_GetTick()
void display_mm_ss(int mm,int ss,long long *last_blink, int mode_blink); 

extern const char numbers[12]; //0-9, offLed, '-'
extern const char letters[21];
extern unsigned char points[5];// K5-K1
extern uint16_t led_data16[6];
#endif	//_MYLED_H_
