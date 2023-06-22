#include <iostream>
#include <stdlib.h>
#include<windows.h>
#include <ctime>
 
using namespace std;

void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

bool SetSize(int width, int height)
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE); //获取输出句柄
	SMALL_RECT wrt = { 0, 0, width - 1, height - 1 }; //设置宽高
	bool ret = SetConsoleWindowInfo(hOutput, TRUE, &wrt); // 设置窗体尺寸
	if (!ret) return false;
	COORD coord = { width, height };
	ret = SetConsoleScreenBufferSize(hOutput, coord); // 设置缓冲尺寸
	return ret;
}

void cmd_ctrl() {
	HWND hWnd = GetConsoleWindow(); //获取窗口句柄
	LONG_PTR sty = GetWindowLongPtrA(hWnd, GWL_STYLE); //获取窗口样式
	sty = sty & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX; //去除可变化大小,最大,最小化按钮,~是取反,&是与,这是位运算相关的知识了
	SetWindowLongPtrA(hWnd, GWL_STYLE, sty); //设置窗体不可更改大小,不可最大化
}
 
 void SetFont(int size = 30) {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof cfi;
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = size;  //设置字体大小
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL; //字体粗细 FW_BOLD
	//wcscpy_s(cfi.FaceName, L"黑体");  //设置字体，必须是控制台已有的
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	//获得当前字体
	//HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//CONSOLE_FONT_INFO consoleCurrentFont;
	//GetCurrentConsoleFont(handle, FALSE, &consoleCurrentFont);
}
 
void time_1()
{
   // 基于当前系统的当前日期/时间
   time_t now = time(0);
   
   // 把 now 转换为字符串形式
   char* dt = ctime(&now);
 
   cout <</* "本地日期和时间：" <<*/ dt << endl;
 
   // 把 now 转换为 tm 结构
  // tm *gmtm = gmtime(&now);
   //dt = asctime(gmtm);
  // cout << "UTC 日期和时间："<< dt << endl;
}

int main(){
	SetConsoleTitleA("时间查看器");
	SetSize(25, 3);
	HideCursor();
	cmd_ctrl();
	SetFont(50);
	while(1){
		system("cls");
		time_1();
		Sleep(1000);
	}
	return 0;
}




