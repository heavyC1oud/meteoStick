
#include <stddef.h>
#include "stm32f0xx.h"
#include "interrupt.h"
#include "delay.h"
#include "led.h"
#include "main.h"

/*********************************************************************/


/*************************	FUNCTION	******************************/

/**********************************************************************
*	function name	:	main
*	Description		:	main function
*	Arguments		:	none
*	Return value	:	none
**********************************************************************/
int main(void)
{
	initLED();

	while(1) {

	}
}
