//--------------------------------------
// cutter.h
//--------------------------------------
// wire cutter controlled by servo

#pragma once


#include <ESP32Servo.h>



class Cutter
{
public:

	Cutter(uint8_t pin);

	void begin();

	bool busy();

	void move(int pos);

	int getPosition()	{ return m_pos; }

	const char *getStatusStr();


private:

	Servo m_servo;
	
	uint8_t m_pin;

	int m_pos;
	int m_angle;
	
	bool m_attached;
	uint32_t m_move_time;
	uint32_t m_idle_time;

};
