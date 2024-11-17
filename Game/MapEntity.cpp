#include "MapEntity.h"

MapEntity::MapEntity() {
	std::string path = "res/Stage/";

	JsonUtility* jUtil;
	jUtil = new JsonUtility();
	nlohmann::json stage = jUtil->Import("res/Json/stage/DS_Stage.json").at("Stage");
	//nlohmann::json stage = jUtil->Import("res/Json/stage/Stage_Pos.json").at("asset");
	for (auto& data : stage) {	// 複数データを回す
		BLOCKPOS pos;
		data.at("objectName").get_to(pos.name);
		// UEは左手座標系/Zup →左手座標系/Yup に変換しつつ取得
		data.at("translate").at("x").get_to(pos.x);
		data.at("translate").at("z").get_to(pos.y);
		data.at("translate").at("y").get_to(pos.z);
		pos.z *= -1.f;				// 座標の変換
		data.at("rotate").at("x").get_to(pos.rx);
		data.at("rotate").at("z").get_to(pos.ry);
		data.at("rotate").at("y").get_to(pos.rz);
		pos.rx = Math::DegToRad(pos.rx);	// 回転はdegree→radianに
		pos.ry = Math::DegToRad(pos.ry);
		pos.rz = Math::DegToRad(pos.rz);
		data.at("scale").at("x").get_to(pos.sx);
		data.at("scale").at("z").get_to(pos.sy);
		data.at("scale").at("y").get_to(pos.sz);

		// 名前のモデルがすでに読み込み済か？
		if (_mapModelHandle.count(pos.name) == 0) {
			_mapModelHandle[pos.name] = gGlobal._RS->mGetModel()[pos.name]._handle;
		}

		// 名前から使うモデルハンドル＆表示フレームを決める
		if (_mapModelHandle.count(pos.name) > 0) {
			pos.modelHandle = _mapModelHandle[pos.name];
			pos.drawFrame = MV1SearchFrame(pos.modelHandle, pos.name.c_str());
		}
		if (isPlayAnimation(pos.name)) {
			//構造体の宣言
			ANIMATIONMODEL  _animModel;
			//モデルハンドル
			_animModel.model = _mapModelHandle[pos.name];
			//アニメーションスピードの係数
			_animModel.factor= gGlobal._RS->mGetAttach()[pos.name]._attach_speed;
			//アニメーションアタッチインデックス
			_animModel.attachIndex = MV1AttachAnim(_animModel.model, 0, -1, FALSE);
			//アニメーション総合時間
			_animModel.totalTime = gGlobal._RS->mGetAttach()[pos.name]._attach_time;
			//アニメーション再生時間
			_animModel.playTime = rand() % 5;
			//コンテナに格納
			_vAnim.push_back(_animModel);
		}
		// データをコンテナに追加（モデル番号があれば）
		if (pos.modelHandle != -1) {
			_vBlockPos.push_back(pos);
		}
	}
}

bool MapEntity::isPlayAnimation(std::string s)
{
	//アニメーション対象のモデルハンドル
	if (s == "grassShake2" || s == "E_Flag" || s == "E_Flag2" || s == "BigTreeLeaf"){
		return true;
	}
	return false;
}

MapEntity::~MapEntity() {
	_vBlockPos.clear();
	_mapModelHandle.clear();
}

void MapEntity::Initialize(stage global) {

}

void MapEntity::Process() {
	for (auto&& anim : _vAnim){
		//再生速度はモデルによって変わるため係数をかける
		anim.playTime += 1 * anim.factor;
		//総再生時間に到達
		if (anim.playTime >= anim.totalTime) {
			//再生時間を0に
			anim.playTime = 0;
		}
	}
}

void MapEntity::Render() {
		// 3Dブロックを描画する
	for (auto ite = _vBlockPos.begin(); ite != _vBlockPos.end(); ++ite) {
		MV1SetPosition((*ite).modelHandle, VGet((*ite).x, (*ite).y, (*ite).z));
		MV1SetRotationXYZ((*ite).modelHandle, VGet((*ite).rx, (*ite).ry, (*ite).rz));
		MV1SetScale((*ite).modelHandle, VGet((*ite).sx, (*ite).sy, (*ite).sz));
		MV1DrawFrame((*ite).modelHandle, (*ite).drawFrame);
		for (auto&& anim : _vAnim){
			MV1SetAttachAnimTime(anim.model, anim.attachIndex, anim.playTime);
		}
		MV1DrawModel((*ite).modelHandle);
	}
}


