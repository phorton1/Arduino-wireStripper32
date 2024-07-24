//--------------------------------------
// ir.h
//--------------------------------------
// simple IR detector

#include "irSensor.h";
#include "wireStripper.h"
#include <myIOTLog.h>


void irSensor::begin()
{
	m_value = 0;
	m_above = false;
	m_cur = 0;
	m_buf_value = 0;
	memset(m_buf,0,NUM_IR_SAMPLES * sizeof(int));

	pinMode(m_pin,INPUT);

	int val = analogRead(m_pin);
	delay(1);

	for (m_cur=0; m_cur<NUM_IR_SAMPLES; m_cur++)
	{
		val = analogRead(m_pin);
		m_buf[m_cur] = val;
		m_buf_value += val;
		delay(1);
	}
	m_cur = 0;
	m_value = m_buf_value / NUM_IR_SAMPLES;
	m_above = m_value > wire_stripper->_ir_thresh ? 1 : 0;
	LOGU("IR initial(%d) thresh(%d)",m_value,wire_stripper->_ir_thresh);
}



bool irSensor::sense()
{
	m_buf_value -= m_buf[m_cur];
	volatile int val = analogRead(m_pin);
	delayMicroseconds(100);
	val = analogRead(m_pin);
	m_buf_value += val;
	m_buf[m_cur] = val;
	m_cur++;
	if (m_cur == NUM_IR_SAMPLES)
		m_cur = 0;

	m_value = m_buf_value / NUM_IR_SAMPLES;
	m_above = m_value > wire_stripper->_ir_thresh ? 1 : 0;
	return m_above;
}
