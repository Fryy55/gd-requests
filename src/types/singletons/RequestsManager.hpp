#pragma once

#include <unordered_map>


class RequestsManager final {
public:
	static RequestsManager* get();

	[[nodiscard]] std::unordered_map<std::string, std::string>* getDB() const { return m_db; }
	[[nodiscard]] bool getDebugLabelSetting() const { return m_debugLabel; }

	RequestsManager(RequestsManager const&) = delete;
	RequestsManager(RequestsManager&&) = delete;
	RequestsManager& operator=(RequestsManager const&) = delete;
	RequestsManager& operator=(RequestsManager&&) = delete;

private:
	RequestsManager();

	// Fields
	std::unordered_map<std::string, std::string>* m_db;
	bool m_debugLabel;
};