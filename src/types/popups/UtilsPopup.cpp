#include "UtilsPopup.hpp"

#include "UtilityWCell.hpp"

using namespace geode::prelude;


UtilsPopup* UtilsPopup::create() {
	auto ret = new UtilsPopup;

	if (ret->initAnchored(330.f, 240.f)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

bool UtilsPopup::setup() {
	this->setTitle("Utilities", "goldFont.fnt", 1.f);
	this->setID("UtilsPopup");



	auto menu = CCMenu::create();
	menu->setLayout(
		RowLayout::create()
			->setGrowCrossAxis(true)
	);
	menu->setContentSize(
		{ m_mainLayer->getContentWidth() - 20.f, m_mainLayer->getContentHeight() - 50.f }
	);
	menu->setAnchorPoint({ 0.5f, 0.f });
	menu->setID("main-menu");
	m_mainLayer->addChildAtPosition(menu, Anchor::Bottom, { 0.f, 12.f });


	menu->addChild(UtilityWCell::create(UtilityWCell::GJP2));
	menu->addChild(UtilityWCell::create(UtilityWCell::LevelString));
	menu->addChild(UtilityWCell::create(UtilityWCell::CompressLS));

	menu->updateLayout();

	return true;
}