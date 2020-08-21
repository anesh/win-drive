#include "stringTools.h"



int forceNullTermination(char* string, unsigned int len)
{
	if(string[len] != 0)
		string[len] = 0;
	return 1;
}

unsigned int getStrLen(char* str, int includeTerminator, unsigned int maxLen)
{
	unsigned int i = 0;

	for(i = 0; i < maxLen; i++)
		if(str[i] == 0)
			break;

	return (includeTerminator ? i + 1: i);
}

int getParam(char* source, char* out, unsigned int outSize, unsigned int param, char clipChar) 
{
	
	unsigned int clipCount  = 0;
	unsigned int i          = 0;
	int          len        = strlen(source);

	zeroMemory((char*)out, outSize);

	
	for(i = 0; i < len; i++) 
	{
		if(source[i] == clipChar)
			clipCount++;

		if(clipCount == param)
		{
			int bufCount = 0;
			if(source[i] == clipChar)
				i++;

			for(; i < len; i++)
				if(source[i] == clipChar)
					break;
				else
				{
					out[bufCount] = source[i];
					bufCount++;
				}	

			break;
		}
	}
	return 1;
}

int   strIsEqual(char* source, char* source2)
{
	unsigned int i;
	unsigned int sourceLen;

	sourceLen = getStrLen(source, 0, 100);

	if(sourceLen != getStrLen(source2, 0, 100))
		return 0;

	for(i = 0; i < sourceLen; i++)
	{
		if(source[i] != source2[i])
			return 0;
	}

	return 1;
}