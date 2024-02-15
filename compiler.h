#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <regex>
#include<unordered_set>
struct info {
    std::string type;
    std::string value;
    int line;
    int pos;
};
void used_types(std::string& input) {
    std::ifstream inputFile(input);
    std::ofstream simple("Typeinfo.txt");
    if (!inputFile) {
        std::cerr << "Couldn't open the file";
        return;
    }
    std::regex types("int|bool|char|short|double|long int|long long int|float|unsigned int|unsigned short|const int");
    std::unordered_set<std::string> result;
    std::string line;
    std::string word;
    std::smatch match;
    while (std::getline(inputFile, line)) {
        auto words_begin = std::sregex_iterator(line.begin(), line.end(), types);
        auto words_end = std::sregex_iterator();
        for (std::sregex_iterator it = words_begin; it != words_end; ++it) {
            result.insert(it->str());
        }
    }
    for (const std::string& it : result) {
        simple << it + " val;" << std::endl;
    }
    simple.close();
    inputFile.close();
}
std::string change(std::string str)
{
    std::string tmp = "";
    std::string t{};
    int i = 0;
    std::stringstream s(str);
    while (s >> t) {
        tmp += t[0];
    }
    return tmp;
}
void create_table(std::string& input) {
    std::ifstream inputFile(input);
    if (!inputFile.is_open()) {
        throw std::invalid_argument("Don't open input file");
    }
    std::ofstream outputFile("result.txt");
    outputFile << std::setw(30) << std::left << "Type"
        << std::setw(30) << std::left << "Value"
        << std::setw(30) << std::left << "Name"
        << std::setw(30) << std::left << "Line"
        << std::setw(30) << std::left << "Pos"
        << std::endl;
    ;
    outputFile << std::endl << std::endl;
    std::map<std::string, info> m;
    int l = 0;
    std::string oneline = "";
    while (std::getline(inputFile, oneline), !inputFile.eof()) {
        bool b = false;
        if (oneline[oneline.size() - 1] != ';') {
            b = true;
        }
        int p = 0;
        if (b) {
            std::string tmp1 = "";
            std::getline(inputFile, tmp1, ';');
            oneline += tmp1;
            oneline += ';';
        }
        std::string str = "";
        std::istringstream ssi(oneline);
        while (std::getline(ssi, str, ';'), !ssi.eof()) {
            std::vector<std::string> vec;
            std::stringstream s(str);
            std::string tmp;
            bool flag = false;
            int size = 0;
            while (s >> tmp) {
                ++size;
                vec.push_back(tmp);
                if (tmp == "=") {
                    flag = true;
                }
            }
            std::string n = "";
            std::string v = "";
            std::string t = "";
            if (size > 1) {
                if (flag) {
                    n = vec[size - 3];
                    v = vec[size - 1];
                    for (int i = 0; i < size - 3; ++i) {
                        t += vec[i] + " ";
                    }
                    t[t.size() - 1] = '\0';
                }
                else {
                    n = vec[size - 1];
                    v = "GARBAGE";
                    for (int i = 0; i < size - 1; ++i) {
                        t += vec[i] + " ";
                    }
                    t[t.size() - 1] = '\0';
                }
            }
            else {
                n = vec[size - 1];
                bool b = false;
                for (auto el : m) {
                    if (el.first == n) {
                        b = true;
                        outputFile << std::left << std::setw(30) << change(el.second.type)
                            << std::setw(30) << el.second.value
                            << std::setw(30) << el.first
                            << std::setw(30) << el.second.line
                            << std::setw(30) << el.second.pos
                            << std::endl;
                        break;
                    }
                }
                if (!b) {
                    outputFile << std::left << std::setw(30) << "-"
                        << std::setw(30) << "-"
                        << std::setw(30) << n
                        << std::setw(30) << l
                        << std::setw(30) << p
                        << std::endl;
                }
                ++p;
                continue;
            }
            info ob{ t, v, l, p };
            m[n] = ob;
            ++p;
        }
        ++l;
    }
    inputFile.close();
    outputFile.close();
}