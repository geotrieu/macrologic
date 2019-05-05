# MacPill32 - A Macro Keyboard based on the STM32F103C8T6
<img src="https://i.imgur.com/joyodGK.png" alt="MacPill32 Logo" width="400"/>
This project is based on the STM32 Black Pill, also known as the STM32F103C8T6.
Uses the STM32duino platform including arpruss's HID library: http://www.stm32duino.com/viewtopic.php?t=2926

## Updates:
This project is currently a work in progress.
### As of the current commit, the USB HID interface is completely functional with all keys working. WS2812B LEDs support. Serial Support.
- 08/24/2018: First Commit, USB HID Functionality. (LEGACY, found in uVision branch)
- 04/30/2019: Converted to STM32duino platform, with support for WS2812B leds, serial communication, and USB HID functionality.
- 05/05/2019: 
General: Reorganized File Structure
Firmware: Added OLED support, Patterns for LEDs, Added PB0 Button
Client: Basic Color Client created

## Materials used so far:
- STM32F103c8t6
- WS2812B LEDs (x9)
- 9 Mechanical Switches
- Rotary Encoder
- OLED
