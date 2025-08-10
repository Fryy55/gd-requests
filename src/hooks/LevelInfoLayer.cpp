#include <Geode/modify/LevelInfoLayer.hpp>

#include "utils.hpp"

using namespace geode::prelude;


class $modify(LevelInfoLayer) {
	$override
	bool init(GJGameLevel* level, bool challenge) {
		if (!LevelInfoLayer::init(level, challenge))
			return false;

		req::utils::createCopyLSButton(level, this->getChildByID("left-side-menu"));

		return true;
	}
};