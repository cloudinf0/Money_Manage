//
// Created by 11534 on 2025/3/9.
//
#include "WinOut.h"
#include <iostream>

int getFirstDay() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm *now_tm = std::localtime(&now_c);

    int weekday = now_tm->tm_wday;

    ::std::stringstream ss;
    ss << ::std::put_time(now_tm, "%d");
    int minDay = (::std::stoi(ss.str())) % 7;

    for (; minDay > 1; --minDay) {
        if (weekday == 0) weekday += 6;
        else --weekday;
    }
    return weekday;
}

int getCurrentMonth() {
    // 获取当前时间点，将时间点转换为 time_t，将 time_t 转换为 tm 结构，使用 stringStream 格式化日期
    auto now = ::std::chrono::system_clock::now();
    ::std::time_t now_time = ::std::chrono::system_clock::to_time_t(now);
    ::std::tm *now_tm = ::std::localtime(&now_time);
    ::std::stringstream ss;
    ss << ::std::put_time(now_tm, "%m");

    return ::std::stoi(ss.str());
}

static const ::std::vector<int> daysInAMonth = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void creatOutputScreen(Storage &stg) {


    const ::std::vector<::std::string> num_to_Mon = {"January", "February", "March", "April", "May", "June", "July",
                                                     "August", "September", "October", "November", "December"};


    setbkcolor(RGB(220, 245, 220));
    cleardevice();

    //创建栅格
    setfillcolor(RGB(230, 230, 220));
    solidrectangle(0, 40, 640, 45);
    const int temp1 = 72;
    const int temp2 = 91;
    for (int i = 1; i < 6; ++i) {
        solidrectangle(0, 45 + temp1 * i - 1, 640, 45 + temp1 * i);
    }
    for (int i = 1; i < 7; ++i) {
        solidrectangle(temp2 * i - 1, 45, temp2 * i, 480);
    }

    //创建文字
    setbkcolor(RGB(220, 245, 220));
    settextcolor(RGB(180, 205, 180));
    settextstyle(30, 0, "Consolas");
    outtextxy(280, 5, (num_to_Mon[getCurrentMonth() - 1]).c_str());
    outtextxy(10, 5, "<");
    outtextxy(615, 5, ">");

//创建每个窗口的文字和数字

    int temp3 = getFirstDay();
    int temp4 = 1;
    int twoflag = 0;
    int flag2 = daysInAMonth[getCurrentMonth()];

    for (int i = 1; i <= flag2; ++i) {
        char s[5];
        sprintf(s, "%d", i);

        int x = 38 + (temp3 - 1) * 91;
        int y = 48 + 72 * (temp4 - 1);

        settextstyle(30, 0, "Consolas");
        outtextxy(x - twoflag, y, s);
        settextstyle(18, 0, "Consolas");
        outtextxy(x - 30, y + 37, "total");
        fillNumber(x + 20, y + 37, i, stg);

        if (temp3 == 7) {
            temp3 = 0;
            ++temp4;
        }
        if (i == 9) twoflag = 7;
        ++temp3;
    }

}

void interact(Storage &stg) {
    ExMessage msg;
    while (true) {
        creatOutputScreen(stg);
        msg = getmessage(EX_KEY);
        if (msg.message == WM_KEYDOWN && msg.vkcode == 0x4C) {
            if (creatDailyScreen(stg)) return;
        } else if (msg.vkcode == VK_ESCAPE) return;
    }
}

void fillNumber(int x, int y, int date, Storage &stg) {
    auto vec = stg.getCount(date);
    int totalCount = 0;
    for (auto i: vec) {
        totalCount += i;
    }
    char s[5];
    sprintf(s, "%d", totalCount);
    outtextxy(x, y, s);
}

bool creatDailyScreen(Storage &stg) {
    //初始化
    int page = 0;

    cleardevice();
    setfillcolor(RGB(230, 230, 220));
    solidrectangle(0, 40, 640, 45);
    setfillcolor(RGB(240, 240, 240));
    setlinecolor(RGB(230, 230, 220));
    int temp1 = 80;
    for (int i = 0; i < 7; ++i) {
        fillroundrect(10 * (i + 1) + temp1 * i, 60, 10 * (i + 1) + temp1 * (1 + i), 465, 10, 10);
    }


    char page_c = '1' + page;
    fillEveryDay(page, stg);
    creatTitle(page_c);

    outtextxy(270, 5, "week");
    outtextxy(10, 5, "<");
    outtextxy(615, 5, ">");

    //交互逻辑

    ExMessage msg;
    while (true) {
        msg = getmessage(EX_KEY);
        if (msg.message == WM_KEYDOWN) {

            setfillcolor(RGB(240, 240, 240));
            setlinecolor(RGB(230, 230, 220));
            for (int i = 0; i < 7; ++i) {
                solidrectangle(10 * (i + 1) + temp1 * i +3, 113, 10 * (i + 1) + temp1 * (1 + i) - 3, 460);
            }
            setlinecolor(RGB(220 ,245,220));

            if (msg.vkcode == VK_ESCAPE) return true;
            else if (msg.vkcode == 0x4C) return false;
            else if (msg.vkcode == VK_RIGHT && page < 4) {
                ++page;
            } else if (msg.vkcode == VK_LEFT && page > 0) {
                --page;
            }
            page_c = '1' + page;
            setfillcolor(RGB(220, 245, 220));
            fillrectangle(348, 5, 368, 15);
            fillEveryDay(page, stg);
            creatTitle(page_c);
        }
    }

}

void fillEveryDay(int page, Storage &stg) {

    //填入每日的消费名称、金额
    ::std::vector<::std::string> nameVec;
    ::std::vector<int> countVec;
    setbkcolor(RGB(240, 240, 240));
    int flag2 = daysInAMonth[getCurrentMonth()];

    if (page < 4) {
        for (int i = 1; i <= 7; ++i) {

            settextstyle(40, 0, "Consolas");
            char c = '0' + i;
            outtextxy(40 + 90 * (i - 1), 80, c);

            settextstyle(20, 0, "Consolas");
            nameVec = stg.getName(i + page * 7);
            countVec = stg.getCount(i + page * 7);
            int flag3 = nameVec.size();

            if (flag3 != 0) {
                for (int j = 0; j < flag3; ++j) {
                    outtextxy(20 + 90 * (i - 1), 120 + 20 * j, (nameVec[j]).c_str());
                    outtextxy(60 + 90 * (i - 1), 120 + 20 * j, (::std::to_string(countVec[j])).c_str());
                }
            } else {
                outtextxy(20 + 90 * (i - 1), 120, "null");
                outtextxy(60 + 90 * (i - 1), 120, '0');
            }
        }
    } else {
        for (int i = 29; i <= flag2; ++i) {
            nameVec = stg.getName(i);
            countVec = stg.getCount(i);
            int flag3 = nameVec.size();
            if (flag3 != 0) {
                for (int j = 0; j < flag3; ++j) {
                    outtextxy(20 + 90 * (i - 1), 120 + 20 * j, (nameVec[j]).c_str());
                    outtextxy(60 + 90 * (i - 1), 120 + 20 * j, (::std::to_string(countVec[j])).c_str());
                }
            } else {
                outtextxy(20 + 90 * (i - 1), 120, "null");
                outtextxy(60 + 90 * (i - 1), 120, '0');
            }
        }
    }
}

void creatTitle(char page_c) {
    setbkcolor(RGB(220, 245, 220));
    settextstyle(30, 0, "Consolas");
    outtextxy(350, 5, page_c);
}