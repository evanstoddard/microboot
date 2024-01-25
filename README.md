# MicroBoot (WIP)

A stripped down bootloader. (for now)

This project is very much a work in progress. 

## Current State

This will boot out of the primary partition, given the header and footer magics are valid and the image size reported is not greater than the partition size **INCLUDING** the header and footer.

## Needs to be Implemented
- CRC Validation
- Implementing Swap via overwrite
- Image signing
- Logging Mechanism
- Version validation
- Multiple storage medium support (e.g. swapping between internal/external flash)