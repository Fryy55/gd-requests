#include <Geode/modify/EditLevelLayer.hpp>

#include "RequestsManager.hpp"
#include "utils.hpp"

using namespace geode::prelude;


class $modify(EditLevelLayer) {
	$override
	bool init(GJGameLevel* level) {
		if (!EditLevelLayer::init(level))
			return false;

		if (!RequestsManager::get()->getCopyLevelStringValue())
			return true;

		auto button = CCMenuItemExt::createSpriteExtra(
			CircleButtonSprite::createWithSpriteFrameName(
				"clipboard_copy.png"_spr,
				1.f,
				CircleBaseColor::Cyan
			),
			[level](CCMenuItemSpriteExtra*) {
				req::utils::copyClipboard(level->m_levelString, "Level string");
			}
		);
		button->setID("copy-level-string-button"_spr);

		auto menu = this->getChildByID("level-actions-menu");
		menu->addChild(button);
		menu->updateLayout();

		return true;
	}
};