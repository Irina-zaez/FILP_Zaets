#include "stdafx.h"
#include "windows.h"
#include "Task1.h"
#include <iostream>
#include <map>
#include <String>
#include <cctype>

int main()
{
	HANDLE myFile = CreateFile(L"book.txt", GENERIC_READ,
		FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	LARGE_INTEGER size;
	GetFileSizeEx(myFile, &size);
	
	std::cout << "Size of file: " << size.QuadPart << "\n";

	DWORD textSize;
	char* text = new char[size.QuadPart + 1];
	ReadFile(myFile, text, size.QuadPart, &textSize, NULL);
	CloseHandle(myFile);

	std::map <std::string, int> freqDict;
	std::string word = "";
	for (int i = 0; i < size.QuadPart; i++) {
		if (isalpha(text[i]))
			word += tolower(text[i]);
		else 
			if (word != "") {
				if (freqDict.find(word) == freqDict.cend())
					freqDict[word] = 1;
				else
					freqDict[word]++;
				word = "";
			}
	}
	std::map<std::string, int>::iterator it;
	for (it = freqDict.begin(); it != freqDict.end(); it++)
		std::cout << it->first << " : " << it->second << '\n';
}

