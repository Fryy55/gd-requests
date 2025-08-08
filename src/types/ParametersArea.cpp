#include "ParametersArea.hpp"

#include <Geode/ui/Layout.hpp>

#include "QuickNotification.hpp"
#include "constants.hpp"
#include "utils.hpp"

using namespace geode::prelude;


ParametersArea* ParametersArea::create() {
	auto ret = new ParametersArea;

	if (ret->init()) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

bool ParametersArea::init() {
	if (!CCNode::init())
		return false;

	this->setContentSize(s_contentSize);


	auto bg = CCScale9Sprite::create("square02b_001.png");
	bg->setContentSize(s_contentSize);
	bg->setColor({ 0, 0, 0 });
	bg->setOpacity(90);
	bg->setID("background");
	this->addChildAtPosition(bg, Anchor::Center);



	constexpr float padding = 25.f;

	auto menu = CCMenu::create();
	menu->setLayout(RowLayout::create()->setGap(25.f));
	menu->setContentWidth(s_contentSize.width - padding);
	menu->setID("menu");
	this->addChildAtPosition(menu, Anchor::Center);


	auto commonSecretBtn = CCMenuItemExt::createSpriteExtra(
		ButtonSprite::create(
			"?",
			"bigFont.fnt",
			"GJ_button_05.png"
		),
		[this](CCMenuItemSpriteExtra*) {
			QuickNotification::create("Common secret pasted.", NotificationIcon::None, 0.5f)->show();

			m_keyInput->setString("secret");
			m_valueInput->setString("Wmfd2893gb7");
		}
	);
	commonSecretBtn->setID("common-secret-button");
	menu->addChild(commonSecretBtn);


	auto inputMenu = CCMenu::create();
	inputMenu->setLayout(RowLayout::create()->setGrowCrossAxis(true));
	inputMenu->setContentWidth(175.f);
	inputMenu->setID("input-menu");
	menu->addChild(inputMenu);

	m_keyInput = TextInput::create(120.f, "Key");
	m_keyInput->setCommonFilter(CommonFilter::Alphanumeric);
	m_keyInput->setID("key-input");
	inputMenu->addChild(m_keyInput);

	auto pasteKeyBtnTopSpr = CCSprite::createWithSpriteFrameName("clipboard_paste.png"_spr);
	auto pasteKeyBtnSpr = ButtonSprite::create(
		pasteKeyBtnTopSpr,
		40.f,
		true,
		40.f,
		"GJ_button_04.png",
		1.f
	);
	pasteKeyBtnTopSpr->setScale(1.2f);
	pasteKeyBtnSpr->setScale(0.6f);
	auto pasteKeyBtn = CCMenuItemExt::createSpriteExtra(
		pasteKeyBtnSpr,
		[this](CCMenuItemSpriteExtra*) {
			req::utils::pasteClipboard(m_keyInput);
		}
	);
	pasteKeyBtn->setID("paste-key-button");
	inputMenu->addChild(pasteKeyBtn);

	auto clearKeyBtnTopSpr = CCSprite::createWithSpriteFrameName("GJ_deleteIcon_001.png");
	auto clearKeyBtnSpr = ButtonSprite::create(
		clearKeyBtnTopSpr,
		40.f,
		true,
		40.f,
		"GJ_button_04.png",
		1.f
	);
	clearKeyBtnTopSpr->setPositionY(20.f);
	clearKeyBtnSpr->setScale(0.6f);
	auto clearKeyBtn = CCMenuItemExt::createSpriteExtra(
		clearKeyBtnSpr,
		[this](CCMenuItemSpriteExtra*) {
			m_keyInput->setString("");
		}
	);
	clearKeyBtn->setID("clear-key-button");
	inputMenu->addChild(clearKeyBtn);

	m_valueInput = TextInput::create(120.f, "Value");
	m_valueInput->setFilter(constants::valueFilter);
	m_valueInput->setID("value-input");
	inputMenu->addChild(m_valueInput);

	auto pasteValueBtnTopSpr = CCSprite::createWithSpriteFrameName("clipboard_paste.png"_spr);
	auto pasteValueBtnSpr = ButtonSprite::create(
		pasteValueBtnTopSpr,
		40.f,
		true,
		40.f,
		"GJ_button_04.png",
		1.f
	);
	pasteValueBtnTopSpr->setScale(1.2f);
	pasteValueBtnSpr->setScale(0.6f);
	auto pasteValueBtn = CCMenuItemExt::createSpriteExtra(
		pasteValueBtnSpr,
		[this](CCMenuItemSpriteExtra*) {
			req::utils::pasteClipboard(m_valueInput);
		}
	);
	pasteValueBtn->setID("paste-value-button");
	inputMenu->addChild(pasteValueBtn);

	auto clearValueBtnTopSpr = CCSprite::createWithSpriteFrameName("GJ_deleteIcon_001.png");
	auto clearValueBtnSpr = ButtonSprite::create(
		clearValueBtnTopSpr,
		40.f,
		true,
		40.f,
		"GJ_button_04.png",
		1.f
	);
	clearValueBtnTopSpr->setPositionY(20.f);
	clearValueBtnSpr->setScale(0.6f);
	auto clearValueBtn = CCMenuItemExt::createSpriteExtra(
		clearValueBtnSpr,
		[this](CCMenuItemSpriteExtra*) {
			m_valueInput->setString("");
		}
	);
	clearValueBtn->setID("clear-value-button");
	inputMenu->addChild(clearValueBtn);

	inputMenu->updateLayout();


	auto addBtnSpr = ButtonSprite::create(
		"+",
		"bigFont.fnt",
		"GJ_button_05.png"
	);
	auto plus = addBtnSpr->getChildByType<CCLabelBMFont>(0);
	plus->setScale(1.25f);
	plus->setPosition(18.7f, 22.3f);
	auto addBtn = CCMenuItemSpriteExtra::create(
		addBtnSpr,
		this,
		menu_selector(ParametersArea::onAdd)
	);
	addBtn->setID("add-button");
	menu->addChild(addBtn);


	menu->updateLayout();

	return true;
}