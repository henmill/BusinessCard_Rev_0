/*
 * custom_stuff.c
 *
 * Created: 6/29/2020 10:29:28 PM
 *  Author: henmi
 */ 

#include <atmel_start.h>
#include <stdio.h>

volatile uint8_t t1callbackflag = 0;
volatile uint16_t t1cnt = 0;

volatile uint16_t t1cntmax = 4;