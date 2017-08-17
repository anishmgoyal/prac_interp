#include "Main.h"

#include "Data.h"

namespace Prac
{

	void destroyData(Data *d)
	{
		if (d == NULL)
		{
			return;
		}

		prepareDataForChange(d);

		delete d;
	}

	Data *cloneData(Data *d)
	{
		if (d == NULL)
		{
			return NULL;
		}

		Data *ret = new Data();
		ret->choice = d->choice;

		std::map<std::string, DataUnion> *map;
		const std::string *str;

		switch (d->choice)
		{
		case dcChar:
			ret->data.asCharacter = d->data.asCharacter;
			break;
		case dcInt:
			ret->data.asInteger = d->data.asInteger;
			break;
		case dcMap:
			map = new std::map<std::string, DataUnion>(*(d->data.asMap));
			ret->data.asMap = map;
			break;
		case dcNum:
			ret->data.asNumber = d->data.asNumber;
			break;
		case dcStr:
			str = new std::string(*(d->data.asString));
			ret->data.asString = str;
			break;
		case dcBool:
			ret->data.asBoolean = d->data.asBoolean;
			break;
		}
		return ret;
	}

	void prepareDataForChange(Data *d)
	{
		switch (d->choice)
		{
		case dcMap:
			delete d->data.asMap;
			break;
		case dcStr:
			delete d->data.asString;
			break;
		}
	}

	void setDataChar(Data *d, char c)
	{
		prepareDataForChange(d);
		d->choice = dcChar;
		d->data.asCharacter = c;
	}

	void setDataInt(Data *d, long long i)
	{
		prepareDataForChange(d);
		d->choice = dcInt;
		d->data.asInteger = i;
	}

	void setDataMap(Data *d, std::map<std::string, DataUnion> *m)
	{
		prepareDataForChange(d);
		d->choice = dcMap;
		d->data.asMap = m;
	}

	void setDataNum(Data *d, double dd)
	{
		prepareDataForChange(d);
		d->choice = dcNum;
		d->data.asNumber = dd;
	}

	void setDataStr(Data *d, const std::string *s)
	{
		prepareDataForChange(d);
		d->choice = dcStr;
		d->data.asString = s;
	}

	void setDataBool(Data *d, bool b)
	{
		prepareDataForChange(d);
		d->choice = dcBool;
		d->data.asBoolean = b;
	}
}