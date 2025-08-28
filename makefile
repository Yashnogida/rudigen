

# 	  --- TO DO ---
# 1. Fix multiple "Could not find del" Errors
# 2. Check to see if obj directory exists and create it if it doesn't

.PHONY: test
.PHONY: clean

OBJ_DIR = obj
SRC_DIR = src

vpath %.c src
vpath %.h include


CC = gcc

INCLUDE = -Iinclude/SDL2 \
          -Iinclude/SDL_ttf \
		  -Iinclude \

CFLAGS += -ggdb $(INCLUDE)

SDL_LIB = -L./lib/SDL2 \
          -lSDL2main \
		  -lSDL2 \
		  -L./lib/SDL_ttf \
		  -lSDL2_ttf 

LIBS += -lmingw32 -lws2_32 $(SDL_LIB) 

srcs := $(wildcard $(SRC_DIR)/*.c)           # Get List of all C files in source directory
objects := $(notdir $(srcs:%.c=%.o))         # Remove source directory prefix
objs := $(addprefix $(OBJ_DIR)/,$(objects))  # Add object directory prefix

a.exe : $(objs)
	$(CC) $(LDFLAGS) $(objs) $(LIBS) -o $@ 

$(OBJ_DIR) $(OBJ_DIR)/%.o : %.c 
	$(CC) -c $(CFLAGS) $< -o $@ 


del_arg := $(addprefix $(OBJ_DIR)\,$(objects))

clean:
	$(foreach file,$(del_arg),del $(file))
