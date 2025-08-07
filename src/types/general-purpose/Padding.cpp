#include "Padding.hpp"

using namespace geode::prelude;


Padding* Padding::create(float padding) {
	auto ret = new Padding;

	if (ret->init(padding)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

bool Padding::init(float padding) {
	if (!CCNode::init())
		return false;

	this->setContentSize({ padding, padding });

	return true;
}