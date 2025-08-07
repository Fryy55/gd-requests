#include "RequestsLayer.hpp"

#include "ResponseArea.hpp"
#include "ParametersArea.hpp"
#include "ParametersList.hpp"
#include "RequestsManager.hpp"

using namespace geode::prelude;


RequestsLayer* RequestsLayer::create() {
	auto ret = new RequestsLayer;

	if (ret->init()) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

CCScene* RequestsLayer::scene() {
	auto scene = CCScene::create();
	auto layer = RequestsLayer::create();
	layer->setID("RequestsLayer");

	scene->addChild(layer);

	return scene;
}

bool RequestsLayer::init() {
	if (!CCLayer::init())
		return false;

	this->setKeypadEnabled(true);
	RequestsManager::get()->init();
	auto winSize = CCDirector::get()->getWinSize();


	auto bg = createLayerBG();
	if (auto transparentWallpaper = Loader::get()->getLoadedMod("naxrin.transparent"))
		if (transparentWallpaper->getSettingValue<bool>("BG"))
			bg->setColor({ 255, 255, 255 });
	bg->setID("background");
	this->addChild(bg);

	addSideArt(this);
	this->getChildByID("side-art-bottom-left")->setZOrder(3);
	this->getChildByID("side-art-bottom-right")->setZOrder(3);


	auto backMenu = CCMenu::create();
	backMenu->setPosition(0.f, 0.f);
	backMenu->setID("back-menu");
	this->addChild(backMenu);

	auto backBtn = CCMenuItemExt::createSpriteExtraWithFrameName(
		"GJ_arrow_01_001.png",
		1.f,
		[this](CCMenuItemSpriteExtra*) {
			this->onBack();
		}
	);
	backBtn->setPosition(25.f, winSize.height - 22.5f);
	backBtn->setID("back-button");
	backMenu->addChild(backBtn);


	auto title = CCLabelBMFont::create("GD Requests", "goldFont.fnt");
	title->setPosition(winSize.width / 2.f, winSize.height - 23.f);
	title->setID("title-label");
	this->addChild(title);


	auto gdDocsMenu = CCMenu::create();
	gdDocsMenu->setPosition(0.f, 0.f);
	gdDocsMenu->setID("gd-docs-menu");
	this->addChild(gdDocsMenu);

	auto gdDocsBtnSpr = ButtonSprite::create("GDDocs", "bigFont.fnt", "GJ_button_02.png");
	gdDocsBtnSpr->setScale(0.5f);
	auto gdDocsBtn = CCMenuItemExt::createSpriteExtra(
		gdDocsBtnSpr,
		[](CCMenuItemSpriteExtra*) {
			web::openLinkInBrowser("https://wyliemaster.github.io/gddocs");
		}
	);
	gdDocsBtn->setPosition(winSize.width - 160.f, winSize.height - 26.f);
	gdDocsBtn->setID("gd-docs-button");
	gdDocsMenu->addChild(gdDocsBtn);



	auto responseArea = ResponseArea::create();
	responseArea->setPosition(260.f, 22.f);
	responseArea->setID("response-area");
	this->addChild(responseArea);



	auto paramArea = ParametersArea::create();
	paramArea->setPosition(23.f, 212.f);
	paramArea->setID("parameters-area");
	this->addChild(paramArea);


	auto paramList = ParametersList::create();
	paramList->setPosition(133.f, 105.f);
	paramList->setID("parameters-list");
	this->addChild(paramList);

	return true;
}

RequestsLayer::~RequestsLayer() {
	RequestsManager::get()->kill();
}