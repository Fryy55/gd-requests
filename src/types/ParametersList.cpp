#include "ParametersList.hpp"

#include "ScrollBorders.hpp"
#include "ParameterCell.hpp"
#include "RequestsManager.hpp"
#include "utils.hpp"

using namespace geode::prelude;


ParametersList* ParametersList::create() {
	auto ret = new ParametersList;

	if (ret->init()) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

bool ParametersList::init() {
	if (!CCScale9Sprite::initWithFile("GJ_square01.png"))
		return false;

	this->setContentSize(s_contentSize);



	m_scrollLayer = ScrollLayer::create({ s_contentSize.width, s_contentSize.height - 10.f });
	m_scrollLayer->m_contentLayer->setLayout(
		ColumnLayout::create()
			->setGap(0.f)
			->setAxisReverse(true)
			->setAxisAlignment(AxisAlignment::End)
			->setAutoGrowAxis(m_scrollLayer->getContentHeight())
	);
	m_scrollLayer->setID("scroll-layer");
	this->addChildAtPosition(m_scrollLayer, Anchor::Center);
	m_scrollLayer->setPosition(0.f, 5.f);



	auto border = ScrollBorders::create({ 330.f, 252.f }, "Parameters");
	border->setScale(0.7f);
	border->setID("border");
	this->addChildAtPosition(border, Anchor::Center);



	m_emptyListLabel = CCLabelBMFont::create("Empty... so far", "bigFont.fnt");
	m_emptyListLabel->setID("empty-list-label");
	m_emptyListLabel->setScale(0.7f);
	m_emptyListLabel->setOpacity(0);
	this->addChildAtPosition(m_emptyListLabel, Anchor::Center, { 0.f, 5.f });



	m_parameterCountLabel = LimitedTextArea::create(
		{ 80.f, 30.f },
		"",
		16,
		"bigFont.fnt",
		{ 0.f, 2.f },
		{ 0, 0, 0, 60 }
	);
	m_parameterCountLabel->setScale(0.45f);
	m_parameterCountLabel->setID("parameter-count-label");
	this->addChildAtPosition(m_parameterCountLabel, Anchor::BottomRight, { -75.f, -10.f });



	auto resetMenu = CCMenu::create();
	resetMenu->setID("reset-menu");
	this->addChildAtPosition(resetMenu, Anchor::BottomRight);


	auto resetBtn = CCMenuItemSpriteExtra::create(
		CCSprite::createWithSpriteFrameName("GJ_trashBtn_001.png"),
		this,
		menu_selector(ParametersList::onReset)
	);
	resetBtn->setID("reset-button");
	resetMenu->addChild(resetBtn);



	// add children if db has them on init
	for (auto const& [key, value] : *RequestsManager::get()->getDB())
		m_scrollLayer->m_contentLayer->addChild(ParameterCell::create(key, value, s_contentSize.width));


	this->updateState();

	return true;
}

void ParametersList::addCell(std::string const& key, std::string const& value) {
	if (
		!req::utils::validateString(key, req::utils::StringType::Key)
		||
		!req::utils::validateString(value, req::utils::StringType::Value)
	) return;

	RequestsManager::get()->getDB()->insert({ key, value });
	m_scrollLayer->m_contentLayer->addChild(ParameterCell::create(key, value, s_contentSize.width));

	this->updateState();

	return;
}

void ParametersList::updateState() {
	m_emptyListLabel->setOpacity(
		m_scrollLayer->m_contentLayer->getChildrenCount() ?
			0
			:
			255
	);

	m_parameterCountLabel->setText(
		RequestsManager::get()->getDebugLabelSetting() ?
			fmt::format(
				"{}/{}",
				m_scrollLayer->m_contentLayer->getChildrenCount(),
				RequestsManager::get()->getDB()->size()
			)
			:
			numToString<std::uint32_t>(m_scrollLayer->m_contentLayer->getChildrenCount())
	);

	bool dark = true;
	for (auto cell : CCArrayExt<ParameterCell>(m_scrollLayer->m_contentLayer->getChildren())) {
		cell->setBGColor(dark);

		dark = !dark;
	}

	m_scrollLayer->m_contentLayer->updateLayout();

	m_scrollLayer->scrollToTop();

	return;
}

void ParametersList::onReset(CCObject*) {
	createQuickPopup(
		"Reset parameters",
		"Are you sure you want to clear <cr>all</c> parameters?",
		"Cancel", "Yes",
		[this](auto, bool yes) {
			if (yes) {
				m_scrollLayer->m_contentLayer->removeAllChildren();
				RequestsManager::get()->getDB()->clear();

				updateState();
			}
		}
	);

	return;
}

ListenerResult ParametersList::onAddCellEvent(AddCellEvent* event) {
	this->addCell(event->key, event->value);

	return ListenerResult::Stop;
}

ListenerResult ParametersList::onUpdateStateEvent(UpdateListStateEvent*) {
	this->updateState();

	return ListenerResult::Stop;
}