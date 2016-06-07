#ifndef TFTBUTTON1
#define TFTBUTTON1

#include <stdint.h>
#include "TFTButton.h"

class Button1 : public Button {

public:
	Button1();
	Button1(uint16_t x0, uint16_t y0, uint16_t w0, uint16_t h0, uint8_t id, bool mirrored = false, uint16_t backC = 0);
	void updateGraphic();
private:	

};


#endif

