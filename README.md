# MacroLogic - An open-source macro keyboard based on the STM32F103C8T6 microcontroller
<img src="https://i.imgur.com/bLer908.png" alt="MacroLogic Logo" width="400"/>
This project is based on the STM32 Black Pill, also known as the STM32F103C8T6.
Built in STM32Cube.

## Updates:
This project is currently a work in progress.
- 08/24/2018: First Commit, USB HID Functionality. (LEGACY, found in uVision branch)
- 04/30/2019: Converted to STM32duino platform, with support for WS2812B leds, serial communication, and USB HID functionality.
- 05/05/2019: 
  - General: Reorganized File Structure
  - Firmware: Added OLED support, Patterns for LEDs, Added PB0 Button
  - Client: Basic Color Client created
- 12/22/2022: Rebranded, started work to completely rewrite this project using STM32Cube. Support for WS2812B LEDs.

## Why the rebrand and rewrite:
The Arduino platform was great for beginner projects, however lacked a lot of support for advanced microcontroller techniques like Direct Memmory Access (DMA).
Support for hardware timers and interrupts are also easier to perform natively in STM32Cube.
This rewrite implements many of these techniques to make the code more efficient without relying on non-blocking timestamp checks (like v1).

## Materials used so far:
- STM32F103c8t6
- WS2812B LEDs (x9)
- 9 Mechanical Switches
- Rotary Encoder
- OLED
