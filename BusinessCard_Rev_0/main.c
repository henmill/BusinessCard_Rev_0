#include <atmel_start.h>
#include <stdio.h>
#include <util/delay.h>

void slider_to_state(void);
void state_to_LED(uint8_t state);

/*----------------------------------------------------------------------------
 *   Extern variables (originally declared elsewhere)
 *----------------------------------------------------------------------------*/
extern volatile uint8_t measurement_done_touch;
extern volatile uint8_t t1callbackflag;
extern volatile uint16_t t1cnt;
extern volatile uint16_t t1cntmax;

/*----------------------------------------------------------------------------
 *   Global variables
 *----------------------------------------------------------------------------*/
volatile uint16_t scroll_val = 0;
volatile uint16_t old_scroll_val = 0;
volatile uint8_t slider_status = 0;
volatile uint8_t LED_state = 0;	

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	// light up the leds sequentially on startup
	LED1_set_level(true); _delay_ms(60); LED1_set_level(false);
	LED2_set_level(true); _delay_ms(60); LED2_set_level(false);
	LED3_set_level(true); _delay_ms(60); LED3_set_level(false);
	LED4_set_level(true); _delay_ms(60); LED4_set_level(false);
	LED5_set_level(true); _delay_ms(60); LED5_set_level(false);
	LED6_set_level(true); _delay_ms(60); LED6_set_level(false);
	LED7_set_level(true); _delay_ms(60); LED7_set_level(false);
	LED6_set_level(true); _delay_ms(60); LED6_set_level(false);
	LED5_set_level(true); _delay_ms(60); LED5_set_level(false);
	LED4_set_level(true); _delay_ms(60); LED4_set_level(false);
	LED3_set_level(true); _delay_ms(60); LED3_set_level(false);
	LED2_set_level(true); _delay_ms(60); LED2_set_level(false);
	LED1_set_level(true); _delay_ms(60); LED1_set_level(false);
	
	//sleep_enter();
	//SLEEP_MODE_PWR_SAVE  --> PTC can wake from power save mode according to datasheet
	// look into PCINT (pin change) interrupt as method of waking
	//t1cnt = 0;

	/* Replace with your application code */
	while (1) 
	{
		// HAPPY WITH THIS, next investigate timer based to save battery
		
		touch_process();
		
		if(t1callbackflag == 1)
		{
			t1callbackflag = 0;			
			
			if(measurement_done_touch){
				measurement_done_touch = 0;
				
				slider_status = get_scroller_state(0);
				scroll_val = get_scroller_position(0);
				
				if(slider_status != 0u){		//if slider has anything going on, process it
					slider_to_state();
				}
				else{						//otherwise, turn off LEDs
					LED_state = 0;
				}
				
				state_to_LED(LED_state);	//decode slider position to LEDs
			}
			
		}		
		
	}
}

void slider_to_state(void)
{
	if(scroll_val <= 146){
		LED_state = 1;
	}
	else if((scroll_val > 147)&&(scroll_val <= 292))
	{
		LED_state = 2;
	}
	else if((scroll_val > 293)&&(scroll_val <= 438))
	{
		LED_state = 3;
	}
	else if((scroll_val > 439)&&(scroll_val <= 585))
	{
		LED_state = 4;
	}
	else if((scroll_val > 586)&&(scroll_val <= 731))
	{
		LED_state = 5;
	}
	else if((scroll_val > 732)&&(scroll_val <= 877))
	{
		LED_state = 6;
	}
	else if(scroll_val > 873){
		LED_state = 7;
	}
}

void state_to_LED(uint8_t state)
{
	switch(state)
	{
		case 0: LED1_set_level(false);LED2_set_level(false);LED3_set_level(false);LED4_set_level(false);LED5_set_level(false);LED6_set_level(false);LED7_set_level(false);
				break;
		case 1: LED1_set_level(true); 
				LED2_set_level(false); LED3_set_level(false);LED4_set_level(false); 
				LED5_set_level(false); LED6_set_level(false);LED7_set_level(false);
				break;
		case 2: LED2_set_level(true); 
				LED1_set_level(false); LED3_set_level(false);LED4_set_level(false);
				LED5_set_level(false); LED6_set_level(false);LED7_set_level(false);
				break;
		case 3: LED3_set_level(true); 
				LED1_set_level(false); LED2_set_level(false);LED4_set_level(false);
				LED5_set_level(false); LED6_set_level(false);LED7_set_level(false);
				break;
		case 4: LED4_set_level(true); 
				LED1_set_level(false); LED2_set_level(false);LED3_set_level(false); 
				LED5_set_level(false); LED6_set_level(false);LED7_set_level(false);
				break;
		case 5: LED5_set_level(true); 
				LED1_set_level(false); LED2_set_level(false);LED3_set_level(false); 
				LED4_set_level(false); LED6_set_level(false);LED7_set_level(false);
				break;
		case 6: LED6_set_level(true); 
				LED1_set_level(false); LED2_set_level(false);LED3_set_level(false); 
				LED4_set_level(false); LED5_set_level(false);LED7_set_level(false);
				break;
		case 7: LED7_set_level(true); 
				LED1_set_level(false); LED2_set_level(false);LED3_set_level(false); 
				LED4_set_level(false); LED5_set_level(false);LED6_set_level(false);
				break;
		default: LED1_set_level(false);LED2_set_level(false);LED3_set_level(false);LED4_set_level(false);LED5_set_level(false);LED6_set_level(false);LED7_set_level(false);
				break;
	}
}
