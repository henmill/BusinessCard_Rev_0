/*
 * custom_stuff.c
 *
 * Created: 6/29/2020 10:29:28 PM
 *  Author: hank
 */ 

#include <atmel_start.h>
#include <stdio.h>


//volatile uint8_t t1callbackflag = 0;
//volatile uint16_t t1cnt = 0;
//uint16_t t1cntmax = 4;

volatile uint8_t t2callbackflag = 0;
volatile uint16_t t2cnt = 0;
uint16_t t2cntmax = 100;

volatile uint16_t wakecnt = 0;

uint8_t sleepmax = 200;
volatile uint16_t sleep_timer = 0;

