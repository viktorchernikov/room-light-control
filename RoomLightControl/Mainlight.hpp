#include "Arduino.h"
#include "TinyIRSender.hpp"


struct MainlightAction {
	char key;
	byte value;
	String name;
};

class Mainlight
{
	public:
		static MainlightAction actions[];
		static byte necAddress;
		static bool tryGetAction(char key, MainlightAction* result);
		static byte sendAction(MainlightAction cmd);
	Mainlight() = delete;
};


MainlightAction Mainlight::actions[] = {
	{'P', 0x8, String("Power ON/OFF")},
	{'C', 0x12, String("Temperature - Colder")},
	{'W', 0x5C, String("Temperature - Warmer")},
	{'U', 0x9, String("Brightness - Up")},
	{'D', 0xC, String("Brightness - Down")},
	{'J', 0x43, String("Mode - Job")},
	{'R', 0x44, String("Mode - Reading")},
	{'E', 0x45, String("Mode - Evening")},
	{'L', 0x46, String("Mode - Lunch")}
};
byte Mainlight::necAddress = 0x80;

bool Mainlight::tryGetAction(char key, MainlightAction* result)
{
	for (int i = 0; i < sizeof(actions) / sizeof(actions[0]); i++) 
  {
		if (actions[i].key == key) 
    {
			*result = actions[i];
			return true;
    }
	}
	return false;
}
byte Mainlight::sendAction(MainlightAction cmd)
{
  // TODO: If command is not supported by the Mainlight, then return unknown code.
  // return RESCODE_UNKNOWN;
	sendNEC(IR_SEND_PIN, necAddress, cmd.value, 1);
  return RESCODE_SUCCESS;
}
