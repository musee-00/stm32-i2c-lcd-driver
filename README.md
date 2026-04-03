# STM32 Bare-Metal I2C LCD Driver with GPIO LED

A bare-metal I2C driver for the LCD1602 display with PCF8574 I2C backpack, combined with a GPIO-controlled LED indicator. Written in C for the STM32F411RE with zero HAL dependencies. All I2C and GPIO communication done through direct register access.

## Features
- Bare-metal I2C1 peripheral configuration at register level
- LCD1602 initialization sequence in 4-bit mode
- Write strings to any position on the display
- Set cursor to any row and column
- GPIO output on PA0 for external LED indicator
- Counting demo: counts 1 to 10 and back, LED flashes at min and max

## Hardware
- STM32F411RE (ARM Cortex-M4, 100MHz) — Nucleo-F411RE
- LCD1602 display with PCF8574 I2C backpack
- External LED + resistor on PA0
- Wiring: SDA → PB9, SCL → PB8, VCC → 5V, GND → GND
- Note: PA3 is reserved on Nucleo-F411RE for ST-Link UART RX — do not use for GPIO output

## Usage
```c
lcd_init();
led_init();
lcd_set_cursor(0, 0);
lcd_send_string("  Counting...   ");
```

## What I learned
- I2C peripheral register configuration on STM32F4
- LCD1602 4-bit mode initialization sequence
- PCF8574 I2C backpack communication protocol
- Nucleo-F411RE reserved pins (PA2, PA3 used by ST-Link)
- Debugging hardware conflicts between peripherals

## Build
Built with STM32CubeIDE 2.1.1 targeting ARM Cortex-M4.
