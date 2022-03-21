#ifndef COMMON_H
#define COMMON_H

#include <raylib.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define CustomSaveStorageValue(position, value)\
EM_ASM(\
	window.localStorage.setItem($0 + "", $1 + "");\
, position, value)

#define CustomLoadStorageValue(position)\
EM_ASM_INT(\
	var data = window.localStorage.getItem($0 + "");\
	if (data != null) {\
		return data;\
	}\
	else {\
		return 0;\
	}\
, position)
#define CustomSetClipboardText(text)\
EM_ASM(\
	Asyncify.handleAsync(async () => {\
		await navigator.clipboard.writeText(Module.UTF8ToString($0));\
	});\
, text)
#define CustomGetClipboardText()\
((const char*)EM_ASM_INT(\
	return Asyncify.handleAsync(async () => {\
		const clip = await navigator.clipboard.readText();\
		const byteCount = Module.lengthBytesUTF8(clip) + 1;\
		const ptr = Module._malloc(byteCount);\
		Module.stringToUTF8(clip, ptr, byteCount);\
		return ptr;\
	});\
))
#define CustomFreeClipboardText(ptr)\
do\
{\
	free((void*)ptr);\
}\
while (false)
#else
#define CustomSaveStorageValue(position, value) SaveStorageValue(position, value)
#define CustomLoadStorageValue(position) LoadStorageValue(position)
#define CustomSetClipboardText(text) SetClipboardText(text)
#define CustomGetClipboardText() GetClipboardText()
#define CustomFreeClipboardText(ptr)
#endif // __EMSCRIPTEN__

// modify this struct as needed
struct AppState
{
};

extern AppState appState;
void Setup();
void Update();
void Draw();
void Shutdown();

#endif // COMMON_H
