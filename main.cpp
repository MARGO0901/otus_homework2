#include <algorithm>
#include <sstream>

#include "function.h"

int main(int, char **) {

  	std::vector<std::vector<int>> ip_address;
    ReadData(std::cin, ip_address);

    //сортировка по возрастанию
    std::sort(ip_address.rbegin(), ip_address.rend(),
		[](std::vector<int> &v1, std::vector<int> &v2) {
			for (auto i = 0; i < 4; i++) {
			if (v1[i] != v2[i])
				return v1[i] < v2[i];
			}
			return false;
		});

	//вывод сортировки по возрастанию
  	for (const auto &ip : ip_address) {
		std::stringstream str;
		for (auto i = 0; i < 4; ++i) {
			str << ip.at(i);
			if (i < 3) str << ".";
		}
		std::cout << str.str() << std::endl;
	}

	//вывод адресов, начинающихся с 1
	for (const auto &ip: ip_address) {
		std::stringstream str;
		if (ip[0] == 1) {
			for (auto i = 0; i < 4; ++i) {
				str << ip[i];
				if(i < 3) str << '.';
			}
			std::cout << str.str() << std::endl;
		}
	}

	//вывод адресов, начинающихся с 46 и 70
	for (const auto &ip: ip_address) {
		std::stringstream str;
		if (ip[0] == 46 && ip[1] == 70) {
			for (auto i = 0; i<4; ++i) {
				str << ip[i];
				if(i < 3) str << '.';
			}
			std::cout << str.str() << std::endl;
		}
	}

	//вывод адресов, содержащих 46
	for (const auto &ip: ip_address) {
		std::stringstream str;
		if (ip[0] == 46 || ip[1] == 46 || ip[2] == 46 || ip[3] == 46) {
			for (auto i = 0; i < 4; i++) {
				str << ip[i];
				if(i < 3) str << '.';
			}
			std::cout << str.str() << std::endl;
		}
	}
	return 0;
} 
