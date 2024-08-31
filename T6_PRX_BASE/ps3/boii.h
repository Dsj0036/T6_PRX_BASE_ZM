#include "System.h"
#include "define.h"
#ifndef __BOII__

#define FONT_SMALL_DEV    "fonts/720/smallDevFont"
#define FONT_BIG_DEV    "fonts/720/bigDevFont"
#define FONT_CONSOLE    "fonts/720/consoleFont"
#define FONT_BIG        "fonts/720/bigFont"
#define FONT_SMALL        "fonts/720/smallFont"
#define FONT_BOLD        "fonts/720/boldFont"
#define FONT_NORMAL        "fonts/normalFont"
#define FONT_NORMAL2        "fonts/720/normalFont2"
#define FONT_EXTRA_BIG    "fonts/720/extraBigFont"
#define FONT_OBJECTIVE    "fonts/720/objectiveFont"
#define FONT_italicFont    "fonts/720/italicFont"

template <typename R, typename ...Arguments>
inline R fcall(long long function, Arguments... args)
{
	int toc_t[2] = { function,  TOC };
	R(*temp)(Arguments...) = (R(*)(Arguments...)) & toc_t;
	return temp(args...);
}
enum class Buttons
{
	Null = 0,
	Cross = 1,
	Circle = 2,
	Square = 3,
	Triangle = 4,
	L1 = 5,
	R1 = 6,
	Start = 14,
	Select = 15,
	L3 = 16,
	R3 = 17,
	L2 = 18,
	R2 = 19,
	UP = 20,
	DOWN = 21,
	LEFT = 22,
	RIGHT = 23,
	APAD_UP = 28,
	APAD_DOWN = 29,
	APAD_LEFT = 30,
	APAD_RIGHT = 31
};

bool detect(Buttons Button)
{
	// a call. Basically
	int Key_IsDown_t[2] = { 0x1185BC, 0xD67E98 };
	int(*Key_IsDown)(int localClientNum, int keynum) = (int(*)(int, int)) & Key_IsDown_t;
	return Key_IsDown(0, (byte)Button);
}
enum dvarType_t {
	DVAR_TYPE_INVALID = 0x0,
	DVAR_TYPE_BOOL = 0x1,
	DVAR_TYPE_FLOAT = 0x2,
	DVAR_TYPE_FLOAT_2 = 0x3,
	DVAR_TYPE_FLOAT_3 = 0x4,
	DVAR_TYPE_FLOAT_4 = 0x5,
	DVAR_TYPE_INT = 0x6,
	DVAR_TYPE_ENUM = 0x7,
	DVAR_TYPE_STRING = 0x8,
	DVAR_TYPE_COLOR = 0x9,
	DVAR_TYPE_INT64 = 0xA,
	DVAR_TYPE_LINEAR_COLOR_RGB = 0xB,
	DVAR_TYPE_COLOR_XYZ = 0xC,
	DVAR_TYPE_COUNT = 0xD,
};
union DvarLimits {
	struct {
		int stringCount;
		const char** strings;
	} enumeration;

	struct {
		int min;
		int max;
	} integer;

	struct {
		float min;
		float max;
	} value, vector;

	struct {
		int64_t min;
		int64_t max;
	} integer64;
};
union DvarValue {
	bool enabled;
	int integer;
	unsigned int unsignedInt;
	int64_t integer64;
	int64_t unsignedInt64;
	float value;
	float vectorv[4];
	const char* string;
	char color[4];
};
struct dvar_t {
	const char* name;
	const char* description;
	int hash;
	unsigned int flags;
	dvarType_t type;
	bool modified;
	DvarValue current;
	DvarValue latched;
	DvarValue reset;
	DvarLimits domain;
	dvar_t* hashNext;
	int unknown3;
};

dvar_t* FindMaleableVar(const char* varName) {
	return (dvar_t*)fcall<uint>(0x3DA628, varName);
}
any Cbuff_addText(int client, char* data) {
	return fcall<uint>(0x313c18, client, data);
}
bool getBool_dvar(dvar_t* var) {
	if (fcall<bool>(0x3da948, var))
	{
		return true;
	}
	return false;
}
uintptr_t RegisterFont(const char* name, int imageTrack) {
	return fcall<uint>(0x75A2C0, name, imageTrack);
}
void* RegisterHandle(char* name, int imageTrack, bool errorIfMissing, int waitTime) {
	return fcall<void*>(0x763220, name, imageTrack, errorIfMissing, waitTime);
}
void cmdDrawText(const char* xtext, float x, float y, char* xfont, float fontsize, float* color) {
	fcall<uint>(0x76A910, xtext, 0x7fffffff, RegisterFont(xfont, 0), x,y, fontsize, fontsize, 0, color, 0);
}
void cmdDrawPictureStretch(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float* color, void* material) {
	fcall<uint>(0x076A3E8, x, y, w, h, s0, t0, s1, t1, color, material);
}


#endif
