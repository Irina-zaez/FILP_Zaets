#include "stdafx.h"
#include "windows.h"
#include <iostream>
#include <map>
#include <set>
#include <String>
#include <cctype>
#include <ctime>

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

	clock_t startTime = clock();
	int start = -1;
	int lenWord = 0;
	char* firstWord;
	std::map<char*, int> firstFreq;
	for (int i = 0; i < size.QuadPart; i++)
	{
		if (isalpha(text[i]))
		{
			if (start == -1)
				start = i;
			lenWord += 1;
		}
		else
			if (lenWord != 0)
			{
				firstWord = (char*)malloc(lenWord);
				for (int j = 0; j < lenWord; j++)
				{
					firstWord[j] = tolower(text[start + j]);
				}
				if (firstFreq.find(firstWord) == firstFreq.cend())
					firstFreq[firstWord] = 1;
				else
					firstFreq[firstWord]++;
				lenWord = 0;
				start = -1;
			}
	}
	clock_t endTime = clock();

	int firstTime = ((endTime - startTime) * 1000) / CLOCKS_PER_SEC;
	std::cout << "First method: " << firstTime << " ms\n";

	startTime = clock();
	std::map <std::string, int> secondFreq;
	std::string secondWord = "";
	for (int i = 0; i < size.QuadPart; i++)
	{
		if (isalpha(text[i]))
			secondWord += tolower(text[i]);
		else
			if (secondWord != "")
			{
				if (secondFreq.find(secondWord) == secondFreq.cend())
					secondFreq[secondWord] = 1;
				else
					secondFreq[secondWord]++;
				secondWord = "";
			}
	}
	endTime = clock();

	int secondTime = ((endTime - startTime) * 1000) / CLOCKS_PER_SEC;
	std::cout << "Second method: " << firstTime << " ms\n";

	std::map<std::string, int>::iterator it;
	for (it = secondFreq.begin(); it != secondFreq.end(); it++)
		std::cout << it->first << " : " << it->second << '\n';
}
