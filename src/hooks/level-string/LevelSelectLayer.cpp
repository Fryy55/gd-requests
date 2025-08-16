#include <Geode/modify/LevelSelectLayer.hpp>

#include "RequestsManager.hpp"
#include "utils.hpp"

using namespace geode::prelude;


class $modify(LevelSelectLayer) {
	$override
	bool init(int page) {
		if (!LevelSelectLayer::init(page))
			return false;

		if (!RequestsManager::get()->getCopyLevelStringValue())
			return true;

		auto button = CCMenuItemExt::createSpriteExtra(
			CircleButtonSprite::createWithSpriteFrameName(
				"clipboard_copy.png"_spr,
				1.f,
				CircleBaseColor::Cyan
			),
			[this](CCMenuItemSpriteExtra*) {
				req::utils::copyClipboard(
					static_cast<LevelPage*>(
						m_scrollLayer->getPage(m_scrollLayer->m_page)
					)->m_level->m_levelString,
					"Level string"
				);
			}
		);
		button->setID("copy-level-string-button"_spr);

		auto menu = this->getChildByID("info-menu");
		menu->addChild(button);
		button->setPosition(-5.f, button->getContentHeight() / 2.f - menu->getPositionY());

		return true;
	}
};