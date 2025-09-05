#include <sstream>

#include "function.h"

void ReadData(std::istream &input, std::vector<std::vector<int>> &ip_address) {
    std::string line;

    while (std::getline(input, line)) {
        std::vector<int> i_vector;
        i_vector.reserve(4);

        std::stringstream ss(line);
        std::string part;

        // разделяем строку по табуляции
        while (std::getline(ss, part, '\t')) {
        std::stringstream sss(part);
        std::string pa;

        while (std::getline(sss, pa, '.')) {
            i_vector.push_back(std::stoi(pa));
        }
        break;
        }
        ip_address.push_back(std::move(i_vector));
    }
}