#pragma once
#include "appframe.h"
#include <unordered_map>
#include <string>
#include "JsonUtility.h"

namespace PP {
	class Parameter {
	public:
		Parameter() { _ATK = 0; _DEF = 0; _SPD = 0; ju = new JsonUtility(); }
		virtual ~Parameter() { delete ju; }

		void TestJsonLoad(const std::string path);
		void TestJsonSave(const std::string path);

		int GetATK(){ return _ATK; }
		int GetDEF() { return _DEF; }
		int GetSPD() { return _SPD; }

		void SetATK(int parameter) { _ATK = parameter; }
		void SetDEF(int parameter) { _DEF = parameter; }
		void SetSPD(int parameter) { _SPD = parameter; }
	protected:

		int _ATK;
		int _DEF;
		int _SPD;
		JsonUtility* ju;

	};

	//template <typename T>
	//void Parameter::TestJsonSave(const std::string filepath, const std::string name, const T content) {
	//	ju->Save(filepath, ju->json);
	//}
}