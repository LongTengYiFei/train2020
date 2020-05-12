NAME = test
INC_DIR = ./include
BUILD_DIR = ./build
SRC_DIR = ./src

INCLUDES = $(addprefix -I, $(INC_DIR))
CFLAGS += $(INCLUDES)

SRCS = $(shell find src/ -name "*.c")
objects =$(SRCS:.c=.o) 

test : $(objects)
	gcc -o $(NAME) $(objects)
	mkdir $(BUILD_DIR)
	mv $(SRC_DIR)/*.o $(BUILD_DIR)
	mv $(NAME) $(BUILD_DIR)

.PHONY: clean
clean:
	rm  -fr $(BUILD_DIR)
