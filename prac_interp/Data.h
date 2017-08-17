#ifndef Data_H
#define Data_H

#include "Main.h"

#include <map>

namespace Prac
{

	union DataUnion {
		char								 asCharacter;
		unsigned long long					 asInteger;
		std::map<std::string, DataUnion>	*asMap;
		double								 asNumber;
		const std::string					*asString;
		bool								 asBoolean;
	};

	const unsigned char dcChar = 0;
	const unsigned char dcInt = 1;
	const unsigned char dcMap = 2;
	const unsigned char dcNum = 3;
	const unsigned char dcStr = 4;
	const unsigned char dcBool = 5;

	struct Data {
		DataUnion data;
		unsigned char choice;
	};

	void destroyData(Data *d);
	Data *cloneData(Data *d);
	
	void prepareDataForChange(Data *d);
	
	void setDataChar(Data *d, char c);
	void setDataInt(Data *d, long long i);
	void setDataMap(Data *d, std::map<std::string, DataUnion> *m);
	void setDataNum(Data *d, double dd);
	void setDataStr(Data *d, const std::string *s);
	void setDataBool(Data *d, bool b);

}

#endif