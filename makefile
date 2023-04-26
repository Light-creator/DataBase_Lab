TARGET = ./main.o
HDRS_DIR = \
		headers
SRCS = \
		main.cpp \
		utils.cpp \
		structures.cpp
.PHONY: all, build, clean, run

$(TARGET):
		g++ -I $(HDRS_DIR) -g $(SRCS) -o $(TARGET)

all: clean build

build: $(TARGET)

clean: 
		rm -rf $(TARGET)

run: 
		$(TARGET)