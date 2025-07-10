/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include "myGPIO.h"
#include "myLed.h"
/* USER CODE END Includes */
//--------------------------
/* USER CODE BEGIN PV */
uint8_t D1_Val=0, P1State=BUTTON_INACTIVE, 
									P2State=BUTTON_INACTIVE, 
									P3State=BUTTON_INACTIVE, 
									P4State=BUTTON_INACTIVE, flag=0;
int num= 12345;
uint8_t hh=12,mm=00,ss=00;
int led_blink= NO_MODE;
long long lastToggle, lastButton=0, lastCurrent=0, lastBlink;
int sp=0;
int tick=5;

void bai2_LED7DOAN(){
		uint8_t curP1State= PushButton_read(P1);
		uint8_t curP2State= PushButton_read(P2);
		uint8_t curP3State= PushButton_read(P3);
		uint8_t curP4State= PushButton_read(P4);
		if (curP1State == BUTTON_ACTIVE && P1State == BUTTON_INACTIVE){
        	num++;
					flag=0;
    }
		else if (curP2State == BUTTON_ACTIVE && P2State == BUTTON_INACTIVE){
        num--;
				flag=0;
    }
		else if (curP3State == BUTTON_ACTIVE && P3State == BUTTON_INACTIVE){
        num=12345;
				flag=0;
    }
		else if (curP4State == BUTTON_ACTIVE && P4State == BUTTON_INACTIVE){
				lastCurrent= HAL_GetTick();
				flag =1;
       
    }
		if(flag){
			 if(HAL_GetTick() - lastCurrent > 1000){
					num=(num > 99999) ? 99999 : num+1 ;
					lastCurrent= HAL_GetTick();
				}
		}
		P1State = curP1State;
		P2State = curP2State;
		P3State = curP3State;
		P4State = curP4State;
		//Display
		display_LED(num, 1, 5);
}
//------------------------------------------
void counter_mm_ss(long long *dem, int mode, uint8_t *mm, uint8_t *ss){
	if(HAL_GetTick() - *dem >= 1000){
		switch(mode){
			case 0:
				break;
			case 1:	//CTU
				*ss= (*ss +1) % 60;
				if(*ss==0) *mm= (*mm +1)%60;
				break;
			case 2:	//CTD
				if((*ss ==0) &&(*mm >0)){
					*ss=59;
					*mm-=1;
				}
				else if((*ss !=0) &&(*mm >=0))
					*ss-=1;
				if(*mm<0)	*mm=0;
				break;
		}
		*dem= HAL_GetTick();
	}
}
void bai3_LED7DOAN(){
	uint8_t curP1State= PushButton_read(P1);
	uint8_t curP2State= PushButton_read(P2);
	uint8_t curP3State= PushButton_read(P3);
	uint8_t curP4State= PushButton_read(P4);
	//Read button status
	if (curP1State == BUTTON_ACTIVE && P1State == BUTTON_INACTIVE){
        flag ^=1;
		D1_Val= CTU;
		lastCurrent= HAL_GetTick();
  }
	else if (curP2State == BUTTON_ACTIVE && P2State == BUTTON_INACTIVE){
        flag ^=1;
		D1_Val= CTD;
		lastCurrent= HAL_GetTick();
  }
	else if (curP3State == BUTTON_ACTIVE && P3State == BUTTON_INACTIVE){
        led_blink= (led_blink +1)%3;
		lastBlink= HAL_GetTick();
  }
	else if (curP4State == BUTTON_ACTIVE && P4State == BUTTON_INACTIVE){
		switch(led_blink){
			case NO_MODE:
				break;
			case MODE_SS:
				ss= (ss+1)%60;
				break;
			case MODE_MM:
				mm= (mm+1)%60;
				break;						
		}				      
   }
	P1State = curP1State;
	P2State = curP2State;
	P3State = curP3State;
	P4State = curP4State;
	if(flag)
		counter_mm_ss(&lastCurrent, D1_Val, &mm, &ss);
	//Display
	display_mm_ss(mm, ss, &lastBlink, led_blink);
}
/* USER CODE END PV */
int main(void){
	/* USER CODE BEGIN 2 */
	HAL_GPIO_WritePin(RCL_GPIO_Port, RCL_Pin, GPIO_PIN_RESET); //enable 74HC594
	Light_cmd(D1,D_OFF);
	Light_cmd(D2,D_OFF);
	/* USER CODE END 2 */
	
}
