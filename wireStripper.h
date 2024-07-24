//--------------------------------------
// wireStripper.h
//--------------------------------------
// Using myIOT library, A4988 stepper motor driver, and a 5V Servo.

#pragma once

#include <myIOTDevice.h>

#define WIRE_STRIPPER			"wireStripper"
#define WIRE_STRIPPER_VERSION	"ws1.0"
#define WIRE_STRIPPER_URL		"https://github.com/phorton1/Arduino-wireStripper32"


//------------------------
// ids
//------------------------

#define ID_STATUS           "STATUS"

#define ID_STOP      		"STOP"
#define ID_LOAD      		"LOAD"
#define ID_UNLOAD      		"UNLOAD"
#define ID_GO				"GO"
#define ID_CUT				"CUT"


#define ID_END1				"END1"
#define ID_LENGTH			"LENGTH"
#define ID_HOLES			"HOLES"
#define ID_END2				"END2"
#define ID_QTY				"QTY"
#define ID_UNLOAD_LEN		"UNLOAD_LEN"
#define ID_LOAD_LEN			"LOAD_LEN"
#define ID_LOAD_DIST		"LOAD_DIST"
#define ID_PULL_MAX			"PULL_MAX"
#define ID_PULL_EXTRA		"PULL_EXTRA"
#define ID_PULL_COMPENSATE	"PULL_COMPENSATE"
#define ID_CUT_STATUS		"CUT_STATUS"
#define ID_CUT_POS          "CUT_POS"
#define ID_CUT_OPEN         "CUT_OPEN"
#define ID_CUT_GRIP         "CUT_GRIP"
#define ID_CUT_TRIM         "CUT_TRIM"
#define ID_CUT_CUT          "CUT_CUT"
#define ID_CUT_USER         "CUT_USER"
#define ID_CUT_MIN_MS     	"CUT_MIN_MS"
#define ID_CUT_MS_PER_DEG   "CUT_MS_PER_DEG"
#define ID_CUT_DETACH_MS   	"CUT_DETACH_MS"
#define ID_IR_THRESH        "IR_THRESH"
#define ID_EXT_SPEED        "EXT_SPEED"
#define ID_EXT_CALIB        "EXT_CALIB"
#define ID_EXT_RADIUS       "EXT_RADIUS"
#define ID_EXT_REV_STEPS    "EXT_REV_STEPS"
#define ID_EXT_ACCEL        "EXT_ACCEL"
#define ID_DEBUG_PAUSE      "DEBUG_PAUSE"


//------------------------
// enums
//------------------------

#define	CUTTER_OPEN			0
#define	CUTTER_GRIP			1
#define CUTTER_TRIM			2
#define CUTTER_CUT			3
#define CUTTER_USER			4




typedef struct
    // a structure containing the states used by stateMachine()
    // for asynchronous publishing during loop()
{
    uint32_t state;


} wireStripperState_t;





class wireStripper : public myIOTDevice
{
public:

    wireStripper();
    ~wireStripper() {}

    virtual void setup() override;
    virtual void loop() override;

	// commands

    static void stop();
    static void load();
    static void unload();
	static void execute();	  // go()
	static void docut();

    static const valDescriptor m_wire_stripper_values[];
    static wireStripperState_t m_publish_state;

    // values

	static String	_status;
	static float	_end1;
	static float	_length;
	static float	_holes;
	static float	_end2;
	static int		_qty;
	static float	_unload_len;
	static float	_load_len;
	static float	_load_dist;
	static float 	_pull_max;
	static float 	_pull_extra;
	static float 	_pull_compensate;
	static String	_cut_status;
	static int		_cut_pos;		// enum
	static int		_cut_open_deg;
	static int		_cut_grip_deg;
	static int		_cut_trim_deg;
	static int		_cut_cut_deg;
	static int		_cut_user_deg;
	static int		_cut_min_ms;
	static int		_cut_ms_per_deg;
	static int 		_cut_detach_ms;
	static int		_ir_thresh;
	static int		_ext_speed;
	static float	_ext_calib;
	static float	_ext_radius;
	static float	_ext_rev_steps;
	static int		_ext_accel;
	static int		_debug_pause;

	// methods

	void stateMachine();
	static void stateTask(void *param);

	static void onLengthChanged(const myIOTValue *value, float val);
	static void onHolesChanged(const myIOTValue *value, float val);
	static void onCutPosChanged(const myIOTValue *value, uint32_t val);
	static void onCutAngleChanged(const myIOTValue *value, int val);
};


extern wireStripper *wire_stripper;

