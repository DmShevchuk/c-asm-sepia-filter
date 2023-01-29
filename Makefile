NAME := image-transformer

BUILDDIR = build
OBJDIR = obj
SOLUTION_DIR = solution

CFLAGS= -std=c17 -pedantic -Wall -O3 -g -c
ASMFLAGS = -g -f elf64

RM = rm -rf

CC = gcc
LINKER = $(CC)
ASM = nasm

SOLUTION = solution

SRC_DIR = $(SOLUTION_DIR)/src

MKDIR = mkdir -p

all: $(OBJDIR) $(BUILDDIR)  $(OBJDIR)/bmp_reader.o  \
$(OBJDIR)/bmp_writer.o  \
$(OBJDIR)/file_io.o \
$(OBJDIR)/header_creator.o \
$(OBJDIR)/image.o \
$(OBJDIR)/sepia.o \
$(OBJDIR)/sepia_filter.o \
$(OBJDIR)/asm_filter_caller.o \
$(OBJDIR)/main.o
	$(LINKER) -g -o $(BUILDDIR)/main $(OBJDIR)/*.o

$(OBJDIR)/bmp_reader.o: $(SRC_DIR)/bmp_reader.c
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR)/bmp_writer.o: $(SRC_DIR)/bmp_writer.c
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR)/file_io.o: $(SRC_DIR)/file_io.c
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR)/header_creator.o: $(SRC_DIR)/header_creator.c
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR)/image.o: $(SRC_DIR)/image.c
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR)/sepia.o: $(SRC_DIR)/sepia.c
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR)/sepia_filter.o: $(SRC_DIR)/sepia_filter.asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(OBJDIR)/asm_filter_caller.o: $(SRC_DIR)/asm_filter_caller.c
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR)/main.o: $(SRC_DIR)/main.c
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR):
	$(MKDIR) $@

$(BUILDDIR):
	$(MKDIR) $@

clean:
	$(RM) $(OBJDIR) $(BUILDDIR)

run: $(BUILDDIR)/main
	$(BUILDDIR)/main input.bmp out.bmp