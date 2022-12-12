# target-STM32F401-drivers
This project uses STM32CubeIDE and it's a program created to practice my C habilities during the course 'Mastering Microcontroller and Embedded Driver Development' from FastBit Embedded Brain Academy. I am using a NUCLEO-F401RE board.

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

