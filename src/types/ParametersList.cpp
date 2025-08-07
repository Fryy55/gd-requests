#include "ParametersList.hpp"

#include "ScrollBorders.hpp"

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



	auto scrollLayer = ScrollLayer::create(s_contentSize);
	scrollLayer->setID("scroll-layer");
	this->addChildAtPosition(scrollLayer, Anchor::Center);
	scrollLayer->setPosition(0.f, 0.f);



	auto border = ScrollBorders::create({ 330.f, 252.f }, "Parameters");
	border->setScale(0.7f);
	border->setID("border");
	this->addChildAtPosition(border, Anchor::Center);

	return true;
}