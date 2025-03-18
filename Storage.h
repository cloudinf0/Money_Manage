//
// Created by 11534 on 2025/3/3.
//

#ifndef MONEY_MANAGE_STORAGE_H
#define MONEY_MANAGE_STORAGE_H

//预估：map<date,pair<name, count>>
//date由本类生成，name和count由接口输入
#include <vector>
#include <map>
#include <utility>
#include <string>

struct Storage {
private:
    ::std::vector<int> date;
    ::std::multimap<int, ::std::pair<::std::string, int>> expend;
    int entertainment;
    int food;
public:
    void set(int &, ::std::string &, bool);

    ::std::vector<::std::string> getName(int);

    ::std::vector<int> getCount(int);

    void creatStorage();

};

int getCurrentDate();

#endif //MONEY_MANAGE_STORAGE_H