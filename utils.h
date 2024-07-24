//--------------------------------------
// extruder.h
//--------------------------------------
// extruder controlled by Nema17 stepper motor

#pragma once

#include <AccelStepper.h>

#define EXTRUDER_EEPROM_BASE			10

class Extruder
{
public:

	Extruder(uint8_t step_pin, uint8_t dir_pin, uint8_t enable_pin);

	void begin();

	bool busy();

	void move(long hundreths, int speed);

	void stop();

	void setCalibration(long calib_hundreths);


private:

	AccelStepper m_stepper;

	float m_calib;

	long m_target_pos;

};
