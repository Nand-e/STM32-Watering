#include "WHolder.h"


WHolder::WHolder()
{
	for (uint8_t i = 0; i < MAXW; i++) {
		widgets[i] = NULL;
	}
	wnumbers = 0; 
}


void WHolder::addWidget(Widget * wid, ButtonHandler * handler) {
	if ( handler != NULL ) wid->setHandler( handler );
	if (wnumbers < MAXW) {
		widgets[wnumbers] =  wid;
		wnumbers++;
		if (wnumbers < MAXW ) {
			widgets[wnumbers] = NULL;
		}
	}
	else {
		// error 
	}
}

void WHolder::updateWs(uint16_t x, uint16_t y, uint16_t z) {
	uint8_t i = 0; 
	while (widgets[i] != NULL && i < MAXW) {
		widgets[i]->update(x, y, z);
		 i ++;
	}
}

void WHolder::redrawWs() {
	uint8_t i = 0;
	while (widgets[i] != NULL && i < MAXW) {
		widgets[i]->reDraw();
		  i++;
	}
}


WHolder::~WHolder()
{
}
