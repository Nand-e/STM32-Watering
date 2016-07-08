#pragma once

#include <Arduino.h>

template < class T >
class DataStore
{
public:
	DataStore(uint16_t start, uint8_t maxdata) : 
		startAddres(start),
		maxData(maxdata)
	{
		lastData = 0;
	}

	~DataStore() {};
	void pushBack(T data);
	T getData(uint8_t idex);
		

private:
	uint16_t startAddres;
	uint8_t maxData;
	uint8_t lastData;
};

