#pragma once
#include "define.h"
#include "debug.h"
#include "render.h"
#include "np.h"
#include "np\common.h"
#include "np\basic.h"
#include <cstring>
// Created by josh, addresses by stankey or something like that.
namespace Prog
{
#define NP_PRESENCE_ARGUMENTS SceNpBasicPresenceDetails2* data, int opt
	CREATE_DUMMY_STUB(int, __pres_s, SceNpBasicPresenceDetails2*, int);
	bool wasInGame = false;
	bool isInGame = true;
	const char* mapName = nullptr;

	int update_presence_details(NP_PRESENCE_ARGUMENTS) {
		int stub_orig = __pres_s(data, opt);
		
		std::string str = ".presence\n{\n\t";
		str += "\"status\": \"";
		str += data->status;
		str += "\"\n";
		str += "\"state\": \"";
		str += data->state;
		str += "\"\n";
		str += "\"title\": \"";
		str += data->title;
		str += "\"\n";
		str += "}";
		char* jason = (char*)str.c_str();

		FS_RECREATE(RICHPC_DUMP);
		FS_APPEND_STRING(RICHPC_DUMP, jason);

		return stub_orig;
	}

	void gameStateChangeCallback(bool was, bool isIt) {
		if (isIt && (!was)) {
			Cbuff_addText(0, "cg_fov 120");
			Cbuff_addText(0, "cg_fov_default 120");
			Cbuff_addText(0, "r_dof_enable 20");
			*(int*)0x01CB6F38 = 120; // cg max fps
		}
	}

	void updateInGame(bool x, void(*single)(bool, bool) = nullptr) {
		if (isInGame != x) {

			wasInGame = isInGame;
			isInGame = x;
			if (single) {
				single(wasInGame, isInGame);
			}

		}
	}

	float color[4];
	DEBUG_ONCE(GamePaint);
	CREATE_DUMMY_STUB(int, __BoiiPaint, PAINT_ARGS);
	int PaintOverride(PAINT_ARGS) {

		bool ingame = getBoolByDvarName("cl_ingame");
		once_GamePaint();
		
		if (ingame) {
			Renderer::createColor(color, 200, 50, 50, 255);
			Renderer::DrawText("FontBig", 20, 20, FONT_BIG, 1.0, color);
			Renderer::DrawText("FontBigDev", 20, 32, FONT_BIG_DEV, 1.0, color);
			Renderer::DrawText("FontBold", 20, 44, FONT_BOLD, 1.0, color);
			Renderer::DrawText("FontConsole", 20, 56, FONT_CONSOLE, 1.0, color);

		}
		
		updateInGame(ingame, gameStateChangeCallback);
		return __BoiiPaint(a, b);
	}
	void Write() {
		hookfunction(0x008DE874, take(update_presence_details), take(__pres_s));
		hookfunction(0x3971A0, take(PaintOverride), take(__BoiiPaint));
		// sceNpPresenceSetDetails 0x008DE874
	}
}
/*
  public static UInt32 cg_fov = 0x1CC5200 + 0x18;
  public static UInt32 cg_fovExtraCam = 0x1CC5320 + 0x18;
  public static UInt32 cg_fovMin = 0x1CC52C0 + 0x18;
  public static UInt32 cg_fovScale = 0x1CC5260 + 0x18;
  public static UInt32 cg_friendlyNameFadeIn = 0x1CC70C0 + 0x18;
  public static UInt32 cg_friendlyNameFadeOut = 0x1CC7180 + 0x18;
  public static UInt32 cg_fuelHudVersion = 0x1CCB260 + 0x18;
  public static UInt32 cg_gun_move_f = 0x1CCD780 + 0x18;
  public static UInt32 cg_gun_move_minspeed = 0x1CCDB40 + 0x18;
  public static UInt32 cg_gun_move_r = 0x1CCD7E0 + 0x18;
  public static UInt32 cg_gun_move_rate = 0x1CCDAE0 + 0x18;
  public static UInt32 cg_gun_move_u = 0x1CCD840 + 0x18;
  public static UInt32 cg_gun_ofs_f = 0x1CCD8A0 + 0x18;
  public static UInt32 cg_gun_ofs_r = 0x1CCD900 + 0x18;
  public static UInt32 cg_gun_ofs_u = 0x1CCD960 + 0x18;
  public static UInt32 cg_gun_rot_minspeed = 0x1CCDC00 + 0x18;
  public static UInt32 cg_gun_rot_p = 0x1CCD9C0 + 0x18;
  public static UInt32 cg_gun_rot_r = 0x1CCDA80 + 0x18;
  public static UInt32 cg_gun_rot_rate = 0x1CCDBA0 + 0x18;
  public static UInt32 cg_gun_rot_y = 0x1CCDA20 + 0x18;
  public static UInt32 cg_gun_x = 0x1CCD660 + 0x18;
  public static UInt32 cg_gun_y = 0x1CCD6C0 + 0x18;
  public static UInt32 cg_gun_z = 0x1CCD720 + 0x18;

*/