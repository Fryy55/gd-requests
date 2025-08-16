#pragma once

#include <Geode/ui/Popup.hpp>


class CompressLSPopup final : public geode::Popup<> {
public:
	static CompressLSPopup* create();

private:
	bool setup() override;
};