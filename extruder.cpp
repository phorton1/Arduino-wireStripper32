//--------------------------------------
// extruder.cpp
//--------------------------------------
// Extruder controlled by Nema17 stepper motor
// Note use of 4x MICROSTEPPING

#include "extruder.h"
#include "wireStripper.h"
#include <myIOTLog.h>


Extruder::Extruder(uint8_t step_pin, uint8_t dir_pin, uint8_t enable_pin) :
	m_stepper(1,step_pin,dir_pin)		// AccelStepper::DRIVER
{
	m_stepper.setEnablePin(enable_pin);
	m_stepper.setPinsInverted(false,false,true);
		// dir, step, enable
}


void Extruder::begin()
{
	LOGU("Extruder::begin()");

	m_stepper.disableOutputs();
	m_stepper.setAcceleration(wire_stripper->_ext_accel);
	m_target_pos = 0;

	// debugging

	float mm_per_rev = 2 * 3.1415926 * wire_stripper->_ext_radius;		// 20.828758938
	LOGV("MM_PER_REV = %0.6f",mm_per_rev);
		// 20.828758938 arduino(20.828758)
	float mm_per_step = mm_per_rev / wire_stripper->_ext_rev_steps;
	LOGV("MM_PER_STEP = %0.6f",mm_per_step);
		// 0.10414379469 arduino(0.104144)
	float steps_per_mm = 1 / mm_per_step;
	LOGV("STEPS_PER_MM = %0.6f",steps_per_mm);
		// 9.602108344300816 arduino(9.602109)
}


void Extruder::stop()
{
	LOGD("Extruder::stop()");
	m_stepper.stop();
	m_stepper.disableOutputs();
	m_target_pos = 0;
}


bool Extruder::busy()
{
	bool running = m_stepper.run();
	if (m_target_pos && !running)
	{
		stop();
		running = 0;
	}
	return running;
}



void Extruder::move(float mm, int speed)
{
	float mm_per_rev = 2 * 3.1415926 * wire_stripper->_ext_radius;
	float revs = mm / mm_per_rev;
	revs *= wire_stripper->_ext_calib;

	float steps = revs * wire_stripper->_ext_rev_steps;
	uint32_t i_steps = steps;
	LOGD("Extruder:move(%0.3f) steps=%ld speed=%d",mm,i_steps,speed);
	m_stepper.setMaxSpeed(speed);
	m_stepper.setCurrentPosition(0);
	m_stepper.enableOutputs();
	m_stepper.moveTo(i_steps);
	m_target_pos = i_steps;
}
