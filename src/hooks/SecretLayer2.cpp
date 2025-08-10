#include <Geode/modify/SecretLayer2.hpp>

#include "utils.hpp"

using namespace geode::prelude;


class $modify(SecretLayer2) {
	$override
	bool init() {
		if (!SecretLayer2::init())
			return false;

		req::utils::createCopyLSButton(this->getChildByID("menu"));

		return true;
	}
};