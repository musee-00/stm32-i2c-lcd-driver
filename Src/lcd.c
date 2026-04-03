#include "lcd.h"

static void delay_ms(volatile uint32_t ms) {
    while (ms--) {
        volatile uint32_t i = 1600;
        while (i--);
    }
}

static void i2c_start(void) {
    I2C1->CR1 |= (1U << 8);   /* START */
    while (!(I2C1->SR1 & (1U << 0)));
}

static void i2c_stop(void) {
    I2C1->CR1 |= (1U << 9);   /* STOP */
}

static void i2c_write_addr(uint8_t addr) {
    I2C1->DR = (addr << 1);    /* write mode */
    while (!(I2C1->SR1 & (1U << 1)));
    (void)I2C1->SR2;           /* clear ADDR flag */
}

static void i2c_write_byte(uint8_t data) {
    while (!(I2C1->SR1 & (1U << 7)));
    I2C1->DR = data;
    while (!(I2C1->SR1 & (1U << 2)));
}

static void lcd_write_nibble(uint8_t nibble, uint8_t rs) {
    uint8_t data = (nibble << 4) | 0x08;  /* backlight on */
    if (rs) data |= 0x01;                  /* RS bit */

    i2c_start();
    i2c_write_addr(LCD_ADDR);
    i2c_write_byte(data | 0x04);           /* EN high */
    i2c_write_byte(data & ~0x04);          /* EN low */
    i2c_stop();
    delay_ms(2);
}

static void lcd_send_cmd(uint8_t cmd) {
    lcd_write_nibble(cmd >> 4, 0);
    lcd_write_nibble(cmd & 0x0F, 0);
}

static void lcd_send_char(uint8_t ch) {
    lcd_write_nibble(ch >> 4, 1);
    lcd_write_nibble(ch & 0x0F, 1);
}

void lcd_init(void) {
    /* 1. Enable clocks */
    RCC_AHB1ENR |= RCC_GPIOB_EN;
    RCC_APB1ENR |= RCC_I2C1_EN;

    /* 2. Configure PB8 (SCL) and PB9 (SDA) as AF, open-drain */
    GPIOB->MODER  &= ~(0xFU << 16);
    GPIOB->MODER  |=  (0xAU << 16);   /* AF mode for PB8 and PB9 */
    GPIOB->OTYPER |=  (0x3U << 8);    /* open-drain */
    GPIOB->AFR[1] &= ~(0xFFU << 0);
    GPIOB->AFR[1] |=  (0x44U << 0);   /* AF4 = I2C1 */

    /* 3. Configure I2C1 for 100kHz at 16MHz */
    I2C1->CR1   &= ~(1U << 0);        /* disable I2C */
    I2C1->CR2    =  16;               /* 16MHz peripheral clock */
    I2C1->CCR    =  80;               /* 100kHz */
    I2C1->TRISE  =  17;               /* max rise time */
    I2C1->CR1   |=  (1U << 0);        /* enable I2C */

    /* 4. LCD init sequence (4-bit mode) */
    delay_ms(50);
    lcd_write_nibble(0x03, 0);
    delay_ms(5);
    lcd_write_nibble(0x03, 0);
    delay_ms(1);
    lcd_write_nibble(0x03, 0);
    lcd_write_nibble(0x02, 0);         /* set 4-bit mode */

    lcd_send_cmd(0x28);                /* 4-bit, 2 lines, 5x8 */
    lcd_send_cmd(0x0C);                /* display on, cursor off */
    lcd_send_cmd(0x06);                /* entry mode */
    lcd_send_cmd(0x01);                /* clear display */
    delay_ms(2);
}

void lcd_clear(void) {
    lcd_send_cmd(0x01);
    delay_ms(2);
}

void lcd_set_cursor(uint8_t row, uint8_t col) {
    uint8_t addr = (row == 0) ? 0x00 : 0x40;
    lcd_send_cmd(0x80 | (addr + col));
}

void lcd_send_string(const char *str) {
    while (*str) {
        lcd_send_char((uint8_t)*str++);
    }
}
