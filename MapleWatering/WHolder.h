#pragma once

#include "widget.h"
#include "wButton.h"

#define MAXW 15


class WHolder
{
public:
	WHolder();
	~WHolder();
	void addWidget( Widget * wid, ButtonHandler * handler = NULL);
	void updateWs(uint16_t x, uint16_t y, uint16_t z);
	void redrawWs();

private:
	Widget * widgets[MAXW];
	uint8_t wnumbers;

};

