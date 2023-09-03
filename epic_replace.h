#pragma once

#include <string.h>
#include <stdlib.h>

typedef unsigned int uint;

uint clamp(uint in, uint min, uint max)
{
	if (in < min) return min;
	if (in > max) return max;
	return in;
}

char* strsub(char* source, int startPos, int endPos)
{
	int length = clamp((endPos - startPos) + 1, 0, strlen(source));

	char* newString = new char[length];
	memcpy(newString, &source[startPos], length);
	newString[length - 1] = '\0';

	return newString;
}

uint strcount(char* sourceString, char* oldString)
{
	uint sourceLength = strlen(sourceString);
	uint oldLength = strlen(oldString);

	uint count = 0;

	char oldFirst = oldString[0];
	for (int i = 0; i < sourceLength; i++)
	{
		if (sourceString[i] != oldFirst) continue;

		char* test = strsub(sourceString, i, i + oldLength);
		if (strcmp(test, oldString) == 0)
			count++;
	}

	return count;
}

char* strappend(char* string, char character)
{
	uint length = strlen(string);

	char* newString = new char[length + 2];
	strcpy_s(newString, length + 1, string);

	newString[length] = character;
	newString[length + 1] = '\0';

	return newString;
}

char* strreplace(char* sourceString, char* oldString, char* newString)
{
	uint sourceLength = strlen(sourceString);
	uint oldLength = strlen(oldString);
	uint newLength = strlen(newString);

	uint occurences = strcount(sourceString, oldString);
	int lengthDifference = abs((int)oldLength - (int)newLength);
	int lengthOffset = ((lengthDifference * occurences) + 1);

	uint finalLength = 0;
	if (newLength < oldLength)
		finalLength = sourceLength - lengthOffset;
	else
		finalLength = sourceLength + lengthOffset;

	char* finalString = new char[1];
	finalString[0] = '\0';

	char oldFirst = oldString[0];
	for (int i = 0; i < sourceLength; i++)
	{
		if (sourceString[i] != oldFirst)
		{
			finalString = strappend(finalString, sourceString[i]);
			continue;
		}

		char* test = strsub(sourceString, i, i + oldLength);
		if (strcmp(test, oldString) == 0)
		{
			strcat_s(finalString, finalLength, newString);
			i += oldLength - 1;
		}
		else
			finalString = strappend(finalString, sourceString[i]);
	}

	return finalString;
}

char* strreplace(const char* sourceString, const char* oldString, const char* newString)
{
	return strreplace(_strdup(sourceString), _strdup(oldString), _strdup(newString));
}