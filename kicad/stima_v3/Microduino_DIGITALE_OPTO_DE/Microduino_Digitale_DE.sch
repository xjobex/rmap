EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Microduino Digitale DE"
Date "06 aprile 2019"
Rev "0.1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
NoConn ~ 4400 2550
NoConn ~ 4500 2550
NoConn ~ 4100 2550
NoConn ~ 4000 2550
NoConn ~ 3900 2550
NoConn ~ 3800 2550
NoConn ~ 3700 2550
NoConn ~ 5150 3100
NoConn ~ 5150 3200
NoConn ~ 5150 3500
NoConn ~ 5150 3600
NoConn ~ 5150 3800
$Comp
L Microduino_Digitale_DE-rescue:GND #PWR01
U 1 1 58D4FFFC
P 4900 4050
F 0 "#PWR01" H 4900 3800 50  0001 C CNN
F 1 "GND" H 4900 3900 50  0000 C CNN
F 2 "" H 4900 4050 50  0000 C CNN
F 3 "" H 4900 4050 50  0000 C CNN
	1    4900 4050
	1    0    0    -1  
$EndComp
$Comp
L Microduino_Digitale_DE-rescue:+5V #PWR02
U 1 1 58D50BEE
P 2750 3900
F 0 "#PWR02" H 2750 3750 50  0001 C CNN
F 1 "+5V" H 2750 4040 50  0000 C CNN
F 2 "" H 2750 3900 50  0000 C CNN
F 3 "" H 2750 3900 50  0000 C CNN
	1    2750 3900
	1    0    0    -1  
$EndComp
$Comp
L Microduino_Digitale_DE-rescue:+3.3V #PWR03
U 1 1 58D50CA7
P 2950 3800
F 0 "#PWR03" H 2950 3650 50  0001 C CNN
F 1 "+3.3V" H 2950 3940 50  0000 C CNN
F 2 "" H 2950 3800 50  0000 C CNN
F 3 "" H 2950 3800 50  0000 C CNN
	1    2950 3800
	1    0    0    -1  
$EndComp
Text Label 3150 3700 0    60   ~ 0
D7
Text Label 3150 3600 0    60   ~ 0
D8
Text Label 3150 3500 0    60   ~ 0
D9
Text Label 3150 3400 0    60   ~ 0
D10
Text Label 3150 3300 0    60   ~ 0
D11
Text Label 3150 3200 0    60   ~ 0
D12
Text Label 3150 3100 0    60   ~ 0
D13
NoConn ~ 3150 3700
NoConn ~ 3150 3600
NoConn ~ 3150 3500
NoConn ~ 3150 3400
NoConn ~ 3150 3300
NoConn ~ 3150 3200
NoConn ~ 3150 3100
Text Label 3700 2550 3    60   ~ 0
AREF
Text Label 3800 2550 3    60   ~ 0
A0
Text Label 3900 2550 3    60   ~ 0
A1
Text Label 4000 2550 3    60   ~ 0
A2
Text Label 4100 2550 3    60   ~ 0
A3
Text Label 4200 2550 3    60   ~ 0
SDA
Text Label 4300 2550 3    60   ~ 0
SCL
Text Label 4400 2550 3    60   ~ 0
A6
Text Label 4500 2550 3    60   ~ 0
A7
NoConn ~ 4300 2550
NoConn ~ 4200 2550
Text Label 5150 3100 2    60   ~ 0
RX0
Text Label 5150 3200 2    60   ~ 0
TX0
Text Label 5150 3300 2    60   ~ 0
D2
Text Label 5150 3400 2    60   ~ 0
D3
Text Label 5150 3500 2    60   ~ 0
D4
Text Label 5150 3600 2    60   ~ 0
D5
Text Label 5150 3700 2    60   ~ 0
D6
Text Label 5150 3800 2    60   ~ 0
RESET
Text Notes 3750 4300 0    118  ~ 24
UPIN 27
$Comp
L Microduino_Digitale_DE-rescue:CONN_1x27 P1
U 1 1 58E8C7EF
P 3600 3900
F 0 "P1" H 3600 3800 50  0000 C CNN
F 1 "CONN_1x27" V 4500 4300 50  0001 C CNN
F 2 "Libreria_PCB_mia:Upin_27" H 4600 4300 50  0001 C CNN
F 3 "" H 4600 4300 50  0000 C CNN
	1    3600 3900
	1    0    0    -1  
$EndComp
Text Notes 7150 6950 0    236  Italic 47
DigitEco s.r.l.
$Comp
L Microduino_Digitale_DE-rescue:CONN_01X04 P2
U 1 1 58E8CD07
P 8300 3350
F 0 "P2" H 8300 3600 50  0000 C CNN
F 1 "CONN_01X04" H 8300 3050 50  0001 C CNN
F 2 "Libreria_PCB_mia:WHURT_4pin_90°_61900411021" H 8300 3350 50  0001 C CNN
F 3 "280378-1" H 8300 3350 50  0001 C CNN
	1    8300 3350
	1    0    0    -1  
$EndComp
Text Notes 8500 3550 0    60   ~ 0
COM2
Text Notes 8500 3450 0    60   ~ 0
IN2 - D3
Text Notes 8500 3350 0    60   ~ 0
COM1
Text Notes 8500 3250 0    60   ~ 0
IN1 - D2
$Comp
L Microduino_Digitale_DE-rescue:+3.3V #PWR04
U 1 1 5A3F7B13
P 3600 5400
F 0 "#PWR04" H 3600 5250 50  0001 C CNN
F 1 "+3.3V" H 3600 5540 50  0000 C CNN
F 2 "" H 3600 5400 50  0001 C CNN
F 3 "" H 3600 5400 50  0001 C CNN
	1    3600 5400
	1    0    0    -1  
$EndComp
$Comp
L Microduino_Digitale_DE-rescue:+5V #PWR05
U 1 1 5A3F7B2B
P 4150 5400
F 0 "#PWR05" H 4150 5250 50  0001 C CNN
F 1 "+5V" H 4150 5540 50  0000 C CNN
F 2 "" H 4150 5400 50  0001 C CNN
F 3 "" H 4150 5400 50  0001 C CNN
	1    4150 5400
	1    0    0    -1  
$EndComp
$Comp
L Microduino_Digitale_DE-rescue:GND #PWR06
U 1 1 5A3F7B43
P 4700 5600
F 0 "#PWR06" H 4700 5350 50  0001 C CNN
F 1 "GND" H 4700 5450 50  0000 C CNN
F 2 "" H 4700 5600 50  0001 C CNN
F 3 "" H 4700 5600 50  0001 C CNN
	1    4700 5600
	1    0    0    -1  
$EndComp
$Comp
L Microduino_Digitale_DE-rescue:PWR_FLAG #FLG07
U 1 1 5A3F7B5B
P 4700 5400
F 0 "#FLG07" H 4700 5475 50  0001 C CNN
F 1 "PWR_FLAG" H 4700 5550 50  0000 C CNN
F 2 "" H 4700 5400 50  0001 C CNN
F 3 "" H 4700 5400 50  0001 C CNN
	1    4700 5400
	1    0    0    -1  
$EndComp
$Comp
L Microduino_Digitale_DE-rescue:PWR_FLAG #FLG08
U 1 1 5A3F7B73
P 4150 5600
F 0 "#FLG08" H 4150 5675 50  0001 C CNN
F 1 "PWR_FLAG" H 4150 5750 50  0000 C CNN
F 2 "" H 4150 5600 50  0001 C CNN
F 3 "" H 4150 5600 50  0001 C CNN
	1    4150 5600
	-1   0    0    1   
$EndComp
$Comp
L Microduino_Digitale_DE-rescue:PWR_FLAG #FLG09
U 1 1 5A3F7B8B
P 3600 5600
F 0 "#FLG09" H 3600 5675 50  0001 C CNN
F 1 "PWR_FLAG" H 3600 5750 50  0000 C CNN
F 2 "" H 3600 5600 50  0001 C CNN
F 3 "" H 3600 5600 50  0001 C CNN
	1    3600 5600
	-1   0    0    1   
$EndComp
NoConn ~ 5150 3700
$Comp
L Microduino_Digitale_DE-rescue:PC827 U1
U 1 1 5CA8D3BE
P 6500 2800
F 0 "U1" H 6300 3000 50  0000 L CNN
F 1 "MOCD207M" H 6500 3000 50  0000 L CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 6300 2600 50  0001 L CIN
F 3 "" H 6500 2800 50  0000 L CNN
	1    6500 2800
	-1   0    0    -1  
$EndComp
$Comp
L Microduino_Digitale_DE-rescue:PC827 U1
U 2 1 5CA8D3F1
P 6500 4100
F 0 "U1" H 6300 4300 50  0000 L CNN
F 1 "MOCD207M" H 6500 4300 50  0000 L CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 6300 3900 50  0001 L CIN
F 3 "" H 6500 4100 50  0000 L CNN
	2    6500 4100
	-1   0    0    -1  
$EndComp
$Comp
L Microduino_Digitale_DE-rescue:GND #PWR010
U 1 1 5CA8D58D
P 6150 2950
F 0 "#PWR010" H 6150 2700 50  0001 C CNN
F 1 "GND" H 6150 2800 50  0000 C CNN
F 2 "" H 6150 2950 50  0000 C CNN
F 3 "" H 6150 2950 50  0000 C CNN
	1    6150 2950
	1    0    0    -1  
$EndComp
$Comp
L Microduino_Digitale_DE-rescue:R R1
U 1 1 5CA8D5D2
P 5950 2400
F 0 "R1" V 6030 2400 50  0000 C CNN
F 1 "10k" V 5950 2400 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 5880 2400 50  0001 C CNN
F 3 "" H 5950 2400 50  0000 C CNN
	1    5950 2400
	1    0    0    -1  
$EndComp
Connection ~ 5950 2700
Wire Wire Line
	5950 2550 5950 2700
Wire Wire Line
	6150 2900 6150 2950
Wire Wire Line
	6200 2900 6150 2900
Wire Wire Line
	5400 2700 5950 2700
Wire Wire Line
	5150 3700 4800 3700
Wire Wire Line
	4700 5400 4700 5600
Wire Wire Line
	4150 5400 4150 5600
Wire Wire Line
	3600 5400 3600 5600
Wire Wire Line
	4800 3500 5150 3500
Wire Wire Line
	4800 3100 5150 3100
Wire Wire Line
	3800 2550 3800 2800
Wire Wire Line
	4000 2550 4000 2800
Wire Wire Line
	4200 2550 4200 2800
Wire Wire Line
	4400 2550 4400 2800
Wire Wire Line
	3700 2550 3700 2800
Wire Wire Line
	3900 2550 3900 2800
Wire Wire Line
	4100 2550 4100 2800
Wire Wire Line
	4300 2550 4300 2800
Wire Wire Line
	4500 2800 4500 2550
Wire Wire Line
	3400 3500 3150 3500
Wire Wire Line
	3400 3300 3150 3300
Wire Wire Line
	3400 3100 3150 3100
Wire Wire Line
	3400 3700 3150 3700
Wire Wire Line
	2750 3900 3400 3900
Wire Wire Line
	4900 3900 4900 4050
Wire Wire Line
	5150 3800 4800 3800
Wire Wire Line
	5150 3600 4800 3600
Wire Wire Line
	5150 3200 4800 3200
Wire Wire Line
	3400 3800 2950 3800
Wire Wire Line
	3400 3600 3150 3600
Wire Wire Line
	3400 3400 3150 3400
Wire Wire Line
	3150 3200 3400 3200
Wire Wire Line
	5400 2700 5400 3300
Wire Wire Line
	5400 3300 4800 3300
$Comp
L Microduino_Digitale_DE-rescue:R R3
U 1 1 5CA90BF7
P 5950 3700
F 0 "R3" V 6030 3700 50  0000 C CNN
F 1 "10k" V 5950 3700 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 5880 3700 50  0001 C CNN
F 3 "" H 5950 3700 50  0001 C CNN
	1    5950 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 4000 5950 4000
Wire Wire Line
	5400 4000 5400 3400
Wire Wire Line
	5400 3400 4800 3400
Wire Wire Line
	5950 3850 5950 4000
Connection ~ 5950 4000
$Comp
L Microduino_Digitale_DE-rescue:+3.3V #PWR011
U 1 1 5CA90CF0
P 5950 3450
F 0 "#PWR011" H 5950 3300 50  0001 C CNN
F 1 "+3.3V" H 5950 3590 50  0000 C CNN
F 2 "" H 5950 3450 50  0001 C CNN
F 3 "" H 5950 3450 50  0001 C CNN
	1    5950 3450
	1    0    0    -1  
$EndComp
$Comp
L Microduino_Digitale_DE-rescue:+3.3V #PWR012
U 1 1 5CA90D10
P 5950 2150
F 0 "#PWR012" H 5950 2000 50  0001 C CNN
F 1 "+3.3V" H 5950 2290 50  0000 C CNN
F 2 "" H 5950 2150 50  0001 C CNN
F 3 "" H 5950 2150 50  0001 C CNN
	1    5950 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 2150 5950 2250
Wire Wire Line
	5950 3450 5950 3550
Wire Wire Line
	4900 3900 4800 3900
Wire Wire Line
	6200 4200 6150 4200
Wire Wire Line
	6150 4200 6150 4250
$Comp
L Microduino_Digitale_DE-rescue:GND #PWR013
U 1 1 5CA90E4B
P 6150 4250
F 0 "#PWR013" H 6150 4000 50  0001 C CNN
F 1 "GND" H 6150 4100 50  0000 C CNN
F 2 "" H 6150 4250 50  0001 C CNN
F 3 "" H 6150 4250 50  0001 C CNN
	1    6150 4250
	1    0    0    -1  
$EndComp
$Comp
L Microduino_Digitale_DE-rescue:R R4
U 1 1 5CA90E83
P 7300 4000
F 0 "R4" V 7380 4000 50  0000 C CNN
F 1 "1k" V 7300 4000 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 7230 4000 50  0001 C CNN
F 3 "" H 7300 4000 50  0001 C CNN
	1    7300 4000
	0    1    1    0   
$EndComp
$Comp
L Microduino_Digitale_DE-rescue:R R2
U 1 1 5CA90EA8
P 7100 2600
F 0 "R2" V 7180 2600 50  0000 C CNN
F 1 "330" V 7100 2600 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 7030 2600 50  0001 C CNN
F 3 "" H 7100 2600 50  0001 C CNN
	1    7100 2600
	0    1    1    0   
$EndComp
Wire Wire Line
	7150 4000 6800 4000
Wire Wire Line
	8100 3500 8100 4200
Wire Wire Line
	8100 4200 6800 4200
Wire Wire Line
	7450 4000 7800 4000
Wire Wire Line
	7800 4000 7800 3400
Wire Wire Line
	7800 3400 8100 3400
$Comp
L Microduino_Digitale_DE-rescue:GS3 J3
U 1 1 5CA9103E
P 7450 3300
F 0 "J3" H 7500 3500 50  0000 C CNN
F 1 "GS3" H 7500 3101 50  0001 C CNN
F 2 "Connectors:GS3" V 7538 3226 50  0001 C CNN
F 3 "" H 7450 3300 50  0001 C CNN
	1    7450 3300
	1    0    0    -1  
$EndComp
$Comp
L Microduino_Digitale_DE-rescue:GS3 J2
U 1 1 5CA910BA
P 7850 2800
F 0 "J2" H 7900 3000 50  0000 C CNN
F 1 "GS3" H 7900 2601 50  0001 C CNN
F 2 "Connectors:GS3" V 7938 2726 50  0001 C CNN
F 3 "" H 7850 2800 50  0001 C CNN
	1    7850 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 3300 7600 3300
Wire Wire Line
	7300 3200 7250 3200
Wire Wire Line
	7300 3400 7250 3400
Wire Wire Line
	7250 3400 7250 3500
$Comp
L Microduino_Digitale_DE-rescue:GND #PWR014
U 1 1 5CA912F5
P 7250 3500
F 0 "#PWR014" H 7250 3250 50  0001 C CNN
F 1 "GND" H 7250 3350 50  0000 C CNN
F 2 "" H 7250 3500 50  0001 C CNN
F 3 "" H 7250 3500 50  0001 C CNN
	1    7250 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 3200 8100 2800
Wire Wire Line
	8100 2800 8000 2800
Wire Wire Line
	6800 2900 7250 2900
Wire Wire Line
	7250 3200 7250 2900
Connection ~ 7250 2900
$Comp
L Microduino_Digitale_DE-rescue:GS3 J1
U 1 1 5CA986BE
P 7450 2600
F 0 "J1" H 7500 2400 50  0000 C CNN
F 1 "GS3" H 7500 2401 50  0001 C CNN
F 2 "Connectors:GS3" V 7538 2526 50  0001 C CNN
F 3 "" H 7450 2600 50  0001 C CNN
	1    7450 2600
	-1   0    0    1   
$EndComp
Wire Wire Line
	7600 2700 7700 2700
Wire Wire Line
	7300 2600 7250 2600
Wire Wire Line
	6950 2600 6850 2600
Wire Wire Line
	6850 2600 6850 2700
Wire Wire Line
	6850 2700 6800 2700
Wire Wire Line
	7600 2500 7700 2500
Wire Wire Line
	7700 2500 7700 2400
$Comp
L Microduino_Digitale_DE-rescue:+3.3V #PWR015
U 1 1 5CA98987
P 7700 2400
F 0 "#PWR015" H 7700 2250 50  0001 C CNN
F 1 "+3.3V" H 7700 2540 50  0000 C CNN
F 2 "" H 7700 2400 50  0001 C CNN
F 3 "" H 7700 2400 50  0001 C CNN
	1    7700 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 2700 6200 2700
Wire Wire Line
	5950 4000 6200 4000
Wire Wire Line
	7250 2900 7700 2900
$EndSCHEMATC
