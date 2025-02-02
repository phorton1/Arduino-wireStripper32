//--------------------------------------
// wireStripper.cpp
//--------------------------------------

#include "wireStripper.h"
#include <myIOTLog.h>
#include "cutter.h"
#include "extruder.h"
#include "irSensor.h"
#include <Adafruit_NeoPixel.h>


#define ONBOARD_LED 2
#define SERVO_PIN   26
#define ENABLE_PIN	32
#define STEP_PIN	25
#define DIR_PIN 	33

#define IR_PIN		35	
	// these are all the ESP32 analog capable pins
	// ADC1(32-36)
	// ADC2(0,2,4,12,13,14,15,25,26,27)  is not available when Wifi is turned on

#define BUTTON_PIN	22
#define LED_PIN		23

#define MY_LED_BLACK    0x000000
#define MY_LED_RED      0x440000
#define MY_LED_GREEN    0x003300
#define MY_LED_BLUE     0x000044
#define MY_LED_CYAN     0x003333
#define MY_LED_YELLOW   0x333300
#define MY_LED_MAGENTA  0x330033
#define MY_LED_WHITE    0x000044

#define STATE_NONE			0
#define STATE_START			1
#define STATE_ADVANCE1		2
#define STATE_TRIM_CUT1		3
#define STATE_TRIM_GRIP1	4
#define STATE_PULL1			5
#define STATE_OPEN1			6
#define STATE_ADVANCE2		7
#define STATE_TRIM_CUT2		8
#define STATE_GRIP2			9
#define STATE_PULL2			10
#define STATE_OPEN2			11
#define STATE_ADVANCE3		12
#define STATE_CUT			13
#define STATE_DONE			14
#define STATE_UNLOAD		15
#define STATE_UNLOADING		16
#define STATE_LOAD			17
#define STATE_LOADING		18

// factory reset defaults

#define DEFAULT_UNLOAD_LEN			70.0		// how far to unload
#define DEFAULT_LOAD_LEN			400.0		// how far to go until failing trying to load
#define DEFAULT_LOAD_DIST			11.0		// post wire-sense how far to cutter
#define DEFAULT_MOVE_DIST			10.0
#define DEFAULT_END_LENGTH			8.0
#define DEFAULT_HOLES				4.0
#define DEFAULT_LENGTH    			(DEFAULT_HOLES * 2.54)
#define	DEFAULT_PULL_MAX			100.0
#define DEFAULT_PULL_EXTRA			4.0
#define DEFAULT_EXT_SPEED			3000
#define DEFAULT_PULL_COMPENSATE		2.0
#define DEFAULT_CUT_OPEN_DEG		10
#define DEFAULT_CUT_GRIP_DEG		145
#define DEFAULT_CUT_TRIM_DEG		157
#define DEFAULT_CUT_CUT_DEG			170
#define DEFAULT_CUT_USER_DEG		20
#define DEFAULT_CUT_MIN_MS			100
#define DEFAULT_CUT_MS_PER_DEG		4
#define DEFAULT_CUT_DETACH_MS		1000
#define DEFAULT_IR_THRESH			3000
#define DEFAULT_EXT_SPEED			3000
#define DEFAULT_EXT_CALIB			1.0
#define DEFAULT_EXT_RADIUS			3.3813
#define DEFAULT_EXT_REV_STEPS		800.0
#define DEFAULT_EXT_ACCEL			100000
#define DEFAULT_DEBUG_PAUSE			0


static valueIdType dash_items[] = {
	ID_STATUS,
    ID_STOP,
    ID_LOAD,
    ID_UNLOAD,
    ID_QTY,
    ID_GO,
    ID_END1,
    ID_LENGTH,
    ID_HOLES,
    ID_END2,
    ID_CUT,
	ID_MOVE,
	ID_MOVE_DIST,
    ID_REBOOT,
    0
};

// what shows up on the "device" UI tab

static valueIdType config_items[] = {
    ID_CUT_STATUS,
    ID_CUT_POS,
    ID_CUT_OPEN,
    ID_CUT_GRIP,
    ID_CUT_TRIM,
    ID_CUT_CUT,
    ID_CUT_USER,
	ID_DEBUG_PAUSE,
	ID_UNLOAD_LEN,
    ID_LOAD_LEN,
    ID_LOAD_DIST,
    ID_PULL_MAX,
    ID_PULL_EXTRA,
    ID_PULL_COMPENSATE,
    ID_CUT_MIN_MS,
    ID_CUT_MS_PER_DEG,
    ID_CUT_DETACH_MS,
    ID_IR_THRESH,
    ID_EXT_SPEED,
    ID_EXT_CALIB,
    ID_EXT_RADIUS,
    ID_EXT_REV_STEPS,
    ID_EXT_ACCEL,
    0
};


//-------------------------------------------
// value definitions
//-------------------------------------------

#define MAX_ANGLE	180

static enumValue cutPositions[] = {
    "Open",
    "Grip",
    "Trim",
	"Cut",
	"User",
    0};


// value descriptors for bilgeAlaram

#define disabled_busy 	"not_if_busy"


const valDescriptor wireStripper::m_wire_stripper_values[] =
{
    {ID_DEVICE_NAME,	VALUE_TYPE_STRING,   VALUE_STORE_PREF,     VALUE_STYLE_REQUIRED,   NULL,   	NULL,   WIRE_STRIPPER },        // override base class element

	// commands

    {ID_STOP,			VALUE_TYPE_COMMAND,	VALUE_STORE_SUB,		VALUE_STYLE_NONE,       NULL,	(void *) stop },	// range,	extra_class
	{ID_LOAD,			VALUE_TYPE_COMMAND,	VALUE_STORE_SUB,		VALUE_STYLE_NONE,       NULL,	(void *) load, 		NULL,		disabled_busy },
    {ID_UNLOAD,			VALUE_TYPE_COMMAND,	VALUE_STORE_SUB,		VALUE_STYLE_NONE,       NULL,	(void *) unload, 	NULL,		disabled_busy },
    {ID_GO,				VALUE_TYPE_COMMAND,	VALUE_STORE_SUB,		VALUE_STYLE_NONE,       NULL,	(void *) execute, 	NULL,		disabled_busy },
    {ID_CUT,			VALUE_TYPE_COMMAND,	VALUE_STORE_SUB,		VALUE_STYLE_NONE,       NULL,	(void *) docut, 	NULL,		disabled_busy },
	{ID_MOVE,			VALUE_TYPE_COMMAND,	VALUE_STORE_SUB,		VALUE_STYLE_NONE,       NULL,	(void *) domove, 	NULL,		disabled_busy },

	// readonly status fields

    {ID_STATUS,			VALUE_TYPE_STRING,	VALUE_STORE_TOPIC,    	VALUE_STYLE_READONLY,   (void *) &_status },
	{ID_CUT_STATUS,	    VALUE_TYPE_STRING,	VALUE_STORE_TOPIC,		VALUE_STYLE_READONLY,	(void *) &_cut_status },

	// values

	{ID_END1,		    VALUE_TYPE_FLOAT,	VALUE_STORE_PREF,		VALUE_STYLE_NONE,		(void *) &_end1,			NULL,						{ .float_range	= {DEFAULT_END_LENGTH, 		0, 100}},		disabled_busy },
	{ID_LENGTH,	    	VALUE_TYPE_FLOAT,	VALUE_STORE_PREF,		VALUE_STYLE_NONE,		(void *) &_length,			(void *) onLengthChanged, 	{ .float_range	= {DEFAULT_LENGTH, 			0, 2540}},		disabled_busy },
	{ID_HOLES,		    VALUE_TYPE_FLOAT,	VALUE_STORE_PREF,		VALUE_STYLE_NONE,		(void *) &_holes,			(void *) onHolesChanged,	{ .float_range	= {DEFAULT_HOLES, 			0, 1000}},		disabled_busy },
	{ID_END2,		    VALUE_TYPE_FLOAT,	VALUE_STORE_PREF,		VALUE_STYLE_NONE,		(void *) &_end2,			NULL,						{ .float_range	= {DEFAULT_END_LENGTH, 		0, 100}},		disabled_busy },
	{ID_QTY,		    VALUE_TYPE_INT,		VALUE_STORE_TOPIC,		VALUE_STYLE_NONE,		(void *) &_qty,				NULL,						{ .int_range	= {1, 						1, 9999}},		disabled_busy },
	{ID_UNLOAD_LEN,    	VALUE_TYPE_FLOAT,	VALUE_STORE_PREF,		VALUE_STYLE_NONE,		(void *) &_unload_len,		NULL,						{ .float_range	= {DEFAULT_UNLOAD_LEN, 		0, 1000}},		disabled_busy },
	{ID_LOAD_LEN,	    VALUE_TYPE_FLOAT,	VALUE_STORE_PREF,		VALUE_STYLE_NONE,		(void *) &_load_len,		NULL,						{ .float_range	= {DEFAULT_LOAD_LEN, 		0, 1000}},		disabled_busy },
	{ID_LOAD_DIST,	    VALUE_TYPE_FLOAT,	VALUE_STORE_PREF,		VALUE_STYLE_NONE,		(void *) &_load_dist,		NULL,						{ .float_range	= {DEFAULT_LOAD_DIST, 		0, 100}},		disabled_busy },
	{ID_MOVE_DIST,	    VALUE_TYPE_FLOAT,	VALUE_STORE_TOPIC,		VALUE_STYLE_NONE,		(void *) &_move_dist,		NULL,						{ .float_range	= {DEFAULT_MOVE_DIST, 		-1000, 1000}},	disabled_busy },
	{ID_PULL_MAX,		VALUE_TYPE_FLOAT,	VALUE_STORE_PREF,		VALUE_STYLE_NONE,		(void *) &_pull_max,		NULL,						{ .float_range	= {DEFAULT_PULL_MAX, 		0, 1000}},		disabled_busy },
	{ID_PULL_EXTRA,		VALUE_TYPE_FLOAT,	VALUE_STORE_PREF,		VALUE_STYLE_NONE,		(void *) &_pull_extra,		NULL,						{ .float_range	= {DEFAULT_PULL_EXTRA, 		0, 10}},		disabled_busy },
	{ID_PULL_COMPENSATE,VALUE_TYPE_FLOAT,	VALUE_STORE_PREF,		VALUE_STYLE_NONE,		(void *) &_pull_compensate,	NULL,						{ .float_range	= {DEFAULT_PULL_COMPENSATE, 0, 10}},		disabled_busy },

	{ID_CUT_POS,		VALUE_TYPE_ENUM,	VALUE_STORE_TOPIC,		VALUE_STYLE_NONE,		(void *) &_cut_pos,			(void *) onCutPosChanged,	{ .enum_range 	= {0,						cutPositions}},	disabled_busy },
	{ID_CUT_OPEN,		VALUE_TYPE_INT,		VALUE_STORE_PREF,		VALUE_STYLE_NONE,		(void *) &_cut_open_deg,	(void *) onCutAngleChanged,	{ .int_range 	= {DEFAULT_CUT_OPEN_DEG, 	0, MAX_ANGLE}},	disabled_busy },
	{ID_CUT_GRIP,		VALUE_TYPE_INT,		VALUE_STORE_PREF,		VALUE_STYLE_NONE,		(void *) &_cut_grip_deg,	(void *) onCutAngleChanged,	{ .int_range 	= {DEFAULT_CUT_GRIP_DEG, 	0, MAX_ANGLE}},	disabled_busy },
	{ID_CUT_TRIM,		VALUE_TYPE_INT,		VALUE_STORE_PREF,		VALUE_STYLE_NONE,		(void *) &_cut_trim_deg,	(void *) onCutAngleChanged,	{ .int_range 	= {DEFAULT_CUT_TRIM_DEG, 	0, MAX_ANGLE}},	disabled_busy },
	{ID_CUT_CUT,		VALUE_TYPE_INT,		VALUE_STORE_PREF,		VALUE_STYLE_NONE,		(void *) &_cut_cut_deg,		(void *) onCutAngleChanged,	{ .int_range 	= {DEFAULT_CUT_CUT_DEG,  	0, MAX_ANGLE}},	disabled_busy },
	{ID_CUT_USER,      	VALUE_TYPE_INT,		VALUE_STORE_PREF,		VALUE_STYLE_NONE,		(void *) &_cut_user_deg,	(void *) onCutAngleChanged,	{ .int_range 	= {DEFAULT_CUT_USER_DEG, 	0, MAX_ANGLE}},	disabled_busy },
                                                                                                                                                                                                            
	{ID_CUT_MIN_MS,  	VALUE_TYPE_INT,		VALUE_STORE_PREF,		VALUE_STYLE_NONE,		(void *) &_cut_min_ms,		NULL,						{ .int_range 	= {DEFAULT_CUT_MIN_MS,   	0, 1000}},		disabled_busy },
	{ID_CUT_MS_PER_DEG, VALUE_TYPE_INT,		VALUE_STORE_PREF,		VALUE_STYLE_NONE,		(void *) &_cut_ms_per_deg,	NULL,						{ .int_range 	= {DEFAULT_CUT_MS_PER_DEG, 	0, 999999}},	disabled_busy },
	{ID_CUT_DETACH_MS, 	VALUE_TYPE_INT,		VALUE_STORE_PREF,		VALUE_STYLE_NONE,		(void *) &_cut_detach_ms,	NULL,						{ .int_range 	= {DEFAULT_CUT_DETACH_MS, 	0, 999999}},	disabled_busy },
	{ID_IR_THRESH,     	VALUE_TYPE_INT,		VALUE_STORE_PREF,		VALUE_STYLE_NONE,		(void *) &_ir_thresh,		NULL,						{ .int_range 	= {DEFAULT_IR_THRESH, 		0, 4096}},		disabled_busy },
	{ID_EXT_SPEED,     	VALUE_TYPE_INT,		VALUE_STORE_PREF,		VALUE_STYLE_NONE,		(void *) &_ext_speed,		NULL,						{ .int_range 	= {DEFAULT_EXT_SPEED, 		0, 10000}},		disabled_busy },
	{ID_EXT_CALIB,     	VALUE_TYPE_FLOAT,	VALUE_STORE_PREF,		VALUE_STYLE_NONE,		(void *) &_ext_calib,		NULL,						{ .float_range 	= {DEFAULT_EXT_CALIB, 		0, 2.0}},		disabled_busy },
	{ID_EXT_RADIUS,    	VALUE_TYPE_FLOAT,	VALUE_STORE_PREF,		VALUE_STYLE_NONE,		(void *) &_ext_radius,		NULL,						{ .float_range 	= {DEFAULT_EXT_RADIUS, 		0, 100}},		disabled_busy },
	{ID_EXT_REV_STEPS, 	VALUE_TYPE_FLOAT,	VALUE_STORE_PREF,		VALUE_STYLE_NONE,		(void *) &_ext_rev_steps,	NULL,						{ .float_range 	= {DEFAULT_EXT_REV_STEPS, 	0, 4000}},		disabled_busy },
	{ID_EXT_ACCEL,     	VALUE_TYPE_INT,		VALUE_STORE_PREF,		VALUE_STYLE_NONE,		(void *) &_ext_accel,		NULL,						{ .int_range 	= {DEFAULT_EXT_ACCEL, 		0, 10000000}},	disabled_busy },
	{ID_DEBUG_PAUSE,    VALUE_TYPE_INT,		VALUE_STORE_PREF,		VALUE_STYLE_NONE,		(void *) &_debug_pause,		NULL,						{ .int_range 	= {DEFAULT_DEBUG_PAUSE, 	0, 10000}}		},

};


#define NUM_WIRE_STRIPPER_VALUES (sizeof(m_wire_stripper_values)/sizeof(valDescriptor))



// static member variable declarations

String	wireStripper::_status;
float	wireStripper::_end1;
float	wireStripper::_length;
float	wireStripper::_holes;
float	wireStripper::_end2;
int		wireStripper::_qty;
float	wireStripper::_unload_len;
float	wireStripper::_load_len;
float	wireStripper::_load_dist;
float	wireStripper::_move_dist;
float 	wireStripper::_pull_max;
float 	wireStripper::_pull_extra;
float 	wireStripper::_pull_compensate;
String	wireStripper::_cut_status;
int		wireStripper::_cut_pos;		// enum
int		wireStripper::_cut_open_deg;
int		wireStripper::_cut_grip_deg;
int		wireStripper::_cut_trim_deg;
int		wireStripper::_cut_cut_deg;
int		wireStripper::_cut_user_deg;
int		wireStripper::_cut_min_ms;
int		wireStripper::_cut_ms_per_deg;
int 	wireStripper::_cut_detach_ms;
int		wireStripper::_ir_thresh;
int		wireStripper::_ext_speed;
float	wireStripper::_ext_calib;
float	wireStripper::_ext_radius;
float	wireStripper::_ext_rev_steps;
int		wireStripper::_ext_accel;
int		wireStripper::_debug_pause;


wireStripper *wire_stripper;



//===========================================
// static application specific variables
//===========================================

Cutter cutter(SERVO_PIN);
Extruder extruder(STEP_PIN, DIR_PIN, ENABLE_PIN);
irSensor ir_sensor(IR_PIN);
Adafruit_NeoPixel pixels(1,LED_PIN);


volatile int state = 0;
volatile bool cutter_busy = 0;
volatile bool extruder_busy = 0;
volatile bool any_state = 0;

volatile int quantity = 0;
volatile bool have_wire = 0;

volatile bool in_length_change = 0;
volatile int pending_cut = -1;
volatile float pending_move = 0.00;



//--------------------------------
// utilities
//--------------------------------

void setPixel(int color)
{
	static int pixel_color = 0;
	if (pixel_color != color)
	{
		pixel_color = color;
		pixels.setPixelColor(0,pixel_color);
		pixels.show();
	}
}

const char *stateStr()
{
	switch (state)
	{
		case STATE_NONE			: return "STATE_NONE";
		case STATE_START		: return "STATE_START";
		case STATE_ADVANCE1		: return "STATE_ADVANCE1";
		case STATE_TRIM_CUT1	: return "STATE_TRIM_CUT1";
		case STATE_TRIM_GRIP1	: return "STATE_TRIM_GRIP1";
		case STATE_PULL1		: return "STATE_PULL1";
		case STATE_OPEN1		: return "STATE_OPEN1";
		case STATE_ADVANCE2		: return "STATE_ADVANCE2";
		case STATE_TRIM_CUT2	: return "STATE_TRIM_CUT2";
		case STATE_GRIP2		: return "STATE_GRIP2";
		case STATE_PULL2		: return "STATE_PULL2";
		case STATE_OPEN2		: return "STATE_OPEN2";
		case STATE_ADVANCE3		: return "STATE_ADVANCE3";
		case STATE_CUT			: return "STATE_CUT";
		case STATE_DONE			: return "STATE_DONE";
		case STATE_UNLOAD       : return "STATE_UNLOAD";
		case STATE_UNLOADING    : return "STATE_UNLOAD";
		case STATE_LOAD   		: return "STATE_LOAD";
		case STATE_LOADING		: return "STATE_LOADING";
	}
	return "UNKNOWN_STATE!";
}



//--------------------------------
// implementation
//--------------------------------

wireStripper::wireStripper()
{
    wire_stripper = this;
    addValues(m_wire_stripper_values,NUM_WIRE_STRIPPER_VALUES);
    setTabLayouts(dash_items,config_items);
}


void wireStripper::setup()
{
    LOGD("wireStripper::setup(%s) started",getVersion());
    proc_entry();

	pinMode(BUTTON_PIN,INPUT_PULLUP);
    pinMode(ONBOARD_LED,OUTPUT);
	setPixel(MY_LED_MAGENTA);

    myIOTDevice::setup();

	cutter.begin();
	extruder.begin();
	ir_sensor.begin();

	setPixel(MY_LED_RED);

	LOGI("starting stateTask");
    xTaskCreatePinnedToCore(stateTask,
        "stateTask",
        8192,           // task stack
        NULL,           // param
        5,  	        // note that the priority is higher than one
        NULL,           // returned task handle
        ESP32_CORE_OTHER);

    proc_leave();
    LOGD("wireStripper::setup(%s) completed",getVersion());
}



void wireStripper::stateTask(void *param)
{
    delay(1200);
    LOGI("starting stateTask loop on core(%d)",xPortGetCoreID());
    delay(1200);
    while (1)
    {
		// vTaskDelay(1000 / portTICK_PERIOD_MS);
		vTaskDelay(1);
        wire_stripper->stateMachine();
    }
}



//--------------------------------
// commands
//--------------------------------

void wireStripper::stop()
{
	state = STATE_NONE;
	LOGI("STOP!");
	if (extruder_busy)
		extruder.stop();
	if (cutter.getPosition() != CUTTER_OPEN)
		cutter.move(CUTTER_OPEN);
	#if 0
		delay(500);
		if (cutter.getPosition() != CUTTER_CUT)
			cutter.move(CUTTER_CUT);
		delay(1000);
		if (cutter.getPosition() != CUTTER_OPEN)
			cutter.move(CUTTER_OPEN);
	#endif
}


void wireStripper::load()
{
	if (!any_state)
	{
		state = STATE_LOAD;
	}
}

void wireStripper::unload()
{
	if (!any_state)
	{
		state = STATE_UNLOAD;
	}
}

void wireStripper::execute()	// "go" command
{
	if (!any_state)
	{
		quantity = _qty;
		state = STATE_START;
	}
}

void wireStripper::docut()
{
	if (!any_state)
	{
		cutter.move(CUTTER_OPEN);
		delay(200);
		cutter.move(CUTTER_CUT);
		delay(700);
		cutter.move(CUTTER_OPEN);
	}
}

void wireStripper::domove()
{
	if (!any_state)
	{
		LOGD("domove(%0.03f,%d)",_move_dist,_ext_speed);
		extruder.move(_move_dist,_ext_speed);
	}
}


void wireStripper::onLengthChanged(const myIOTValue *value, float val)
{
	if (!in_length_change)
	{
		in_length_change = true;
		float holes = val / 2.54;
		wire_stripper->setFloat(ID_HOLES,holes);
		in_length_change = false;
	}
}

void wireStripper::onHolesChanged(const myIOTValue *value, float val)
{
	if (!in_length_change)
	{
		in_length_change = true;
		float length = val * 2.54;
		wire_stripper->setFloat(ID_LENGTH,length);
		in_length_change = false;

		// used to test myIOT disabled_classes string manipulation
		// will set or clear additional classes based on the number of holes

		#if 0
			static char hole_class[20];
			static bool hole_disabled[20];
			int hole = val;
			sprintf(hole_class,"hole_class%d",hole);
			hole_disabled[hole] = !hole_disabled[hole];
			wire_stripper->disableClass(hole_class,hole_disabled[hole]);
		#endif

	}
}

void wireStripper::onCutPosChanged(const myIOTValue *value, uint32_t val)
{
	if (!any_state)
		cutter.move(val);
}

void wireStripper::onCutAngleChanged(const myIOTValue *value, int val)
{
	if (!any_state)
	{
		int pos = -1;
		const char *id = value->getId();
		if (!strcmp(id,ID_CUT_OPEN))
			pos = CUTTER_OPEN;
		else if (!strcmp(id,ID_CUT_GRIP))
			pos = CUTTER_GRIP;
		else if (!strcmp(id,ID_CUT_TRIM))
			pos = CUTTER_TRIM;
		else if (!strcmp(id,ID_CUT_CUT))
			pos = CUTTER_CUT;
		else if (!strcmp(id,ID_CUT_USER))
			pos = CUTTER_USER;
		else
			LOGE("unknown cutter id: %s",id);
		if (pos != -1)
		{
			LOGV("onAngleChanged pos(%d) angle(%d)",pos,val);
			pending_cut = pos;
		}
	}
}



//--------------------------------
// stateMachine
//--------------------------------

void cutterMachine()
{
	static bool double_pull = 0;
	int speed = wire_stripper->_ext_speed;
	int extra = wire_stripper->_pull_extra;
	int compensate = wire_stripper->_pull_compensate;

	int pull_1 = wire_stripper->_end2;
	if (double_pull)
		pull_1 += wire_stripper->_end1;

	LOGV("%s",stateStr());
	if (wire_stripper->_debug_pause)
		delay(wire_stripper->_debug_pause);

	switch (state)
	{
		case STATE_START :
		{
			double_pull = wire_stripper->_length > wire_stripper->_pull_max ? 0 : 1;
			int num = wire_stripper->_qty - quantity + 1;
			LOGI("%sCUTTING(%d) of %d  (end1=%0.2f  length=%%0.2f  end2=%0.2f)",
				(double_pull?"DOUBLE ":""),
				 num,
				 wire_stripper->_qty,
				 wire_stripper->_end1,
				 wire_stripper->_length,
				 wire_stripper->_end2 );
			if (cutter.getPosition() != CUTTER_OPEN)
				cutter.move(CUTTER_OPEN);

			state++;
			break;
		}
		case STATE_ADVANCE1		:
			extruder.move(pull_1,speed);
			state++;
			break;
		case STATE_TRIM_CUT1	:
			cutter.move(CUTTER_TRIM);
			state++;
			break;
		case STATE_TRIM_GRIP1	:
			cutter.move(CUTTER_GRIP);
			state++;
			break;
		case STATE_PULL1		:
			extruder.move(-(pull_1 + extra),speed);
			state++;
			break;

		case STATE_OPEN1		:
			cutter.move(CUTTER_OPEN);
			state++;
			break;
		case STATE_ADVANCE2		:
			extruder.move(wire_stripper->_length + pull_1 + extra - compensate,speed);
			state++;
			break;
		case STATE_TRIM_CUT2	:
			cutter.move(CUTTER_TRIM);
			state++;
			break;
		case STATE_GRIP2		:
			if (double_pull)
				cutter.move(CUTTER_GRIP);
			state++;
			break;
		case STATE_PULL2		:
			if (double_pull)
				extruder.move(-wire_stripper->_end2,speed);
			state++;
			break;

		case STATE_OPEN2		:
			cutter.move(CUTTER_OPEN);
			state++;
			break;
		case STATE_ADVANCE3		:
			if (double_pull)
				delay(200);		// let the wire unstretch a bit
			extruder.move(wire_stripper->_end2,speed);
			state++;
			break;
		case STATE_CUT			:
			cutter.move(CUTTER_CUT);
			state++;
			break;
		case STATE_DONE			:
			quantity--;
			if (quantity)
				state = STATE_START;
			else
			{
				wire_stripper->disableClass(disabled_busy,false);
				cutter.move(CUTTER_OPEN);
				state = STATE_NONE;
			}
			break;

		// separate UNLOAD and LOAD state machines

		case STATE_UNLOAD   :
			cutter.move(CUTTER_OPEN);
			extruder.move(-wire_stripper->_unload_len,speed/4);
			state = STATE_UNLOADING;
			break;
		case STATE_UNLOADING :
			state = STATE_NONE;
			break;

		case STATE_LOAD   :
			cutter.move(CUTTER_OPEN);
			extruder.move(wire_stripper->_load_len,speed/4);
			state = STATE_LOADING;
			break;
		case STATE_LOADING    :
			// it only gets here if the move times out
			LOGE("Failed to load wire!!");
			state = STATE_NONE;
			break;
	}
}




void wireStripper::stateMachine()
{
	uint32_t now = millis();

	// time sensitive process functions

	cutter_busy = cutter.busy();
	extruder_busy = extruder.busy();
	any_state = state || cutter_busy || extruder_busy;

	// check the wire sensor

	static uint32_t wire_check_time = 0;
	if (now > wire_check_time)
	{
		wire_check_time = wire_check_time + 50;
		bool have = !ir_sensor.sense();
		if (have_wire != have)
		{
			have_wire = have;
			LOGI("HAVE_WIRE(%d)",have_wire);
		}
	}

	// check for load complete

	if (state == STATE_LOADING)
	{
		if (have_wire)
		{
			extruder.stop();
			LOGI("LOAD COMPLETE");
			extruder.move(wire_stripper->_load_dist,wire_stripper->_ext_speed);
			state = STATE_NONE;
		}
	}

	// do the cutterMachine

	if (state && !cutter_busy && !extruder_busy)
	{
		cutterMachine();
	}
}




//-------------------------------
// loop
//-------------------------------

void wireStripper::loop()
{
	myIOTDevice::loop();

	uint32_t now = millis();

	// handle the button

	bool button_pressed = 0;
	static bool button_state = 0;
	static uint32_t button_check_time = 0;
	if (now > button_check_time)
	{
		button_check_time = button_check_time + 50;
		bool button = !digitalRead(BUTTON_PIN);
		if (button_state != button)
		{
			button_state = button;
			button_pressed = button;
		}
	}

	if (button_pressed)
	{
		if (any_state)
		{
			stop();
		}
		else if (have_wire)
		{
			state = STATE_UNLOAD;
		}
		else
		{
			state = STATE_LOAD;
		}
	}

	// flash the led

	static bool flash = 0;
	static uint32_t flash_time = 0;
	if (now - flash_time > 200)
	{
		flash_time = now;
		flash = !flash;
		digitalWrite(ONBOARD_LED,flash);
		LOGV("IR_SENSOR=%d",ir_sensor.getValue());
	}

	// show the pixel

	int color =
		any_state ? MY_LED_YELLOW :
		!have_wire ? MY_LED_RED :
		MY_LED_GREEN;
	setPixel(color);

	// update the UI when any_state changes
	// or the status message changes

	static uint32_t ui_time = 0;
	if (now - ui_time > 50)
	{
		ui_time = now;

		static bool last_any = false;
		if (last_any != any_state)
		{
			last_any = any_state;
			wire_stripper->disableClass(disabled_busy,any_state);
		}

		int num = wire_stripper->_qty - quantity + 1;
		static String last_status = "";
		String status_str =
			state == STATE_UNLOAD || state == STATE_UNLOADING ? "Unloading ..." :
			state == STATE_LOAD || state == STATE_LOADING ? "Loading ..." :
			state ? "Cutting(" + String(num) + ") of " + String(wire_stripper->_qty) :
			cutter_busy || extruder_busy ? "ACTIVE" :
			have_wire ? "READY" :
			"!! NO WIRE !!";
		if (!_status.equals(status_str))
		{
			setString(ID_STATUS,status_str);
		}

		if (!any_state)
		{
			String cut_status_str = String(cutter.getStatusStr());
			if (!_cut_status.equals(cut_status_str))
			{
				setString(ID_CUT_STATUS,cut_status_str);
			}
		}
	}	// ui_time

	// handle pending cut from onCutAngleChanged()

	if (pending_cut != -1)
	{
		cutter.move(pending_cut);
		pending_cut = -1;
	}
}
