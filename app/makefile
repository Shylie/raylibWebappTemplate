ifeq ($(OS),Windows_NT)
	USER_SHELL  ?= cmd
else
	USER_SHELL  ?= sh
endif

EMSDK_PATH           = ../emsdk
EMSCRIPTEN_PATH      = $(EMSDK_PATH)/upstream/emscripten

RAYLIB_PATH          = ../raylib

CC                   = $(EMSCRIPTEN_PATH)/emcc
CFLAGS              := -Wall -D_DEFAULT_SOURCE -Wno-missing-braces -Werror=pointer-arith -fno-strict-aliasing -std=c++17 -O3 $(CFLAGS)

INCLUDE_PATHS        = -I. -I$(RAYLIB_PATH)/src -I$(EMSCRIPTEN_PATH)/system/include
LDFLAGS             := $(RAYLIB_PATH)/src/libraylib.a  -s USE_GLFW=3 -s ASYNCIFY -s ASYNCIFY_IMPORTS=['emscripten_asm_const_int'] -s EXPORTED_RUNTIME_METHODS=['lengthBytesUTF8','stringToUTF8','UTF8ToString'] --shell-file minshell.html $(LDFLAGS)

SOURCE_FILES         = app.cpp main.cpp
OBJS                 = $(patsubst %.cpp, %.o, $(SOURCE_FILES))

build: setup activate_emsdk raylib $(OBJS)
	"$(CC)" $(CFLAGS) $(OBJS) $(LDFLAGS) -o build/app.html

run: build activate_emsdk
	emrun build/app.html

%.o: %.cpp
	"$(CC)" -c $(CFLAGS) $(INCLUDE_PATHS) $< -o $@

setup: setup_$(USER_SHELL)

setup_cmd:
	if not exist build\ ( mkdir build )

setup_sh:
	mkdir -p build

clean: clean_$(USER_SHELL)

clean_cmd: clean_raylib
	del *.o
	del build\*.html
	del build\*.wasm
	del build\*.js

clean_sh: clean_raylib
	rm -f *.o
	rm -f build/*.html
	rm -f build/*.wasm
	rm -f build/*.js

clean_raylib:
	$(MAKE) -C $(RAYLIB_PATH)/src/ clean

raylib:
	$(MAKE) PLATFORM=PLATFORM_WEB EMSDK_PATH=../$(EMSDK_PATH) PYTHON_PATH=../$(EMSDK_PATH)/python/3.9.2_64bit -C $(RAYLIB_PATH)/src

activate_emsdk:
	"$(EMSDK_PATH)/emsdk" activate latest