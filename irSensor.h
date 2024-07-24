//--------------------------------------
// ir.h
//--------------------------------------
// simple IR detector

#pragma once

#define NUM_IR_SAMPLES	6

class irSensor
{
public:

	irSensor(int pin) { m_pin = pin; }
		// must be an analog pin

	void begin();
	
	bool sense();

	int  getValue()		  { return m_value; }
	bool aboveThreshold() { return m_above; };
		// returns value without polling


private:

	int m_pin;
	int m_value;
	bool m_above;
	
	int m_buf[NUM_IR_SAMPLES];
	int m_cur;
	int m_buf_value;

};
