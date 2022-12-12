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
