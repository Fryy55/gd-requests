#pragma once

#include <Geode/ui/Popup.hpp>

#include "ParameterCell.hpp"


class EditParameterPopup final : public geode::Popup<ParameterCell*> {
public:
	static EditParameterPopup* create(ParameterCell* cell);

private:
	bool setup(ParameterCell*) override;

	void keyDown(cocos2d::enumKeyCodes) override;

	void onConfirm(cocos2d::CCObject*);

	// Fields
	LimitedTextArea* m_keyField;
	LimitedTextArea* m_valueField;

	geode::TextInput* m_keyInput;
	geode::TextInput* m_valueInput;
};