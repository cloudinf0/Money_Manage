#include <iostream>
//一个收支管理小程序
//最终目的是，生成一张日历，每格标注每天支出多少，右侧标注总支出
//另外要分类，显示娱乐支出、餐饮支出
//
//额外需求，日历格式可以切换，分别为周表和月表
//将日历每格按照不同的支出数目，加深背景格颜色
//
//
//可能涉及到外部存储的功能要学习
//涉及到exe程序导出的学习
//请教一下关于引用和const的优化
//学到了抛出异常（一点点）
//
//
//规划：
//实现一个单独的输入窗口，具备输入消费名称、消费数额、自动读取日期的功能
//提供一个切换按钮，用于在输入、输出窗口之间切换
//后台记录模块，用一个类来承载所有的信息，并提供set get的接口\/
//实现一个输出窗口，默认以月的形式展示，按钮切换至周
//侧面总输出
#include <windows.h>
#include <string>
#include "Storage.h"
#include "WinIn.h"
#include "WinOut.h"
#include <iostream>


int main() {

    SetConsoleCP(65001); // input gbk -> utf8
    SetConsoleOutputCP(65001); // output gbk -> utf8

//存储初始化
    Storage dataStorage;
    dataStorage.creatStorage();

//屏幕初始化
    creatScreen();
//交互逻辑
    ExMessage m;
    ::std::pair<::std::string, int> result;

    while (true) {
        m = getmessage(EX_MOUSE | EX_KEY);
        switch (m.message) {
            case WM_LBUTTONDOWN:
                if (m.x > 350 && m.x < 550 && m.y > 230 && m.y < 318) {
                    result = keyInput();
                    dataStorage.set(result.second, result.first, true);
                } else if (m.x > 350 && m.x < 550 && m.y > 322 && m.y < 410) {
                    result = keyInput();
                    dataStorage.set(result.second, result.first, false);
                } else if (m.x > 346 && m.x < 554 && m.y > 186 && m.y < 214) {
                    interact(dataStorage);
                    creatScreen();
                }
                    break;
            case WM_KEYDOWN:
                if (m.vkcode == VK_ESCAPE) goto End;
                break;
            default:
                break;
        }
    }
    //以下为测试代码用
    End:

    return 0;
}
