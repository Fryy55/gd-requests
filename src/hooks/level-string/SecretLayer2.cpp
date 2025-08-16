#include <Geode/modify/SecretLayer2.hpp>

#include "RequestsManager.hpp"
#include "utils.hpp"

using namespace geode::prelude;


class $modify(SecretLayer2) {
	$override
	bool init() {
		if (!SecretLayer2::init())
			return false;

		if (!RequestsManager::get()->getCopyLevelStringValue())
			return true;

		auto spr = CircleButtonSprite::createWithSpriteFrameName(
			"clipboard_copy.png"_spr,
			1.f,
			CircleBaseColor::Cyan
		);
		spr->setScale(0.8f);
		auto button = CCMenuItemExt::createSpriteExtra(
			spr,
			[](CCMenuItemSpriteExtra*) {
				req::utils::copyClipboard(
					GameLevelManager::get()->getMainLevel(3001, false)->m_levelString,
					"Level string"
				);
			}
		);
		button->setID("copy-level-string-button"_spr);

		auto menu = this->getChildByID("menu");
		menu->addChild(button);

		auto playBtn = menu->getChildByID("the-challenge-button");
		button->setPosition(playBtn->getPositionX() - 50.f, playBtn->getPositionY());

		return true;
	}
};