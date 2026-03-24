# Makefile for MSD.
# This is part of the Micha1207's System Data program (MSD)
#
# Author:  Micha1207
# Date:    Mar 14, 2025
# License: GNU GPL v3 (full license in LICENSE file)
# This program comes with NO WARRANTY; to the extent permitted by law.
CC      = gcc
CFLAGS  = -Wall -Wextra -std=gnu99 -Iinclude -g
LIBS    = -lncurses -lm
TARGET  = msd
SRC_DIR = src
OBJ_DIR = obj
INSTALL_PATH = /usr/local/bin

SRCS    = $(wildcard $(SRC_DIR)/*.c)
OBJS    = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

.PHONY: all
all: $(OBJ_DIR) $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/ $(TARGET)

install:
	install -m 775 $(TARGET) $(INSTALL_PATH)
