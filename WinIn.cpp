//
// Created by 11534 on 2025/3/4.
//
#include <iostream>
#include "WinIn.h"

//创建输入屏幕
void creatInNameScreen();

void creatInCountScreen();

::std::string name_inTimelyOutput(ExMessage inName);

int count_inTimelyOutput(ExMessage inMess);


void creatScreen() {

    //初始屏幕
    initgraph(640, 480);
    setbkcolor(RGB(220, 245, 220));
    cleardevice();

    //saying hello
    setfillcolor(RGB(245, 245, 220));
    fillrectangle(346, 66, 554, 174);
    setfillcolor(WHITE);
    fillrectangle(350, 70, 550, 170);

    settextstyle(50, 0, "Consolas");
    settextcolor(RGB(245, 222, 220));
    setbkcolor(WHITE);
    outtextxy(380, 100, "Hello!");

    setbkcolor(RGB(220, 245, 220));

    creatInputScreen();

    //look back
    setfillcolor(RGB(245, 245, 220));
    fillrectangle(346, 186, 554, 214);
    setfillcolor(WHITE);
    fillrectangle(350, 190, 550, 210);

    settextstyle(20, 0, "Consolas");
    settextcolor(RGB(245, 222, 220));
    setbkcolor(WHITE);
    outtextxy(405, 190, "Look Back");

}

void creatInNameScreen() {
    //先转换局部窗口
    fillrectangle(350, 230, 550, 410);
    //添加局部窗口文字
    settextstyle(26, 0, "Consolas");
    settextcolor(RGB(245, 222, 220));
    setbkcolor(WHITE);
    outtextxy(360, 250, "Key-in the Name");
    settextstyle(36, 0, "Consolas");
    outtextxy(390, 280, "at Here!");
}

void creatInCountScreen() {
    fillrectangle(350, 230, 550, 410);
    settextstyle(26, 0, "Consolas");
    settextcolor(RGB(245, 222, 220));
    setbkcolor(WHITE);
    outtextxy(360, 250, "Key-in the Count");
    settextstyle(36, 0, "Consolas");
    outtextxy(390, 280, "at Here!");
}

void creatInputScreen() {
//添加输入口图形
    setfillcolor(RGB(245, 245, 220));
    fillrectangle(346, 226, 554, 414);
    setfillcolor(WHITE);
    fillrectangle(350, 230, 550, 318);
    fillrectangle(350, 322, 550, 410);

    //添加输入口文字
    settextstyle(50, 0, "Consolas");
    settextcolor(RGB(245, 222, 220));
    setbkcolor(WHITE);
    outtextxy(412, 252, "eat");
    outtextxy(402, 338, "play");
    setbkcolor(RGB(220, 245, 220));
}

void clearMessageQueue() {
    ExMessage msg;
    while (peekmessage(&msg, EM_CHAR)) {}  // 循环读取消息直到队列为void
}


::std::pair<::std::string, int> keyInput() {

    creatInNameScreen();

    //执行输入逻辑
    ExMessage mes;
    ::std::string inName;
    int inCount;

    bool flag = true;
    while (flag) {
        mes = getmessage(EX_KEY);

        if (mes.message == WM_KEYDOWN) {
            if (mes.vkcode == VK_ESCAPE) flag = false;
            else {
                inName = name_inTimelyOutput(mes);

                if (!inName.empty()) {
                    cleardevice();
                    creatScreen();
                    creatInCountScreen();
                    while (peekmessage(&mes)) {}
                    flushmessage();
                    inCount = count_inTimelyOutput(mes);
                }
                flag = false;
            }
        }
    }

//    ::std::cout << "I 'm going to creat the InputScreen!" << ::std::endl;
    cleardevice();
    creatScreen();
    return ::std::make_pair(inName, inCount);
}


::std::string name_inTimelyOutput(ExMessage inMess) {
    ::std::string input;
    int x = 380, y = 340;

    ExMessage msg;
    while (true) {
        if (peekmessage(&msg, EM_CHAR)) {
            HRGN rgn = CreateRectRgn(380, 340, 540, 400);
            setcliprgn(rgn);
            if (msg.message == WM_CHAR) {
                char ch = msg.ch;
                if (ch == '\r') {  // Enter 键
                    clearMessageQueue();  // 清空消息队列
                    return input;
                } else if (ch == '\b' && !input.empty()) {  // Backspace 键
                    clearcliprgn();
                    input.pop_back();
                } else if (ch == 0x1B) {
                    clearMessageQueue();
                    input.clear();
                    return input;
                } else if (isprint(ch)) {  // 可打印字符
                    input.push_back(ch);
                }
                outtextxy(x, y, input.c_str());  // 实时显示输入
            }
        }
    }
}

int count_inTimelyOutput(ExMessage inMess) {
    ::std::cout << "function run " << ::std::endl;
    int input = 0;
    int x = 380, y = 340;

    ExMessage msg;
    while (true) {
        if (peekmessage(&msg, EM_CHAR)) {
            HRGN rgn = CreateRectRgn(380, 340, 540, 400);
            setcliprgn(rgn);
            if (msg.message == WM_CHAR) {
                char ch = msg.ch;
                if (ch == '\r') {  // Enter 键
                    clearMessageQueue();  // 清空消息队列
                    return input;
                } else if (ch == 0x1B) {
                    clearMessageQueue();
                    input = 0;
                    return input;
                } else if (ch == '\b' && input > 0) {  // Backspace 键
                    clearcliprgn();
                    input /= 10;
                } else if (isdigit(ch)) {  // 数字字符
                    input = input * 10 + (ch - '0');
                }
                outtextxy(x, y, std::to_string(input).c_str());  // 实时显示输入
            }
        }
    }
}