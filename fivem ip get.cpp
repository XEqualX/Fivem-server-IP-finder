#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "wldap32.lib")
#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "normaliz.lib")
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "secur32.lib")

using json = nlohmann::json;

int menu()
{
		std::cout << "1. View server IP\n";
		std::cout << "2. View server resources\n";
		std::cout << "3. View server name\n";
		std::cout << "4. View extra info\n"; // caution while using, it prints unicode characters depending on the servers bio and stuff.
		int choice{};
		std::cin >> choice;
		return choice;
}

void req(std::string code, int choice)
{
	std::string fivem{ "https://frontend.cfx-services.net/api/servers/single/" + code };
	cpr::Response query = cpr::Get(cpr::Url{ fivem },
	cpr::Header{{"User-Agent", "Mozilla/5.0"}});
		auto parse = json::parse(query.text);
		std::string ip = parse["Data"]["connectEndPoints"][0].get<std::string>();
		std::string resources = parse["Data"]["resources"].dump(4);
		std::string name = parse["Data"]["hostname"].get<std::string>();
		std::string extraInfo = parse["Data"]["vars"].dump(4);
	if (choice == 1)
	{
		std::cout << ip << '\n';
	}
	else if (choice == 2)
	{
		std::cout << resources << '\n';
	}
	else if (choice == 3)
	{
		std::cout << name << '\n';
	}
	else if (choice == 4)
	{
		std::cout << extraInfo << '\n';
	}
	else 
	{
		std::cout << "Error, that isnt an option";
	}
	
}

int main()
{
	std::cout << "Enter server code (E.g. ab3kpg): ";
	std::string connectcode{};
	std::cin >> connectcode;
	bool running{ true };
	while (running)
	{
		int choice{ menu() };
		req(connectcode, choice);
	}
}
