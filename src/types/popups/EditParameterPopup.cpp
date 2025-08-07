#include "EditParameterPopup.hpp"

#include "QuickNotification.hpp"
#include "RequestsManager.hpp"

using namespace geode::prelude;


EditParameterPopup* EditParameterPopup::create(ParameterCell* cell) {
	auto ret = new EditParameterPopup;

	if (ret->initAnchored(235.f, 185.f, cell)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

bool EditParameterPopup::setup(ParameterCell* cell) {
	auto fields = cell->getFields();
	m_keyField = fields.first;
	m_valueField = fields.second;

	this->setTitle("Edit Parameter", "goldFont.fnt", 0.9f);
	this->setID("EditParameterPopup");

	m_buttonMenu->removeFromParent();



	auto menu = CCMenu::create();
	menu->setContentSize(m_mainLayer->getContentSize());
	menu->setID("main-menu");
	m_mainLayer->addChildAtPosition(menu, Anchor::Center);


	auto confirmBtn = CCMenuItemSpriteExtra::create(
		ButtonSprite::create(
			"Confirm", 60,
			true, "bigFont.fnt",
			"GJ_button_01.png",
			25, 1.f
		),
		this,
		menu_selector(EditParameterPopup::onConfirm)
	);
	confirmBtn->setID("confirm-button");
	menu->addChildAtPosition(confirmBtn, Anchor::Bottom, { 50.f, 22.f });

	auto cancelBtn = CCMenuItemSpriteExtra::create(
		ButtonSprite::create(
			"Cancel", 60,
			true, "bigFont.fnt",
			"GJ_button_06.png",
			25, 1.f
		),
		this,
		menu_selector(EditParameterPopup::onClose)
	);
	cancelBtn->setID("cancel-button");
	menu->addChildAtPosition(cancelBtn, Anchor::Bottom, { -50.f, 22.f });


	constexpr float keyLabelY = 45.f;

	auto keyLabel = CCLabelBMFont::create("Key", "goldFont.fnt");
	keyLabel->setScale(0.8f);
	keyLabel->setID("key-label");
	m_mainLayer->addChildAtPosition(keyLabel, Anchor::Left, { 40.f, keyLabelY });

	m_keyInput = TextInput::create(180.f, "Key");
	m_keyInput->setCommonFilter(CommonFilter::Any);
	m_keyInput->setString(m_keyField->getText());
	m_keyInput->setID("key-input");
	menu->addChildAtPosition(m_keyInput, Anchor::Left, { 100.f, keyLabelY - 28.f });

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
	clearKeyBtnSpr->setScale(0.8f);
	auto clearKeyBtn = CCMenuItemExt::createSpriteExtra(
		clearKeyBtnSpr,
		[this](CCMenuItemSpriteExtra*) {
			m_keyInput->setString("");
		}
	);
	clearKeyBtn->setID("clear-key-button");
	menu->addChildAtPosition(clearKeyBtn, Anchor::Right, { -25.f, keyLabelY - 28.f });


	constexpr float valueLabelY = 83.f;

	auto valueLabel = CCLabelBMFont::create("Value", "goldFont.fnt");
	valueLabel->setScale(0.8f);
	valueLabel->setID("value-label");
	m_mainLayer->addChildAtPosition(valueLabel, Anchor::BottomLeft, { 50.f, valueLabelY });

	m_valueInput = TextInput::create(180.f, "Value");
	m_valueInput->setCommonFilter(CommonFilter::Any);
	m_valueInput->setString(m_valueField->getText());
	m_valueInput->setID("value-input");
	menu->addChildAtPosition(m_valueInput, Anchor::BottomLeft, { 100.f, valueLabelY - 28.f });

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
	clearValueBtnSpr->setScale(0.8f);
	auto clearValueBtn = CCMenuItemExt::createSpriteExtra(
		clearValueBtnSpr,
		[this](CCMenuItemSpriteExtra*) {
			m_valueInput->setString("");
		}
	);
	clearValueBtn->setID("clear-value-button");
	menu->addChildAtPosition(clearValueBtn, Anchor::BottomRight, { -25.f, valueLabelY - 28.f });

	return true;
}

void EditParameterPopup::keyDown(enumKeyCodes key) {
	switch (key) {
		case KEY_Escape:
			this->onConfirm(nullptr);
			break;

		default:
			break;
	}

	return;
}

void EditParameterPopup::onConfirm(CCObject*) {
	auto key = m_keyInput->getString();
	auto value = m_valueInput->getString();
	auto oldKey = m_keyField->getText();

	if (key == "") {
		QuickNotification::create("Key can't be empty!", NotificationIcon::Error, 0.5f)->show();
		return;
	} else if (value == "") {
		QuickNotification::create("Value can't be empty!", NotificationIcon::Error, 0.5f)->show();
		return;
	}

	auto db = RequestsManager::get()->getDB();
	if (db->contains(key) && key != oldKey) {
		QuickNotification::create("Key already exists!", NotificationIcon::Error, 0.5f)->show();
		return;
	}


	m_keyField->setText(key);
	m_valueField->setText(value);
	db->erase(oldKey);
	db->insert({ std::move(key), std::move(value) });

	onClose(nullptr);

	return;
}