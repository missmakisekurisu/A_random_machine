#include "encoder.h"
#include "usbd_custom_hid_if.h"

int currentRad = 0;
extern USBD_HandleTypeDef hUsbDeviceFS;

//struct mouseHID_t {
//		uint8_t x;
//		uint8_t y;
//		uint8_t buttons;

//		int8_t wheel;
//}; 
// 
//struct mouseHID_t mouseHID;

 
T_MOUSEE_HID mouseHID = {0};


void key1_interupt_routine(void)
{
		currentRad = ENCODER_RESOLUTION/2;
}

    
uint8_t encoder_read_position(void){
    //if(!ENCODER_READ_Z){currentRad = 0;}
    static uint8_t state = 0;
    static uint8_t lastState = 0;
//    if(currentRad > ENCODER_RESOLUTION || currentRad <(-ENCODER_RESOLUTION)){
//        currentRad = 0;
//    }  
		
    
    //A->B: 00-10-01-00
    //B->A: 00-01-10-00    
    switch(state){
        case 0:{
            if(ENCODER_READ_A && ENCODER_READ_B && lastState != 0){
                currentRad = currentRad + (lastState == 1?(1):(-1));
                lastState = 0;
            }
            if(!ENCODER_READ_A){state = 1U;}
            if(!ENCODER_READ_B){state = 2U;}
            break;
        }
        case 1:{
            if(ENCODER_READ_A && ENCODER_READ_B){state = 0;}
            if(ENCODER_READ_A && (!ENCODER_READ_B)){
                lastState = state; 
                state = 2U;
            }
            break;
        }
        case 2:{
            if(ENCODER_READ_A && ENCODER_READ_B){state = 0;}
            if((!ENCODER_READ_A) && ENCODER_READ_B){
                lastState = state; 
                state = 1U;
            }
            break;
        }
        default: state = 0;
    }        
		if(currentRad < 0){currentRad = 0;}
		if(currentRad > ENCODER_RESOLUTION){currentRad = ENCODER_RESOLUTION;}
		mouseHID.x = 127U * currentRad/ENCODER_RESOLUTION;
		USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&mouseHID, sizeof(T_MOUSEE_HID));		
    return 0;
}

void encoder_Task(void){
	for(;1;){
		encoder_read_position();
	}
}
