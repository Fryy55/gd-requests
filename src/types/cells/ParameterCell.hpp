#pragma once

#include <Geode/cocos/layers_scenes_transitions_nodes/CCLayer.h>

#include "LimitedTextArea.hpp"


class ParameterCell final : public cocos2d::CCLayerColor {
public:
	static ParameterCell* create(std::string const& key, std::string const& value, float width);

private:
	bool init(std::string const&, std::string const&, float);


public:
	void setBGColor(bool dark) { this->setOpacity(dark ? 60 : 20); }
	[[nodiscard]] std::pair<LimitedTextArea*, LimitedTextArea*> getFields() const { return { m_keyField, m_valueField }; }

	void onDelete(cocos2d::CCObject*);

private:
	void onEdit(cocos2d::CCObject*);

	// Fields
	LimitedTextArea* m_keyField;
	LimitedTextArea* m_valueField;

	static constexpr float s_height = 35.f;
};