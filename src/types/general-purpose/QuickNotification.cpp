#include "QuickNotification.hpp"

using namespace geode::prelude;


QuickNotification* QuickNotification::create(
	std::string const& text, NotificationIcon icon, float time
) {
	return create(text, createIcon(icon), time);
}

QuickNotification* QuickNotification::create(
	std::string const& text, CCSprite* icon, float time
) {
	auto ret = new QuickNotification;

	if (ret->init(text, icon, time)) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

bool QuickNotification::init(std::string const& text, CCSprite* icon, float time) {
	return Notification::init(text, icon, time);
}

// NOOOO, my DRY collection :WHY:
void QuickNotification::show() {
	if (!m_showing) {
		if (!this->getParent()) {
			auto winSize = CCDirector::get()->getWinSize();
			this->setPosition(winSize.width / 2, winSize.height / 4);
			this->setZOrder(CCScene::get()->getChildrenCount() > 0 ? CCScene::get()->getHighestChildZ() + 2 : 10);
		}
		SceneManager::get()->keepAcrossScenes(this);
		m_showing = true;
	}
	this->runAction(CCSequence::create(
		CCCallFunc::create(this, callfunc_selector(QuickNotification::animateIn)),
		// wait for fade-in to finish
		CCDelayTime::create(0.3f),
		CCCallFunc::create(this, callfunc_selector(QuickNotification::wait)),
		nullptr
	));

	return;
}

void QuickNotification::hide() {
	this->stopAllActions();
	this->runAction(CCSequence::create(
		CCCallFunc::create(this, callfunc_selector(QuickNotification::animateOut)),
		// wait for fade-out to finish
		CCDelayTime::create(1.f),
		CCCallFunc::create(this, callfunc_selector(QuickNotification::showNextNotification)),
		nullptr
	));

	return;
}

void QuickNotification::wait() {
	this->stopAllActions();
	if (m_time) {
		this->runAction(CCSequence::create(
			CCDelayTime::create(m_time),
			CCCallFunc::create(this, callfunc_selector(QuickNotification::hide)),
			nullptr
		));
	}

	return;
}

void QuickNotification::showNextNotification() {
	m_showing = false;

	SceneManager::get()->forget(this);

	this->removeFromParent();

	return;
}