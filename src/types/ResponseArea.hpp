#pragma once

#include <Geode/cocos/base_nodes/CCNode.h>

#include "ScrollTextArea.hpp"


class ResponseArea final : public cocos2d::CCNode {
public:
	static ResponseArea* create();

	~ResponseArea() override;

private:
	bool init() override;

	void onSend(cocos2d::CCObject*);
	void onRequest(geode::utils::web::WebTask::Event*);

	// Fields
	geode::TextInput* m_endpointInput;
	geode::LoadingSpinner* m_loadingCircle;
	bool m_reqMutex = false;
	ScrollTextArea* m_responseField;
	geode::EventListener<geode::utils::web::WebTask> m_requestListener { this, &ResponseArea::onRequest };

	static constexpr cocos2d::CCSize s_contentSize { 290.f, 240.f };
};