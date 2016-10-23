#include "stdafx.h"
#include "Function.h"

HashTable::HashTable()
{
	m_bIsExist = false;
	m_unHashA = 0;
	m_unHashB = 0;
	m_chKey[0] = '\0';
	m_pNext = NULL;
}

/*
	nTableLength：哈希表的长度
*/
HashAlgorithm::HashAlgorithm(int nTableLength /*= DEFAULT_SIZE*/)
{
	m_HashTableLength = nTableLength;
	m_HashTable = new HashTable[m_HashTableLength]();
}

HashAlgorithm::~HashAlgorithm()
{
	for (int i = 0; i < m_HashTableLength; i++)
	{
		if (m_HashTable[i].m_pNext != NULL)
		{
			HashTable* pCurrent = m_HashTable[i].m_pNext;
			HashTable* pDel = NULL;
			while (pCurrent != NULL)
			{
				pDel = pCurrent;
				pCurrent = pCurrent->m_pNext;
				delete pDel;
			}
		}
	}
	delete[] m_HashTable;
}

/*
	返回当前字符串的哈希函值。
	lpszKey：待进行哈希函数运算的字符串，lpszHashType：哈希函数的类型
*/
unsigned int HashAlgorithm::HashFunction(char* lpszKey, const char* lpszHashType /* = BKDRHash、APHash、DJBHash、JSHash、RSHash、SDBMHash、PJWHash 、ELFHash */)
{
	if (lpszHashType=="BKDRHash")
	{
		unsigned int unSeed = 131; 
		unsigned int unHash = 0;
		while (*lpszKey)
		{
			unHash = unHash*unSeed + (*lpszKey++);
		}
		return unHash;
	}
	else if (lpszHashType == "APHash")
	{
		unsigned int unHash = 0;
		for (int i = 0; *lpszKey; i++)
		{
			if ((i & 1) == 0)
			{
				unHash ^= ((unHash << 7) ^ (*lpszKey++) ^ (unHash >> 3));
			}
			else
			{
				unHash ^= (~((unHash << 11) ^ (*lpszKey++) ^ (unHash >> 5)));
			}
		}
		return unHash;
	}
	else if (lpszHashType == "DJBHash")
	{
		unsigned int unHash = 5381;

		while (*lpszKey)
		{
			unHash += (unHash << 5) + (*lpszKey++);
		}

		return unHash;
	}
	else if (lpszHashType == "JSHash")
	{
		unsigned int unHash = 1315423911;
		while (*lpszKey)
		{
			unHash ^= ((unHash << 5) + (*lpszKey++) + (unHash >> 2));
		}
		return unHash;
	}
	else if (lpszHashType == "RSHash")
	{
		unsigned int unA = 378551;
		unsigned int unB = 63689;
		unsigned int unHash = 0;
		while (*lpszKey)
		{
			unHash = unHash*unA + (*lpszKey++);
			unA *= unB;
		}
		return unHash;
	}
	else if (lpszHashType == "SDBMHash")
	{
		unsigned int unHash = 0;
		while (*lpszKey)
		{
			unHash = (*lpszKey++) + (unHash << 6) + (unHash << 16) - unHash;
		}
		return unHash;
	}
	else if (lpszHashType == "PJWHash")
	{
		unsigned int unBitsInUnignedInt = (unsigned int)(sizeof(unsigned int)* 8);
		unsigned int unThreeQuarters = (unsigned int)((unBitsInUnignedInt * 3) / 4);
		unsigned int unOneEighth = (unsigned int)(unBitsInUnignedInt / 8);
		unsigned int unHighBits = (unsigned int)(0xFFFFFFFF) << (unBitsInUnignedInt - unOneEighth);
		unsigned int unHash = 0;
		unsigned int unTest = 0;

		while (*lpszKey)
		{
			unHash = (unHash << unOneEighth) + (*lpszKey++);
			if ((unTest = unHash&unHighBits) != 0)
			{
				unHash = ((unHash ^ (unTest >> unThreeQuarters))&(~unHighBits));
			}
		}

		return unHash;
	}
	else if (lpszHashType == "ELFHash")
	{
		unsigned int unHash = 0;
		unsigned int unX = 0;
		while (*lpszKey)
		{
			unHash = (unHash << 4) + (*lpszKey++);
			if ((unX = unHash & 0xF0000000L) != 0)
			{
				unHash ^= (unX >> 24);
				unHash &= ~unX;
			}
		}
		return unHash;
	}
	else
		return -1;
}

/*
	返回当前字符串的在哈希表中的位置指针,如果未找到则返回NULL。
	lpszKey：待进行哈希函数运算的字符串，lpszHashType：查找位置用哈希函数类型，lpszHashAType、lpszHashBType：校验用哈希函数类型
*/
HashTable* HashAlgorithm::GetFromHashTable(char* lpszKey, const char* lpszHashType, const char* lpszHashAType, const char* lpszHashBType
	/* = BKDRHash、APHash、DJBHash、JSHash、RSHash、SDBMHash、PJWHash 、ELFHash */)
{
	unsigned int unHash = HashFunction(lpszKey, lpszHashType);
	unsigned int unHashA = HashFunction(lpszKey, lpszHashAType);
	unsigned int unHashB = HashFunction(lpszKey, lpszHashBType);
	unsigned int unIndex = unHash%m_HashTableLength;
	HashTable* pCurrent = &m_HashTable[unIndex];

	if (m_HashTable[unIndex].m_bIsExist == false)
	{
		return NULL;
	}

	while (pCurrent != NULL)
	{
		if (pCurrent->m_unHashA == unHashA&&pCurrent->m_unHashB == unHashB)
		{
			return pCurrent;
		}
		pCurrent = pCurrent->m_pNext;
	}

	return NULL;
}

/*
	返回哈希表的长度。
*/
unsigned int HashAlgorithm::GetHashTableLength()
{
	return m_HashTableLength;
}

/*
	将关键字lpszKey插入到哈希表中。
	lpszKey：带插入关键字，lpszHashType：查找位置用哈希函数类型，lpszHashAType、lpszHashBType：校验用哈希函数类型
*/
bool HashAlgorithm::InsertIntoHashTable(char* lpszKey, const char* lpszHashType, const char* lpszHashAType, const char* lpszHashBType
	/* = BKDRHash、APHash、DJBHash、JSHash、RSHash、SDBMHash、PJWHash 、ELFHash */)
{
	HashTable* pSearch = GetFromHashTable(lpszKey, lpszHashType, lpszHashAType, lpszHashBType);
	if (pSearch != NULL)
	{
		return false;
	}

	unsigned int unHash = HashFunction(lpszKey, lpszHashType);
	unsigned int unHashA = HashFunction(lpszKey, lpszHashAType);
	unsigned int unHashB = HashFunction(lpszKey, lpszHashBType);
	unsigned int unIndex = unHash % m_HashTableLength;

	if (m_HashTable[unIndex].m_bIsExist)
	{
		HashTable* pCurrent = &m_HashTable[unIndex];
		while (pCurrent->m_pNext != NULL)
		{
			pCurrent = pCurrent->m_pNext;
		}
		pCurrent->m_pNext = new HashTable();

		if (pCurrent->m_pNext == NULL)
		{
			return false;
		}

		pCurrent->m_pNext->m_bIsExist = true;
		strcpy(pCurrent->m_pNext->m_chKey, lpszKey);
		pCurrent->m_pNext->m_unHashA = unHashA;
		pCurrent->m_pNext->m_unHashB = unHashB;
	}
	else
	{
		m_HashTable[unIndex].m_bIsExist = true;
		strcpy(m_HashTable[unIndex].m_chKey, lpszKey);
		m_HashTable[unIndex].m_unHashA = unHashA;
		m_HashTable[unIndex].m_unHashB = unHashB;
	}
	return true;
}

/*
	返回冲突的桶的个数。
*/
int HashAlgorithm::GetSumOfCollisionalBuckets()
{
	int nCount = 0;
	HashTable* pCurrent = NULL;
	for (int i = 0; i < m_HashTableLength; i++)
	{
		pCurrent = &m_HashTable[i];
		if (pCurrent->m_bIsExist&&pCurrent->m_pNext != NULL)
		{
			nCount++;
		}
	}
	return nCount;
}

/*
	返回最长的链表的长度。
*/
int HashAlgorithm::GetLongestLengthOfLinkList()
{
	int nMax = 0;
	int nLength = 0;
	HashTable* pCurrent = NULL;
	for (int i = 0; i < m_HashTableLength; i++)
	{
		nLength = 0;
		pCurrent = &m_HashTable[i];
		while (pCurrent->m_bIsExist&&pCurrent->m_pNext != NULL)
		{
			nLength++;
			pCurrent = pCurrent->m_pNext;
		}
		if (nLength>nMax)
		{
			nMax = nLength;
		}
	}
	return nMax;
}

/*
	返回链表的平均长度。
*/
double HashAlgorithm::GetAverageLengthOfLinkList()
{
	int nSum = 0;
	int nLength = 0;
	int nCount = 0;
	HashTable* pCurrent = NULL;
	for (int i = 0; i < m_HashTableLength; i++)
	{
		nLength = 0;
		pCurrent = &m_HashTable[i];
		if (pCurrent->m_bIsExist&&pCurrent->m_pNext != NULL)
		{
			nCount++;
		}
		while (pCurrent->m_bIsExist&&pCurrent->m_pNext != NULL)
		{
			nLength++;
			pCurrent = pCurrent->m_pNext;
		}
		nSum += nLength;
	}
	return (nSum*1.0) / (nCount*1.0);
}

/*
	返回哈希表桶的使用率。
*/
double HashAlgorithm::GetUtilizationRateOfBuckets()
{
	int nUsed = GetSumOfCollisionalBuckets();
	return (nUsed*1.0) / (m_HashTableLength*1.0);
}

