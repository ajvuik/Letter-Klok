EESchema Schematic File Version 4
EELAYER 26 0
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
L ESP8266:ESP-01v090 U1
U 1 1 5D035E74
P 3100 2550
F 0 "U1" H 3100 3065 50  0000 C CNN
F 1 "ESP-01" H 3100 2974 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x04_P2.54mm_Vertical" H 3100 2550 50  0001 C CNN
F 3 "http://l0l.org.uk/2014/12/esp8266-modules-hardware-guide-gotta-catch-em-all/" H 3100 2550 50  0001 C CNN
	1    3100 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D035F35
P 4350 3350
F 0 "#PWR?" H 4350 3100 50  0001 C CNN
F 1 "GND" H 4355 3177 50  0000 C CNN
F 2 "" H 4350 3350 50  0001 C CNN
F 3 "" H 4350 3350 50  0001 C CNN
	1    4350 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 2400 4350 2400
Wire Wire Line
	4350 2400 4350 3350
$Comp
L power:+3.3V #PWR?
U 1 1 5D036006
P 1600 1700
F 0 "#PWR?" H 1600 1550 50  0001 C CNN
F 1 "+3.3V" H 1615 1873 50  0000 C CNN
F 2 "" H 1600 1700 50  0001 C CNN
F 3 "" H 1600 1700 50  0001 C CNN
	1    1600 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 2700 1600 2700
Wire Wire Line
	1600 2700 1600 2600
$Comp
L Device:R R2
U 1 1 5D036077
P 1900 2600
F 0 "R2" V 1700 2600 50  0000 C CNN
F 1 "10K" V 1600 2600 50  0000 C CNN
F 2 "" V 1830 2600 50  0001 C CNN
F 3 "~" H 1900 2600 50  0001 C CNN
	1    1900 2600
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R1
U 1 1 5D0360E6
P 1900 2500
F 0 "R1" V 2100 2500 50  0000 C CNN
F 1 "10K" V 2016 2500 50  0000 C CNN
F 2 "" V 1830 2500 50  0001 C CNN
F 3 "~" H 1900 2500 50  0001 C CNN
	1    1900 2500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2150 2600 2050 2600
Wire Wire Line
	2150 2500 2050 2500
Wire Wire Line
	1750 2500 1600 2500
Connection ~ 1600 2500
Wire Wire Line
	1600 2500 1600 1700
Wire Wire Line
	1750 2600 1600 2600
Connection ~ 1600 2600
Wire Wire Line
	1600 2600 1600 2500
$Comp
L Regulator_Linear:LM1117-3.3 U?
U 1 1 5D0364D2
P 2850 5050
F 0 "U?" H 2850 5292 50  0000 C CNN
F 1 "LM1117-3.3" H 2850 5201 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 2850 5050 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm1117.pdf" H 2850 5050 50  0001 C CNN
	1    2850 5050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D0365A1
P 2850 5700
F 0 "#PWR?" H 2850 5450 50  0001 C CNN
F 1 "GND" H 2855 5527 50  0000 C CNN
F 2 "" H 2850 5700 50  0001 C CNN
F 3 "" H 2850 5700 50  0001 C CNN
	1    2850 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 5350 2850 5550
$Comp
L power:+5V #PWR?
U 1 1 5D036652
P 2000 4700
F 0 "#PWR?" H 2000 4550 50  0001 C CNN
F 1 "+5V" H 2015 4873 50  0000 C CNN
F 2 "" H 2000 4700 50  0001 C CNN
F 3 "" H 2000 4700 50  0001 C CNN
	1    2000 4700
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5D036691
P 3700 4700
F 0 "#PWR?" H 3700 4550 50  0001 C CNN
F 1 "+3.3V" H 3715 4873 50  0000 C CNN
F 2 "" H 3700 4700 50  0001 C CNN
F 3 "" H 3700 4700 50  0001 C CNN
	1    3700 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 4700 2000 5050
Wire Wire Line
	2000 5050 2550 5050
Wire Wire Line
	3700 4700 3700 5050
Wire Wire Line
	3700 5050 3250 5050
Text GLabel 4850 2500 2    50   Input ~ 0
GPIO2
Wire Wire Line
	4050 2500 4850 2500
$Comp
L Connector:Screw_Terminal_01x02 J1
U 1 1 5D0388FF
P 8300 1500
F 0 "J1" H 8380 1492 50  0000 L CNN
F 1 "5V power" H 8380 1401 50  0000 L CNN
F 2 "" H 8300 1500 50  0001 C CNN
F 3 "~" H 8300 1500 50  0001 C CNN
	1    8300 1500
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x03 J2
U 1 1 5D038997
P 8300 3150
F 0 "J2" H 8379 3192 50  0000 L CNN
F 1 "Led strip" H 8379 3101 50  0000 L CNN
F 2 "" H 8300 3150 50  0001 C CNN
F 3 "~" H 8300 3150 50  0001 C CNN
	1    8300 3150
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5D038AB5
P 7700 1300
F 0 "#PWR?" H 7700 1150 50  0001 C CNN
F 1 "+5V" H 7715 1473 50  0000 C CNN
F 2 "" H 7700 1300 50  0001 C CNN
F 3 "" H 7700 1300 50  0001 C CNN
	1    7700 1300
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5D038AE3
P 7700 2750
F 0 "#PWR?" H 7700 2600 50  0001 C CNN
F 1 "+5V" H 7715 2923 50  0000 C CNN
F 2 "" H 7700 2750 50  0001 C CNN
F 3 "" H 7700 2750 50  0001 C CNN
	1    7700 2750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D038C4D
P 7700 1850
F 0 "#PWR?" H 7700 1600 50  0001 C CNN
F 1 "GND" H 7705 1677 50  0000 C CNN
F 2 "" H 7700 1850 50  0001 C CNN
F 3 "" H 7700 1850 50  0001 C CNN
	1    7700 1850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5D038C7B
P 7700 3550
F 0 "#PWR?" H 7700 3300 50  0001 C CNN
F 1 "GND" H 7705 3377 50  0000 C CNN
F 2 "" H 7700 3550 50  0001 C CNN
F 3 "" H 7700 3550 50  0001 C CNN
	1    7700 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 1500 7700 1500
Wire Wire Line
	7700 1500 7700 1300
Wire Wire Line
	8100 1600 7700 1600
Wire Wire Line
	7700 1600 7700 1850
Wire Wire Line
	8100 3050 7700 3050
Wire Wire Line
	7700 3050 7700 2750
Wire Wire Line
	8100 3250 7700 3250
Wire Wire Line
	7700 3250 7700 3550
Text GLabel 7100 3150 0    50   Input ~ 0
GPIO2
Wire Wire Line
	7100 3150 8100 3150
$Comp
L Device:C C1
U 1 1 5D039650
P 3700 5400
F 0 "C1" H 3815 5446 50  0000 L CNN
F 1 "100nF" H 3815 5355 50  0000 L CNN
F 2 "" H 3738 5250 50  0001 C CNN
F 3 "~" H 3700 5400 50  0001 C CNN
	1    3700 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 5550 3250 5550
Connection ~ 2850 5550
Wire Wire Line
	2850 5550 2850 5700
Wire Wire Line
	3700 5250 3700 5050
Connection ~ 3700 5050
$Comp
L Device:CP C2
U 1 1 5D039C39
P 2000 5400
F 0 "C2" H 2118 5446 50  0000 L CNN
F 1 "10nF" H 2118 5355 50  0000 L CNN
F 2 "" H 2038 5250 50  0001 C CNN
F 3 "~" H 2000 5400 50  0001 C CNN
	1    2000 5400
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C3
U 1 1 5D039CCD
P 3250 5400
F 0 "C3" H 3368 5446 50  0000 L CNN
F 1 "10nF" H 3368 5355 50  0000 L CNN
F 2 "" H 3288 5250 50  0001 C CNN
F 3 "~" H 3250 5400 50  0001 C CNN
	1    3250 5400
	1    0    0    -1  
$EndComp
Connection ~ 3250 5550
Wire Wire Line
	3250 5550 2850 5550
Wire Wire Line
	2000 5550 2850 5550
Wire Wire Line
	2000 5250 2000 5050
Connection ~ 2000 5050
Wire Wire Line
	3250 5250 3250 5050
Connection ~ 3250 5050
Wire Wire Line
	3250 5050 3150 5050
$EndSCHEMATC
