# Porting MicroBoot

Porting MicroBoot to your platform entails implementing a flash interface for your target hardware (usually binding to your target's HAL) and implementing the function to kick into the loaded application.

Feel free to take inspiration from existing ports located in the `ports` directory. Please feel free to submit a PR with new ports.

## Flash Interface

The definitions of the of the needed functions can be found in the `flash_interface.h` file of in the `src` directory.

## Start Function

The start function takes the new program counter and stack pointer and attempts to kick into the new application.

The target hardware's manual should referenced.

