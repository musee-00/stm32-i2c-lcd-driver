#include <stdint.h>
#include "lcd.h"

static void delay_ms(volatile uint32_t ms) {
    while (ms--) {
        volatile uint32_t i = 1600;
        while (i--);
    }
}

static void lcd_print_number(uint8_t num) {
    char buf[3];
    if (num < 10) {
        buf[0] = '0' + num;
        buf[1] = ' ';   /* clear previous digit */
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

    lcd_set_cursor(0, 0);
    lcd_send_string("  Counting...   ");

    while (1) {
        /* Count up 1 to 10 */
        for (uint8_t i = 1; i <= 10; i++) {
            lcd_set_cursor(1, 7);
            lcd_print_number(i);
            delay_ms(1000);
        }

        /* Count down 9 to 1 */
        for (uint8_t i = 9; i >= 1; i--) {
            lcd_set_cursor(1, 7);
            lcd_print_number(i);
            delay_ms(1000);
            if (i == 1) break;  /* prevent underflow on uint8_t */
        }
    }
}
