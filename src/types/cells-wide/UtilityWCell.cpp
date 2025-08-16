#include "UtilityWCell.hpp"

#include "RequestsManager.hpp"
#include "QuickNotification.hpp"
#include "CompressLSPopup.hpp"
#include "Seed2Popup.hpp"

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
	m_bg = CCScale9Sprite::create("square02b_001.png");
	m_bg->setContentSize(s_contentSize);
	if (!CCMenuItemSpriteExtra::init(
		m_bg, nullptr,
		this, nullptr
	)) return false;

	m_utility = utility;

	// bg init related stuff
	m_bg->setColor({ 0, 0, 0 });
	m_bg->setOpacity(90);
	m_bg->setID("background");

	// CCMISE init related stuff
	m_scaleMultiplier = 0.975f;
	m_pfnSelector = menu_selector(UtilityWCell::onClick);


	char const* utilityName;
	CCSprite* utilitySpr;

	switch (m_utility) {
		case GJP2:
			utilityName = "GJP2";
			utilitySpr = CCSprite::createWithSpriteFrameName("GJLargeLock_001.png");
			utilitySpr->setScale(0.8f);
			break;

		case LevelString:
			utilityName = "Level String";
			utilitySpr = CCSprite::createWithSpriteFrameName("folderIcon_001.png");
			utilitySpr->setScale(1.5f);

			updateLevelStringBGColor(RequestsManager::get()->getCopyLevelStringValue());
			break;

		case CompressLS: {
			utilityName = "Compress\nLevel String";
			utilitySpr = CCSprite::createWithSpriteFrameName("folderIcon_001.png");
			utilitySpr->setScale(1.5f);
			
			auto lockSpr = CCSprite::createWithSpriteFrameName("GJ_lock_001.png");
			lockSpr->CCNode::setPosition(33.f, 5.f);
			lockSpr->setScale(0.5f);
			utilitySpr->addChild(lockSpr);
		} break;

		case Seed2:
			utilityName = "Seed2";
			utilitySpr = CCSprite::createWithSpriteFrameName("GJ_hammerIcon_001.png");
			utilitySpr->setScale(1.75f);
			break;

		default:
			utilityName = "UNKNOWN";
			utilitySpr = CCSprite::createWithSpriteFrameName("GJ_deleteIcon_001.png");
			utilitySpr->setScale(2.f);
			break;
	}

	std::string utilityID = utilityName;
	this->setID(fmt::format("{}-utility", nameToID(utilityID)));

	auto nameLabel = CCLabelBMFont::create(utilityName, "bigFont.fnt");
	nameLabel->limitLabelWidth(s_contentSize.width - 10.f, 1.f, 0.1f);
	nameLabel->setID("name-label");
	this->addChildAtPosition(nameLabel, Anchor::Top, { 0.f, -15.f });

	utilitySpr->setID("info-sprite");
	this->addChildAtPosition(utilitySpr, Anchor::Center, { 0.f, -10.f });

	return true;
}

void UtilityWCell::onClick(CCObject*) {
	switch (m_utility) {
		case GJP2:
			clipboard::write(GJAccountManager::get()->m_GJP2);

			QuickNotification::create(
				" GJP2 copied to clipboard.\n"
				" <cr>Don't show it to anyone - this is your encrypted password!</c>",
				NotificationIcon::Info,
				1.5f
			)->show();
			break;

		case LevelString: {
			bool enabled = RequestsManager::get()->toggleCopyLevelString();
			updateLevelStringBGColor(enabled);

			QuickNotification::create(
				fmt::format(
					"{} level string <cf>copy</c> button in level menus.",
					enabled ? "Enabled" : "Disabled"
				),
				NotificationIcon::Info,
				1.5f
			)->show();
		} break;

		case CompressLS:
			CompressLSPopup::create()->show();
			break;

		case Seed2:
			Seed2Popup::create()->show();
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

std::string& UtilityWCell::nameToID(std::string& str) const {
	string::replaceIP(str, " ", "-");
	string::replaceIP(str, "\n", "-");

	return string::toLowerIP(str);
}

void UtilityWCell::updateLevelStringBGColor(bool enabled) {
	m_bg->setColor(enabled ? ccc3(0, 255, 0) : ccc3(0, 0, 0));

	return;
}