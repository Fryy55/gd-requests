#pragma once

#include <Geode/ui/Popup.hpp>


class Seed2Popup final : public geode::Popup<> {
public:
	static Seed2Popup* create();

private:
	bool setup() override;
};