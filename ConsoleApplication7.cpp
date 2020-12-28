// ConsoleApplication7.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <windows.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include "opencv2/imgproc/imgproc_c.h"
#include <filesystem>
using namespace cv;
	int kazu = 0;
cv::VideoCapture video;
HBITMAP *bms;
static std::vector<HBITMAP> tmp = std::vector<HBITMAP>();
std::filesystem::path path2 = "c:\\images\\k";
std::filesystem::path path = "c:\\images";
void load_img() {
	kazu = 0;
	for (const auto& file : std::filesystem::recursive_directory_iterator(path)) {
		kazu++;
	}
	bms =(HBITMAP*) malloc(sizeof(HBITMAP ) * kazu);
	int i = 0;
	for (const auto& file : std::filesystem::recursive_directory_iterator(path)) {
		bms[i]=(HBITMAP)LoadImage(NULL, PCWSTR(file.path().c_str()), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		i++;
	}
}
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"hwnd is null", L"aa", MB_OK);
	}
	std::cout << "ex";
	HWND p = FindWindowEx(hwnd, 0, L"SHELLDLL_DefView", 0);
	HWND* ret = (HWND*)lParam;
	HWND workerw = nullptr;
	if (p != NULL)
	{
		workerw = FindWindowEx(NULL, hwnd, L"WorkerW", NULL);
		load_img();
		if (workerw != NULL) {
			HDC dc = GetDC(workerw);
			while (true) {
				for (int cnt = 0; cnt < kazu; cnt++) {
					Sleep(24);
					bms[cnt];
					if (bms[cnt] == NULL) {
						MessageBox(NULL, L"Failed to open file", L"aa", MB_OK);
					}
					else {
						HDC hMdc = CreateCompatibleDC(dc);
						SelectObject(hMdc, bms[cnt]);
						BitBlt(dc, 0, 0, 1920, 1080, hMdc, 0, 0, SRCCOPY);
						DeleteDC(hMdc);
					}
				}
			}



		}
	}
	return true;
}
HWND get_wallpaper_window()
{
	HWND progman = FindWindow(L"Progman", NULL);
	if (progman == NULL) {
		MessageBox(NULL, L"progma is null", L"fail", MB_OK);
	}
	PDWORD_PTR result = nullptr;
	int i = SendMessageTimeout(progman, 0x052C, 0, 0, SMTO_NORMAL, 1000, result);
	MessageBox(NULL, LPCWSTR(i + ""), L"result", MB_OK);
	HWND wallpaper_hwnd = progman;
	EnumWindows(EnumWindowsProc, (LPARAM)&wallpaper_hwnd);
	return wallpaper_hwnd;
}

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine,
	int nCmdShow
)
{
	get_wallpaper_window();
	Sleep(100);
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
