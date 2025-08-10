#pragma once

#include <Geode/ui/Popup.hpp>


class UtilsPopup final : public geode::Popup<> {
public:
	static UtilsPopup* create();

private:
	bool setup() override;
};