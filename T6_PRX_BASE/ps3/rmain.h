#pragma once
#include "define.h"
#include "debug.h"
#include "render.h"


namespace Prog
{

	float color[4];
	DEBUG_ONCE(GamePaint)
		CREATE_DUMMY_STUB(int, __BoiiPaint, PAINT_ARGS);
	int PaintOverride(PAINT_ARGS) {
		once_GamePaint();
		Renderer::createColor(color, 200, 50, 50, 255);
		Renderer::DrawText("Black Ops 2", 20, 20, FONT_NORMAL, 12, color);

		return __BoiiPaint(a, b);
	}
	void Write() {
		hookfunction(0x3971A0, (void*) & PaintOverride, (void*)&__BoiiPaint);
	}
}