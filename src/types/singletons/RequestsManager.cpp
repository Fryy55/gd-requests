#include "RequestsManager.hpp"

using namespace geode::prelude;


RequestsManager* RequestsManager::get() {
	static auto instance = RequestsManager();

	return &instance;
}

RequestsManager::RequestsManager() {
	m_db = new std::unordered_map<std::string, std::string>;
	updateDebugLabelSetting();

	log::info("Manager initialized.");
}