#include "appframe.h"
#include "PlayerParameter.h"

namespace PP {
	void Parameter::TestJsonLoad(const std::string path) {
    ju->Import(path);

	  ju->Read("ATK", _ATK);
		ju->Read("DEF", _DEF);
		ju->Read("SPD", _SPD);
	}

	void Parameter::TestJsonSave(const std::string path) {
		ju->Import(path);
		ju->jsonWrite("ATK", _ATK);
		ju->jsonWrite("DEF", _DEF);
		ju->jsonWrite("SPD", _SPD);
		ju->Save(path);
	}
}
