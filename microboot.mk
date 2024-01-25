# Please define the following variable in your Makefile
# MICROBOOT_ROOT_DIR=path/to/microboot/

# Src files
MICROBOOT_SOURCE_FILES = \
	${MICROBOOT_ROOT_DIR}/src/microboot.c \
	${MICROBOOT_ROOT_DIR}/src/image_loader.c

# Include path
MICROBOOT_INCLUDE_PATH=${MICROBOOT_ROOT_DIR}/src