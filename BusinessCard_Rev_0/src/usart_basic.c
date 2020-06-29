/**
 * \file
 *
 * \brief USART basic driver.
 *
 (c) 2018 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms,you may use this software and
    any derivatives exclusively with Microchip products.It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

/**
 * \defgroup doc_driver_usart_basic USART Basic
 * \ingroup doc_driver_usart
 *
 * \section doc_driver_usart_basic_rev Revision History
 * - v0.0.0.1 Initial Commit
 *
 *@{
 */
#include <compiler.h>
#include <clock_config.h>
#include <usart_basic.h>
#include <atomic.h>

#include <stdio.h>

#if defined(__GNUC__)

int USART_0_printCHAR(char character, FILE *stream)
{
	USART_0_write(character);
	return 0;
}

FILE USART_0_stream = FDEV_SETUP_STREAM(USART_0_printCHAR, NULL, _FDEV_SETUP_WRITE);

#elif defined(__ICCAVR__)

int putchar(int outChar)
{
	USART_0_write(outChar);
	return outChar;
}
#endif

/**
 * \brief Initialize USART interface
 * If module is configured to disabled state, the clock to the USART is disabled
 * if this is supported by the device's clock system.
 *
 * \return Initialization status.
 * \retval 0 the USART init was successful
 * \retval 1 the USART init was not successful
 */
int8_t USART_0_init()
{

	// Module is in UART mode

	/* Enable USART1 */
	PRR0 &= ~(1 << PRUSART1);

#define BAUD 9600

#include <utils/setbaud.h>

	UBRR1H = UBRRH_VALUE;
	UBRR1L = UBRRL_VALUE;

	UCSR1A = USE_2X << U2X1 /*  */
	         | 0 << MPCM1;  /* Multi-processor Communication Mode: disabled */

	UCSR1B = 1 << RXCIE1    /* RX Complete Interrupt Enable: enabled */
	         | 0 << TXCIE1  /* TX Complete Interrupt Enable: disabled */
	         | 0 << UDRIE1  /* USART Data Register Empty Interupt Enable: disabled */
	         | 1 << RXEN1   /* Receiver Enable: enabled */
	         | 1 << TXEN1   /* Transmitter Enable: enabled */
	         | 0 << UCSZ12; /*  */

	// UCSR1C = (0 << UMSEL11) | (0 << UMSEL10) /*  */
	//		 | (0 << UPM11) | (0 << UPM10) /* Disabled */
	//		 | 0 << USBS1 /* USART Stop Bit Select: disabled */
	//		 | (1 << UCSZ11) | (1 << UCSZ10); /* 8-bit */

	// UCSR1D = 0 << RXSIE /* USART RX Start Interrupt Enable: disabled */
	//		 | 0 << SFDE; /* Start Frame Detection Enable: disabled */

#if defined(__GNUC__)
	stdout = &USART_0_stream;
#endif

	return 0;
}

/**
 * \brief Enable RX and TX in USART_0
 * 1. If supported by the clock system, enables the clock to the USART
 * 2. Enables the USART module by setting the RX and TX enable-bits in the USART control register
 *
 * \return Nothing
 */
void USART_0_enable()
{
	UCSR1B |= ((1 << TXEN1) | (1 << RXEN1));
}

/**
 * \brief Enable RX in USART_0
 * 1. If supported by the clock system, enables the clock to the USART
 * 2. Enables the USART module by setting the RX enable-bit in the USART control register
 *
 * \return Nothing
 */
void USART_0_enable_rx()
{
	UCSR1B |= (1 << RXEN1);
}

/**
 * \brief Enable TX in USART_0
 * 1. If supported by the clock system, enables the clock to the USART
 * 2. Enables the USART module by setting the TX enable-bit in the USART control register
 *
 * \return Nothing
 */
void USART_0_enable_tx()
{
	UCSR1B |= (1 << TXEN1);
}

/**
 * \brief Disable USART_0
 * 1. Disables the USART module by clearing the enable-bit(s) in the USART control register
 * 2. If supported by the clock system, disables the clock to the USART
 *
 * \return Nothing
 */
void USART_0_disable()
{
	UCSR1B &= ~((1 << TXEN1) | (1 << RXEN1));
}

/**
 * \brief Get recieved data from USART_0
 *
 * \return Data register from USART_0 module
 */
uint8_t USART_0_get_data()
{
	return UDR1;
}

/**
 * \brief Check if the usart can accept data to be transmitted
 *
 * \return The status of USART TX data ready check
 * \retval false The USART can not receive data to be transmitted
 * \retval true The USART can receive data to be transmitted
 */
bool USART_0_is_tx_ready()
{
	return (UCSR1A & (1 << UDRE1));
}

/**
 * \brief Check if the USART has received data
 *
 * \return The status of USART RX data ready check
 * \retval true The USART has received data
 * \retval false The USART has not received data
 */
bool USART_0_is_rx_ready()
{
	return (UCSR1A & (1 << RXC1));
}

/**
 * \brief Check if USART_0 data is transmitted
 *
 * \return Receiver ready status
 * \retval true  Data is not completely shifted out of the shift register
 * \retval false Data completely shifted out if the USART shift register
 */
bool USART_0_is_tx_busy()
{
	return (!(UCSR1A & (1 << TXC1)));
}

/**
 * \brief Read one character from USART_0
 *
 * Function will block if a character is not available.
 *
 * \return Data read from the USART_0 module
 */
uint8_t USART_0_read()
{
	while (!(UCSR1A & (1 << RXC1)))
		;
	return UDR1;
}

/**
 * \brief Write one character to USART_0
 *
 * Function will block until a character can be accepted.
 *
 * \param[in] data The character to write to the USART
 *
 * \return Nothing
 */
void USART_0_write(const uint8_t data)
{
	while (!(UCSR1A & (1 << UDRE1)))
		;
	UDR1 = data;
}
