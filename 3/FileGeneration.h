#pragma once
#ifndef FILEGENERATION_H
#define FILEGENERATION_H

#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

void FileGeneration(FILE* fStream, int nStringSize, int nStringCount)
{
	const char* SYMBOL_TABLE = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char* szStr = new char[nStringSize + 1];
	szStr[nStringSize] = '\0';
	char chTemp = '    ';
	srand((unsigned)time(0));

	fwrite(&nStringSize, sizeof(int), 1, fStream);
	fwrite(&chTemp, sizeof(char), 1, fStream);
	fwrite(&nStringCount, sizeof(int), 1, fStream);
	fwrite(&chTemp, sizeof(char), 1, fStream);

	for (int j = 0; j < nStringCount; j++)
	{
		int nRand = 0;
		for (int i = 0; i < nStringSize; ++i)
		{
			nRand = rand() % 62;
			szStr[i] = SYMBOL_TABLE[nRand];
		}
		fwrite(szStr, sizeof(char)*(nStringSize + 1), 1, fStream);
		fwrite(&chTemp, sizeof(char), 1, fStream);
	}
	delete[] szStr;
}

void FileGeneration(ofstream& fStream, int nStringSize, int nStringCount)
{
	const char* SYMBOL_TABLE = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	
	string szStr="";

	srand((unsigned)time(0));

	for (int j = 0; j < nStringCount; j++)
	{
		int nRand = 0;
		for (int i = 0; i < nStringSize; ++i)
		{
			nRand = rand() % 62;
			char sTemp = SYMBOL_TABLE[nRand];
			fStream << sTemp;
		}
		fStream << ' ';
	}
	fStream.close();
}

#endif