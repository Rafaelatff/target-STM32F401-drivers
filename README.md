# target-STM32F401-drivers
This project uses STM32CubeIDE and it's a program created to practice my C habilities during the course 'Mastering Microcontroller and Embedded Driver Development' from FastBit Embedded Brain Academy. I am using a NUCLEO-F401RE board.

## drivers library creation

Add a folder to the project with the name 'drivers'. Inside the 'drivers' folder, create 2 more folders. One with the name 'Inc' for the header files (.h) and another with the name 'Src' for the source files (.c). Then create both files in those reespectives folders (stm32f401xx.h inside 'Inc' and stm32f401xx.c inside 'Src').

It is necessary to inform to the compiler the path for the 'drivers->Inc' folder. For that, right-click in the project (on the project tree), go 'Properties' -> 'C/C++ Build' -> 'Settings' -> 'Tool Settings' -> 'MCU GCC Compiler' and add the path to 'drivers->Inc'.

![image](https://user-images.githubusercontent.com/58916022/207178796-0350de6b-c151-4e4f-a5fb-b5c3934841bb.png)

Before leaving the settings, uncheck the option 'Exclude resource from build'.

![image](https://user-images.githubusercontent.com/58916022/207180678-8917b73a-3994-4723-9d7f-dbabcce02167.png)

## Base address memories

*Flash* and *SRAM* 

![image](https://user-images.githubusercontent.com/58916022/207028999-ce0e94d8-f434-4550-9434-68cc9c43ddee.png)

```
/*
    Base addresses of Flash and SRAM memories
*/
#define FLASH_BASEADDR	0x08000000UL //typecast also would work (uint32_t) isntead of UL
#define SRAM1_BASEADDR	0x20000000UL
#define SRAM SRAM1_BASEADDR 
// #define SRAM2_BASEADDR	// uC doen't have SRAM2
#define ROM_BASEADDR	0x1FFF0000UL // ROM = System memory
```
*Base addresses of AHBx and APBx Bus Peripheral*

![image](https://user-images.githubusercontent.com/58916022/207036964-8ee3715f-3105-4ae4-8ffa-afa8a187ddef.png)
![image](https://user-images.githubusercontent.com/58916022/207036881-ced6d2fd-f7ef-4bac-a224-4d4178f21d7f.png)

```
/*
    Base addresses of AHBx and APBx Bus Peripheral
*/
#define PERIPH_BASE	0x40000000UL
#define APB1PERIPH_BASE PERIPH_BASE
#define APB2PERIPH_BASE 0x40010000UL
#define AHB1PERIPH_BASE 0x40020000UL
#define AHB2PERIPH_BASE 0x50000000UL
```
Following the 'Table 1. STM32F401xB/C and STM32F401xD/E register boundary addresses' of the Reference Manual (RM0368), it is possible to get the peripheral addresses for the peripheral hanging on AHB2 bus.

```
/*
    Base addresses of peripherals which are hanging on AHB2 bus
*/
```
Following the 'Table 1. STM32F401xB/C and STM32F401xD/E register boundary addresses' of the Reference Manual (RM0368), it is possible to get the peripheral addresses for the peripheral hanging on AHB1 bus.

```
/*
    Base addresses of peripherals which are hanging on AHB1 bus
*/
#define GPIOA_BASEADDR (AHB1PERIPH_BASE + 0x0000)
#define GPIOB_BASEADDR (AHB1PERIPH_BASE + 0x0400)
#define GPIOC_BASEADDR (AHB1PERIPH_BASE + 0x0800)
#define GPIOD_BASEADDR (AHB1PERIPH_BASE + 0x0C00)
#define GPIOE_BASEADDR (AHB1PERIPH_BASE + 0x1000)
#define GPIOH_BASEADDR (AHB1PERIPH_BASE + 0x1C00)
#define CRC_BASEADDR (AHB1PERIPH_BASE + 0x3000)
#define RCC_BASEADDR (AHB1PERIPH_BASE + 0x3800)
#define FIR_BASEADDR (AHB1PERIPH_BASE + 0x3C00)
#define DMA1_BASEADDR (AHB1PERIPH_BASE + 0x6000)
#define DMA2_BASEADDR (AHB1PERIPH_BASE + 0x6400)
#define USB_OTG_FS_BASEADDR (AHB1PERIPH_BASE + 0xFFE0000)
```
Following the 'Table 1. STM32F401xB/C and STM32F401xD/E register boundary addresses' of the Reference Manual (RM0368), it is possible to get the peripheral addresses for the peripheral hanging on APB2 bus.

```
/*
    Base addresses of peripherals which are hanging on APB2 bus
*/
```
Following the 'Table 1. STM32F401xB/C and STM32F401xD/E register boundary addresses' of the Reference Manual (RM0368), it is possible to get the peripheral addresses for the peripheral hanging on APB1 bus.

```
/*
    Base addresses of peripherals which are hanging on APB1 bus
*/
#define TIM2_BASEADDR (APB1PERIPH_BASE + 0x0000)
#define TIM3_BASEADDR (APB1PERIPH_BASE + 0x0400)
#define TIM4_BASEADDR (APB1PERIPH_BASE + 0x0800)
#define TIM5_BASEADDR (APB1PERIPH_BASE + 0x0C00)
#define RTC_n_BKP_BASEADDR (APB1PERIPH_BASE + 0x2800)
#define WWDG_BASEADDR (APB1PERIPH_BASE + 0x2C00)
#define IWDG_BASEADDR (APB1PERIPH_BASE + 0x3000)
#define I2S2ext_BASEADDR (APB1PERIPH_BASE + 0x3400)
#define SPI2_BASEADDR (APB1PERIPH_BASE + 0x3800) // SPI2 and I2S2 has same base addres
#define I2S2_BASEADDR (APB1PERIPH_BASE + 0x3800)
#define SPI3_BASEADDR (APB1PERIPH_BASE + 0x3C00) // SPI3 and I2S3 has same base addres
#define I2S3_BASEADDR (APB1PERIPH_BASE + 0x3C00)
#define I2S3ext_BASEADDR (APB1PERIPH_BASE + 0x4000)
#define USART2_BASEADDR (APB1PERIPH_BASE + 0x4400)
#define I2C1_BASEADDR (APB1PERIPH_BASE + 0x5400)
#define I2C2_BASEADDR (APB1PERIPH_BASE + 0X5800)
#define I2C3_BASEADDR (APB1PERIPH_BASE + 0x5C00)
#define PWR_BASEADDR (APB1PERIPH_BASE + 0x7000)
```

Now, let´t build the struct that holds the peripheral register addresses. For that, we are going to use the 'Table 27. GPIO register map and reset values'. We can notice that some offset values were repeated. That happens, because some ports may have different initial values. But besides that, they have the same bit fields as all others GPIOs configuration.

![image](https://user-images.githubusercontent.com/58916022/207079136-1765ead4-5bb6-4494-986d-f623531da0e3.png)
![image](https://user-images.githubusercontent.com/58916022/207079270-e0bb9d7c-0dad-437e-9d5c-fc8471e19276.png)

Reminder1: To use uint32_t, we need to add #include <stdint.h>.
Reminder2: Registers must be volatile type, since it can change without notice (eg.: GPIO port input data register).
Reminder3: uint32_t = 32-bit = 4-bytes = +0x04 (that increases the address offset).

```
/*
    Peripheral register definition structure for GPIO
*/
typedef struct {
	volatile uint32_t MODER; // GPIO port mode register - Address offset: 0x00
	volatile uint32_t OTYPER; // GPIO port output type register - Address offset: 0x04
	volatile uint32_t OSPEEDER; // GPIO port output speed register - Address offset: 0x08
	volatile uint32_t PUPDR; // GPIO port pull-up/pull-down register - Address offset: 0x0C
	volatile uint32_t IDR; // GPIO port input data register - Address offset: 0x10
	volatile uint32_t ODR; // GPIO port output data register - Address offset: 0x14
	volatile uint32_t BSRR; // GPIO port bit set/reset register - Address offset: 0x18
	volatile uint32_t LCKR; // GPIO port configuration lock register - Address offset: 0x1C
	volatile uint32_t AFR[2]; // GPIO alternate function low register AFR[0] = AFRL and AFR[1] = AFRH - Address offset: 0x20-0X24
} GPIO_RegDef_t;
```
Using the struct that we just created, we can also create the macro peripheral definitions for the GPIOS.

```
/*
    Peripheral definitions (Peripheral base addresses typecasted to xxx_RegDef_t)
*/
#define GPIOA ((GPIO_RegDef_t*)GPIOA_BASEADDR) 
#define GPIOB ((GPIO_RegDef_t*)GPIOB_BASEADDR) 
#define GPIOC ((GPIO_RegDef_t*)GPIOC_BASEADDR) 
#define GPIOD ((GPIO_RegDef_t*)GPIOD_BASEADDR) 
#define GPIOE ((GPIO_RegDef_t*)GPIOE_BASEADDR) 
#define GPIOF ((GPIO_RegDef_t*)GPIOF_BASEADDR) 
#define GPIOG ((GPIO_RegDef_t*)GPIOG_BASEADDR) 
#define GPIOH ((GPIO_RegDef_t*)GPIOH_BASEADDR) 
```

Using the 'Table 22. RCC register map and reset values for STM32F401xB/C and STM32F401xD/E' we are going to create a new struct to use for the RCC register addresses.

![image](https://user-images.githubusercontent.com/58916022/207089304-14d7a912-dd7f-4ae0-94f7-6ad1639e6341.png)
![image](https://user-images.githubusercontent.com/58916022/207089910-f3c0a1f4-5005-4492-86ef-43d74cdfb512.png)
![image](https://user-images.githubusercontent.com/58916022/207089994-eb3ace3a-564e-44fa-ac9e-b150cdcb7025.png)

```
/* 
    Peripheral register definition structure for RCC
*/
typedef struct {
	volatile uint32_t CR; // RCC clock control register - Address offset: 0x00
	volatile uint32_t PLLCFGR; // RCC PLL configuration register - Address offset: 0x04
	volatile uint32_t CFGR; // RCC clock configuration register - Address offset: 0x08
	volatile uint32_t CIR; // RCC clock interrupt register - Address offset: 0x0C
	volatile uint32_t AHB1RSTR; // RCC AHB1 peripheral reset register - Address offset: 0x10
	volatile uint32_t AHB2RSTR; // RCC AHB2 peripheral reset register - Address offset: 0x14
	volatile uint32_t Reserved0; // Reserved - Address offset: 0x18
	volatile uint32_t Reserved1; // Reserved - Address offset: 0x1C
	volatile uint32_t APB1RSTR; // RCC APB1 peripheral reset register - Address offset: 0x20
	volatile uint32_t APB2RSTR; // RCC APB2 peripheral reset register - Address offset: 0x24
	volatile uint32_t Reserved2; // Reserved - Address offset: 0x28
	volatile uint32_t Reserved3; // Reserved - Address offset: 0x2C
	volatile uint32_t AHB1ENR; // RCC AHB1 peripheral clock enable register - Address offset: 0x30
	volatile uint32_t AHB2ENR; // RCC AHB2 peripheral clock enable register - Address offset: 0x34
	volatile uint32_t Reserved4; // Reserved - Address offset: 0x38
	volatile uint32_t Reserved5; // Reserved - Address offset: 0x3C
	volatile uint32_t APB1ENR; // RCC APB1 peripheral clock enable register - Address offset: 0x40
	volatile uint32_t APB2ENR; // RCC APB2 peripheral clock enable register - Address offset: 0x44
	volatile uint32_t Reserved6; // Reserved - Address offset: 0x48
	volatile uint32_t Reserved7; // Reserved - Address offset: 0x4C
	volatile uint32_t AHB1LPENR; // RCC AHB1 peripheral clock enable in low power mode register - Address offset: 0x50
	volatile uint32_t AHB2LPENR; // RCC AHB2 peripheral clock enable in low power mode register - Address offset: 0x54
	volatile uint32_t Reserved8; // RCC - Address offset: 0x58
	volatile uint32_t Reserved9; // RCC - Address offset: 0x5C
	volatile uint32_t APB1LPENR; // RCC APB1 peripheral clock enable in low power mode register - Address offset: 0x60
	volatile uint32_t APB2LPENR; // RCC APB2 peripheral clock enable in low power mode register - Address offset: 0x64
	volatile uint32_t Reserved10; // Reserved - Address offset: 0x68
	volatile uint32_t Reserved11; // Reserved - Address offset: 0x6C
	volatile uint32_t BDCR; // RCC Backup domain control register - Address offset: 0x70
	volatile uint32_t CSR; // RCC clock control & status register - Address offset: 0x74
	volatile uint32_t Reserved12; // Reserved - Address offset: 0x78
	volatile uint32_t Reserved13; // Reserved - Address offset: 0x7C
	volatile uint32_t SSCGR; // RCC spread spectrum clock generation register - Address offset: 0x80
	volatile uint32_t PLLI2SCFGR; // RCC PLLI2S configuration register - Address offset: 0x84
	volatile uint32_t Reserved14; // Reserved - Address offset: 0x88
	volatile uint32_t DCKCFGR; // RCC  Dedicated Clocks Configuration Register - Address offset: 0x8C
} RCC_RegDef_t;
*/ 
    Peripheral definitions (Peripheral base addresses typecasted to xxx_RegDef_t)
*/
#define RCC	((RCC_RegDef_t*)RCC_BASEADDR)
```

To easy the programming routines, we can create some Macro Functions to quickly initialize the peripherals. This is showed in the following command lines: 

```
// Clock Enable Macros for GPIOx peripherals
#define GPIOA_PCLK_EN() (RCC->AHB1ENR |= (1<<0))
#define GPIOB_PCLK_EN() (RCC->AHB1ENR |= (1<<1))
#define GPIOC_PCLK_EN() (RCC->AHB1ENR |= (1<<2))
#define GPIOD_PCLK_EN() (RCC->AHB1ENR |= (1<<3))
#define GPIOE_PCLK_EN() (RCC->AHB1ENR |= (1<<4))

// Clock Enable Macros for I2Cx peripherals
#define I2C1_PCLK_EN() (RCC->APB1ENR |= (1<<21))
#define I2C2_PCLK_EN() (RCC->APB1ENR |= (1<<22))
#define I2C3_PCLK_EN() (RCC->APB1ENR |= (1<<23))

// Clock Enable Macros for SPIx peripherals
#define SPI1_PCLK_EN() (RCC->APB2ENR |= (1<<12))
#define SPI2_PCLK_EN() (RCC->APB1ENR |= (1<<14))
#define SPI3_PCLK_EN() (RCC->APB1ENR |= (1<<15))
#define SPI4_PCLK_EN() (RCC->APB2ENR |= (1<<13))

// Clock Enable Macros for UARTx/USARTx peripherals
#define USART1_PCLK_EN() (RCC->APB2ENR |= (1<<4))
#define USART2_PCLK_EN() (RCC->APB1ENR |= (1<<17))
#define USART6_PCLK_EN() (RCC->APB2ENR |= (1<<5))

// Clock Enable Macros for SYSCFG peripherals
#define SYSCFG_PCLK_EN() (RCC->APB2ENR |= (1<<14))
```

The same way as showed above, we can create the clock disable macro to ease the disable of peripherals.

```
// Clock Disable Macros for GPIOx peripherals
#define GPIOA_PCLK_DI() (RCC->AHB1ENR &= ~(1<<0))
#define GPIOB_PCLK_DI() (RCC->AHB1ENR &= ~(1<<1))
#define GPIOC_PCLK_DI() (RCC->AHB1ENR &= ~(1<<2))
#define GPIOD_PCLK_DI() (RCC->AHB1ENR &= ~(1<<3))
#define GPIOE_PCLK_DI() (RCC->AHB1ENR &= ~(1<<4))

// Clock Disable Macros for I2Cx peripherals
#define I2C1_PCLK_DI() (RCC->APB1ENR &= ~(1<<21))
#define I2C2_PCLK_DI() (RCC->APB1ENR &= ~(1<<22))
#define I2C3_PCLK_DI() (RCC->APB1ENR &= ~(1<<23))

// Clock Disable Macros for SPIx peripherals
#define SPI1_PCLK_DI() (RCC->APB2ENR &= ~(1<<12))
#define SPI2_PCLK_DI() (RCC->APB1ENR &= ~(1<<14))
#define SPI3_PCLK_DI() (RCC->APB1ENR &= ~(1<<15))
#define SPI4_PCLK_DI() (RCC->APB2ENR &= ~(1<<13))

// Clock Disable Macros for USARTx peripherals
#define USART1_PCLK_DI() (RCC->APB2ENR &= ~(1<<4))
#define USART2_PCLK_DI() (RCC->APB1ENR &= ~(1<<17))
#define USART6_PCLK_DI() (RCC->APB2ENR &= ~(1<<5))

// Clock Disable Macros for SYSCFG peripherals
#define SYSCFG_PCLK_DI() (RCC->APB2ENR &= ~(1<<14))
```

Inside the stm32f401xx.h file, we can create some macros that will be used along the drivers (diffent .h files). Such as:

```
// Some generic macros
#define ENABLE 1
#define DISABLE 0
#define SET ENABLE
#define RESET DISABLE
#define GPIO_PIN_SET SET
```

We can create a stm32f401xx_GPIO_driver.h file, to list all the related GPIO macros, structs and funcions, being:

```
//@GPIO_PIN_NUMBERS
#define GPIO_PIN_NO_0 0 
#define GPIO_PIN_NO_1 1 
#define GPIO_PIN_NO_2 2 
#define GPIO_PIN_NO_3 3 
#define GPIO_PIN_NO_4 4 
#define GPIO_PIN_NO_5 5 
#define GPIO_PIN_NO_6 6 
#define GPIO_PIN_NO_7 7 
#define GPIO_PIN_NO_8 8 
#define GPIO_PIN_NO_9 9 
#define GPIO_PIN_NO_10 10 
#define GPIO_PIN_NO_11 11 
#define GPIO_PIN_NO_12 12 
#define GPIO_PIN_NO_13 13 
#define GPIO_PIN_NO_14 14 
#define GPIO_PIN_NO_15 15 

//@GPIO_PIN_MODES
#define GPIO_MODE_IN 0
#define GPIO_MODE_OUT 1
#define GPIO_MODE_ALTFN 2
#define GPIO_MODE_ANALOG 3 // value equal or less than 3 = non interrupt modes
#define GPIO_MODE_IT_FT 4 //interruptt falling edge trigger
#define GPIO_MODE_IT_RT 5 //input rising edge trigger
#define GPIO_MODE_IT_RFT 6 //input rising/falling edge trigger

//GPIO pin possible output types
#define GPIO_OP_TYPE_PP 0 // push pull
#define GPIO_OP_TYPE_OD 1 // open drain

//GPIO pin possible output speeds
//@GPIO_PIN_SPEEDS
#define GPIO_SPEED_LOW 0
#define GPIO_SPEED_MEDIUM 1
#define GPIO_SPEED_FAST 2
#define GPIO_SPEED_HIGH 3

//GPIO pin possible pull up and down
#define GPIO_NO_PUPD 0
#define GPIO_PIN_PU 1
#define GPIO_PIN_PD 2

typedef struct{
	uint8_t GPIO_PinNumber; //@GPIO_PIN_NUMBERS
	uint8_t GPIO_PinMode; // possible valyes from @GPIO_PIN_MODES
	uint8_t GPIO_PinSpeed; //@GPIO_PIN_SPEEDS
	uint8_t GPIO_PinPuPdControl;
	uint8_t GPIO_PinOpType;
	uint8_t GPIO_PinAltFunMode;
}GPIO_PinConfig_t;

typedef struct{
	GPIO_RegDef_t *pGPIOx; //Holds the base addess of the GPIO port
	GPIO_PinConfig_t GPIO_PinConfig; //Holds the GPIO pin config. settings
}GPIO_Handle_t;

// APIs supported by this driver
//Peripheral clock setup
void GPIO_PeriClkCtrl(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi);

// Initi and De-init
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

// Data read and write
uint8_t GPIO_Read(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber); //It also could be a boolean
uint16_t GPIO_PortRead(GPIO_RegDef_t *pGPIOx); // returns te port value
void GPIO_Out(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value); //value can be SET or RESET
void GPIO_PortOut(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_Toggle(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

// IRQ handling
void GPIO_IRQConfig(uint8_t ORQNumber, uint8_t IRQPriority, uint8_t EnOrDi);
void GPIO_IRQHandling(uint8_t GPIO_PinNumber);
```



And in the source file (stm32f401xx_GPIO_driver.c), we can copy those same functions (not the structs, only the functions) and open to statements. For every function, it is important to write a small header to explain its functions. We can use @ for the parameters and stuff.

**@fn** = functio name

**@brief** = a brief of what this function does

**@param** = parameter descriptions - base addres of GPIO 

				- macros ENABLE DISABLE
				
**@return** = expected return value for this function (none if void)

**@note** = especial note

And we can start to write the functions. Let´s begin with the configuration of peripheral clock control.

```
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
```
The following function, initializes the GPIO pin.

```
void GPIO_Init(GPIO_Handle t *pGPIOHandle){
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
```
We also need to be able of resetting the port configuration. Observe that the reset function works on the entire port, not being able to reset a single pin.

```
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
```
Then, at the stm32f401xx.h file we can create some macros that will do the reset configuration. Note that we are not creating those macros inside the stm32f401xx_GPIO_driver.h file, that is because RCC_AHB1RSTR registers have different peripherals than GPIOs and need to be accessed for all the others different drivers.

To assist us with the shift bitwise operator, an image of the Reset and Clock Control AHB1 peripheral reset register from RM0368 Reference Manual.

![image](https://user-images.githubusercontent.com/58916022/207433773-6b2f29f6-0adc-422b-ae20-b0817c0c21a3.png)

To reset the port, the value must go to 1 (being set) and then must return to 0 (or it will stay in reset mode);

![image](https://user-images.githubusercontent.com/58916022/207434198-92ac033a-e375-481e-ac39-8d404cf07c33.png)

```
#define GPIOA_REG_RESET() do { (RCC->AHB1RSTR |= (1<<0)); (RCC->AHB1RSTR &= ~(1<<0)); } while(0)
#define GPIOB_REG_RESET() do { (RCC->AHB1RSTR |= (1<<1)); (RCC->AHB1RSTR &= ~(1<<1)); } while(0)
#define GPIOC_REG_RESET() do { (RCC->AHB1RSTR |= (1<<2)); (RCC->AHB1RSTR &= ~(1<<2)); } while(0)
#define GPIOD_REG_RESET() do { (RCC->AHB1RSTR |= (1<<3)); (RCC->AHB1RSTR &= ~(1<<3)); } while(0)
#define GPIOE_REG_RESET() do { (RCC->AHB1RSTR |= (1<<4)); (RCC->AHB1RSTR &= ~(1<<4)); } while(0)
#define GPIOH_REG_RESET() do { (RCC->AHB1RSTR |= (1<<7)); (RCC->AHB1RSTR &= ~(1<<7)); } while(0)

```

PAREI AQUI: 
Quando implementar, checar nome das funções, explicar e comentar o que for necessário:

Reading functions

```
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
```

Writting functions

```
// Writting functions

void GPIO_Out(GPIO_RegDef_t *pGPIOx, uint8_t GPIO_PinNumber, uint8_t Value){
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

void GPIO_Toggle(GPIO_RegDef_t *pGPIOx, uint8_t GPIO_PinNumber){
	pGPIOx->ODR ^= (1 << PinNumber);
}
```

# Testing drivers

## Case 1 - 001led_toogle.c (Push pull config)

Delete the main.c file and let's create a new source file int the main 'Src' source folder. 

Note that, when writting the code, always that you are using a variable with struct type, after writting the name of this variable, at the moment you write the dot '.', the IDE presents you with the possible inputs available. In the case of a 'GPIO_Handle_t', its possible to edit the '*pGPIOx' (that holds the base address of the GPIO port), or the 'GPIO_PinConfig' (that holds the GPIO pin config. settings).

![image](https://user-images.githubusercontent.com/58916022/208116152-0c8364f9-a32d-4fdd-a293-3c9c4191bc5c.png)

Since you have netsted structures, you can enter the value of a struct that is inside another struct. You can see that in the next image, where is being configured the 'GPIO_PinConfig' of the 'GPIO_PinNumber'.

![image](https://user-images.githubusercontent.com/58916022/208117659-e1b59953-805e-4139-a79c-12c45d57c46c.png)

Just to help remembering, we have those structs:

![image](https://user-images.githubusercontent.com/58916022/208118259-741b8b48-637c-477f-9591-5a620decd5d2.png)

To get the auto suggestions in eclipse, you have to press and hold the left CTRL key and then press the SPACE key. Remember that if is something that you need from stm32f401xx_gpio_driver.h, you must include the file in the document. Since after the creating of all the drivers we are going to have a lot of '.h' files. We can simply add the #include "stm32f401xx_gpio_driver.h" line inside the #include "stm32f401xx.h".

![image](https://user-images.githubusercontent.com/58916022/208118901-f7c09983-6d74-4797-99d4-3473aaeefa0c.png)

Same thing happens when you are writting a function. It's really helpful since the auto suggestions shows, at the moment you are writting, the syntax of that functions.

![image](https://user-images.githubusercontent.com/58916022/208120652-a5c57901-5329-4981-8fb1-1867ca278f5d.png)

![image](https://user-images.githubusercontent.com/58916022/208120836-0aa5c45a-9eb6-4099-a9c8-27c9c549b202.png)

Final code:

```
#include "stm32f401xx.h"

void delay(void){
	for (uint32_t i=0; i<500000; i++);
}

int main (void){
	GPIO_Handle_t LD2; // LD2 connected to GPIO A (port A) and pin 5

	LD2.pGPIOx = GPIOA;
	LD2.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	LD2.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	LD2.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	LD2.GPIO_PinConfig.GPIO_PinOpType = GPIO_OP_TYPE_PP;
	LD2.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	//No need of config. PUPD since it's already PP (push pull)

	GPIO_PeriClkCtrl(GPIOA, ENABLE);
	GPIO_Init(&LD2);

	while (1){
		GPIO_Toggle(GPIOA,GPIO_PIN_NO_5);
		delay();
	}
}
```




