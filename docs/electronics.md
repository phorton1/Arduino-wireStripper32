# wireStripper32 - Electronics

**[Home](readme.md)** --
**[Design](design.md)** --
**Electronics** --
**[Build](build.md)** --
**[Firmware](firmware.md)** --

This page shows all of the schematics, PCB designs, and has
photos of the completed circuit boards used in the wireStripper.
Please see the **/docs/kicad** folder for the actual schematics
and PCB designs.


![electronics.jpg](images/electronics.jpg)


## The Power Board

The *Power Board* takes a **12V DC** input and has two **buck converters* on it.
One buck converter produces **7V DC** (the maximum rated voltage) for the
Servo and the other convertor produces **5V** DC to go to the ESP32.
The Power Board has a **scocket** for the *A4988 stepper motor controller**,
and **plugs** for the *Nema17 stepper motor* and *MG995 Servo*.
The Power Board connects to the Main Board with a **6 pin cable** that
caries GND, 5V, the **Enable, Step, and Direction** signals for
the stepper motor, and the PWM signal for the *Servo*.

![elec_power_schematic.jpg](images/elec_power_schematic.jpg)
![elec_power_pcb.jpg](images/elec_power_pcb.jpg)
![elec_power_front.jpg](images/elec_power_front.jpg)
![elec_power_back.jpg](images/elec_power_back.jpg)



## The Main Board

The *Main Board* has a **socket** for the ESP32 dev board, and
**plugs** to connect it to the *Power Board*, the *IR Sensor*
LEDs, and the **UI Board**.   It also has a **jumper** that
allows the ESP32 to connect the **5V** from Power Board to the
*VIN pin* on the ESP32, along with a 100uf capacitor to smooth
out the 5V VIN power supply

![elec_board_schematic.jpg](images/elec_board_schematic.jpg)
![elec_board_pcb.jpg](images/elec_board_pcb.jpg)
![elec_board_front.jpg](images/elec_board_front.jpg)
![elec_board_back.jpg](images/elec_board_back.jpg)



## The UI (User Interface) Board

The UI board simply has a **push button** and a **WS2812b LED**
on it, along with a cable that reaches to the Main Board.

![elec_ui_schematic.jpg](images/elec_ui_schematic.jpg)
![elec_ui_pcb.jpg](images/elec_ui_pcb.jpg)
![elec_ui_front.jpg](images/elec_ui_front.jpg)
![elec_ui_back.jpg](images/elec_ui_back.jpg)

I used a 9mm circular WS2812b breakout board for the LED:

![elec_led_detail.jpg](images/elec_led_detail.jpg)



## The IR Sensor

The IR Sensor merely consists of an **850nm** *LED* (clear)
and *sensor* (black), soldered directly to a 3 pin JST wire
header with some heat shrink tubing.

![elec_ir_schematic.jpg](images/elec_ir_schematic.jpg)
![elec_ir_sensor.jpg](images/elec_ir_sensor.jpg)

The key is that the **LED is wired normally** with the anode
(the long leg) to the 3.3V power supply, but **the Sensor is
wired backwards** with the cathode (the short leg) connected
to the 3.3V power supply.


## Other Cables/Connectors

I also put a 4-pin JST connector on the end of a short standard
stepper motor cable,

![elec_stepper_cable.jpg](images/elec_stepper_cable.jpg)

and added a 3-pin JST connector to the (shorted) cable on the
Servo.

![elec_servo_connector.jpg](images/elec_servo_connector.jpg)



**Next:** - [**Building**](building.md) the wireStripper ..
