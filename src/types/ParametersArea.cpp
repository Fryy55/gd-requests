#include "ParametersArea.hpp"

#include "QuickNotification.hpp"
#include "Padding.hpp"

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
	menu->setLayout(RowLayout::create());
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


	menu->addChild(Padding::create(7.5f));


	m_keyInput = TextInput::create(60.f, "Key");
	m_keyInput->setCommonFilter(CommonFilter::Any);
	m_keyInput->setID("key-input");
	menu->addChild(m_keyInput);


	auto clearBtnTopSpr = CCSprite::createWithSpriteFrameName("GJ_deleteIcon_001.png");
	auto clearBtnSpr = ButtonSprite::create(
		clearBtnTopSpr,
		40.f,
		true,
		40.f,
		"GJ_button_04.png",
		1.f
	);
	clearBtnTopSpr->setPositionY(20.f);
	clearBtnSpr->setScale(0.6f);
	auto clearBtn = CCMenuItemExt::createSpriteExtra(
		clearBtnSpr,
		[this](CCMenuItemSpriteExtra*) {
			m_keyInput->setString("");
			m_valueInput->setString("");
		}
	);
	clearBtn->setID("clear-button");
	menu->addChild(clearBtn);


	m_valueInput = TextInput::create(60.f, "Value");
	m_valueInput->setCommonFilter(CommonFilter::Any);
	m_valueInput->setID("value-input");
	menu->addChild(m_valueInput);


	menu->addChild(Padding::create(7.5f));


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

void ParametersArea::onAdd(CCObject*) {


	return;
}