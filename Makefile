CC := "$(HOME)/opt/cross/bin/i686-elf-gcc"
ASM := nasm

SRC_DIR ?= src
BIN_DIR ?= bin

KERNEL_BIN_NAME ?= kernel.bin
KERNEL_BIN_FILE := $(BIN_DIR)/$(KERNEL_BIN_NAME)

LINKER_FILE_NAME ?= linker.ld
LINKER_FILE := $(SRC_DIR)/$(LINKER_FILE_NAME)

ISO_NAME ?= worstosever.iso
ISO_DIR_NAME ?= isodir

ISO_DIR := $(BIN_DIR)/$(ISO_DIR_NAME)
ISO_BOOT_DIR := $(ISO_DIR)/boot
ISO_GRUB_DIR := $(ISO_BOOT_DIR)/grub

ISO_FILE := $(BIN_DIR)/$(ISO_NAME)

GRUB_FILE_NAME ?= grub.cfg
GRUB_FILE := $(SRC_DIR)/$(GRUB_FILE_NAME)

ASM_FLAGS ?= -felf32

C_COMMON_FLAGS ?= -ffreestanding -O2
C_COMPILE_FLAGS ?= -std=gnu99 -Wall -Wextra -MMD
C_LINK_FLAGS ?= -nostdlib -lgcc

SRC_SUBDIRS := $(shell find $(SRC_DIR) -type d)
BIN_SUBDIRS := $(patsubst $(SRC_DIR)%,$(BIN_DIR)%,$(SRC_SUBDIRS))

C_SRC_FILES := $(foreach SRC_SUBDIR,$(SRC_SUBDIRS), $(wildcard $(SRC_SUBDIR)/*.c))
C_BIN_FILES := $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(C_SRC_FILES))

ASM_SRC_FILES := $(foreach SRC_SUBDIR,$(SRC_SUBDIRS), $(wildcard $(SRC_SUBDIR)/*.asm))
ASM_BIN_FILES := $(patsubst $(SRC_DIR)/%.asm,$(BIN_DIR)/%.o,$(ASM_SRC_FILES))

.PHONY: clean

$(ISO_FILE): $(KERNEL_BIN_FILE) $(GRUB_FILE) | $(ISO_GRUB_DIR)
	cp $(KERNEL_BIN_FILE) $(ISO_BOOT_DIR)
	cp $(GRUB_FILE) $(ISO_GRUB_DIR)
	grub-mkrescue -o $(ISO_FILE) $(ISO_DIR)

$(KERNEL_BIN_FILE): $(ASM_BIN_FILES) $(C_BIN_FILES) | $(LINKER_FILE)
	$(CC) -T $(LINKER_FILE) $(C_COMMON_FLAGS) $(C_LINK_FLAGS) -o $@ $^

-include $(C_BIN_FILES:.o=.d)

$(C_BIN_FILES): $(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_SUBDIRS)
	$(CC) $(C_COMMON_FLAGS) $(C_COMPILE_FLAGS) -o $@ -c $<

$(ASM_BIN_FILES): $(BIN_DIR)/%.o: $(SRC_DIR)/%.asm | $(BIN_SUBDIRS)
	$(ASM) $(ASM_FLAGS) -o $@ $^

$(ISO_GRUB_DIR): | $(BIN_DIR)
	mkdir -p $@

$(BIN_SUBDIRS):
	mkdir $@

clean:
	rm -rf $(BIN_DIR)