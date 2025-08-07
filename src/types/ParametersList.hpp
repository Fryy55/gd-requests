#pragma once

#include <Geode/cocos/extensions/GUI/CCControlExtension/CCScale9Sprite.h>

#include "LimitedTextArea.hpp"
#include "AddCellEvent.hpp"
#include "UpdateListStateEvent.hpp"


class ParametersList final : public cocos2d::extension::CCScale9Sprite {
public:
	static ParametersList* create();

private:
	bool init() override;

public:
	void addCell(std::string const& key, std::string const& value);

private:
	void updateState();

	void onReset(cocos2d::CCObject*);
	geode::ListenerResult onAddCellEvent(AddCellEvent*);
	geode::ListenerResult onUpdateStateEvent(UpdateListStateEvent*);

	// Fields
	geode::ScrollLayer* m_scrollLayer;
	cocos2d::CCLabelBMFont* m_emptyListLabel;
	LimitedTextArea* m_parameterCountLabel;
	geode::EventListener<geode::EventFilter<AddCellEvent>> m_addCellListener {
		this,
		&ParametersList::onAddCellEvent
	};
	geode::EventListener<geode::EventFilter<UpdateListStateEvent>> m_updateStateListener {
		this,
		&ParametersList::onUpdateStateEvent
	};

	static constexpr cocos2d::CCSize s_contentSize { 215.f, 170.f };
};