#include "Seed2Popup.hpp"

#include "LimitedTextArea.hpp"
#include "utils.hpp"
#include "QuickNotification.hpp"

using namespace geode::prelude;


Seed2Popup* Seed2Popup::create() {
	auto ret = new Seed2Popup;

	if (ret->initAnchored(230.f, 160.f)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

bool Seed2Popup::setup() {
	this->setTitle("Generate Seed2");
	this->setID("Seed2Popup");



	auto menu = CCMenu::create();
	menu->setContentSize(m_mainLayer->getContentSize());
	menu->setPosition(0.f, 0.f);
	menu->setAnchorPoint({ 0.f, 0.f });
	menu->setID("main-menu");
	m_mainLayer->addChild(menu);


	constexpr char const* clsPlaceholder = "Compressed Level String...";
	constexpr char const* seed2Placeholder = "         Seed2         ";



	constexpr float clsY = 10.f;

	auto clsField = LimitedTextArea::create(
		{ 180.f, 30.f },
		clsPlaceholder,
		28,
		"bigFont.fnt",
		{ 0.f, 0.f }
	);
	clsField->getLabel()->setColor({ 100, 100, 100 });
	clsField->setID("compressed-level-string-field");
	m_mainLayer->addChildAtPosition(clsField, Anchor::Left, { 10.f, clsY });

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
		[clsField](CCMenuItemSpriteExtra*) {
			req::utils::pasteClipboard(clsField);
			clsField->getLabel()->setColor({ 255, 255, 255 });
		}
	);
	pasteBtn->setID("paste-cls-button");
	menu->addChildAtPosition(
		pasteBtn,
		Anchor::Right,
		{ -20.f, clsField->getContentHeight() / 2.f + clsY }
	);



	constexpr float seed2Y = 12.f;

	auto seed2Field = LimitedTextArea::create(
		{ 180.f, 30.f },
		seed2Placeholder,
		28,
		"bigFont.fnt",
		{ 0.f, 0.f }
	);
	seed2Field->getLabel()->setColor({ 100, 100, 100 });
	seed2Field->setID("seed2-field");
	m_mainLayer->addChildAtPosition(seed2Field, Anchor::BottomLeft, { 10.f, seed2Y });

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
		[seed2Field](CCMenuItemSpriteExtra*) {
			if (auto seed2 = seed2Field->getText(); seed2 == seed2Placeholder)
				QuickNotification::create(
					"No Seed2 to copy!",
					NotificationIcon::Error,
					0.5f
				)->show();
			else
				req::utils::copyClipboard(seed2, "Seed2");
		}
	);
	copyBtn->setID("copy-seed2-button");
	menu->addChildAtPosition(
		copyBtn,
		Anchor::BottomRight,
		{ -20.f, seed2Field->getContentHeight() / 2.f + seed2Y }
	);



	auto generateBtnSpr = ButtonSprite::create(
		"Generate",
		160, 0,
		1.f, true,
		"bigFont.fnt",
		"GJ_button_01.png"
	);
	generateBtnSpr->setScale(0.8f);
	auto generateBtn = CCMenuItemExt::createSpriteExtra(
		generateBtnSpr,
		[clsField, seed2Field](CCMenuItemSpriteExtra*) {
			if (auto cls = clsField->getText(); cls == clsPlaceholder) {
				QuickNotification::create(
					"No string to generate from!",
					NotificationIcon::Error,
					0.5f
				)->show();
			} else {
				seed2Field->getLabel()->setColor({ 255, 255, 255 });
				seed2Field->setText(ZipUtils::base64EncodeEnc(cls, "41274"));
			}
		}
	);
	generateBtn->setID("generate-button");
	menu->addChildAtPosition(generateBtn, Anchor::Center, { 0.f, -14.f });

	return true;
}