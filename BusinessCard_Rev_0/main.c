#include <atmel_start.h>
#include <stdio.h>
#include <util/delay.h>

const uint16_t t1cntmax = 10;

/*----------------------------------------------------------------------------
 *   Extern variables
 *----------------------------------------------------------------------------*/
extern volatile uint8_t measurement_done_touch;
extern volatile uint8_t t1callbackflag;
volatile uint16_t t1cnt;

/*----------------------------------------------------------------------------
 *   Global variables
 *----------------------------------------------------------------------------*/
uint16_t scroll_val = 0;
uint16_t old_scroll_val = 0;

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	LED1_set_level(true); _delay_ms(100);
	LED2_set_level(true); _delay_ms(100);
	LED3_set_level(true); _delay_ms(100);
	LED4_set_level(true); _delay_ms(100);
	LED5_set_level(true); _delay_ms(100);
	LED6_set_level(true); _delay_ms(100);
	LED7_set_level(true); _delay_ms(100); _delay_ms(200);
	
	LED1_set_level(false);
	LED2_set_level(false);
	LED3_set_level(false);
	LED4_set_level(false);
	LED5_set_level(false);
	LED6_set_level(false);
	LED7_set_level(false);
	
	t1cnt = 0;

	/* Replace with your application code */
	while (1) 
	{
		
		touch_process();
		
		if(measurement_done_touch){
			measurement_done_touch = 0;
			
			scroll_val = get_scroller_position(0);
			
		}
		
		if(t1callbackflag)
		{
			t1callbackflag = 0;		//reset the flag
			
			old_scroll_val = scroll_val;
			
			t1cnt++;
			
			//printf("%d \r\n",scroll_val);
			if(t1cnt >= t1cntmax){
				t1cnt = 0;
				
				if(scroll_val == old_scroll_val){
					scroll_val = 0;
				}
			}
		}
		
		if(scroll_val == 0){
			LED1_set_level(false);LED2_set_level(false);LED3_set_level(false);LED4_set_level(false);LED5_set_level(false);LED6_set_level(false);LED7_set_level(false);
		}
		else if((scroll_val > 15)&&(scroll_val <= 120)){
			LED1_set_level(true); LED2_set_level(false); LED3_set_level(false);
			LED4_set_level(false); LED5_set_level(false); LED6_set_level(false);
			LED7_set_level(false);
		}
		else if((scroll_val > 121)&&(scroll_val <= 271))
		{
			LED2_set_level(true); LED1_set_level(false); LED3_set_level(false);
			LED4_set_level(false); LED5_set_level(false); LED6_set_level(false);
			LED7_set_level(false);
		}
		else if((scroll_val > 272)&&(scroll_val <= 420))
		{
			LED3_set_level(true); LED1_set_level(false); LED2_set_level(false);
			LED4_set_level(false); LED5_set_level(false); LED6_set_level(false);
			LED7_set_level(false);
		}
		else if((scroll_val > 421)&&(scroll_val <= 571))
		{
			LED4_set_level(true); LED1_set_level(false); LED2_set_level(false);
			LED3_set_level(false); LED5_set_level(false); LED6_set_level(false);
			LED7_set_level(false);
		}
		else if((scroll_val > 572)&&(scroll_val <= 721))
		{
			LED5_set_level(true); LED1_set_level(false); LED2_set_level(false);
			LED3_set_level(false); LED4_set_level(false); LED6_set_level(false);
			LED7_set_level(false);
		}
		else if((scroll_val > 722)&&(scroll_val <= 871))
		{
			LED6_set_level(true); LED1_set_level(false); LED2_set_level(false);
			LED3_set_level(false); LED4_set_level(false); LED5_set_level(false);
			LED7_set_level(false);
		}
		else if(scroll_val > 872){
			LED7_set_level(true); LED1_set_level(false); LED2_set_level(false);
			LED3_set_level(false); LED4_set_level(false); LED5_set_level(false);
			LED6_set_level(false);
		}
		
	}
}
