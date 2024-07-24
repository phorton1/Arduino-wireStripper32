//--------------------------------------
// cutter.h
//--------------------------------------
// wire Cutter controlled by servo

#include "cutter.h"
#include "wireStripper.h"
#include <myIOTLog.h>


int getCutDegrees(int pos)
{
	switch (pos)
	{
		case CUTTER_OPEN : return wire_stripper->_cut_open_deg;
		case CUTTER_GRIP : return wire_stripper->_cut_grip_deg;
		case CUTTER_TRIM : return wire_stripper->_cut_trim_deg;
		case CUTTER_CUT  : return wire_stripper->_cut_cut_deg;
		case CUTTER_USER : return wire_stripper->_cut_user_deg;
	}
	return 0;
}



Cutter::Cutter(uint8_t pin) :
	m_servo()
{
	m_pin = pin;
	m_move_time = 0;
	m_pos = 0;
	m_angle = 0;
	m_attached = 0;
	m_idle_time = 0;
}


void Cutter::begin()
{
	LOGU("Cutter::begin()");
	move(CUTTER_OPEN);
}


bool Cutter::busy()
{
	uint32_t now = millis();
	if (m_move_time)
	{
		m_idle_time = now;
		if (now > m_move_time)
		{
			LOGD("cutter::stop()");
			m_move_time = 0;
			m_angle = getCutDegrees(m_pos);
		}
	}
	else if (m_attached && m_pos == CUTTER_OPEN &&
			 now > m_idle_time + wire_stripper->_cut_detach_ms)
	{
		m_attached = 0;
		m_servo.detach();
		LOGD("cutter::detach()");
	}

	return m_move_time ? 1 : 0;
}


void Cutter::move(int pos)
{
	int angle = getCutDegrees(pos);
	int degrees = abs(m_angle - angle);
	LOGD("Cutter:move pos(%d) angle(%d) degrees(%d)",pos,angle,degrees);

	uint32_t now = millis();
	uint32_t delay =
		wire_stripper->_cut_min_ms +
		degrees * wire_stripper->_cut_ms_per_deg;

	m_move_time = now + delay;
	m_attached = true;
	m_pos = pos;

	m_servo.attach(m_pin);
	m_servo.write(angle);
}


const char *Cutter::getStatusStr()
{
	const char *pos_name =
		m_pos == CUTTER_USER ? "USER" :
		m_pos == CUTTER_CUT  ? "CUT" :
		m_pos == CUTTER_TRIM ? "TRIM" :
		m_pos == CUTTER_GRIP ? "GRIP" :
		"OPEN";

	static char buf[32];
	sprintf(buf,"%s - %d degrees",pos_name,m_angle);
	return buf;
}
