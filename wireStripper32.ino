//-----------------------------------
// wireStripper32.ino
//-----------------------------------

#include "wireStripper.h"
#include <myIOTLog.h>


//--------------------------------
// main
//--------------------------------


void setup()
{
    Serial.begin(921600);
    delay(1000);

    wireStripper::setDeviceType(WIRE_STRIPPER);
    wireStripper::setDeviceVersion(WIRE_STRIPPER_VERSION);
    wireStripper::setDeviceUrl(WIRE_STRIPPER_URL);

    LOGU("");
    LOGU("wireStripper.ino setup() started on core(%d)",xPortGetCoreID());

    wire_stripper = new wireStripper();
    wire_stripper->setup();

    LOGU("wireStripper.ino setup() finished",0);
}



void loop()
{
    wire_stripper->loop();
}

