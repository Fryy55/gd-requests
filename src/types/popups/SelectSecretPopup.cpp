#include "SelectSecretPopup.hpp"

#include "QuickNotification.hpp"

using namespace geode::prelude;


SelectSecretPopup* SelectSecretPopup::create(TextInput* keyInput, TextInput* valueInput) {
	auto ret = new SelectSecretPopup;

	if (ret->initAnchored(180.f, 260.f, keyInput, valueInput)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

bool SelectSecretPopup::setup(TextInput* keyInput, TextInput* valueInput) {
	m_keyInput = keyInput;
	m_valueInput = valueInput;

	this->setTitle("Select a secret");
	this->setID("SelectSecretPopup");



	auto menu = CCMenu::create();
	menu->setLayout(ColumnLayout::create()->setAxisReverse(true));
	menu->setContentSize(
		{ m_mainLayer->getContentWidth() - 20.f, m_mainLayer->getContentHeight() - 50.f }
	);
	m_buttonWidth = static_cast<int>(menu->getContentWidth()) - 16;
	menu->setAnchorPoint({ 0.5f, 0.f });
	menu->setID("main-menu");
	m_mainLayer->addChildAtPosition(menu, Anchor::Bottom, { 0.f, 12.f });


	menu->addChild(createSecretButton(Secret::Common));
	menu->addChild(createSecretButton(Secret::Account));
	menu->addChild(createSecretButton(Secret::Level));
	menu->addChild(createSecretButton(Secret::Mod));
	menu->addChild(createSecretButton(Secret::Admin));

	static_cast<ColumnLayout*>(menu->getLayout())->setGap(
		(menu->getContentHeight() - menu->getChildrenCount() * s_buttonHeight) / (menu->getChildrenCount() - 1)
	);

	menu->updateLayout();

	return true;
}

CCMenuItemSpriteExtra* SelectSecretPopup::createSecretButton(Secret secret) {
	char const* secretName;
	char const* secretValue;

	switch (secret) {
		case Secret::Common:
			secretName = "Common";
			secretValue = "Wmfd2893gb7";
			break;

		case Secret::Account:
			secretName = "Account";
			secretValue = "Wmfv3899gc9";
			break;

		case Secret::Level:
			secretName = "Level";
			secretValue = "Wmfv2898gc9";
			break;

		case Secret::Mod:
			secretName = "Mod";
			secretValue = "Wmfp3879gc3";
			break;

		case Secret::Admin:
			secretName = "Admin";
			secretValue = "Wmfx2878gb9";
			break;

		default:
			secretName = "UNKNOWN";
			secretValue = "UNKNOWN";
			break;
	}

	auto button = CCMenuItemExt::createSpriteExtra(
		ButtonSprite::create(secretName, m_buttonWidth, 0, 1.f, true),
		[this, secretName, secretValue](CCMenuItemSpriteExtra*) {
			m_keyInput->setString("secret");
			m_valueInput->setString(secretValue);

			QuickNotification::create(
				fmt::format("{} secret pasted.", secretName),
				NotificationIcon::None,
				0.5f
			)->show();

			onClose(nullptr);
		}
	);
	button->setID(fmt::format("{}-secret-button", string::toLower(secretName)));

	return button;
}