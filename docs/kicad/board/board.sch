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
Text GLabel 1600 2600 2    50   Input ~ 0
SERVO
$Comp
L Device:R R1
U 1 1 66A397C0
P 4700 2450
F 0 "R1" V 4600 2450 50  0000 C CNN
F 1 "220" V 4700 2450 50  0000 C CNN
F 2 "0_my_footprints2:resistor" V 4630 2450 50  0001 C CNN
F 3 "~" H 4700 2450 50  0001 C CNN
	1    4700 2450
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 66A3B19F
P 4700 2650
F 0 "R2" V 4800 2650 50  0000 C CNN
F 1 "1K" V 4700 2650 50  0000 C CNN
F 2 "0_my_footprints2:resistor" V 4630 2650 50  0001 C CNN
F 3 "~" H 4700 2650 50  0001 C CNN
	1    4700 2650
	0    1    1    0   
$EndComp
Text GLabel 4950 2900 0    50   Input ~ 0
IR_SENSE
Wire Wire Line
	5150 2450 4850 2450
Text GLabel 4750 4550 0    50   Input ~ 0
LED
Text GLabel 4750 4450 0    50   Input ~ 0
BTN
$Comp
L Connector_Generic:Conn_01x03 J5
U 1 1 66A324B4
P 5350 2550
F 0 "J5" H 5430 2592 50  0001 L CNN
F 1 "IR_SENSOR" H 5150 2850 50  0000 L CNN
F 2 "0_my_footprints2:JST3" H 5350 2550 50  0001 C CNN
F 3 "~" H 5350 2550 50  0001 C CNN
	1    5350 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 669CD604
P 2450 3850
F 0 "#PWR011" H 2450 3600 50  0001 C CNN
F 1 "GND" V 2450 3650 50  0000 C CNN
F 2 "" H 2450 3850 50  0001 C CNN
F 3 "" H 2450 3850 50  0001 C CNN
	1    2450 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C2
U 1 1 669CD5FE
P 2450 3700
F 0 "C2" V 2300 3550 50  0001 R CNN
F 1 "100uf" H 2300 3700 50  0000 R CNN
F 2 "0_my_footprints:CP_my10uf" H 2488 3550 50  0001 C CNN
F 3 "~" H 2450 3700 50  0001 C CNN
	1    2450 3700
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J4
U 1 1 63212548
P 2450 3350
F 0 "J4" V 2450 3050 50  0001 L CNN
F 1 "5V Jumper" V 2600 3150 50  0000 L CNN
F 2 "0_my_footprints2:pinHeader1x2" H 2450 3350 50  0001 C CNN
F 3 "~" H 2450 3350 50  0001 C CNN
	1    2450 3350
	0    1    -1   0   
$EndComp
$Comp
L power:+5V #PWR010
U 1 1 6696FEDC
P 1600 2400
F 0 "#PWR010" H 1600 2250 50  0001 C CNN
F 1 "+5V" V 1600 2600 50  0000 C CNN
F 2 "" H 1600 2400 50  0001 C CNN
F 3 "" H 1600 2400 50  0001 C CNN
	1    1600 2400
	0    1    1    0   
$EndComp
Text GLabel 3550 3600 1    50   Input ~ 0
EXT_EN
Text GLabel 3350 3600 1    50   Input ~ 0
EXT_STEP
Text GLabel 3450 3600 1    50   Input ~ 0
EXT_DIR
Text GLabel 3650 3600 1    50   Input ~ 0
IR_SENSE
Text GLabel 4050 4600 3    50   Input ~ 0
LED
Text GLabel 3950 4600 3    50   Input ~ 0
BTN
Wire Wire Line
	4550 2450 4350 2450
Wire Wire Line
	4350 2650 4550 2650
$Comp
L power:GND #PWR015
U 1 1 66A3D833
P 4350 2750
F 0 "#PWR015" H 4350 2500 50  0001 C CNN
F 1 "GND" V 4350 2550 50  0000 C CNN
F 2 "" H 4350 2750 50  0001 C CNN
F 3 "" H 4350 2750 50  0001 C CNN
	1    4350 2750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR014
U 1 1 62AB8487
P 2750 3600
F 0 "#PWR014" H 2750 3350 50  0001 C CNN
F 1 "GND" V 2750 3400 50  0000 C CNN
F 2 "" H 2750 3600 50  0001 C CNN
F 3 "" H 2750 3600 50  0001 C CNN
	1    2750 3600
	-1   0    0    1   
$EndComp
$Comp
L 0_my_symbols:ESP32_DEV_0 U1
U 1 1 6120DB8C
P 3450 4150
F 0 "U1" H 4178 4246 50  0001 L CNN
F 1 "ESP32_DEV_0" H 4178 4200 50  0001 L CNN
F 2 "0_my_footprints2:esp32_dev_0" H 2900 4250 50  0001 C CNN
F 3 "" H 2900 4250 50  0001 C CNN
	1    3450 4150
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C3
U 1 1 61697EE0
P 4200 3600
F 0 "C3" V 3945 3600 50  0001 C CNN
F 1 "10uF" V 4050 3550 50  0000 C CNN
F 2 "0_my_footprints:CP_my10uf" H 4238 3450 50  0001 C CNN
F 3 "~" H 4200 3600 50  0001 C CNN
	1    4200 3600
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR017
U 1 1 623FFFB3
P 2650 4600
F 0 "#PWR017" H 2650 4450 50  0001 C CNN
F 1 "+3.3V" V 2650 4850 50  0000 C CNN
F 2 "" H 2650 4600 50  0001 C CNN
F 3 "" H 2650 4600 50  0001 C CNN
	1    2650 4600
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR018
U 1 1 624003E7
P 2750 4600
F 0 "#PWR018" H 2750 4350 50  0001 C CNN
F 1 "GND" V 2750 4400 50  0000 C CNN
F 2 "" H 2750 4600 50  0001 C CNN
F 3 "" H 2750 4600 50  0001 C CNN
	1    2750 4600
	1    0    0    -1  
$EndComp
Text GLabel 1600 2900 2    50   Input ~ 0
EXT_EN
Text GLabel 3250 3600 1    50   Input ~ 0
SERVO
$Comp
L Connector_Generic:Conn_01x06 J1
U 1 1 669A96D5
P 1400 2700
F 0 "J1" H 1318 3117 50  0001 C CNN
F 1 "POWER" H 1300 2250 50  0000 C CNN
F 2 "0_my_footprints:myJSTx06" H 1400 2700 50  0001 C CNN
F 3 "~" H 1400 2700 50  0001 C CNN
	1    1400 2700
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR01
U 1 1 669BF650
P 1600 2500
F 0 "#PWR01" H 1600 2250 50  0001 C CNN
F 1 "GND" V 1600 2300 50  0000 C CNN
F 2 "" H 1600 2500 50  0001 C CNN
F 3 "" H 1600 2500 50  0001 C CNN
	1    1600 2500
	0    -1   1    0   
$EndComp
Text GLabel 1600 2800 2    50   Input ~ 0
EXT_DIR
Text GLabel 1600 2700 2    50   Input ~ 0
EXT_STEP
$Comp
L power:+5V #PWR013
U 1 1 62AAA655
P 2150 3500
F 0 "#PWR013" H 2150 3350 50  0001 C CNN
F 1 "+5V" V 2150 3700 50  0000 C CNN
F 2 "" H 2150 3500 50  0001 C CNN
F 3 "" H 2150 3500 50  0001 C CNN
	1    2150 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 3550 2650 3600
Wire Wire Line
	2350 3550 2150 3550
Wire Wire Line
	2150 3550 2150 3500
Wire Wire Line
	2450 3550 2650 3550
$Comp
L power:GND #PWR020
U 1 1 6694D8CB
P 4750 4250
F 0 "#PWR020" H 4750 4000 50  0001 C CNN
F 1 "GND" V 4750 4050 50  0000 C CNN
F 2 "" H 4750 4250 50  0001 C CNN
F 3 "" H 4750 4250 50  0001 C CNN
	1    4750 4250
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J2
U 1 1 669C8399
P 4950 4350
F 0 "J2" H 5030 4342 50  0001 L CNN
F 1 "USER_INTERFACE" V 5100 4050 50  0000 L CNN
F 2 "0_my_footprints:myJSTx04" H 4950 4350 50  0001 C CNN
F 3 "~" H 4950 4350 50  0001 C CNN
	1    4950 4350
	1    0    0    -1  
$EndComp
Text GLabel 2650 3050 1    50   Input ~ 0
VIN
Wire Wire Line
	2650 3050 2650 3550
Connection ~ 2650 3550
Text GLabel 4750 4350 0    50   Input ~ 0
VIN
$Comp
L power:GND #PWR0101
U 1 1 66A0FBD9
P 4350 3600
F 0 "#PWR0101" H 4350 3350 50  0001 C CNN
F 1 "GND" V 4350 3400 50  0000 C CNN
F 2 "" H 4350 3600 50  0001 C CNN
F 3 "" H 4350 3600 50  0001 C CNN
	1    4350 3600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4950 2650 5150 2650
Wire Wire Line
	4850 2650 4950 2650
Connection ~ 4950 2650
Wire Wire Line
	4950 2900 4950 2650
$Comp
L power:+3.3V #PWR0102
U 1 1 66A1326F
P 5150 2550
F 0 "#PWR0102" H 5150 2400 50  0001 C CNN
F 1 "+3.3V" V 5150 2800 50  0000 C CNN
F 2 "" H 5150 2550 50  0001 C CNN
F 3 "" H 5150 2550 50  0001 C CNN
	1    5150 2550
	0    -1   -1   0   
$EndComp
Connection ~ 2450 3550
Wire Wire Line
	4350 2450 4350 2650
Wire Wire Line
	4350 2650 4350 2750
Connection ~ 4350 2650
$EndSCHEMATC
