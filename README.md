# MicroBoot

Another bootloader for your MCU project.

This is heavily inspired by MCUBoot, but was born out of my frustrations I had porting and integrating MCUBoot with some projects I was working. 

## Current State

This project is very much a work in progress. At the moment, it simply verifies the existence of an image header and footer with valid magic values and boots into the primary slot.

## Needs to be Implemented

A more concrete roadmap with the intentions and philosophy of this bootloader needs to be formalized and outlined.  However, below is a very short list of the immediate features that need to be implemented

- CRC Validation
- Implementing Swap via overwrite
- Image signing
- Logging Mechanism
- Version validation
- Multiple storage medium support (e.g. swapping between internal/external flash)

## Integrating

Please refer to the [Integration Document](./docs/integrating.md) for a guide on integrating MicroBoot into your project.

## Porting

Please refer to the [Porting Document](./docs/porting.md) for a guide on port MicroBoot to your target platform.

## Contributions

Contributions are always appreciated and encouraged.

Formal contribution guidelines have not been specified yet, but they will be outlined in the [Contributions Document](./docs/contributions.md).