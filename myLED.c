#include "myLED.h"

const char numbers[12] = {
    0xF5, // 0
    0x05, // 1
    0x76, // 2
    0x57, // 3
    0x87, // 4
    0xD3, // 5
    0xF3, // 6
    0x45, // 7
    0xF7, // 8
    0xD7, // 9
	0x00,	//LED OFF
	0x02	// '-'
};

const char letters[21] = {
    0xE7, // A
    0xF7, // B
    0xF0, // C
    0xF5, // D
    0xF2, // E
    0xE2, // F
		0x00,	//G-OFF
    0xA7, // H
    0x05, // I
    0x35, // J
		0x00,	//K-OFF
    0xB0, // L
		0x00,	//M-OFF
    0xE5, // N
    0xF5, // O
    0xE6, // P
		0x00,	//Q-OFF
		0x00,	//R-OFF
    0xD3, // S
		0x00,	//T-OFF
    0xB5  // U
};

//unsigned char points[5]={
//		0x01, //K5
//		0x02, //K4
//		0x04, //K3
//		0x08, //K2
//		0x10, //K1
//};

unsigned char points[5]={
	~	0x01, //K5
	~	0x02, //K4
	~	0x04, //K3
	~	0x08, //K2
	~	0x10, //K1
};

uint16_t led_data16[6];


void SCK(){
	HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SCK_GPIO_Port, SCK_Pin, GPIO_PIN_SET);
}

void LATCH(){
	HAL_GPIO_WritePin(RCK_GPIO_Port, RCK_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RCK_GPIO_Port, RCK_Pin, GPIO_PIN_SET);
}

void Data8_put(uint8_t d8){
	for(int index=0; index<8; index++){
		HAL_GPIO_WritePin(MOSI_GPIO_Port, MOSI_Pin,(GPIO_PinState)((d8>>index) & 0x01));
		SCK();
	}
}

void Data16_put(uint16_t d16){
	for(int index= 0; index <16; index++){
		HAL_GPIO_WritePin(MOSI_GPIO_Port, MOSI_Pin, (GPIO_PinState)((d16 >> index) & 0x01));
		SCK();
	}
}

void LED_data(uint8_t n){
	Data8_put(numbers[n]);
	LATCH();
}

void LED_put(uint8_t n, uint8_t p){
	led_data16[p]= (numbers[n] << 8) | points[5-p];
	Data16_put(led_data16[p]);
	LATCH();
}

void LED_putstring(char* s){
	for(int index=0;index<=4;index++){
		if((s[index] >= '0') && (s[index] <= '9')){
			led_data16[index]= (numbers[s[index]-'0'] << 8) | points[5-index -1];
		}
		else if((s[index] >= 'A') && (s[index] <= 'U')){
			led_data16[index]= (letters[s[index]-'A'] << 8) | points[5-index -1];
		}
		else
			led_data16[index]= (0x00 << 8) | points[5-index -1];
		
		Data16_put(led_data16[index]);
		LATCH();
	}
}

void display_LED(int num, uint8_t start, uint8_t stop){	
	for(int pos=stop; pos >= start; pos --){
		LED_put(num %10, pos);
		num /=10;
		//if(num == 0) break;
	}
}

void blink_LED(int num,long long *last_blink, uint8_t start, uint8_t stop){
	if( HAL_GetTick() - *last_blink <=250)
		display_LED(num, start, stop);
	else if(HAL_GetTick() - *last_blink <=500){
		for(int index=start; index<=stop;index++){
			LED_put(10, index);
		}
	}
	else
		*last_blink= HAL_GetTick();
}

void display_mm_ss(int mm,int ss,long long *last_blink, int mode_blink){
	switch(mode_blink){
		case NO_MODE:	
			display_LED(mm, 1, 2);
			LED_put(11,3); //K3: '-'
			display_LED(ss, 4, 5);
			break;
		case MODE_SS:	
			display_LED(mm, 1, 2);
			LED_put(11,3); //K3: '-'
			blink_LED(ss,last_blink, 4, 5);
			break;
		case MODE_MM:	
			blink_LED(mm,last_blink, 1, 2);
			LED_put(11,3); //K3: '-'
			display_LED(ss, 4, 5);
			break;
		
		
	}
}
