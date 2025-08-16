#include "CompressLSPopup.hpp"

#include "LimitedTextArea.hpp"
#include "utils.hpp"
#include "QuickNotification.hpp"

using namespace geode::prelude;


CompressLSPopup* CompressLSPopup::create() {
	auto ret = new CompressLSPopup;

	if (ret->initAnchored(230.f, 160.f)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

bool CompressLSPopup::setup() {
	this->setTitle("Compress Level String");
	this->setID("CompressLSPopup");



	auto menu = CCMenu::create();
	menu->setContentSize(m_mainLayer->getContentSize());
	menu->setPosition(0.f, 0.f);
	menu->setAnchorPoint({ 0.f, 0.f });
	menu->setID("main-menu");
	m_mainLayer->addChild(menu);


	constexpr char const* lsPlaceholder = "       Level String...     ";
	constexpr char const* clsPlaceholder = "Compressed Level String...";



	constexpr float clY = 10.f;

	auto lsField = LimitedTextArea::create(
		{ 180.f, 30.f },
		lsPlaceholder,
		28,
		"bigFont.fnt",
		{ 0.f, 0.f }
	);
	lsField->getLabel()->setColor({ 100, 100, 100 });
	lsField->setID("level-string-field");
	m_mainLayer->addChildAtPosition(lsField, Anchor::Left, { 10.f, clY });

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
		[lsField](CCMenuItemSpriteExtra*) {
			req::utils::pasteClipboard(lsField);
			lsField->getLabel()->setColor({ 255, 255, 255 });
		}
	);
	pasteBtn->setID("paste-ls-button");
	menu->addChildAtPosition(
		pasteBtn,
		Anchor::Right,
		{ -20.f, lsField->getContentHeight() / 2.f + clY }
	);



	constexpr float clsY = -30.f;

	auto clsField = LimitedTextArea::create(
		{ 180.f, 30.f },
		clsPlaceholder,
		28,
		"bigFont.fnt",
		{ 0.f, 0.f }
	);
	clsField->getLabel()->setColor({ 100, 100, 100 });
	clsField->setID("level-string-field");
	m_mainLayer->addChildAtPosition(clsField, Anchor::Left, { 10.f, clsY });

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
		[clsField](CCMenuItemSpriteExtra*) {
			if (auto cls = clsField->getText(); cls == clsPlaceholder)
				QuickNotification::create(
					"No compressed string to copy!",
					NotificationIcon::Error,
					0.5f
				)->show();
			else
				req::utils::copyClipboard(clsField->getText(), "Compressed LS");
		}
	);
	copyBtn->setID("copy-cls-button");
	menu->addChildAtPosition(
		copyBtn,
		Anchor::Right,
		{ -20.f, clsField->getContentHeight() / 2.f + clsY }
	);



	auto compressBtnSpr = ButtonSprite::create(
		"Compress",
		90, 0,
		1.f, true,
		"bigFont.fnt",
		"GJ_button_01.png"
	);
	compressBtnSpr->setScale(0.8f);
	auto compressBtn = CCMenuItemExt::createSpriteExtra(
		compressBtnSpr,
		[lsField, clsField](CCMenuItemSpriteExtra*) {
			if (auto ls = lsField->getText(); ls == lsPlaceholder) {
				QuickNotification::create(
					"No string to compress!",
					NotificationIcon::Error,
					0.5f
				)->show();
			} else {
				clsField->getLabel()->setColor({ 255, 255, 255 });
				clsField->setText(ZipUtils::compressString(lsField->getText(), false, 0));
			}
		}
	);
	compressBtn->setID("compress-button");
	menu->addChildAtPosition(compressBtn, Anchor::Bottom, { 0.f, 27.5f });

	return true;
}