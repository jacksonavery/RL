#pragma once
#include <windows.h>
#include <commdlg.h>
#include <string>

//https://www.youtube.com/watch?v=zn7N7zHgCcs

class FileDialog {
public:
	//returns L"" if cancelled
	static std::wstring loadFile(const wchar_t* filter);
	static std::wstring saveFile(const wchar_t* filter);
};