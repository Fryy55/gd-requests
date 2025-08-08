#include "RequestsManager.hpp"

using namespace geode::prelude;


RequestsManager* RequestsManager::get() {
	static auto instance = RequestsManager();

	return &instance;
}

RequestsManager::RequestsManager() {
	m_db = new std::unordered_map<std::string, std::string>;
	updateSettings();

	log::info("Manager initialized.");
}

void RequestsManager::updateSettings() {
	m_debugLabel = Mod::get()->getSettingValue<bool>("debug-label");
	m_sanitizeText = Mod::get()->getSettingValue<bool>("text-sanitizing");

	return;
}