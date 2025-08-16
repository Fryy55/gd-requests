#include "Base64URLPopup.hpp"

#include "LimitedTextArea.hpp"
#include "utils.hpp"
#include "QuickNotification.hpp"

using namespace geode::prelude;


Base64URLPopup* Base64URLPopup::create() {
	auto ret = new Base64URLPopup;

	if (ret->initAnchored(230.f, 160.f)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

bool Base64URLPopup::setup() {
	this->setTitle("URL-safe Base64 Encode");
	this->setID("Base64URLPopup");



	auto menu = CCMenu::create();
	menu->setContentSize(m_mainLayer->getContentSize());
	menu->setPosition(0.f, 0.f);
	menu->setAnchorPoint({ 0.f, 0.f });
	menu->setID("main-menu");
	m_mainLayer->addChild(menu);


	constexpr char const* stringPlaceholder = "String to encode...";
	constexpr char const* base64Placeholder = "Encoded string...";



	constexpr float stringY = 10.f;

	auto stringField = LimitedTextArea::create(
		{ 180.f, 30.f },
		stringPlaceholder,
		28,
		"bigFont.fnt",
		{ 0.f, 0.f }
	);
	stringField->getLabel()->setColor({ 100, 100, 100 });
	stringField->setID("string-field");
	m_mainLayer->addChildAtPosition(stringField, Anchor::Left, { 10.f, stringY });

	auto pasteBtnTopSpr = CCSprite::createWithSpriteFrameName("clipboard_paste.png"_spr);
	auto pasteBtnSpr = ButtonSprite::create(
		pasteBtnTopSpr,
		40.f,
		true,
		40.f,
		"GJ_button_04.png",
		1.f
	);
	pasteBtnTopSpr->setScale(1.2f);
	pasteBtnSpr->setScale(0.6f);
	auto pasteBtn = CCMenuItemExt::createSpriteExtra(
		pasteBtnSpr,
		[stringField](CCMenuItemSpriteExtra*) {
			req::utils::pasteClipboard(stringField);
			stringField->getLabel()->setColor({ 255, 255, 255 });
		}
	);
	pasteBtn->setID("paste-string-button");
	menu->addChildAtPosition(
		pasteBtn,
		Anchor::Right,
		{ -20.f, stringField->getContentHeight() / 2.f + stringY }
	);



	constexpr float base64Y = 12.f;

	auto base64Field = LimitedTextArea::create(
		{ 180.f, 30.f },
		base64Placeholder,
		28,
		"bigFont.fnt",
		{ 0.f, 0.f }
	);
	base64Field->getLabel()->setColor({ 100, 100, 100 });
	base64Field->setID("base64-field");
	m_mainLayer->addChildAtPosition(base64Field, Anchor::BottomLeft, { 10.f, base64Y });

	auto copyBtnTopSpr = CCSprite::createWithSpriteFrameName("clipboard_copy.png"_spr);
	auto copyBtnSpr = ButtonSprite::create(
		copyBtnTopSpr,
		40.f,
		true,
		40.f,
		"GJ_button_04.png",
		1.f
	);
	copyBtnTopSpr->setPositionY(copyBtnTopSpr->getPositionY() - 2.f);
	copyBtnTopSpr->setScale(1.2f);
	copyBtnSpr->setScale(0.6f);
	auto copyBtn = CCMenuItemExt::createSpriteExtra(
		copyBtnSpr,
		[base64Field](CCMenuItemSpriteExtra*) {
			if (auto base64 = base64Field->getText(); base64 == base64Placeholder)
				QuickNotification::create(
					"No string to copy!",
					NotificationIcon::Error,
					0.5f
				)->show();
			else
				req::utils::copyClipboard(base64, "URL-safe Base64 string");
		}
	);
	copyBtn->setID("copy-base64-button");
	menu->addChildAtPosition(
		copyBtn,
		Anchor::BottomRight,
		{ -20.f, base64Field->getContentHeight() / 2.f + base64Y }
	);



	auto encodeBtnSpr = ButtonSprite::create(
		"Encode",
		120, 0,
		1.f, true,
		"bigFont.fnt",
		"GJ_button_01.png"
	);
	encodeBtnSpr->setScale(0.8f);
	auto encodeBtn = CCMenuItemExt::createSpriteExtra(
		encodeBtnSpr,
		[stringField, base64Field](CCMenuItemSpriteExtra*) {
			if (auto string = stringField->getText(); string == stringPlaceholder) {
				QuickNotification::create(
					"No string to encode!",
					NotificationIcon::Error,
					0.5f
				)->show();
			} else {
				base64Field->getLabel()->setColor({ 255, 255, 255 });
				base64Field->setText(ZipUtils::base64URLEncode(string));
			}
		}
	);
	encodeBtn->setID("encode-button");
	menu->addChildAtPosition(encodeBtn, Anchor::Center, { 0.f, -14.f });

	return true;
}