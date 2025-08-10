#include "UtilityWCell.hpp"

#include "QuickNotification.hpp"

using namespace geode::prelude;


UtilityWCell* UtilityWCell::create(Utility utility) {
	auto ret = new UtilityWCell;

	if (ret->init(utility)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

bool UtilityWCell::init(Utility utility) {
	auto bg = CCScale9Sprite::create("square02b_001.png");
	bg->setContentSize(s_contentSize);
	if (!CCMenuItemSpriteExtra::init(
		bg, nullptr,
		this, nullptr
	)) return false;

	m_utility = utility;

	// bg init related stuff
	bg->setColor({ 0, 0, 0 });
	bg->setOpacity(90);
	bg->setID("background");

	// CCMISE init related stuff
	m_scaleMultiplier = 0.975f;
	m_pfnSelector = menu_selector(UtilityWCell::onClick);


	char const* utilityName;
	char const* utilitySprFN;
	float utilitySprScale = 1.f;

	switch (m_utility) {
		case GJP2:
			utilityName = "GJP2";
			utilitySprFN = "GJLargeLock_001.png";
			utilitySprScale = 0.8f;
			break;

		default:
			utilityName = "UNKNOWN";
			utilitySprFN = "GJ_deleteIcon_001.png";
			utilitySprScale = 2.f;
			break;
	}

	this->setID(fmt::format("{}-utility", string::toLower(utilityName)));

	auto nameLabel = CCLabelBMFont::create(utilityName, "bigFont.fnt");
	nameLabel->limitLabelWidth(s_contentSize.width - 10.f, 1.f, 0.1f);
	nameLabel->setID("name-label");
	this->addChildAtPosition(nameLabel, Anchor::Top, { 0.f, -15.f });

	auto infoSpr = CCSprite::createWithSpriteFrameName(utilitySprFN);
	infoSpr->setScale(utilitySprScale);
	infoSpr->setID("info-sprite");
	this->addChildAtPosition(infoSpr, Anchor::Center, { 0.f, -10.f });

	return true;
}

void UtilityWCell::onClick(CCObject*) {
	switch (m_utility) {
		case GJP2:
			clipboard::write(GJAccountManager::get()->m_GJP2);

			QuickNotification::create(
				"  GJP2 copied to clipboard.\n"
				"  <cr>Don't show it to anyone - this is your encrypted password!</c>",
				NotificationIcon::Info,
				1.5f
			)->show();

			break;

		default:
			QuickNotification::create(
				"  Unknown utility!\n"
				"  This is not your fault, report this to\n"
				"  the developer (Fryy_55).",
				NotificationIcon::Error, 1.5f
			)->show();

			break;
	}

	return;
}