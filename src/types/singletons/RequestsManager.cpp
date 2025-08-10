#include "RequestsManager.hpp"

using namespace geode::prelude;


RequestsManager* RequestsManager::get() {
	static auto instance = RequestsManager();

	return &instance;
}

RequestsManager::RequestsManager() {
	m_db = new std::unordered_map<std::string, std::string>;
	updateSettings();

	m_copyLevelString = Mod::get()->getSavedValue<bool>("copy-level-string");

	log::info("Manager initialized.");
}

bool RequestsManager::toggleCopyLevelString() {
	m_copyLevelString = !m_copyLevelString;

	Mod::get()->setSavedValue("copy-level-string", m_copyLevelString);

	return m_copyLevelString;
}

void RequestsManager::updateSettings() {
	m_debugLabel = Mod::get()->getSettingValue<bool>("debug-label");

	return;
}