/******************************************************************************
 *
 * Module: Application
 *
 * File Name: app.c
 *
 * Description: Source file for the Application
 *
 * Author: Hisham Elsayed
 *
 *******************************************************************************/
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "keypad.h"
#include "app.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
uint8 operation=0;


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void calculate(uint8 num1, uint8 num2)
{
	uint16 result;
	switch(operation)
	{
	case '+':
		result =  num1 + num2;        /* ASCII Code of '+' */
		break;
	case '-': result = num1 - num2;        /* ASCII Code of '-' */
	break;
	case '*':
		result =  num1 * num2;         /* ASCII Code of '*' */
		break;
	case '%':
		result =  num1 / num2;         /* ASCII Code of % */
		break;
	default:
		LCD_displayString("Error");
		break;
	}
LCD_intgerToString(result);
}

uint16 get_key(void)
{
	uint16 key=0;
	uint16 operand=0;
	uint8 valid = TRUE;
	while(valid)
	{
		key = KEYPAD_getPressedKey();
		if( (key == '+') || (key == '-') || (key == '*') || (key == '%') )
		{
			operation = key;
			LCD_displayCharacter(operation);
			valid = FALSE;
		}
		else if (key == '=')
		{
			LCD_displayCharacter('=');
			valid = FALSE;
		}
		else if(key == 13)              /* ASCII Code of Enter */
		{
			LCD_clearScreen();     /* Clear the LCD Screen */
		}
		else
		{
			LCD_intgerToString(key); /* display the pressed keypad switch */
			operand=10*operand + key;
		}
		_delay_ms(250);           /* Press time */
	}
	return operand;
}

int main()
{
	uint8 first,second;
	LCD_init();

	while(1)
	{
		first = get_key();
		second = get_key();
		calculate(first, second);
	}
}

