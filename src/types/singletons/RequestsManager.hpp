#pragma once

#include <unordered_map>


class RequestsManager final {
public:
	static RequestsManager* get();

	[[nodiscard]] std::unordered_map<std::string, std::string>* getDB() const { return m_db; }
	[[nodiscard]] bool getDebugLabelSetting() const { return m_debugLabel; }

	void init();
	void kill();

	RequestsManager(RequestsManager const&) = delete;
	RequestsManager(RequestsManager&&) = delete;
	RequestsManager& operator=(RequestsManager const&) = delete;
	RequestsManager& operator=(RequestsManager&&) = delete;

private:
	RequestsManager() = default;

	// Fields
	std::unordered_map<std::string, std::string>* m_db = nullptr;
	bool m_debugLabel;
};