#include "appframe.h"
#include "PlayerParameter.h"

namespace PP {
	void Parameter::TestJsonLoad(const std::string path) {
		//nlohmann::json json;
    ju->Import(path);

	  ju->Read("ATK", _ATK);
		ju->Read("DEF", _DEF);
		ju->Read("SPD", _SPD);
		//json.at("ATK").get_to(_ATK);
		//json.at("DEF").get_to(_DEF);
		//json.at("SPD").get_to(_SPD);
	}

	void Parameter::TestJsonSave(const std::string path) {
		ju->Import(path);
		ju->jsonWrite("ATK", _ATK);
		ju->jsonWrite("DEF", _DEF);
		ju->jsonWrite("SPD", _SPD);
		ju->Save(path);
	}
}
