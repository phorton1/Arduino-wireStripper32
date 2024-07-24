EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A 11000 8500
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 2400 2350 2    50   Input ~ 0
SERVO
$Comp
L Device:R R1
U 1 1 66A397C0
P 4550 2100
F 0 "R1" V 4450 2100 50  0000 C CNN
F 1 "220" V 4550 2100 50  0000 C CNN
F 2 "0_my_footprints2:resistor" V 4480 2100 50  0001 C CNN
F 3 "~" H 4550 2100 50  0001 C CNN
	1    4550 2100
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 66A3B19F
P 4550 2300
F 0 "R2" V 4650 2300 50  0000 C CNN
F 1 "1K" V 4550 2300 50  0000 C CNN
F 2 "0_my_footprints2:resistor" V 4480 2300 50  0001 C CNN
F 3 "~" H 4550 2300 50  0001 C CNN
	1    4550 2300
	0    1    1    0   
$EndComp
Text GLabel 4800 2550 0    50   Input ~ 0
IR_SENSE
Wire Wire Line
	5000 2100 4700 2100
Text GLabel 4400 5450 1    50   Input ~ 0
LED
Text GLabel 4500 5450 1    50   Input ~ 0
BTN
$Comp
L Connector_Generic:Conn_01x03 J5
U 1 1 66A324B4
P 5200 2200
F 0 "J5" H 5280 2242 50  0001 L CNN
F 1 "IR_SENSOR" H 5000 2500 50  0000 L CNN
F 2 "0_my_footprints2:JST3" H 5200 2200 50  0001 C CNN
F 3 "~" H 5200 2200 50  0001 C CNN
	1    5200 2200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 669CD604
P 3100 3800
F 0 "#PWR011" H 3100 3550 50  0001 C CNN
F 1 "GND" V 3100 3600 50  0000 C CNN
F 2 "" H 3100 3800 50  0001 C CNN
F 3 "" H 3100 3800 50  0001 C CNN
	1    3100 3800
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C2
U 1 1 669CD5FE
P 3100 3650
F 0 "C2" V 2950 3500 50  0001 R CNN
F 1 "100uf" H 2950 3650 50  0000 R CNN
F 2 "0_my_footprints:CP_my10uf" H 3138 3500 50  0001 C CNN
F 3 "~" H 3100 3650 50  0001 C CNN
	1    3100 3650
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J4
U 1 1 63212548
P 3100 3300
F 0 "J4" V 3100 3000 50  0001 L CNN
F 1 "5V Jumper" V 3250 3100 50  0000 L CNN
F 2 "0_my_footprints2:pinHeader1x2" H 3100 3300 50  0001 C CNN
F 3 "~" H 3100 3300 50  0001 C CNN
	1    3100 3300
	0    1    -1   0   
$EndComp
$Comp
L power:+5V #PWR010
U 1 1 6696FEDC
P 2400 2150
F 0 "#PWR010" H 2400 2000 50  0001 C CNN
F 1 "+5V" V 2400 2350 50  0000 C CNN
F 2 "" H 2400 2150 50  0001 C CNN
F 3 "" H 2400 2150 50  0001 C CNN
	1    2400 2150
	0    1    1    0   
$EndComp
Text GLabel 4200 3550 1    50   Input ~ 0
EXT_EN
Text GLabel 4000 3550 1    50   Input ~ 0
EXT_STEP
Text GLabel 4100 3550 1    50   Input ~ 0
EXT_DIR
Text GLabel 4300 3550 1    50   Input ~ 0
IR_SENSE
Text GLabel 4700 4550 3    50   Input ~ 0
LED
Text GLabel 4600 4550 3    50   Input ~ 0
BTN
Wire Wire Line
	4400 2100 4200 2100
Wire Wire Line
	4200 2300 4400 2300
$Comp
L power:GND #PWR015
U 1 1 66A3D833
P 4200 2400
F 0 "#PWR015" H 4200 2150 50  0001 C CNN
F 1 "GND" V 4200 2200 50  0000 C CNN
F 2 "" H 4200 2400 50  0001 C CNN
F 3 "" H 4200 2400 50  0001 C CNN
	1    4200 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR014
U 1 1 62AB8487
P 3400 3550
F 0 "#PWR014" H 3400 3300 50  0001 C CNN
F 1 "GND" V 3400 3350 50  0000 C CNN
F 2 "" H 3400 3550 50  0001 C CNN
F 3 "" H 3400 3550 50  0001 C CNN
	1    3400 3550
	-1   0    0    1   
$EndComp
$Comp
L 0_my_symbols:ESP32_DEV_0 U1
U 1 1 6120DB8C
P 4100 4100
F 0 "U1" H 4828 4196 50  0001 L CNN
F 1 "ESP32_DEV_0" H 4828 4150 50  0001 L CNN
F 2 "0_my_footprints2:esp32_dev_0" H 3550 4200 50  0001 C CNN
F 3 "" H 3550 4200 50  0001 C CNN
	1    4100 4100
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C3
U 1 1 61697EE0
P 4850 3550
F 0 "C3" V 4595 3550 50  0001 C CNN
F 1 "10uF" V 4700 3500 50  0000 C CNN
F 2 "0_my_footprints:CP_my10uf" H 4888 3400 50  0001 C CNN
F 3 "~" H 4850 3550 50  0001 C CNN
	1    4850 3550
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR017
U 1 1 623FFFB3
P 3300 4550
F 0 "#PWR017" H 3300 4400 50  0001 C CNN
F 1 "+3.3V" V 3300 4800 50  0000 C CNN
F 2 "" H 3300 4550 50  0001 C CNN
F 3 "" H 3300 4550 50  0001 C CNN
	1    3300 4550
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR018
U 1 1 624003E7
P 3400 4550
F 0 "#PWR018" H 3400 4300 50  0001 C CNN
F 1 "GND" V 3400 4350 50  0000 C CNN
F 2 "" H 3400 4550 50  0001 C CNN
F 3 "" H 3400 4550 50  0001 C CNN
	1    3400 4550
	1    0    0    -1  
$EndComp
Text GLabel 2400 2650 2    50   Input ~ 0
EXT_EN
Text GLabel 3900 3550 1    50   Input ~ 0
SERVO
$Comp
L Connector_Generic:Conn_01x06 J1
U 1 1 669A96D5
P 2200 2450
F 0 "J1" H 2118 2867 50  0001 C CNN
F 1 "POWER" H 2200 2850 50  0000 C CNN
F 2 "0_my_footprints:myJSTx06" H 2200 2450 50  0001 C CNN
F 3 "~" H 2200 2450 50  0001 C CNN
	1    2200 2450
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR01
U 1 1 669BF650
P 2400 2250
F 0 "#PWR01" H 2400 2000 50  0001 C CNN
F 1 "GND" V 2400 2050 50  0000 C CNN
F 2 "" H 2400 2250 50  0001 C CNN
F 3 "" H 2400 2250 50  0001 C CNN
	1    2400 2250
	0    -1   1    0   
$EndComp
Text GLabel 2400 2550 2    50   Input ~ 0
EXT_DIR
Text GLabel 2400 2450 2    50   Input ~ 0
EXT_STEP
$Comp
L power:+5V #PWR013
U 1 1 62AAA655
P 2800 3450
F 0 "#PWR013" H 2800 3300 50  0001 C CNN
F 1 "+5V" V 2800 3650 50  0000 C CNN
F 2 "" H 2800 3450 50  0001 C CNN
F 3 "" H 2800 3450 50  0001 C CNN
	1    2800 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 3500 3300 3550
Wire Wire Line
	3000 3500 2800 3500
Wire Wire Line
	2800 3500 2800 3450
Wire Wire Line
	3100 3500 3300 3500
$Comp
L power:GND #PWR020
U 1 1 6694D8CB
P 4700 5450
F 0 "#PWR020" H 4700 5200 50  0001 C CNN
F 1 "GND" V 4700 5250 50  0000 C CNN
F 2 "" H 4700 5450 50  0001 C CNN
F 3 "" H 4700 5450 50  0001 C CNN
	1    4700 5450
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J2
U 1 1 669C8399
P 4600 5650
F 0 "J2" H 4680 5642 50  0001 L CNN
F 1 "UI" H 4680 5596 50  0000 L CNN
F 2 "0_my_footprints:myJSTx04" H 4600 5650 50  0001 C CNN
F 3 "~" H 4600 5650 50  0001 C CNN
	1    4600 5650
	0    1    1    0   
$EndComp
Text GLabel 3300 3000 1    50   Input ~ 0
VIN
Wire Wire Line
	3300 3000 3300 3500
Connection ~ 3300 3500
Text GLabel 4600 5450 1    50   Input ~ 0
VIN
$Comp
L power:GND #PWR0101
U 1 1 66A0FBD9
P 5000 3550
F 0 "#PWR0101" H 5000 3300 50  0001 C CNN
F 1 "GND" V 5000 3350 50  0000 C CNN
F 2 "" H 5000 3550 50  0001 C CNN
F 3 "" H 5000 3550 50  0001 C CNN
	1    5000 3550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4800 2300 5000 2300
Wire Wire Line
	4700 2300 4800 2300
Connection ~ 4800 2300
Wire Wire Line
	4800 2550 4800 2300
$Comp
L power:+3.3V #PWR0102
U 1 1 66A1326F
P 5000 2200
F 0 "#PWR0102" H 5000 2050 50  0001 C CNN
F 1 "+3.3V" V 5000 2450 50  0000 C CNN
F 2 "" H 5000 2200 50  0001 C CNN
F 3 "" H 5000 2200 50  0001 C CNN
	1    5000 2200
	0    -1   -1   0   
$EndComp
Connection ~ 3100 3500
Wire Wire Line
	4200 2100 4200 2300
Wire Wire Line
	4200 2300 4200 2400
Connection ~ 4200 2300
$EndSCHEMATC
