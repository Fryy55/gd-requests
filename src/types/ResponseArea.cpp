#include "ResponseArea.hpp"

#include "constants.hpp"
#include "Padding.hpp"
#include "utils.hpp"
#include "Separator.hpp"
#include "QuickNotification.hpp"
#include "RequestsManager.hpp"

using namespace geode::prelude;


ResponseArea* ResponseArea::create() {
	auto ret = new ResponseArea;

	if (ret->init()) {
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}

bool ResponseArea::init() {
	if (!CCNode::init())
		return false;

	this->setContentSize(s_contentSize);


	auto bg = CCScale9Sprite::create("square02b_001.png");
	bg->setContentSize(s_contentSize);
	bg->setColor({ 0, 0, 0 });
	bg->setOpacity(90);
	bg->setID("background");
	this->addChildAtPosition(bg, Anchor::Center);



	constexpr float padding = 25.f;

	m_endpointInput = TextInput::create(s_contentSize.width - padding, "Endpoint");
	m_endpointInput->setFilter(constants::urlFilter);
	m_endpointInput->setID("endpoint-input");
	this->addChildAtPosition(m_endpointInput, Anchor::Top, { 0.f, -25.f });


	auto endpointMenu = CCMenu::create();
	endpointMenu->setLayout(RowLayout::create());
	endpointMenu->setContentWidth(s_contentSize.width - padding);
	endpointMenu->setID("endpoint-menu");
	this->addChildAtPosition(endpointMenu, Anchor::Top, { 0.f, -57.5f });


	auto sendBtnSpr = ButtonSprite::create("Send", "bigFont.fnt", "GJ_button_05.png");
	sendBtnSpr->setScale(0.65f);
	auto sendBtn = CCMenuItemSpriteExtra::create(
		sendBtnSpr,
		this,
		menu_selector(ResponseArea::onSend)
	);
	sendBtn->setID("send-button");
	endpointMenu->addChild(sendBtn);

	m_loadingCircle = LoadingSpinner::create(20.f);
	m_loadingCircle->setVisible(false);
	m_loadingCircle->setID("loading-circle");
	endpointMenu->addChild(m_loadingCircle);

	endpointMenu->addChild(Padding::create(130.f));

	auto pasteBtnTopSpr = CCSprite::createWithSpriteFrameName("clipboard_paste.png"_spr);
	auto pasteBtnSpr = ButtonSprite::create(
		pasteBtnTopSpr,
		40.f,
		true,
		40.f,
		"GJ_button_04.png",
		1.f
	);
	pasteBtnTopSpr->setScale(1.2f);
	pasteBtnSpr->setScale(0.6f);
	auto pasteBtn = CCMenuItemExt::createSpriteExtra(
		pasteBtnSpr,
		[this](CCMenuItemSpriteExtra*) {
			req::utils::pasteClipboard(m_endpointInput);
		}
	);
	pasteBtn->setID("paste-button");
	endpointMenu->addChild(pasteBtn);

	auto clearBtnTopSpr = CCSprite::createWithSpriteFrameName("GJ_deleteIcon_001.png");
	auto clearBtnSpr = ButtonSprite::create(
		clearBtnTopSpr,
		40.f,
		true,
		40.f,
		"GJ_button_04.png",
		1.f
	);
	clearBtnTopSpr->setPositionY(20.f);
	clearBtnSpr->setScale(0.6f);
	auto clearBtn = CCMenuItemExt::createSpriteExtra(
		clearBtnSpr,
		[this](CCMenuItemSpriteExtra*) {
			m_endpointInput->setString("");
		}
	);
	clearBtn->setID("clear-button");
	endpointMenu->addChild(clearBtn);

	endpointMenu->updateLayout();



	auto separator = Separator::create({ 255, 255, 255 }, 80.f, 300.f);
	separator->setOpacity(100);
	separator->setID("separator");
	this->addChildAtPosition(separator, Anchor::Center, { 0.f, 44.f });



	auto responseLabel = CCLabelBMFont::create("Response", "bigFont.fnt");
	responseLabel->setScale(0.5f);
	responseLabel->setID("response-label");
	this->addChildAtPosition(responseLabel, Anchor::Left, { 60.f, 32.5f });


	m_responseField = ScrollTextArea::create(
		"<c-707070>Response will appear here...</c>",
		{ s_contentSize.width - padding, 130.f }
	);
	m_responseField->setID("response-field");
	this->addChildAtPosition(m_responseField, Anchor::Bottom, { 0.f, 75.f });

	return true;
}

void ResponseArea::onSend(CCObject*) {
	auto endpoint = m_endpointInput->getString();

	if (!req::utils::validateString(endpoint, req::utils::StringType::Endpoint))
		return;

	if (m_reqMutex) {
		QuickNotification::create("A request is already processing!", NotificationIcon::Error)->show();
		return;
	}
	m_reqMutex = true;
	m_loadingCircle->setVisible(true);

	std::string bodyString = "";
	bool firstParam = true;

	for (auto const& [key, value] : *RequestsManager::get()->getDB()) {
		bodyString.append(
			fmt::format(
				"{}{}={}",
				firstParam ? "" : "&",
				key,
				value
			)
		);

		firstParam = false;
	}

	m_requestListener.setFilter(
		web::WebRequest()
			.bodyString(bodyString)
			.post(std::string("https://www.boomlings.com/database/").append(m_endpointInput->getString()))
	);

	return;
}

void ResponseArea::onRequest(web::WebTask::Event* event) {
	if (auto res = event->getValue()) {
		m_responseField->setText(res->string().unwrapOr(res->errorMessage()));

		m_loadingCircle->setVisible(false);
		m_reqMutex = false;
	} else if (event->isCancelled()) {
		log::info("Request cancelled.");
	}

	return;
}