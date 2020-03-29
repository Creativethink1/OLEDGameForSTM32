
#include "key_bsp.h"

/* USER CODE BEGIN 0 */

uint8_t ButtonsState(void)
{
  uint8_t buttons = 0;

  if(HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin) == 0){//LEFT
 
		buttons = 1<<0;
  }
  if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin) == 0){//RIGGHT

		buttons = 1<<1;
  }
  if(HAL_GPIO_ReadPin(KEY5_GPIO_Port,KEY5_Pin) == 0){//UP

		buttons = 1<<2;
  }
  if(HAL_GPIO_ReadPin(KEY6_GPIO_Port,KEY6_Pin) == 0){//DOWN

		buttons = 1<<3;
  }
  if(HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin) == 0){//A

		buttons = 1<<4;
  }
  if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin) == 0){//B

		buttons = 1<<5;
  }
  
  return buttons;
}

/* USER CODE END 0 */



/**********************END OF FILE*******************************/
