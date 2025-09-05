#include <boost/test/tools/old/interface.hpp>
#include <cstdlib>
#include <iterator>
#include <fstream>

#include "function.h"

#define BOOST_TEST_MODULE test_version
#include <boost/test/unit_test.hpp>

void CreateTestFile(const std::string &filename) {
    std::ofstream ofs(filename);
    if (!ofs) {
        std::cerr << "Ошибка при открытии файла для записи: " << filename << std::endl;
        return;
    }

    ofs << "192.168.46.7\taaa\tbbb\n";
    ofs << "1.70.46.7\taaa\tbbb\n";
    ofs << "1.7.46.7\taaa\tbbb\n";
    ofs << "46.70.146.7\taaa\tbbb\n";
    ofs << "19.70.146.7\taaa\tbbb\n";
    ofs.close();
}

BOOST_AUTO_TEST_SUITE(test_filter_ip)

BOOST_AUTO_TEST_CASE(test_main) {
    const std::string test_input = "test_input.txt";
    CreateTestFile(test_input);

    std::string command =
        "cat " + test_input + " | ./ip_filter > output_test.txt";
    int ret = std::system(command.c_str());
    BOOST_CHECK_EQUAL(ret, 0);

    //Чтение вывода
    std::ifstream ifs("output_test.txt");
    std::string output((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

    //Ожидаемый вывод
    std::string exp_output = "";
    exp_output.append("192.168.46.7\n");
    exp_output.append("46.70.146.7\n");
    exp_output.append("19.70.146.7\n");
    exp_output.append("1.70.46.7\n");
    exp_output.append("1.7.46.7\n");

    exp_output.append("1.70.46.7\n");
    exp_output.append("1.7.46.7\n");

    exp_output.append("46.70.146.7\n");

    exp_output.append("192.168.46.7\n");
    exp_output.append("46.70.146.7\n");
    exp_output.append("1.70.46.7\n");
    exp_output.append("1.7.46.7\n");

    BOOST_CHECK_EQUAL(output, exp_output);
}

BOOST_AUTO_TEST_CASE(test_parsing_data) {
    const std::string test_input = "test_input.txt";
    CreateTestFile(test_input);

    std::ifstream file(test_input);
    if (!file) {
        std::cerr << "Не удалось открыть файл" << std::endl;
        return;
    }
    std::vector<std::vector<int>> ip_address;
    ReadData(file, ip_address);

    std::vector<std::vector<int>> exp_vector;
    exp_vector.push_back(std::vector<int>{192, 168, 46, 7});
    exp_vector.push_back(std::vector<int>{1, 70, 46, 7});
    exp_vector.push_back(std::vector<int>{1, 7, 46, 7});
    exp_vector.push_back(std::vector<int>{46, 70, 146, 7});
    exp_vector.push_back(std::vector<int>{19, 70, 146, 7});

    BOOST_CHECK(ip_address == exp_vector);
}

BOOST_AUTO_TEST_SUITE_END()
