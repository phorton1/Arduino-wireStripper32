EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A 8500 11000 portrait
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
L Connector_Generic:Conn_01x03 J6
U 1 1 66A324B4
P 1350 1400
F 0 "J6" H 1430 1442 50  0001 L CNN
F 1 "IR_SENSOR" H 1200 1700 50  0000 L CNN
F 2 "0_my_footprints2:JST3" H 1350 1400 50  0001 C CNN
F 3 "~" H 1350 1400 50  0001 C CNN
	1    1350 1400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2350 1700 2450 1700
Wire Wire Line
	2450 1500 1550 1500
Wire Wire Line
	2450 1700 2450 1500
Wire Wire Line
	2450 1100 2450 1300
Wire Wire Line
	2350 1100 2450 1100
Wire Wire Line
	1550 1400 2050 1400
$Comp
L Device:D_Photo D2
U 1 1 66A6C16C
P 2250 1700
F 0 "D2" H 2200 1450 50  0001 C CNN
F 1 "850nm SENSOR (black, reversed)" H 2250 1550 50  0000 C CNN
F 2 "0_my_footprints2:led_blue" H 2200 1700 50  0001 C CNN
F 3 "~" H 2200 1700 50  0001 C CNN
	1    2250 1700
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D1
U 1 1 66A6B5EA
P 2200 1100
F 0 "D1" H 2200 800 50  0001 C CNN
F 1 "850nm EMITTER (clear)" H 2200 1250 50  0000 C CNN
F 2 "0_my_footprints2:led_yellow" H 2200 1100 50  0001 C CNN
F 3 "~" H 2200 1100 50  0001 C CNN
	1    2200 1100
	-1   0    0    -1  
$EndComp
Text Notes 1200 1500 2    50   ~ 0
EMIT_GND\n3.3V\nIR_RAW
Wire Wire Line
	2050 1400 2050 1700
Wire Wire Line
	2050 1100 2050 1400
Connection ~ 2050 1400
Wire Wire Line
	2450 1300 1550 1300
$EndSCHEMATC
