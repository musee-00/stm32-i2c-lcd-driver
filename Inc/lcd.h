#ifndef LCD_H
#define LCD_H

#include <stdint.h>

#define I2C1_BASE     0x40005400UL
#define RCC_BASE      0x40023800UL
#define GPIOB_BASE    0x40020400UL

#define RCC_AHB1ENR  (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define RCC_APB1ENR  (*(volatile uint32_t *)(RCC_BASE + 0x40))

#define RCC_GPIOB_EN  (1U << 1)
#define RCC_I2C1_EN   (1U << 21)

typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
} GPIO_TypeDef;

typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t OAR1;
    volatile uint32_t OAR2;
    volatile uint32_t DR;
    volatile uint32_t SR1;
    volatile uint32_t SR2;
    volatile uint32_t CCR;
    volatile uint32_t TRISE;
} I2C_TypeDef;

#define GPIOB  ((GPIO_TypeDef *) GPIOB_BASE)
#define I2C1   ((I2C_TypeDef *)  I2C1_BASE)

/* LCD I2C address — PCF8574 backpack default */
#define LCD_ADDR  0x3F

void lcd_init(void);
void lcd_send_string(const char *str);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_clear(void);

#endif
