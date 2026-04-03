#include <stdint.h>
#include "lcd.h"

static void delay_ms(volatile uint32_t ms) {
    while (ms--) {
        volatile uint32_t i = 1600;
        while (i--);
    }
}

static void led_init(void) {
    RCC_AHB1ENR |= (1U << 0);              /* enable GPIOA clock */
    GPIOA->MODER &= ~(0x3U << (0 * 2));    /* clear PA0 mode */
    GPIOA->MODER |=  (0x1U << (0 * 2));    /* PA0 output */
    GPIOA->OTYPER &= ~(1U << 0);           /* push-pull */
    GPIOA->BSRR = (1U << (0 + 16));        /* LED off at start */
}

static void led_on(void) {
    GPIOA->BSRR = (1U << 0);
}

static void led_off(void) {
    GPIOA->BSRR = (1U << (0 + 16));
}

static void lcd_print_number(uint8_t num) {
    char buf[3];
    if (num < 10) {
        buf[0] = '0' + num;
        buf[1] = ' ';
        buf[2] = '\0';
    } else {
        buf[0] = '1';
        buf[1] = '0';
        buf[2] = '\0';
    }
    lcd_send_string(buf);
}

int main(void) {
    lcd_init();
    led_init();

    lcd_set_cursor(0, 0);
    lcd_send_string("  Counting...   ");

    while (1) {

        for (uint8_t i = 1; i <= 10; i++) {
            lcd_set_cursor(1, 7);
            lcd_print_number(i);
            if (i == 10) {
                led_on();
                delay_ms(500);
                led_off();
            }
            delay_ms(500);
        }

        for (uint8_t i = 9; i >= 1; i--) {
            lcd_set_cursor(1, 7);
            lcd_print_number(i);
            if (i == 1) {
                led_on();
                delay_ms(500);
                led_off();
                break;
            }
            delay_ms(500);
        }
    }
}
