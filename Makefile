########################################################
# Project: IMS Heat pump and photovoltaic simulation
# File: Makefile
# Date: 21.11.2022
# Author: Adam Dzurilla xdzuri00@stud.fit.vutbr.cz
#
# Description: Build script
########################################################

# Compiler
CC=g++

# Files for compile
FILES=src/*.cpp

# Files for pack
FILES_FOR_PACK=src/*.cpp src/*.hpp IMS_doc.pdf Makefile README.md

# Flags
CFLAGS= -std=c++17 -Wall -Wextra

# Simlib path
SIMLIB_PATH = -I simlib/src

# Project name
PRJ=run

# Pack name
PACK_NAME=02_xdzuri00_xmores02

########################################################

# Main task
.PHONY: all
all: build

# Pack task
pack: $(FILES_FOR_PACK) clean_pack
	zip $(PACK_NAME).zip $(FILES_FOR_PACK)

# Build task
build: clean $(PRJ)

# Build runnable files
$(PRJ):
	$(CC) $(CFLAGS) $(SIMLIB_PATH) -o $@ $(FILES) -lsimlib -lm

# Clean task
.PHONY: clean
clean:
	rm -f $(PRJ)

# Clean packed files task
clean_pack:
	rm -f $(PACK_NAME).zip
