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
P 1200 1050
F 0 "J6" H 1280 1092 50  0001 L CNN
F 1 "IR_SENSOR" H 1050 1400 50  0000 L CNN
F 2 "0_my_footprints2:JST3" H 1200 1050 50  0001 C CNN
F 3 "~" H 1200 1050 50  0001 C CNN
	1    1200 1050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2200 1350 2300 1350
Wire Wire Line
	2300 1150 1400 1150
Wire Wire Line
	2300 1350 2300 1150
Wire Wire Line
	2300 1050 1400 1050
Wire Wire Line
	2300 850  2300 1050
Wire Wire Line
	2200 850  2300 850 
Wire Wire Line
	1900 950  1900 1350
Connection ~ 1900 950 
Wire Wire Line
	1900 950  1900 850 
Wire Wire Line
	1400 950  1900 950 
$Comp
L Device:D_Photo D2
U 1 1 66A6C16C
P 2100 1350
F 0 "D2" H 2050 1100 50  0001 C CNN
F 1 "SENSOR (black, reversed)" H 2100 1200 50  0000 C CNN
F 2 "0_my_footprints2:led_blue" H 2050 1350 50  0001 C CNN
F 3 "~" H 2050 1350 50  0001 C CNN
	1    2100 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D1
U 1 1 66A6B5EA
P 2050 850
F 0 "D1" H 2050 550 50  0001 C CNN
F 1 "EMITTER (clear)" H 2050 1000 50  0000 C CNN
F 2 "0_my_footprints2:led_yellow" H 2050 850 50  0001 C CNN
F 3 "~" H 2050 850 50  0001 C CNN
	1    2050 850 
	-1   0    0    -1  
$EndComp
Text Notes 1000 1150 2    50   ~ 0
3.3V\nEMIT_GND\nIR_RAW
$EndSCHEMATC
