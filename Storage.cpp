//
// Created by 11534 on 2025/3/3.
//
#include "Storage.h"
#include <ctime>
#include <chrono>
#include <iostream>

int getCurrentDate() {
    // 获取当前时间点，将时间点转换为 time_t，将 time_t 转换为 tm 结构，使用 stringStream 格式化日期
    auto now = ::std::chrono::system_clock::now();
    ::std::time_t now_time = ::std::chrono::system_clock::to_time_t(now);
    ::std::tm *now_tm = ::std::localtime(&now_time);
    ::std::stringstream ss;
    ss << ::std::put_time(now_tm, "%d");

    return ::std::stoi(ss.str());
}


void Storage::creatStorage() {
    for (int i = 1; i < 32; ++i) {
        date.push_back(i);
    }
}

void Storage::set(int &in_count, ::std::string &in_name, bool in_type) {
    int dayNumber = getCurrentDate() - 1;
    while (expend.size() < dayNumber) {
        expend.insert(::std::make_pair(0, ::std::make_pair("null", 0)));
    }
    expend.insert(::std::make_pair(getCurrentDate(), ::std::make_pair(in_name, in_count)));

    if (in_type)food += in_count;
    else entertainment += in_count;

}

::std::vector<::std::string> Storage::getName(int inDate) {
    //程序内部调用，不会超出范围
    ::std::vector<::std::string> retName;
    auto it = expend.equal_range(inDate);
    for (auto it2 = it.first; it2 != it.second; ++it2) {
        retName.push_back(it2->second.first);
    }
    return retName;
}

::std::vector<int> Storage::getCount(int inDate) {
    ::std::vector<int> retCount;
    auto it = expend.equal_range(inDate);
    for (auto it2 = it.first; it2 != it.second; ++it2) {
        retCount.push_back(it2->second.second);
    }
    return retCount;
}

