//--------------------------------------
// extruder.h
//--------------------------------------
// extruder controlled by Nema17 stepper motor

#pragma once

#include <AccelStepper.h>


class Extruder
{
public:

	Extruder(uint8_t step_pin, uint8_t dir_pin, uint8_t enable_pin);

	void begin();

	bool busy();

	void move(float mm, int speed);

	void stop();
	

private:

	AccelStepper m_stepper;

	volatile long m_target_pos;

};


