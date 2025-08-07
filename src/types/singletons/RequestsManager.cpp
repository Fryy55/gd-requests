#include "RequestsManager.hpp"

using namespace geode::prelude;


RequestsManager* RequestsManager::get() {
	static auto instance = RequestsManager();

	return &instance;
}

void RequestsManager::init() {
	m_db = new std::unordered_map<std::string, std::string>;
	m_debugLabel = Mod::get()->getSettingValue<bool>("debug-label");

	log::info("New map created.");

	return;
}

void RequestsManager::kill() {
	delete m_db;
	m_db = nullptr;

	log::info("Map deleted.");

	return;
}