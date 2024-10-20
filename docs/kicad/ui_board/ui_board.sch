EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
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
$Comp
L Connector_Generic:Conn_01x04 J1
U 1 1 669D5C6D
P 1150 1550
F 0 "J1" H 1068 1125 50  0001 C CNN
F 1 "USER_INTERFACE" H 1050 1850 50  0000 C CNN
F 2 "cnc3018-PCB:my4pin" H 1150 1550 50  0001 C CNN
F 3 "~" H 1150 1550 50  0001 C CNN
	1    1150 1550
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 669D98D4
P 1350 1450
F 0 "#PWR02" H 1350 1200 50  0001 C CNN
F 1 "GND" V 1355 1322 50  0000 R CNN
F 2 "" H 1350 1450 50  0001 C CNN
F 3 "" H 1350 1450 50  0001 C CNN
	1    1350 1450
	0    -1   -1   0   
$EndComp
Text GLabel 1350 1550 2    50   Input ~ 0
BUTTON
$Comp
L power:+3.3V #PWR03
U 1 1 669D7501
P 1350 1750
F 0 "#PWR03" H 1350 1600 50  0001 C CNN
F 1 "+3.3V" V 1350 1900 50  0000 L CNN
F 2 "" H 1350 1750 50  0001 C CNN
F 3 "" H 1350 1750 50  0001 C CNN
	1    1350 1750
	0    1    1    0   
$EndComp
Text GLabel 1350 1650 2    50   Input ~ 0
LED
$Comp
L power:GND #PWR01
U 1 1 669D9423
P 2600 1400
F 0 "#PWR01" H 2600 1150 50  0001 C CNN
F 1 "GND" V 2605 1272 50  0000 R CNN
F 2 "" H 2600 1400 50  0001 C CNN
F 3 "" H 2600 1400 50  0001 C CNN
	1    2600 1400
	0    -1   -1   0   
$EndComp
Text GLabel 2200 1400 0    50   Input ~ 0
BUTTON
$Comp
L Switch:SW_SPST SW1
U 1 1 669D7A15
P 2400 1400
F 0 "SW1" H 2400 1635 50  0001 C CNN
F 1 "BUTTON" H 2400 1544 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm_H8mm" H 2400 1400 50  0001 C CNN
F 3 "~" H 2400 1400 50  0001 C CNN
	1    2400 1400
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J2
U 1 1 669D73E3
P 2500 1850
F 0 "J2" H 2580 1892 50  0001 L CNN
F 1 "LED" H 2650 1850 50  0000 L CNN
F 2 "cnc3018-PCB:my3pin" H 2500 1850 50  0001 C CNN
F 3 "~" H 2500 1850 50  0001 C CNN
	1    2500 1850
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR05
U 1 1 669D5D09
P 2300 1950
F 0 "#PWR05" H 2300 1800 50  0001 C CNN
F 1 "+3.3V" V 2300 2100 50  0000 L CNN
F 2 "" H 2300 1950 50  0001 C CNN
F 3 "" H 2300 1950 50  0001 C CNN
	1    2300 1950
	0    -1   -1   0   
$EndComp
Text GLabel 2300 1850 0    50   Input ~ 0
LED
$Comp
L power:GND #PWR04
U 1 1 669D833D
P 2300 1750
F 0 "#PWR04" H 2300 1500 50  0001 C CNN
F 1 "GND" V 2305 1622 50  0000 R CNN
F 2 "" H 2300 1750 50  0001 C CNN
F 3 "" H 2300 1750 50  0001 C CNN
	1    2300 1750
	0    1    1    0   
$EndComp
$EndSCHEMATC
