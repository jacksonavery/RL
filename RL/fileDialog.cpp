#include "fileDialog.h"

std::wstring FileDialog::loadFile(const wchar_t* filter) {
	OPENFILENAMEW ofn;
	WCHAR szFile[260] = { 0 };
	ZeroMemory(&ofn, sizeof(OPENFILENAMEW));
	ofn.lStructSize = sizeof(OPENFILENAMEW);
	ofn.hwndOwner = NULL; //technically it should be the game window but whatever
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	if (GetOpenFileNameW(&ofn) == true) {
		return ofn.lpstrFile;
	}
	return L"";
}

std::wstring FileDialog::saveFile(const wchar_t* filter) {
	OPENFILENAMEW ofn;
	WCHAR szFile[260] = { 0 };
	ZeroMemory(&ofn, sizeof(OPENFILENAMEW));
	ofn.lStructSize = sizeof(OPENFILENAMEW);
	ofn.hwndOwner = NULL; //technically it should be the game window but whatever
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	if (GetSaveFileNameW(&ofn) == true) {
		return ofn.lpstrFile;
	}
	return L"";
}