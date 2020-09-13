#include <atmel_start.h>
#include <stdio.h>
#include <util/delay.h>

void slider_to_state(void);
void state_to_LED(uint8_t state);
void sleep_init(void);

void sleep_routine(void);
void quick_wake(void);
void config_pins(void);

/*----------------------------------------------------------------------------
 *   Extern variables (originally declared elsewhere)
 *----------------------------------------------------------------------------*/
extern volatile uint8_t measurement_done_touch;

extern volatile uint8_t t2callbackflag;
extern volatile uint16_t t2cnt;
extern uint16_t t2cntmax;

extern uint8_t sleepmax;
extern volatile uint16_t sleep_timer;

/*----------------------------------------------------------------------------
 *   Global variables
 *----------------------------------------------------------------------------*/
volatile uint16_t scroll_val = 0;
volatile uint16_t old_scroll_val = 0;
volatile uint8_t slider_status = 0;
volatile uint8_t LED_state = 0;	

/*----------------------------------------------------------------------------
 *   State flags
 *----------------------------------------------------------------------------*/
volatile uint8_t awake = 1;


int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	sleep_init();		//simply sets the sleep mode (POWER SAVE)
	
	// light up the leds sequentially on startup
	/*
	
					  *	4	
				  3*	  *5
				 2*		   *6
				   1*    *7
	*/
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
	

	/* Replace with your application code */
	while (1) 
	{
	
		if(awake == 1u){
			touch_process();
		}
		else{
			sleep_routine();
		}		
				
		if(measurement_done_touch){
			measurement_done_touch = 0;
					
			slider_status = get_scroller_state(0);
			scroll_val = get_scroller_position(0);
					
			if(slider_status != 0u){		//if slider has anything going on, process it
				sleep_timer = 0;			//this should keep it awake
				slider_to_state();
			}
			else{							//otherwise, turn off LEDs
				LED_state = 0;
				sleep_timer++;				//sleep_timer increments every time a measurement is completed
				//LED4_toggle_level();	//this will show me how fast the measurement_done_touch flag gets set
			}
		}
		state_to_LED(LED_state);	//decode slider position to LEDs
		
		if(sleep_timer >= sleepmax){	//sleepmax = 200; this gives about 6 seconds before timeout
			sleep_timer = 0;
			awake = 0;					//set the awake flag low
		}
		else{}
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

void sleep_init(void)
{
	set_sleep_mode(SLEEP_MODE_PWR_SAVE);
}

void sleep_routine(void)
{
	sleep_enable();
	sei();				//make sure interrupts are enabled so timer2 will wake us up
	sleep_cpu();
	sleep_disable();	//this is where the code will resume upon wakeup, which is caused by T2 overflow
	
	t2cnt++;
	if(t2cnt >= t2cntmax){		//t2cntmax = 100 (defined in custom stuff.c)
		t2cnt = 0;
		quick_wake();
	}
}

void quick_wake(void)
{
	awake = 1;
	sleep_timer = 180;
}