#include "utils.hpp"

#include <Geode/ui/TextInput.hpp>

#include "constants.hpp"
#include "QuickNotification.hpp"
#include "RequestsManager.hpp"

using namespace geode::prelude;


bool req::utils::validateString(
	std::string const& string,
	req::utils::StringType type,
	std::optional<std::string_view> oldKey
) {
	char const* typeString;
	std::string filter;

	switch (type) {
		case req::utils::StringType::Key:
			typeString = "Key";
			filter = getCommonFilterAllowedChars(CommonFilter::Alphanumeric);
			break;

		case req::utils::StringType::Value:
			typeString = "Value";
			filter = constants::valueFilter;
			break;

		case req::utils::StringType::Endpoint:
			typeString = "Endpoint";
			filter = constants::urlFilter;
			break;

		default:
			throw "Unknown string type";
	}

	if (string.empty()) {
		QuickNotification::create(
			fmt::format("{} can't be empty!", typeString),
			NotificationIcon::Error,
			0.5f
		)->show();
		return false;
	}

	do if (type == req::utils::StringType::Key && RequestsManager::get()->getDB()->contains(string)) {
		if (oldKey && string == oldKey.value())
			break;

		QuickNotification::create("Key already exists!", NotificationIcon::Error, 0.5f)->show();
		return false;
	} while (false);

	if (RequestsManager::get()->getSanitizeTextSetting()) {
		for (auto c : string) {
			if (filter.find(c) == std::string::npos) {
				QuickNotification::create(
					fmt::format("Forbidden character: {}", c),
					NotificationIcon::Error,
					0.5f
				)->show();
				return false;
			}
		}
	}

	return true;
}