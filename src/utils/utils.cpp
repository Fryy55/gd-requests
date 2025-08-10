#include "utils.hpp"

#include <Geode/ui/TextInput.hpp>

#include "constants.hpp"
#include "QuickNotification.hpp"
#include "RequestsManager.hpp"

using namespace geode::prelude;


bool req::utils::validateString(
	std::string const& string,
	req::utils::StringType type,
	std::optional<std::string_view> oldKey
) {
	char const* typeString;
	std::string filter;

	switch (type) {
		case req::utils::StringType::Key:
			typeString = "Key";
			filter = getCommonFilterAllowedChars(CommonFilter::Alphanumeric);
			break;

		case req::utils::StringType::Value:
			typeString = "Value";
			filter = constants::valueFilter;
			break;

		case req::utils::StringType::Endpoint:
			typeString = "Endpoint";
			filter = constants::urlFilter;
			break;

		default:
			throw "Unknown string type";
	}

	if (string.empty()) {
		QuickNotification::create(
			fmt::format("{} can't be empty!", typeString),
			NotificationIcon::Error,
			0.5f
		)->show();
		return false;
	}

	do if (type == req::utils::StringType::Key && RequestsManager::get()->getDB()->contains(string)) {
		if (oldKey && string == oldKey.value())
			break;

		QuickNotification::create("Key already exists!", NotificationIcon::Error, 0.5f)->show();
		return false;
	} while (false);

	for (auto c : string) {
		if (!string::contains(filter, c)) {
			QuickNotification::create(
				fmt::format("Forbidden character: \"{}\"", c),
				NotificationIcon::Error,
				0.5f
			)->show();
			return false;
		}
	}

	return true;
}

void req::utils::pasteClipboard(TextInput* textInput) {
	textInput->setString(clipboard::read());
	QuickNotification::create("Clipboard pasted.", NotificationIcon::None, 0.5f)->show();

	return;
}

void req::utils::copyClipboard(std::string const& string, std::string_view content) {
	clipboard::write(string);
	QuickNotification::create(fmt::format("{} copied to clipboard.", content))->show();

	return;
}

// EditLevelLayer and LevelInfoLayer overload
void req::utils::createCopyLSButton(GJGameLevel* level, CCNode* menu) {
	if (!RequestsManager::get()->getCopyLevelStringValue())
		return;

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

	menu->addChild(button);
	menu->updateLayout();

	return;
}

// LevelSelectLayer overload
void req::utils::createCopyLSButton(BoomScrollLayer* scrollLayer, cocos2d::CCNode* menu) {
	if (!RequestsManager::get()->getCopyLevelStringValue())
		return;

	auto button = CCMenuItemExt::createSpriteExtra(
		CircleButtonSprite::createWithSpriteFrameName(
			"clipboard_copy.png"_spr,
			1.f,
			CircleBaseColor::Cyan
		),
		[scrollLayer](CCMenuItemSpriteExtra*) {
			req::utils::copyClipboard(
				static_cast<LevelPage*>(
					scrollLayer->getPage(scrollLayer->m_page)
				)->m_level->m_levelString,
				"Level string"
			);
		}
	);
	button->setID("copy-level-string-button"_spr);

	menu->addChild(button);
	button->setPosition(-5.f, button->getContentHeight() / 2.f - menu->getPositionY());

	return;
}

// SecretLayer2 overload
void req::utils::createCopyLSButton(cocos2d::CCNode* menu) {
	if (!RequestsManager::get()->getCopyLevelStringValue())
		return;

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

	menu->addChild(button);

	auto playBtn = menu->getChildByID("the-challenge-button");
	button->setPosition(playBtn->getPositionX() - 50.f, playBtn->getPositionY());

	return;
}