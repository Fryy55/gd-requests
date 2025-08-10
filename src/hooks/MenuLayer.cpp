#include <Geode/Geode.hpp>

#include "RequestsLayer.hpp"

#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;


class $modify(MenuLayer) {
	$override
	bool init() {
		if (!MenuLayer::init())
			return false;

		auto rightMenu = this->getChildByID("right-side-menu");
		auto reqBtn = CCMenuItemExt::createSpriteExtra(
			CCSprite::createWithSpriteFrameName("accountBtn_messages_001.png"),
			[](CCMenuItemSpriteExtra*) {
				CCDirector::get()->pushScene(
					CCTransitionFade::create(0.5f, RequestsLayer::scene())
				);
			}
		);
		reqBtn->setID("requests-button"_spr);

		rightMenu->addChild(reqBtn);
		rightMenu->updateLayout();

		return true;
	}
};