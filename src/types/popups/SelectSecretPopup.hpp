#pragma once

#include <Geode/ui/Popup.hpp>


class SelectSecretPopup final : public geode::Popup<geode::TextInput*, geode::TextInput*> {
public:
	static SelectSecretPopup* create(geode::TextInput* keyInput, geode::TextInput* valueInput);

private:
	bool setup(geode::TextInput*, geode::TextInput*) override;

	enum class Secret : std::uint8_t {
		Common,
		Account,
		Level,
		Mod,
		Admin
	};

	CCMenuItemSpriteExtra* createSecretButton(Secret);

	// Fields
	geode::TextInput* m_keyInput;
	geode::TextInput* m_valueInput;
	int m_buttonWidth;

	static constexpr float s_buttonHeight = 30.f; // change this if anything
};