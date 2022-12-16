/*
 * stm32f401xx_gpio_driver.c
 *
 *  Created on: Dec 16, 2022
 *      Author: r.freitas
 */

#include "stm32f401xx.h"
#include "stm32f401xx_gpio_driver.h"


/*
	write the header for the following function
*/
void GPIO_PeriClkCtrl(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi){
	if (EnOrDi == ENABLE){
		if(pGPIOx == GPIOA){
			GPIOA_PCLK_EN();
		} else if (pGPIOx == GPIOB){
			GPIOB_PCLK_EN();
		} else if (pGPIOx == GPIOC){
			GPIOC_PCLK_EN();
		} else if (pGPIOx == GPIOD){
			GPIOD_PCLK_EN();
		} else if (pGPIOx == GPIOE){
			GPIOE_PCLK_EN();
		}
	}else{
		if(pGPIOx == GPIOA){
			GPIOA_PCLK_DI();
		} else if (pGPIOx == GPIOB){
			GPIOB_PCLK_DI();
		} else if (pGPIOx == GPIOC){
			GPIOC_PCLK_DI();
		} else if (pGPIOx == GPIOD){
			GPIOD_PCLK_DI();
		} else if (pGPIOx == GPIOE){
			GPIOE_PCLK_DI();
		}
	}
}

void GPIO_Init(GPIO_Handle_t *pGPIOHandle){
	uint32_t temp =0; // temp. register

	// 1 Configure the mode of GPIO pin
	if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG){
		// value equal or less than 3 = non interrupt modes
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		// 2* pois são 2 bits o MODER
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //Clear bit fields bf setting new value
		pGPIOHandle->pGPIOx->MODER |= temp;
	}else{

	}
	temp=0;

	// 2 Configure Speed
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDER &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //Clear bit fields bf setting new value
	pGPIOHandle->pGPIOx->OSPEEDER |= temp;

	temp=0;

	// 3 Configure the pupd settings
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //Clear bit fields bf setting new value
	pGPIOHandle->pGPIOx->PUPDR |= temp;

	temp=0;

	// 4 Configure the OPTYPE
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOpType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //Clear bit fields bf setting new value
	pGPIOHandle->pGPIOx->OTYPER |= temp;

	temp=0;

	// 5 Configure the alt functionality
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN){
		uint8_t temp1, temp2;

		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber /8;
		//temp1 will find the which AFR to use ([0] or [1]) by:
		//number less than 0 = [0] .. pin 0 to 7 /8 is equal to 0.?
		//number bigger than 1 = [1] .. pin 8 to 16 /8 is equal to 1.? or 2
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber %8;
		//temp2 will find out the number of the field position (pin) by taking the mod by 8
		// 0 mod 8 = 0, 1 mod 8 = 1, 2 mod 8 = 2, 3 mod 8 = 3 ... 7 mod 8 = 7
		// 8 mod 8 = 0, 9 mod 8 = 1, 10 mod 8 = 2, 11 mod 8 = 3 ... 15 mod 8 = 7
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2)); //Clear bit
		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2));
		//AFRL/AFRH uses 4 bit position to configure each pin, so 4 bits must be set (4*)
	}
}

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx){
	if(pGPIOx == GPIOA){
		GPIOA_REG_RESET();
	} else if (pGPIOx == GPIOB){
		GPIOB_REG_RESET();
	} else if (pGPIOx == GPIOC){
		GPIOC_REG_RESET();
	} else if (pGPIOx == GPIOD){
		GPIOD_REG_RESET();
	} else if (pGPIOx == GPIOE){
		GPIOF_REG_RESET();
	} else if (pGPIOx == GPIOH){
		GPIOH_REG_RESET();
	}
}

//Reading functions

uint8_t GPIO_Read (GPIO_RegDef_t *pGPIOx, uint8_t PinNumber){
	uint8_t value;
	// shift value 'Pin Number' times to the right, so it's possible to simple mask and then read LSB
	value = ((uint8_t)(pGPIOx->IDR >> PinNumber) & 0x00000001);
	return value; // @return = return value can be 0 o 1
}

uint16_t GPIO_PortRead (GPIO_RegDef_t *pGPIOx){
	uint16_t value;
	value = (uint16_t)pGPIOx->IDR;
	return value; // @return = return value can be 0 to 0xFFFF
}

// Writting functions

void GPIO_Out(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value){
 //value can be SET or RESET
	if(Value == GPIO_PIN_SET){
		//Write 1 to the output data reguster at the bit field corresponding to the pin
		pGPIOx->ODR |= (1 << PinNumber);
	}else{
		pGPIOx->ODR &= ~(1 << PinNumber);
	}
}

void GPIO_PortOut(GPIO_RegDef_t *pGPIOx, uint16_t Value){
	pGPIOx->ODR = Value;
}

void GPIO_Toggle(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber){
	pGPIOx->ODR ^= (1 << PinNumber);
}


