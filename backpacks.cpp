//
// Created by 11534 on 2025/3/6.
//
void name_inTimelyOutput(ExMessage inMess) {

    char input[50] = {0};           //字符数组中，0会被解释为\0(空字符)
    int x = 380, y = 340;
    int index = 0;

    while (true) {

        inMess = getmessage();          //用ExMessage来处理ESC信息，这样就不会“按一下esc退出两层逻辑”了
        if (inMess.vkcode == VK_ESCAPE){
//            ::std::cout << "I have got esc!" <<::std::endl;
            input[0] = '\0';                        //将字符数组的第一个值设为空字符，这个数组会被认为是空的
            break;
        }else if (inMess.vkcode == VK_RETURN){

        }

        if (_kbhit()) {
            char ch = _getch();
            // 创建一个矩形区域
            HRGN rgn = CreateRectRgn(380, 340, 540, 400);
            // 将该矩形区域设置为裁剪区
            setcliprgn(rgn);
            //太爽啦裁剪区域！！！！！
            if (ch == '\r') {                           //enter确认
                ::std::cout << "Enter has been down!" << ::std::endl;
            } else if (ch == '\b') {                    //退格
//                ::std::cout << "Backspace has been down!" << ::std::endl;
                if (index > 0) {
                    input[--index] = '\0';              //“\0”是一个空字符
                    clearcliprgn();
                    outtextxy(x, y, input);
                }
            } else if (ch == 0x1B){
//                ::std::cout << "little esc was ignored." << ::std::endl;
                outtextxy(x, y, input);
            } else {                                    //输入name
                //这里应该再加一个条件判断，避免输入的字符个数超过100
                input[index++] = ch;
                input[index] = '\0';
                outtextxy(x, y, input);
            }
            DeleteObject(rgn);
        }
    }
}