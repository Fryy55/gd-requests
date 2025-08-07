#include "ParameterCell.hpp"

#include "RequestsManager.hpp"
#include "UpdateListStateEvent.hpp"
#include "EditParameterPopup.hpp"

using namespace geode::prelude;


ParameterCell* ParameterCell::create(std::string const& key, std::string const& value, float width) {
	auto ret = new ParameterCell;

	if (ret->init(key, value, width)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

bool ParameterCell::init(std::string const& key, std::string const& value, float width) {
	if (!CCLayerColor::initWithColor({ 0, 0, 0, 0 }, width, s_height))
		return false;

	this->setID(key);



	auto keyLabel = CCLabelBMFont::create("Key", "goldFont.fnt");
	keyLabel->setScale(0.5f);
	keyLabel->setID("key-label");
	this->addChildAtPosition(keyLabel, Anchor::TopLeft, { 25.f, -7.f });


	m_keyField = LimitedTextArea::create({ 82.5f, 30.f }, key, 12, "bigFont.fnt", { 0.f, 2.f });
	m_keyField->setScale(0.67f);
	m_keyField->setID("key-field");
	this->addChildAtPosition(m_keyField, Anchor::BottomLeft, { 13.f, 1.5f });



	auto valueLabel = CCLabelBMFont::create("Value", "goldFont.fnt");
	valueLabel->setScale(0.5f);
	valueLabel->setID("value-label");
	this->addChildAtPosition(valueLabel, Anchor::TopLeft, { 95.f, -7.f });


	m_valueField = LimitedTextArea::create({ 82.5f, 30.f }, value, 12, "bigFont.fnt", { 0.f, 2.f });
	m_valueField->setScale(0.67f);
	m_valueField->setID("value-field");
	this->addChildAtPosition(m_valueField, Anchor::BottomLeft, { 78.f, 1.5f });



	auto menu = CCMenu::create();
	menu->setContentSize({ 75.f, s_height });
	menu->setScale(0.8f);
	menu->setID("menu");
	this->addChildAtPosition(
		menu,
		Anchor::Right,
		{ -(menu->getContentWidth() / 2.f) - 7.f, 0.f }
	);

	menu->setLayout(RowLayout::create());


	auto editBtn = CCMenuItemSpriteExtra::create(
		CCSprite::createWithSpriteFrameName("GJ_viewLevelsBtn_001.png"),
		this,
		menu_selector(ParameterCell::onEdit)
	);
	editBtn->setID("edit-button");
	menu->addChild(editBtn);


	auto deleteBtn = CCMenuItemSpriteExtra::create(
		CircleButtonSprite::createWithSpriteFrameName("edit_delBtn_001.png", 0.8f),
		this,
		menu_selector(ParameterCell::onDelete)
	);
	deleteBtn->setID("delete-button");
	menu->addChild(deleteBtn);


	menu->updateLayout();

	return true;
}

void ParameterCell::onDelete(CCObject*) {
	RequestsManager::get()->getDB()->erase(m_keyField->getText());
	this->removeFromParent();

	UpdateListStateEvent().post();

	return;
}

void ParameterCell::onEdit(CCObject*) {
	EditParameterPopup::create(this)->show();

	return;
}	