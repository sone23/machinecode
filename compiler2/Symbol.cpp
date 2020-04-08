#include "Symbol.h"

bool SymbolTableClass::Exists(const std::string& s)
{
	for (int i = 0; i < mTable.size(); i++) {
		if (s == mTable[i].mLabel)
			return true;
	}
	return false;
}

void SymbolTableClass::AddEntry(const std::string& s)
{
	if (Exists(s)) {
		exit(1);
	}
	mTable.push_back({ s, 0 });
}

int SymbolTableClass::GetValue(const std::string& s)
{
	if (!Exists(s)) {
		cout << s << " Not found in table" << endl;
		exit(0);
	}
	int value = 0;
	for (int counter = 0; counter < mTable.size(); ++counter)
	{
		if (mTable[counter].mLabel == s)
			value = mTable[counter].mValue;
	}
	return value;
}

void SymbolTableClass::SetValue(const std::string& s, int v)
{
	if (!Exists(s)) {
		exit(1);
	}
	int index = GetIndex(s);
	mTable[index].mValue = v;

}

int SymbolTableClass::GetIndex(const std::string& s)
{
	if (!Exists(s)) {
		return -1;
	}
	int index;
	for (int counter = 0; counter < mTable.size(); counter++)
	{
		if (mTable[counter].mLabel == s)
			index = counter;
	}
	return index;

}

int SymbolTableClass::GetCount()
{
	int count = 0;
	for (int index = 0; index < mTable.size(); index++)
	{
		count++;
	}
	return count;
}
