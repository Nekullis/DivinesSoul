//----------------------------------------------------------------------
// @filename EnumInfo.h
// @author: Fukuma Kyohei,Nara Mitsuki
// @explanation
// スキルや武器の種類をまとめたクラス
//----------------------------------------------------------------------
#pragma once

enum class kindDivine : int
{
	// スキル9種類
	NONE = -1,
	BLEATH, CIRCLE, LASER, 
	SLASH, EXPLOSION, DASH,
	VACCUM, SONIC_WAVE,
};

enum class kindWeapon
{
	SWORD,AXE
};
