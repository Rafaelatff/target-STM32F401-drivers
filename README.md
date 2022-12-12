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
*/ 
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
*/ 
    Base addresses of AHBx and APBx Bus Peripheral
*/
#define PERIPH_BASE	0x40000000UL
#define APB1PERIPH_BASE PERIPH_BASE
#define APB2PERIPH_BASE 0x40010000UL
#define AHB1PERIPH_BASE 0x40020000UL
#define AHB2PERIPH_BASE 0x50000000UL
```

Following the 'Table 1. STM32F401xB/C and STM32F401xD/E register boundary addresses' of the Reference Manual (RM0368), it is possible to get the peripheral addresses for the peripheral hanging on APB1 bus.

```
*/ 
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
*/ 
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
*/ 
    Peripheral definitions (Peripheral base addresses typecasted to xxx_RefDef_t)
*/
#define GPIOA ((GPIO_RefDef_t*)GPIOA_BASEADDR) 
#define GPIOB ((GPIO_RefDef_t*)GPIOB_BASEADDR) 
#define GPIOC ((GPIO_RefDef_t*)GPIOC_BASEADDR) 
#define GPIOD ((GPIO_RefDef_t*)GPIOD_BASEADDR) 
#define GPIOE ((GPIO_RefDef_t*)GPIOE_BASEADDR) 
#define GPIOF ((GPIO_RefDef_t*)GPIOF_BASEADDR) 
#define GPIOG ((GPIO_RefDef_t*)GPIOG_BASEADDR) 
#define GPIOH ((GPIO_RefDef_t*)GPIOH_BASEADDR) 
```

Using the 'Table 22. RCC register map and reset values for STM32F401xB/C and STM32F401xD/E' we are going to create a new struct to use for the RCC register addresses.

![image](https://user-images.githubusercontent.com/58916022/207089304-14d7a912-dd7f-4ae0-94f7-6ad1639e6341.png)
![image](https://user-images.githubusercontent.com/58916022/207089910-f3c0a1f4-5005-4492-86ef-43d74cdfb512.png)
![image](https://user-images.githubusercontent.com/58916022/207089994-eb3ace3a-564e-44fa-ac9e-b150cdcb7025.png)

```
*/ 
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
    Peripheral definitions (Peripheral base addresses typecasted to xxx_RefDef_t)
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

