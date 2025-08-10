#include <Geode/modify/EditLevelLayer.hpp>

#include "utils.hpp"

using namespace geode::prelude;


class $modify(EditLevelLayer) {
	$override
	bool init(GJGameLevel* level) {
		if (!EditLevelLayer::init(level))
			return false;

		req::utils::createCopyLSButton(level, this->getChildByID("level-actions-menu"));

		return true;
	}
};