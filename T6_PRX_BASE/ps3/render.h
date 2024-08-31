#pragma once
#include "boii.h"
#define __RENDER_H__
// this doesnt make sense at all.
// missing parameters.
namespace Renderer
{
	void DrawText(char* text, float x, float y, char* font, float size, float* color) {
		cmdDrawText(text, x, y, font, size, color);
	}
	void DrawNumberedShader(int shaderId, float x, float y, float width, float height, float* color) {
		cmdDrawPictureStretch(x, y, width, height, 1, 1, 1, 1, color, RegisterHandle("white", 0, false, 0));
	}
	void createColor(float(&col)[4], byte r, byte g, byte b, byte a) {
		col[0] = ((float)r) / 255.0f;
		col[1] = ((float)g) / 255.0f;
		col[2] = ((float)b) / 255.0f;
		col[3] = ((float)a) / 255.0f;
	}
}

