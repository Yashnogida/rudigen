

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
		#   -I"C:/Program Files (x86)/Windows Kits/10/Include/10.0.26100.0/um" \
		#   -I"C:/Program Files (x86)/Windows Kits10/Include/10.0.26100.0/shared" \
		#   -I"C:/Program Files (x86)/Windows Kits/10/Include/10.0.26100.0/shared"

CFLAGS += -ggdb $(INCLUDE)

SDL_LIB = -L./lib/SDL2 \
          -lSDL2main \
		  -lSDL2 \
		  -L./lib/SDL_ttf \
		  -lSDL2_ttf 
        #   -l"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.26100.0/um/x64/dwmapi"

LIBS += -lmingw32 -lws2_32 $(SDL_LIB) ./lib/plxapi.lib ./lib/sicl32.lib

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
