# Integrating MicroBoot

Integrating MicroBoot is fairly straightforward, especially when a port for your target hardware/HAL/OS already exists. The high-level steps for integrating MicroBoot are highlighted below.

## Step 1: Create Project & Include MicroBoot Sources

The bootloader exists as a completely separate binary image that is flashed to your target hardware. As such, a new project exclusive to your bootloader must exist.

Once your project is created, bring in the MicroBoot sources into your project. This includes all the files in the `src` folder.

### Bringing MicroBoot into a `Makefile` Project

For `Makefile` based projects, `microboot.mk` is provided.

In your `Makefile`, create the variable `MICROBOOT_ROOT_DIR` which is equal to the path of the `microboot` repo/folder.

Then, include the make include file with `include ${MICROBOOT_ROOT_DIR}`.

The include file provides the following variables:

- `MICROBOOT_SOURCE_FILES`
- `MICROBOOT_INCLUDE_PATH`

The variable `MICROBOOT_SOURCE_FILES` contains paths to all the MicroBoot source files. This variable can be added to the list of sources in your project's `Makefile`.

Use the `MICROBOOT_INCLUDE_PATH` variable to add the MicroBoot source directory to your include path to easily reference needed MicroBoot header files.

### Addition Build Systems

Additional build systems, such as `CMake` are planned on being supported. It could even be you who integrates them! Please feel free to do so and submit a PR!

## Step 2: Include/Generate Port Source Files

Look through the `ports` directory to see if there's an existing port for your target platform. Include these files in your project.

If a port doesn't already exist, please see the [porting guide](./porting.md).

## Step 3: Define Your Partition Map

The description of your partitions need to be defined so MicroBoot knows where to look to find your application and upgrades.

In your project, define an array of partition objects. An example of a partition map is outlined below:

```c
#define APP_BOOTLOADER_ADDR 0x0U
#define APP_BOOTLOADER_SIZE 0x8000U

#define APP_PRIMARY_SLOT_ADDR (APP_BOOTLOADER_ADDR + APP_BOOTLOADER_SIZE)
#define APP_PRIMARY_SLOT_SIZE 0x16000

#define APP_SECONDARY_SLOT_ADDR (APP_PRIMARY_SLOT_ADDR + APP_PRIMARY_SLOT_SIZE)
#define APP_SECONDARY_SLOT_SIZE 0x16000

/**
 * @brief Partition layout defintion
 * 
 */
static flash_partition_t partitions[] = {
    {
        .type = FLASH_PARTITION_BOOTLOADER,
        .addr = APP_BOOTLOADER_ADDR,
        .size = APP_BOOTLOADER_SIZE
    },
    {
        .type = FLASH_PARTITION_SLOT_PRIMARY,
        .addr = APP_PRIMARY_SLOT_ADDR,
        .size = APP_PRIMARY_SLOT_SIZE
    },
    {
        .type = FLASH_PARTITION_SLOT_SECONDARY,
        .addr = APP_SECONDARY_SLOT_ADDR,
        .size = APP_SECONDARY_SLOT_SIZE
    },
};
```

### Partition Descriptor

A partition is defined by a type, partiton address, and size in bytes. 

A partition can be one of following types:

|Name|Enum|Description|
|----|----|-----------|
|Bootloader|`FLASH_PARTITION_BOOTLOADER`|The partition that holds the bootloader|
|Primary|`FLASH_PARTITION_SLOT_PRIMARY`|The partition that holds the image of the application to boot into.|
|Secondary|`FLASH_PARTITION_SLOT_SECONDARY`|The partition that holds the application to upgrade the primary slot with.|


## Step 4: Start MicroBoot

The next step is to initialize MicroBoot and have it start the process of checking for an update, and validating the primary image.

With the partition map outlined in the previous step, an example of starting MicroBoot is outlined below:

```c
#include "microboot.h"
#include "image_types.h"

void main() {
    // Hardware initialization
    ...

    // Initialize MicroBoot with partition map
    microboot_init(partitions, sizeof(partitions)/sizeof(flash_partition_t));

    // Attempt to load primary image
    image_t image;
    if (!microboot_boot(&image)) {
        // Image failed go to error hander
        while(1) {}
    }
}
```

## Step 5: Start Loaded Application

Once a valid image is been returned by MicroBoot, you must kick the processor into the loaded application. This is platform dependant. If an existing port exists, use the ports `start_app` implementation.

An example of starting the application outlined below:

```c
#include "microboot.h"
#include "image_types.h"
#include "start_app.h"

// Partition map definition
...

void main() {
    // Hardware Initialization
    ...

    // Fetch Image
    image_t image;
    ...

    uint32_t sp = image.image_start[0];
    uint32_t pc = image.image_start[1];
    start_app(pc, sp);

    // Should never reach here
    while(1) {}
}

```