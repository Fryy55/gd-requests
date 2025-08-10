#include <Geode/modify/LevelSelectLayer.hpp>

#include "utils.hpp"

using namespace geode::prelude;


class $modify(LevelSelectLayer) {
	$override
	bool init(int page) {
		if (!LevelSelectLayer::init(page))
			return false;

		req::utils::createCopyLSButton(m_scrollLayer, this->getChildByID("info-menu"));

		return true;
	}
};