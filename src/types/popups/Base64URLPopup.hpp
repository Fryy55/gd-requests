#pragma once

#include <Geode/ui/Popup.hpp>


class Base64URLPopup final : public geode::Popup<> {
public:
	static Base64URLPopup* create();

private:
	bool setup() override;
};