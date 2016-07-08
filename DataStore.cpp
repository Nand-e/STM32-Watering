#include "DataStore.h"
#include <EEPROM\EEPROM.h>

/*
template < class T >
DataStore<T>::DataStore(uint16_t start, uint8_t maxdata ) :
	startAddres(start), 
	maxData(maxdata)
{
	lastData = 0;
}
*/
template < class T >
void DataStore<T>::pushBack(T data) {
	uint8_t length = sizeof(T);
	uint8_t * p = (uint8_t *) data;

	for (uint8_t i = 0; i < length; i++) {
		EEPROM.write(startAddres + lastData, *p);
		p++;
	}
}

/*
template < class T >
DataStore<T>::~DataStore()
{
}
*/