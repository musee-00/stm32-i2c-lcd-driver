# STM32 Bare-Metal I2C LCD Driver

A bare-metal I2C driver for the LCD1602 display with PCF8574 I2C backpack, written in C for the STM32F411RE with zero HAL dependencies. All I2C communication done through direct register access.

## Features
- Bare-metal I2C1 peripheral configuration at register level
- LCD1602 initialization sequence in 4-bit mode
- Write strings to any position on the display
- Set cursor to any row and column
- Clear display
- Counting demo: counts 1→10→1 on the LCD

## Hardware
- STM32F411RE (ARM Cortex-M4, 100MHz) — Nucleo-F411RE
- LCD1602 display with PCF8574 I2C backpack
- Wiring: SDA → PB9, SCL → PB8, VCC → 5V, GND → GND

## Usage
```c
lcd_init();
lcd_set_cursor(0, 0);
lcd_send_string("Hello Musee!");
lcd_set_cursor(1, 0);
lcd_send_string("STM32 I2C Driver");
```

## Build
Built with STM32CubeIDE 2.1.1 targeting ARM Cortex-M4.
