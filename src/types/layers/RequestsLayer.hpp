#pragma once

#include <Geode/cocos/layers_scenes_transitions_nodes/CCLayer.h>


class RequestsLayer final : public cocos2d::CCLayer {
public:
	static RequestsLayer* create();
	static cocos2d::CCScene* scene();

private:
	bool init() override;

	void keyBackClicked() override { onBack(); }
	void onBack() { cocos2d::CCDirector::get()->popSceneWithTransition(0.5f, cocos2d::PopTransition::kPopTransitionFade); }

public:
	~RequestsLayer() override;
};