#pragma once
#ifndef FUNCTION_H
#define FUNCTION_H

#define DEFAULT_SIZE 1024
#define MAX_KEY_LENGTH 1000

class HashTable
{
public:
	HashTable();
	unsigned int m_unHashA;
	unsigned int m_unHashB;
	bool m_bIsExist;
	char m_chKey[MAX_KEY_LENGTH];
	HashTable* m_pNext;
};

class HashAlgorithm
{
public:
	HashAlgorithm(int nTableLength = DEFAULT_SIZE);

	unsigned int HashFunction(char* lpszKey, const char* lpszHashType /* = BKDRHash、APHash、DJBHash、JSHash、RSHash、SDBMHash、PJWHash 、ELFHash */);

	HashTable* GetFromHashTable(char* lpszKey, const char* lpszHashType, const char* lpszHashAType, const char* lpszHashBType 
		/* = BKDRHash、APHash、DJBHash、JSHash、RSHash、SDBMHash、PJWHash 、ELFHash */);

	unsigned int GetHashTableLength();

	bool InsertIntoHashTable(char* lpszKey, const char* lpszHashType, const char* lpszHashAType, const char* lpszHashBType
		/* = BKDRHash、APHash、DJBHash、JSHash、RSHash、SDBMHash、PJWHash 、ELFHash */);

	~HashAlgorithm();

	int GetSumOfCollisionalBuckets();

	int GetLongestLengthOfLinkList();

	double GetAverageLengthOfLinkList();

	double GetUtilizationRateOfBuckets();

private:
	int m_HashTableLength;			
	HashTable* m_HashTable;			
};

#endif