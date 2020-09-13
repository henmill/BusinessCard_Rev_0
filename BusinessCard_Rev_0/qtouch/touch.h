/*============================================================================
Filename : touch.h
Project : QTouch Modular Library
Purpose : configuation macros for touch library

This file is part of QTouch Modular Library Release 7.3.1 application.

Important Note: Do not edit this file manually.
                Use QTouch Configurator within Atmel Start to apply any
                modifications to this file.

Usage License: Refer license.h file for license information
Support: Visit http://www.microchip.com/support/hottopics.aspx
               to create MySupport case.

------------------------------------------------------------------------------
Copyright (c) 2020 Microchip. All rights reserved.
------------------------------------------------------------------------------
============================================================================*/

#ifndef TOUCH_H
#define TOUCH_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *     include files
 *----------------------------------------------------------------------------*/

#include <compiler.h>

#include "touch_api_ptc.h"
#include "tc8.h"

/**********************************************************/
/******************* Acquisition controls *****************/
/**********************************************************/
/* Defines the Measurement Time in milli seconds.
 * Range: 1 to 255.
 * Default value: 20.
 */
#define DEF_TOUCH_MEASUREMENT_PERIOD_MS 20		//was 50. not sure where this is set in START config

/* Defines the Type of sensor
 * Default value: NODE_MUTUAL.
 */
#define DEF_SENSOR_TYPE NODE_SELFCAP

/* Set sensor calibration mode for charge share delay ,Prescaler or series resistor.
 * Range: CAL_AUTO_TUNE_NONE / CAL_AUTO_TUNE_RSEL / CAL_AUTO_TUNE_PRSC / CAL_AUTO_TUNE_CSD
 * Default value: CAL_AUTO_TUNE_NONE.
 */
#define DEF_PTC_CAL_OPTION CAL_AUTO_TUNE_NONE

/* Defines the interrupt priority for the PTC. Set low priority to PTC interrupt for applications having interrupt time
 * constraints. Range: 0 to 2 Default: 2 (Lowest Priority)
 */
#define DEF_PTC_INTERRUPT_PRIORITY None

/* Calibration option to ensure full charge transfer */
/* Bits 7:0 = XX | TT SELECT_TAU | X | CAL_OPTION */
#define DEF_PTC_TAU_TARGET CAL_CHRG_5TAU
#define DEF_PTC_CAL_AUTO_TUNE (uint8_t)((DEF_PTC_TAU_TARGET << CAL_CHRG_TIME_POS) | DEF_PTC_CAL_OPTION)

/* Set default bootup acquisition frequency.
 * Range: FREQ_SEL_0 - FREQ_SEL_15 , FREQ_SEL_SPREAD
 * Default value: FREQ_SEL_0.
 */
#define DEF_SEL_FREQ_INIT FREQ_SEL_0

/*----------------------------------------------------------------------------
 *     defines
 *----------------------------------------------------------------------------*/

/**********************************************************/
/***************** Node Params   ******************/
/**********************************************************/
/* Acquisition Set 1 */
/* Defines the number of sensor nodes in the acquisition set
 * Range: 1 to 65535.
 * Default value: 1
 */
#define DEF_NUM_CHANNELS (5)

/* Defines self-cap node parameter setting
 * {X-line, Y-line, Charge Share Delay, Prescaler, NODE_G(Analog Gain , Digital Gain), filter level}
 */
#define NODE_0_PARAMS                                                                                                  \
	{                                                                                                                  \
		X_NONE, Y(19), 0, PRSC_DIV_SEL_8, NODE_GAIN(GAIN_1, GAIN_1), FILTER_LEVEL_16                                   \
	}
#define NODE_1_PARAMS                                                                                                  \
	{                                                                                                                  \
		X_NONE, Y(18), 0, PRSC_DIV_SEL_8, NODE_GAIN(GAIN_1, GAIN_1), FILTER_LEVEL_16                                   \
	}
#define NODE_2_PARAMS                                                                                                  \
	{                                                                                                                  \
		X_NONE, Y(15), 0, PRSC_DIV_SEL_8, NODE_GAIN(GAIN_1, GAIN_1), FILTER_LEVEL_16                                   \
	}
#define NODE_3_PARAMS                                                                                                  \
	{                                                                                                                  \
		X_NONE, Y(14), 0, PRSC_DIV_SEL_8, NODE_GAIN(GAIN_1, GAIN_1), FILTER_LEVEL_16                                   \
	}
#define NODE_4_PARAMS                                                                                                  \
	{                                                                                                                  \
		X_NONE, Y(13), 0, PRSC_DIV_SEL_8, NODE_GAIN(GAIN_1, GAIN_1), FILTER_LEVEL_16                                   \
	}

/**********************************************************/
/***************** Key Params   ******************/
/**********************************************************/
/* Defines the number of key sensors
 * Range: 1 to 65535.
 * Default value: 1
 */
#define DEF_NUM_SENSORS (5)

/* Defines Key Sensor setting
 * {Sensor Threshold, Sensor Hysterisis, Sensor AKS}
 */
#define KEY_0_PARAMS                                                                                                   \
	{                                                                                                                  \
		20, HYST_25, AKS_GROUP_1                                                                                       \
	}
#define KEY_1_PARAMS                                                                                                   \
	{                                                                                                                  \
		20, HYST_25, AKS_GROUP_1                                                                                       \
	}
#define KEY_2_PARAMS                                                                                                   \
	{                                                                                                                  \
		20, HYST_25, AKS_GROUP_1                                                                                       \
	}
#define KEY_3_PARAMS                                                                                                   \
	{                                                                                                                  \
		20, HYST_25, AKS_GROUP_1                                                                                       \
	}
#define KEY_4_PARAMS                                                                                                   \
	{                                                                                                                  \
		20, HYST_25, AKS_GROUP_1                                                                                       \
	}

/* De-bounce counter for additional measurements to confirm touch detection
 * Range: 0 to 255.
 * Default value: 4.
 */
#define DEF_TOUCH_DET_INT 4

/* De-bounce counter for additional measurements to confirm away from touch signal
 * to initiate Away from touch re-calibration.
 * Range: 0 to 255.
 * Default value: 5.
 */
#define DEF_ANTI_TCH_DET_INT 5

/* Threshold beyond with automatic sensor recalibration is initiated.
 * Range: RECAL_100/ RECAL_50 / RECAL_25 / RECAL_12_5 / RECAL_6_25 / MAX_RECAL
 * Default value: RECAL_100.
 */
#define DEF_ANTI_TCH_RECAL_THRSHLD RECAL_100

/* Rate at which sensor reference value is adjusted towards sensor signal value
 * when signal value is greater than reference.
 * Units: 200ms
 * Range: 0-255
 * Default value: 20u = 4 seconds.
 */
#define DEF_TCH_DRIFT_RATE 20

/* Rate at which sensor reference value is adjusted towards sensor signal value
 * when signal value is less than reference.
 * Units: 200ms
 * Range: 0-255
 * Default value: 5u = 1 second.
 */
#define DEF_ANTI_TCH_DRIFT_RATE 5

/* Time to restrict drift on all sensor when one or more sensors are activated.
 * Units: 200ms
 * Range: 0-255
 * Default value: 20u = 4 seconds.
 */
#define DEF_DRIFT_HOLD_TIME 20

/* Set mode for additional sensor measurements based on touch activity.
 * Range: REBURST_NONE / REBURST_UNRESOLVED / REBURST_ALL
 * Default value: REBURST_UNRESOLVED
 */
#define DEF_REBURST_MODE REBURST_UNRESOLVED

/* Sensor maximum ON duration upon touch.
 * Range: 0-255
 * Default value: 0
 */
#define DEF_MAX_ON_DURATION 0

/**********************************************************/
/***************** Slider/Wheel Parameters ****************/
/**********************************************************/
/* Defines the number of scrollers (sliders or wheels)
 */
#define DEF_NUM_SCROLLERS (1)

/* Defines scroller parameter setting
 * {touch_scroller_type, touch_start_key, touch_scroller_size,
 * SCROLLER_RESOL_DEADBAND(touch_scroller_resolution,touch_scroller_deadband), touch_scroller_hysterisis,
 * touch_contact_min_threshold} Configuring contact_min_threshold: By default, contact_min_threshold parameter should be
 * set equal to threshold value of the underlying keys. Then the parameter has to be tuned based on the actual contact
 * size of the touch when moved over the scroller. The contact size of the moving touch can be observed from
 * "contact_size" parameter on scroller runtime data structure.
 */
#define SCROLLER_0_PARAMS                                                                                              \
	{                                                                                                                  \
		SCROLLER_TYPE_SLIDER, 0, 5, SCROLLER_RESOL_DEADBAND(SCR_RESOL_10_BIT, SCR_DB_10_PERCENT), 8, 20                \
	}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // TOUCH_C
