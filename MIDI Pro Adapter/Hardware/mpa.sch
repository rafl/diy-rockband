EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "MIDI Pro Adapter"
Date "2020-04-18"
Rev ""
Comp "Florian Ragwitz"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L mpa:C8051F340 U101
U 1 1 5E994E29
P 4250 2150
F 0 "U101" H 4200 2200 50  0000 L CNN
F 1 "C8051F340" H 4050 2300 50  0000 L CNN
F 2 "" H 4250 2150 50  0001 C CNN
F 3 "" H 4250 2150 50  0001 C CNN
	1    4250 2150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5E997112
P 2850 2200
F 0 "#PWR0101" H 2850 1950 50  0001 C CNN
F 1 "GND" H 2855 2027 50  0000 C CNN
F 2 "" H 2850 2200 50  0001 C CNN
F 3 "" H 2850 2200 50  0001 C CNN
	1    2850 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 2200 3250 2200
$Comp
L Connector:TestPoint TP1
U 1 1 5E997A4F
P 5400 2200
F 0 "TP1" V 5354 2388 50  0000 L CNN
F 1 "P3.0" V 5445 2388 50  0000 L CNN
F 2 "" H 5600 2200 50  0001 C CNN
F 3 "~" H 5600 2200 50  0001 C CNN
	1    5400 2200
	0    1    1    0   
$EndComp
Text GLabel 3250 1600 0    50   Input ~ 0
MIDI_IN
$Comp
L Connector_Generic:Conn_01x05 USB1
U 1 1 5E9DD154
P 10200 5700
F 0 "USB1" H 10280 5742 50  0000 L CNN
F 1 "Conn_01x05" H 10280 5651 50  0000 L CNN
F 2 "" H 10200 5700 50  0001 C CNN
F 3 "~" H 10200 5700 50  0001 C CNN
	1    10200 5700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR012
U 1 1 5E9DE0CF
P 10000 5900
F 0 "#PWR012" H 10000 5650 50  0001 C CNN
F 1 "GND" H 10005 5727 50  0000 C CNN
F 2 "" H 10000 5900 50  0001 C CNN
F 3 "" H 10000 5900 50  0001 C CNN
	1    10000 5900
	1    0    0    -1  
$EndComp
Text GLabel 3250 2300 0    50   BiDi ~ 0
D+
Text GLabel 3250 2400 0    50   BiDi ~ 0
D-
$Comp
L Device:R R110
U 1 1 5E9DE883
P 9700 5950
F 0 "R110" H 9630 5904 50  0000 R CNN
F 1 "22" H 9630 5995 50  0000 R CNN
F 2 "" V 9630 5950 50  0001 C CNN
F 3 "~" H 9700 5950 50  0001 C CNN
	1    9700 5950
	-1   0    0    1   
$EndComp
$Comp
L Device:R R111
U 1 1 5E9DF546
P 9350 5850
F 0 "R111" H 9420 5896 50  0000 L CNN
F 1 "22" H 9420 5805 50  0000 L CNN
F 2 "" V 9280 5850 50  0001 C CNN
F 3 "~" H 9350 5850 50  0001 C CNN
	1    9350 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 5800 10000 5800
Wire Wire Line
	9350 5700 10000 5700
Text GLabel 9350 6000 3    50   BiDi ~ 0
D-
Text GLabel 9700 6100 3    50   BiDi ~ 0
D+
$Comp
L Device:Jumper JP1
U 1 1 5E9E250F
P 10150 3150
F 0 "JP1" H 10150 3414 50  0000 C CNN
F 1 "Jumper" H 10150 3323 50  0000 C CNN
F 2 "" H 10150 3150 50  0001 C CNN
F 3 "~" H 10150 3150 50  0001 C CNN
	1    10150 3150
	1    0    0    -1  
$EndComp
$Comp
L Device:Jumper JP2
U 1 1 5E9E2B75
P 10150 3650
F 0 "JP2" H 10150 3914 50  0000 C CNN
F 1 "Jumper" H 10150 3823 50  0000 C CNN
F 2 "" H 10150 3650 50  0001 C CNN
F 3 "~" H 10150 3650 50  0001 C CNN
	1    10150 3650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR017
U 1 1 5E9E41FB
P 9850 3800
F 0 "#PWR017" H 9850 3550 50  0001 C CNN
F 1 "GND" H 9855 3627 50  0000 C CNN
F 2 "" H 9850 3800 50  0001 C CNN
F 3 "" H 9850 3800 50  0001 C CNN
	1    9850 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 3800 9850 3650
Connection ~ 9850 3650
Wire Wire Line
	9850 3650 9850 3150
$Comp
L Connector:TestPoint TP4
U 1 1 5E9E4938
P 10450 3050
F 0 "TP4" H 10508 3168 50  0000 L CNN
F 1 "JP1" H 10508 3077 50  0000 L CNN
F 2 "" H 10650 3050 50  0001 C CNN
F 3 "~" H 10650 3050 50  0001 C CNN
	1    10450 3050
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP5
U 1 1 5E9E4DF3
P 10450 3500
F 0 "TP5" H 10508 3618 50  0000 L CNN
F 1 "JP2" H 10508 3527 50  0000 L CNN
F 2 "" H 10650 3500 50  0001 C CNN
F 3 "~" H 10650 3500 50  0001 C CNN
	1    10450 3500
	1    0    0    -1  
$EndComp
Text GLabel 10450 3150 2    50   Input ~ 0
JP1
Wire Wire Line
	10450 3050 10450 3150
Wire Wire Line
	10450 3500 10450 3650
Text GLabel 10450 3650 2    50   Input ~ 0
JP2
Text GLabel 5250 2100 2    50   Input ~ 0
JP2
Text GLabel 5250 2000 2    50   Input ~ 0
JP1
$Comp
L Device:R R121
U 1 1 5E9E6E1E
P 1950 6600
F 0 "R121" H 2020 6646 50  0000 L CNN
F 1 "390" H 2020 6555 50  0000 L CNN
F 2 "" V 1880 6600 50  0001 C CNN
F 3 "~" H 1950 6600 50  0001 C CNN
	1    1950 6600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R122
U 1 1 5E9E70F2
P 2900 6600
F 0 "R122" H 2970 6646 50  0000 L CNN
F 1 "390" H 2970 6555 50  0000 L CNN
F 2 "" V 2830 6600 50  0001 C CNN
F 3 "~" H 2900 6600 50  0001 C CNN
	1    2900 6600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R123
U 1 1 5E9E77E0
P 3850 6600
F 0 "R123" H 3920 6646 50  0000 L CNN
F 1 "390" H 3920 6555 50  0000 L CNN
F 2 "" V 3780 6600 50  0001 C CNN
F 3 "~" H 3850 6600 50  0001 C CNN
	1    3850 6600
	1    0    0    -1  
$EndComp
$Comp
L Device:R R124
U 1 1 5E9E7D99
P 4800 6600
F 0 "R124" H 4870 6646 50  0000 L CNN
F 1 "390" H 4870 6555 50  0000 L CNN
F 2 "" V 4730 6600 50  0001 C CNN
F 3 "~" H 4800 6600 50  0001 C CNN
	1    4800 6600
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D102
U 1 1 5E9E856B
P 1950 6900
F 0 "D102" V 1989 6782 50  0000 R CNN
F 1 "LED" V 1898 6782 50  0000 R CNN
F 2 "" H 1950 6900 50  0001 C CNN
F 3 "~" H 1950 6900 50  0001 C CNN
	1    1950 6900
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D102A1
U 1 1 5E9E8D90
P 1500 6900
F 0 "D102A1" V 1539 6783 50  0000 R CNN
F 1 "LED" V 1448 6783 50  0000 R CNN
F 2 "" H 1500 6900 50  0001 C CNN
F 3 "~" H 1500 6900 50  0001 C CNN
	1    1500 6900
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D103
U 1 1 5E9E9409
P 2900 6900
F 0 "D103" V 2939 6782 50  0000 R CNN
F 1 "LED" V 2848 6782 50  0000 R CNN
F 2 "" H 2900 6900 50  0001 C CNN
F 3 "~" H 2900 6900 50  0001 C CNN
	1    2900 6900
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D103A1
U 1 1 5E9E99A1
P 2450 6900
F 0 "D103A1" V 2489 6783 50  0000 R CNN
F 1 "LED" V 2398 6783 50  0000 R CNN
F 2 "" H 2450 6900 50  0001 C CNN
F 3 "~" H 2450 6900 50  0001 C CNN
	1    2450 6900
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D104
U 1 1 5E9EC86D
P 3850 6900
F 0 "D104" V 3889 6782 50  0000 R CNN
F 1 "LED" V 3798 6782 50  0000 R CNN
F 2 "" H 3850 6900 50  0001 C CNN
F 3 "~" H 3850 6900 50  0001 C CNN
	1    3850 6900
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D104A1
U 1 1 5E9ECDFB
P 3400 6900
F 0 "D104A1" V 3439 6783 50  0000 R CNN
F 1 "LED" V 3348 6783 50  0000 R CNN
F 2 "" H 3400 6900 50  0001 C CNN
F 3 "~" H 3400 6900 50  0001 C CNN
	1    3400 6900
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D105
U 1 1 5E9EE29D
P 4800 6900
F 0 "D105" V 4839 6782 50  0000 R CNN
F 1 "LED" V 4748 6782 50  0000 R CNN
F 2 "" H 4800 6900 50  0001 C CNN
F 3 "~" H 4800 6900 50  0001 C CNN
	1    4800 6900
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D105A1
U 1 1 5E9EE8D5
P 4350 6900
F 0 "D105A1" V 4389 6783 50  0000 R CNN
F 1 "LED" V 4298 6783 50  0000 R CNN
F 2 "" H 4350 6900 50  0001 C CNN
F 3 "~" H 4350 6900 50  0001 C CNN
	1    4350 6900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1500 7050 1500 7200
Wire Wire Line
	1500 7200 1950 7200
Wire Wire Line
	4800 7200 4800 7050
Wire Wire Line
	4350 7050 4350 7200
Connection ~ 4350 7200
Wire Wire Line
	4350 7200 4800 7200
Wire Wire Line
	3850 7050 3850 7200
Connection ~ 3850 7200
Wire Wire Line
	3850 7200 4350 7200
Wire Wire Line
	3400 7050 3400 7200
Connection ~ 3400 7200
Wire Wire Line
	3400 7200 3850 7200
Wire Wire Line
	2900 7050 2900 7200
Connection ~ 2900 7200
Wire Wire Line
	2900 7200 3150 7200
Wire Wire Line
	2450 7050 2450 7200
Connection ~ 2450 7200
Wire Wire Line
	2450 7200 2900 7200
Wire Wire Line
	1950 7050 1950 7200
Connection ~ 1950 7200
Wire Wire Line
	1950 7200 2450 7200
Wire Wire Line
	1500 6750 1950 6750
Connection ~ 1950 6750
Wire Wire Line
	2450 6750 2900 6750
Connection ~ 2900 6750
Wire Wire Line
	3400 6750 3850 6750
Connection ~ 3850 6750
Wire Wire Line
	4350 6750 4800 6750
Connection ~ 4800 6750
$Comp
L power:GND #PWR011
U 1 1 5E9FCA33
P 3150 7200
F 0 "#PWR011" H 3150 6950 50  0001 C CNN
F 1 "GND" H 3155 7027 50  0000 C CNN
F 2 "" H 3150 7200 50  0001 C CNN
F 3 "" H 3150 7200 50  0001 C CNN
	1    3150 7200
	1    0    0    -1  
$EndComp
Connection ~ 3150 7200
Wire Wire Line
	3150 7200 3400 7200
Text Notes 3400 7350 0    50   ~ 0
populate D10*A1 for XBox - D10* otherwise
Text GLabel 1950 6450 1    50   Output ~ 0
LED2
Text GLabel 2900 6450 1    50   Output ~ 0
LED3
Text GLabel 3850 6450 1    50   Output ~ 0
LED4
Text GLabel 4800 6450 1    50   Output ~ 0
LED5
$Comp
L Device:R R120
U 1 1 5E9FF27E
P 1000 6600
F 0 "R120" H 1070 6646 50  0000 L CNN
F 1 "390" H 1070 6555 50  0000 L CNN
F 2 "" V 930 6600 50  0001 C CNN
F 3 "~" H 1000 6600 50  0001 C CNN
	1    1000 6600
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D101
U 1 1 5E9FF284
P 1000 6900
F 0 "D101" V 1039 6782 50  0000 R CNN
F 1 "LED" V 948 6782 50  0000 R CNN
F 2 "" H 1000 6900 50  0001 C CNN
F 3 "~" H 1000 6900 50  0001 C CNN
	1    1000 6900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1000 7050 1000 7200
Wire Wire Line
	1000 7200 1500 7200
Text GLabel 1000 6450 1    50   Output ~ 0
LED1
Connection ~ 1500 7200
Text GLabel 5250 1800 2    50   Output ~ 0
LED1
Text GLabel 5250 2300 2    50   Output ~ 0
LED2
Wire Wire Line
	5400 2200 5250 2200
Text GLabel 5250 2400 2    50   Output ~ 0
LED3
Text GLabel 5250 2500 2    50   Output ~ 0
LED4
Text GLabel 5250 2600 2    50   Output ~ 0
LED5
$Comp
L power:VBUS #PWR07
U 1 1 5EA0D036
P 8900 5600
F 0 "#PWR07" H 8900 5450 50  0001 C CNN
F 1 "VBUS" V 8915 5727 50  0000 L CNN
F 2 "" H 8900 5600 50  0001 C CNN
F 3 "" H 8900 5600 50  0001 C CNN
	1    8900 5600
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C101
U 1 1 5EA0D96E
P 8150 5650
F 0 "C101" H 8265 5696 50  0000 L CNN
F 1 "C" H 8265 5605 50  0000 L CNN
F 2 "" H 8188 5500 50  0001 C CNN
F 3 "~" H 8150 5650 50  0001 C CNN
	1    8150 5650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5EA118A3
P 7750 5800
F 0 "#PWR02" H 7750 5550 50  0001 C CNN
F 1 "GND" H 7755 5627 50  0000 C CNN
F 2 "" H 7750 5800 50  0001 C CNN
F 3 "" H 7750 5800 50  0001 C CNN
	1    7750 5800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R113
U 1 1 5EA1264D
P 7750 5650
F 0 "R113" H 7820 5696 50  0000 L CNN
F 1 "10M" H 7820 5605 50  0000 L CNN
F 2 "" V 7680 5650 50  0001 C CNN
F 3 "~" H 7750 5650 50  0001 C CNN
	1    7750 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 5500 8150 5500
Connection ~ 8150 5500
$Comp
L power:GNDA #PWR04
U 1 1 5EA0C17F
P 8450 5500
F 0 "#PWR04" H 8450 5250 50  0001 C CNN
F 1 "GNDA" H 8455 5327 50  0000 C CNN
F 2 "" H 8450 5500 50  0001 C CNN
F 3 "" H 8450 5500 50  0001 C CNN
	1    8450 5500
	-1   0    0    1   
$EndComp
Wire Wire Line
	8150 5500 8450 5500
Connection ~ 8450 5500
Wire Wire Line
	8150 5800 7750 5800
Connection ~ 7750 5800
$Comp
L Device:C C102
U 1 1 5EA1DF63
P 8900 5750
F 0 "C102" H 9015 5796 50  0000 L CNN
F 1 "C" H 9015 5705 50  0000 L CNN
F 2 "" H 8938 5600 50  0001 C CNN
F 3 "~" H 8900 5750 50  0001 C CNN
	1    8900 5750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5EA1EB45
P 8900 5900
F 0 "#PWR08" H 8900 5650 50  0001 C CNN
F 1 "GND" H 8905 5727 50  0000 C CNN
F 2 "" H 8900 5900 50  0001 C CNN
F 3 "" H 8900 5900 50  0001 C CNN
	1    8900 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 5600 10000 5600
Connection ~ 8900 5600
Wire Wire Line
	8450 5500 10000 5500
$Comp
L power:GND #PWR09
U 1 1 5EA2CA39
P 2650 5250
F 0 "#PWR09" H 2650 5000 50  0001 C CNN
F 1 "GND" H 2655 5077 50  0000 C CNN
F 2 "" H 2650 5250 50  0001 C CNN
F 3 "" H 2650 5250 50  0001 C CNN
	1    2650 5250
	1    0    0    -1  
$EndComp
$Comp
L power:VBUS #PWR05
U 1 1 5EA2CF69
P 2000 4650
F 0 "#PWR05" H 2000 4500 50  0001 C CNN
F 1 "VBUS" V 2015 4777 50  0000 L CNN
F 2 "" H 2000 4650 50  0001 C CNN
F 3 "" H 2000 4650 50  0001 C CNN
	1    2000 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:L L101
U 1 1 5EA33978
P 2000 4800
F 0 "L101" H 1956 4754 50  0000 R CNN
F 1 "L" H 1956 4845 50  0000 R CNN
F 2 "" H 2000 4800 50  0001 C CNN
F 3 "~" H 2000 4800 50  0001 C CNN
	1    2000 4800
	-1   0    0    1   
$EndComp
$Comp
L Device:C C106
U 1 1 5EA3488C
P 2000 5100
F 0 "C106" H 2115 5146 50  0000 L CNN
F 1 "C" H 2115 5055 50  0000 L CNN
F 2 "" H 2038 4950 50  0001 C CNN
F 3 "~" H 2000 5100 50  0001 C CNN
	1    2000 5100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5EA36575
P 2000 5250
F 0 "#PWR06" H 2000 5000 50  0001 C CNN
F 1 "GND" H 2005 5077 50  0000 C CNN
F 2 "" H 2000 5250 50  0001 C CNN
F 3 "" H 2000 5250 50  0001 C CNN
	1    2000 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 4950 2350 4950
$Comp
L Device:C C105
U 1 1 5EA3AE44
P 1500 5100
F 0 "C105" H 1615 5146 50  0000 L CNN
F 1 "C" H 1615 5055 50  0000 L CNN
F 2 "" H 1538 4950 50  0001 C CNN
F 3 "~" H 1500 5100 50  0001 C CNN
	1    1500 5100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 5EA3AE4A
P 1500 5250
F 0 "#PWR03" H 1500 5000 50  0001 C CNN
F 1 "GND" H 1505 5077 50  0000 C CNN
F 2 "" H 1500 5250 50  0001 C CNN
F 3 "" H 1500 5250 50  0001 C CNN
	1    1500 5250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C141
U 1 1 5EA3C357
P 1000 5100
F 0 "C141" H 1115 5146 50  0000 L CNN
F 1 "C" H 1115 5055 50  0000 L CNN
F 2 "" H 1038 4950 50  0001 C CNN
F 3 "~" H 1000 5100 50  0001 C CNN
	1    1000 5100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 5EA3C35D
P 1000 5250
F 0 "#PWR01" H 1000 5000 50  0001 C CNN
F 1 "GND" H 1005 5077 50  0000 C CNN
F 2 "" H 1000 5250 50  0001 C CNN
F 3 "" H 1000 5250 50  0001 C CNN
	1    1000 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 4950 1500 4950
Connection ~ 1500 4950
Connection ~ 2000 4950
$Comp
L power:+3.3V #PWR014
U 1 1 5EA30F50
P 3850 4950
F 0 "#PWR014" H 3850 4800 50  0001 C CNN
F 1 "+3.3V" V 3865 5078 50  0000 L CNN
F 2 "" H 3850 4950 50  0001 C CNN
F 3 "" H 3850 4950 50  0001 C CNN
	1    3850 4950
	0    1    1    0   
$EndComp
$Comp
L Device:C C107
U 1 1 5EA4C414
P 3550 5100
F 0 "C107" H 3665 5146 50  0000 L CNN
F 1 "C" H 3665 5055 50  0000 L CNN
F 2 "" H 3588 4950 50  0001 C CNN
F 3 "~" H 3550 5100 50  0001 C CNN
	1    3550 5100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR013
U 1 1 5EA4C41A
P 3550 5250
F 0 "#PWR013" H 3550 5000 50  0001 C CNN
F 1 "GND" H 3555 5077 50  0000 C CNN
F 2 "" H 3550 5250 50  0001 C CNN
F 3 "" H 3550 5250 50  0001 C CNN
	1    3550 5250
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:MCP1700-3302E_SOT89 U102
U 1 1 5EA2BD2C
P 2650 4950
F 0 "U102" H 2650 5192 50  0000 C CNN
F 1 "6206A 028/33" H 2650 5101 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-89-3" H 2650 5150 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20001826C.pdf" H 2650 4900 50  0001 C CNN
	1    2650 4950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5EA4BF84
P 3050 5250
F 0 "#PWR010" H 3050 5000 50  0001 C CNN
F 1 "GND" H 3055 5077 50  0000 C CNN
F 2 "" H 3050 5250 50  0001 C CNN
F 3 "" H 3050 5250 50  0001 C CNN
	1    3050 5250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C108
U 1 1 5EA4B8E8
P 3050 5100
F 0 "C108" H 3165 5146 50  0000 L CNN
F 1 "C" H 3165 5055 50  0000 L CNN
F 2 "" H 3088 4950 50  0001 C CNN
F 3 "~" H 3050 5100 50  0001 C CNN
	1    3050 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 4950 3050 4950
Wire Wire Line
	3050 4950 3550 4950
Connection ~ 3050 4950
Wire Wire Line
	3550 4950 3700 4950
Connection ~ 3550 4950
$Comp
L Connector:TestPoint TP2
U 1 1 5EA608A4
P 3700 4800
F 0 "TP2" H 3758 4918 50  0000 L CNN
F 1 "VDD1" H 3758 4827 50  0000 L CNN
F 2 "" H 3900 4800 50  0001 C CNN
F 3 "~" H 3900 4800 50  0001 C CNN
	1    3700 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 4800 3700 4950
Connection ~ 3700 4950
Wire Wire Line
	3700 4950 3850 4950
$Comp
L Connector:TestPoint TP3
U 1 1 5EA638F2
P 3800 5250
F 0 "TP3" V 3754 5438 50  0000 L CNN
F 1 "GND" V 3845 5438 50  0000 L CNN
F 2 "" H 4000 5250 50  0001 C CNN
F 3 "~" H 4000 5250 50  0001 C CNN
	1    3800 5250
	0    1    1    0   
$EndComp
Wire Wire Line
	3800 5250 3550 5250
Connection ~ 3550 5250
$Comp
L Memory_EEPROM:AT24CS01-XHM U104
U 1 1 5EA6FB1D
P 5500 5150
F 0 "U104" H 5700 4900 50  0000 C CNN
F 1 "XBOX 2 812440 00808" H 6050 4800 50  0000 C CNN
F 2 "Package_SO:TSSOP-8_4.4x3mm_P0.65mm" H 5500 5150 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-8815-SEEPROM-AT24CS01-02-Datasheet.pdf" H 5500 5150 50  0001 C CNN
	1    5500 5150
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR015
U 1 1 5EA70BC2
P 5500 4450
F 0 "#PWR015" H 5500 4300 50  0001 C CNN
F 1 "+3.3V" H 5515 4623 50  0000 C CNN
F 2 "" H 5500 4450 50  0001 C CNN
F 3 "" H 5500 4450 50  0001 C CNN
	1    5500 4450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR016
U 1 1 5EA7177E
P 5500 5450
F 0 "#PWR016" H 5500 5200 50  0001 C CNN
F 1 "GND" H 5505 5277 50  0000 C CNN
F 2 "" H 5500 5450 50  0001 C CNN
F 3 "" H 5500 5450 50  0001 C CNN
	1    5500 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 5450 5000 5450
Wire Wire Line
	5000 5050 5100 5050
Connection ~ 5500 5450
Text GLabel 5900 5050 2    50   BiDi ~ 0
XBOX1
Text GLabel 5900 5150 2    50   BiDi ~ 0
XBOX2
Text GLabel 5900 5250 2    50   BiDi ~ 0
XBOX3
Text GLabel 3250 1800 0    50   BiDi ~ 0
XBOX3
Text GLabel 3250 2000 0    50   BiDi ~ 0
XBOX1
Text GLabel 3250 2100 0    50   BiDi ~ 0
XBOX2
NoConn ~ 3250 1700
NoConn ~ 3250 1900
Wire Wire Line
	5000 5450 5000 5050
Wire Wire Line
	5100 5250 5050 5250
Wire Wire Line
	5050 5250 5050 5150
Wire Wire Line
	5050 4850 5500 4850
Connection ~ 5500 4850
Wire Wire Line
	5100 5150 5050 5150
Connection ~ 5050 5150
Wire Wire Line
	5050 5150 5050 4850
$Comp
L Device:C C113
U 1 1 5EA87DAA
P 5700 4650
F 0 "C113" V 5448 4650 50  0000 C CNN
F 1 "C" V 5539 4650 50  0000 C CNN
F 2 "" H 5738 4500 50  0001 C CNN
F 3 "~" H 5700 4650 50  0001 C CNN
	1    5700 4650
	0    1    1    0   
$EndComp
Wire Wire Line
	5500 4450 5500 4650
Wire Wire Line
	5500 4650 5550 4650
Connection ~ 5500 4650
Wire Wire Line
	5500 4650 5500 4850
$Comp
L power:GND #PWR022
U 1 1 5EA8FEC8
P 5850 4650
F 0 "#PWR022" H 5850 4400 50  0001 C CNN
F 1 "GND" H 5855 4477 50  0000 C CNN
F 2 "" H 5850 4650 50  0001 C CNN
F 3 "" H 5850 4650 50  0001 C CNN
	1    5850 4650
	1    0    0    -1  
$EndComp
Text Notes 4750 4750 0    50   ~ 0
only populated\nfor XBox version
$Comp
L Device:C C110
U 1 1 5EA9F41C
P 1350 2650
F 0 "C110" H 1465 2696 50  0000 L CNN
F 1 "C" H 1465 2605 50  0000 L CNN
F 2 "" H 1388 2500 50  0001 C CNN
F 3 "~" H 1350 2650 50  0001 C CNN
	1    1350 2650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C109
U 1 1 5EA9FAAF
P 1850 2650
F 0 "C109" H 1965 2696 50  0000 L CNN
F 1 "C" H 1965 2605 50  0000 L CNN
F 2 "" H 1888 2500 50  0001 C CNN
F 3 "~" H 1850 2650 50  0001 C CNN
	1    1850 2650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR019
U 1 1 5EAA029A
P 1350 2800
F 0 "#PWR019" H 1350 2550 50  0001 C CNN
F 1 "GND" H 1355 2627 50  0000 C CNN
F 2 "" H 1350 2800 50  0001 C CNN
F 3 "" H 1350 2800 50  0001 C CNN
	1    1350 2800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR020
U 1 1 5EAA08D7
P 1850 2800
F 0 "#PWR020" H 1850 2550 50  0001 C CNN
F 1 "GND" H 1855 2627 50  0000 C CNN
F 2 "" H 1850 2800 50  0001 C CNN
F 3 "" H 1850 2800 50  0001 C CNN
	1    1850 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 2500 1850 2500
$Comp
L power:+3.3V #PWR018
U 1 1 5EAA38CA
P 1150 2500
F 0 "#PWR018" H 1150 2350 50  0001 C CNN
F 1 "+3.3V" H 1165 2673 50  0000 C CNN
F 2 "" H 1150 2500 50  0001 C CNN
F 3 "" H 1150 2500 50  0001 C CNN
	1    1150 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 2500 1350 2500
Connection ~ 1350 2500
$Comp
L Device:R R118
U 1 1 5EAAC079
P 2400 2650
F 0 "R118" H 2470 2696 50  0000 L CNN
F 1 "unpopulated" H 2470 2605 50  0000 L CNN
F 2 "" V 2330 2650 50  0001 C CNN
F 3 "~" H 2400 2650 50  0001 C CNN
	1    2400 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 2500 2250 2500
Connection ~ 1850 2500
Wire Wire Line
	3250 2500 2400 2500
Wire Wire Line
	2400 2800 3000 2800
Wire Wire Line
	3000 2800 3000 2600
Wire Wire Line
	3000 2600 3250 2600
Wire Wire Line
	2250 2500 2250 2900
Wire Wire Line
	2250 2900 3100 2900
Wire Wire Line
	3100 2900 3100 2700
Wire Wire Line
	3100 2700 3250 2700
Wire Wire Line
	2250 2500 2400 2500
Connection ~ 2250 2500
Connection ~ 2400 2500
$Comp
L Device:R R117
U 1 1 5EAC24D9
P 3400 3350
F 0 "R117" V 3193 3350 50  0000 C CNN
F 1 "1K" V 3284 3350 50  0000 C CNN
F 2 "" V 3330 3350 50  0001 C CNN
F 3 "~" H 3400 3350 50  0001 C CNN
	1    3400 3350
	0    1    1    0   
$EndComp
Wire Wire Line
	3700 3150 3700 3350
Wire Wire Line
	3100 3350 3100 2900
Connection ~ 3100 2900
Wire Wire Line
	3550 3350 3700 3350
Wire Wire Line
	3100 3350 3250 3350
$Comp
L Device:C C103
U 1 1 5EAD21C1
P 3400 3750
F 0 "C103" V 3148 3750 50  0000 C CNN
F 1 "unpopulated" V 3239 3750 50  0000 C CNN
F 2 "" H 3438 3600 50  0001 C CNN
F 3 "~" H 3400 3750 50  0001 C CNN
	1    3400 3750
	0    1    1    0   
$EndComp
Wire Wire Line
	3550 3750 3700 3750
$Comp
L power:GND #PWR021
U 1 1 5EAE16A2
P 3100 3750
F 0 "#PWR021" H 3100 3500 50  0001 C CNN
F 1 "GND" H 3105 3577 50  0000 C CNN
F 2 "" H 3100 3750 50  0001 C CNN
F 3 "" H 3100 3750 50  0001 C CNN
	1    3100 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 3350 3700 3750
Connection ~ 3700 3350
$Comp
L Connector:TestPoint TP6
U 1 1 5EAE82CC
P 3700 3750
F 0 "TP6" H 3642 3776 50  0000 R CNN
F 1 "RST/C2CK" H 3642 3867 50  0000 R CNN
F 2 "" H 3900 3750 50  0001 C CNN
F 3 "~" H 3900 3750 50  0001 C CNN
	1    3700 3750
	-1   0    0    1   
$EndComp
Connection ~ 3700 3750
$Comp
L Connector:TestPoint TP7
U 1 1 5EAE8D5A
P 3800 3500
F 0 "TP7" H 3742 3526 50  0000 R CNN
F 1 "C2D" H 3742 3617 50  0000 R CNN
F 2 "" H 4000 3500 50  0001 C CNN
F 3 "~" H 4000 3500 50  0001 C CNN
	1    3800 3500
	-1   0    0    1   
$EndComp
Wire Wire Line
	3800 3500 3800 3150
Wire Wire Line
	3100 3750 3250 3750
NoConn ~ 3900 3150
NoConn ~ 4000 3150
NoConn ~ 4100 3150
NoConn ~ 4200 3150
NoConn ~ 4300 3150
NoConn ~ 4400 3150
NoConn ~ 4500 3150
NoConn ~ 4600 3150
NoConn ~ 3700 1300
NoConn ~ 3800 1300
Text GLabel 4700 1300 1    50   Input ~ 0
K109
Text GLabel 4800 1300 1    50   Input ~ 0
K110
Text GLabel 5250 1700 2    50   Input ~ 0
K112
Text GLabel 5250 1600 2    50   Input ~ 0
K111
Text GLabel 4600 1300 1    50   Input ~ 0
K108
Text GLabel 4400 1300 1    50   Input ~ 0
K106
Text GLabel 4500 1300 1    50   Input ~ 0
K107
Text GLabel 3900 1300 1    50   Input ~ 0
K101
Text GLabel 4000 1300 1    50   Input ~ 0
K102
Text GLabel 4100 1300 1    50   Input ~ 0
K103
Text GLabel 4200 1300 1    50   Input ~ 0
K104
Text GLabel 4300 1300 1    50   Input ~ 0
K105
$Comp
L Device:R_POT RV1
U 1 1 5EB14253
P 9650 2000
F 0 "RV1" H 9581 2046 50  0000 R CNN
F 1 "R_POT" H 9581 1955 50  0000 R CNN
F 2 "" H 9650 2000 50  0001 C CNN
F 3 "~" H 9650 2000 50  0001 C CNN
	1    9650 2000
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR024
U 1 1 5EB15CC3
P 9650 1750
F 0 "#PWR024" H 9650 1600 50  0001 C CNN
F 1 "+3.3V" H 9665 1923 50  0000 C CNN
F 2 "" H 9650 1750 50  0001 C CNN
F 3 "" H 9650 1750 50  0001 C CNN
	1    9650 1750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR025
U 1 1 5EB163C8
P 9650 2300
F 0 "#PWR025" H 9650 2050 50  0001 C CNN
F 1 "GND" H 9655 2127 50  0000 C CNN
F 2 "" H 9650 2300 50  0001 C CNN
F 3 "" H 9650 2300 50  0001 C CNN
	1    9650 2300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C111
U 1 1 5EB17A6A
P 10000 2150
F 0 "C111" H 10115 2196 50  0000 L CNN
F 1 "C" H 10115 2105 50  0000 L CNN
F 2 "" H 10038 2000 50  0001 C CNN
F 3 "~" H 10000 2150 50  0001 C CNN
	1    10000 2150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR026
U 1 1 5EB1849C
P 10000 2300
F 0 "#PWR026" H 10000 2050 50  0001 C CNN
F 1 "GND" H 10005 2127 50  0000 C CNN
F 2 "" H 10000 2300 50  0001 C CNN
F 3 "" H 10000 2300 50  0001 C CNN
	1    10000 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9800 2000 10000 2000
Text GLabel 10400 2000 2    50   Input ~ 0
POT1
Wire Wire Line
	10400 2000 10000 2000
Connection ~ 10000 2000
$Comp
L Device:C C104
U 1 1 5EB204E2
P 9000 2000
F 0 "C104" H 9115 2046 50  0000 L CNN
F 1 "C" H 9115 1955 50  0000 L CNN
F 2 "" H 9038 1850 50  0001 C CNN
F 3 "~" H 9000 2000 50  0001 C CNN
	1    9000 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	9000 1800 9000 1850
Wire Wire Line
	9650 2300 9650 2150
$Comp
L power:GND #PWR023
U 1 1 5EB335BF
P 9000 2300
F 0 "#PWR023" H 9000 2050 50  0001 C CNN
F 1 "GND" H 9005 2127 50  0000 C CNN
F 2 "" H 9000 2300 50  0001 C CNN
F 3 "" H 9000 2300 50  0001 C CNN
	1    9000 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9000 2300 9000 2150
Wire Wire Line
	9650 1750 9650 1800
Wire Wire Line
	9000 1800 9650 1800
Connection ~ 9650 1800
Wire Wire Line
	9650 1800 9650 1850
Text GLabel 5250 1900 2    50   Input ~ 0
POT1
Text GLabel 5250 2700 2    50   Input ~ 0
SW_DRUMS
Text GLabel 4800 3150 3    50   Input ~ 0
SW_KEYS
Text GLabel 4700 3150 3    50   Input ~ 0
SW_GUITAR
$Comp
L mpa:SW_3POS SW101
U 1 1 5EB5016D
P 9600 1000
F 0 "SW101" H 9650 1240 50  0000 C CNN
F 1 "SW_3POS" H 9650 1149 50  0000 C CNN
F 2 "" H 9500 1250 50  0001 C CNN
F 3 "http://cdn-reichelt.de/documents/datenblatt/C200/DS-Serie%23LOR.pdf" H 9500 1250 50  0001 C CNN
	1    9600 1000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR028
U 1 1 5EB51070
P 9200 1050
F 0 "#PWR028" H 9200 800 50  0001 C CNN
F 1 "GND" H 9205 877 50  0000 C CNN
F 2 "" H 9200 1050 50  0001 C CNN
F 3 "" H 9200 1050 50  0001 C CNN
	1    9200 1050
	1    0    0    -1  
$EndComp
Text GLabel 10100 950  2    50   Input ~ 0
SW_DRUMS
Text GLabel 10100 1050 2    50   Input ~ 0
SW_KEYS
Text GLabel 10100 1150 2    50   Input ~ 0
SW_GUITAR
$Comp
L mpa:PC900V U103
U 1 1 5E99CD11
P 8150 4250
F 0 "U103" H 8150 4500 50  0000 C CNN
F 1 "PC900V" H 8150 4000 50  0000 C CNN
F 2 "" H 8150 4250 50  0001 C CNN
F 3 "" H 8150 4250 50  0001 C CNN
	1    8150 4250
	1    0    0    -1  
$EndComp
NoConn ~ 6950 4750
NoConn ~ 7550 4750
NoConn ~ 7250 4450
$Comp
L Device:D D108
U 1 1 5E9A014B
P 7300 4200
F 0 "D108" V 7254 4279 50  0000 L CNN
F 1 "D" V 7345 4279 50  0000 L CNN
F 2 "" H 7300 4200 50  0001 C CNN
F 3 "~" H 7300 4200 50  0001 C CNN
	1    7300 4200
	0    1    1    0   
$EndComp
Wire Wire Line
	7700 4150 7650 4150
Wire Wire Line
	7650 4150 7650 4050
Wire Wire Line
	7700 4250 7650 4250
Wire Wire Line
	7650 4250 7650 4350
$Comp
L Connector:DIN-5_180degree J1
U 1 1 5E99F3D9
P 7250 4750
F 0 "J1" H 7250 4475 50  0000 C CNN
F 1 "DIN-5_180degree" H 7250 4384 50  0000 C CNN
F 2 "" H 7250 4750 50  0001 C CNN
F 3 "http://www.mouser.com/ds/2/18/40_c091_abd_e-75918.pdf" H 7250 4750 50  0001 C CNN
	1    7250 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 4050 7650 4050
Wire Wire Line
	7300 4350 7550 4350
$Comp
L Device:R R115
U 1 1 5E9A5904
P 6950 4200
F 0 "R115" H 7020 4246 50  0000 L CNN
F 1 "270" H 7020 4155 50  0000 L CNN
F 2 "" V 6880 4200 50  0001 C CNN
F 3 "~" H 6950 4200 50  0001 C CNN
	1    6950 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 4050 7300 4050
Connection ~ 7300 4050
Wire Wire Line
	6950 4350 6950 4650
Wire Wire Line
	7550 4650 7550 4350
Connection ~ 7550 4350
Wire Wire Line
	7550 4350 7650 4350
Text GLabel 9250 4350 2    50   Output ~ 0
MIDI_IN
$Comp
L power:+3.3V #PWR0102
U 1 1 5E99EC9C
P 9150 3850
F 0 "#PWR0102" H 9150 3700 50  0001 C CNN
F 1 "+3.3V" H 9165 4023 50  0000 C CNN
F 2 "" H 9150 3850 50  0001 C CNN
F 3 "" H 9150 3850 50  0001 C CNN
	1    9150 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R114
U 1 1 5E9B188E
P 9150 4000
F 0 "R114" H 9220 4046 50  0000 L CNN
F 1 "1k" H 9220 3955 50  0000 L CNN
F 2 "" V 9080 4000 50  0001 C CNN
F 3 "~" H 9150 4000 50  0001 C CNN
	1    9150 4000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C142
U 1 1 5E9AC768
P 8750 4000
F 0 "C142" H 8635 3954 50  0000 R CNN
F 1 "C" H 8635 4045 50  0000 R CNN
F 2 "" H 8788 3850 50  0001 C CNN
F 3 "~" H 8750 4000 50  0001 C CNN
	1    8750 4000
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5E9C0867
P 8750 4850
F 0 "#PWR0103" H 8750 4600 50  0001 C CNN
F 1 "GND" H 8755 4677 50  0000 C CNN
F 2 "" H 8750 4850 50  0001 C CNN
F 3 "" H 8750 4850 50  0001 C CNN
	1    8750 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 4350 9150 4350
Wire Wire Line
	9150 4150 9150 4350
Connection ~ 9150 4350
Wire Wire Line
	9150 4350 9250 4350
Wire Wire Line
	9150 3850 8750 3850
Connection ~ 9150 3850
Wire Wire Line
	8750 4150 8750 4250
Wire Wire Line
	8750 4250 8600 4250
Wire Wire Line
	8600 4150 8600 3850
Wire Wire Line
	8600 3850 8750 3850
Connection ~ 8750 3850
$Comp
L Device:C C112
U 1 1 5E9D20F9
P 9150 4650
F 0 "C112" H 9265 4696 50  0000 L CNN
F 1 "unpopulated" H 9265 4605 50  0000 L CNN
F 2 "" H 9188 4500 50  0001 C CNN
F 3 "~" H 9150 4650 50  0001 C CNN
	1    9150 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 4800 8750 4800
Connection ~ 8750 4800
Wire Wire Line
	8750 4800 8750 4850
Text Label 6950 4500 1    50   ~ 0
P5
Text Label 7550 4500 1    50   ~ 0
P4
Wire Wire Line
	8750 4250 8750 4800
Connection ~ 8750 4250
Wire Wire Line
	9150 4500 9150 4350
$Comp
L Switch:SW_Push K101
U 1 1 5EB5D11F
P 7250 1150
F 0 "K101" H 7250 1435 50  0000 C CNN
F 1 "LEFT" H 7250 1344 50  0000 C CNN
F 2 "" H 7250 1350 50  0001 C CNN
F 3 "" H 7250 1350 50  0001 C CNN
	1    7250 1150
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push K102
U 1 1 5EB5DB8C
P 7250 1600
F 0 "K102" H 7250 1885 50  0000 C CNN
F 1 "RIGHT" H 7250 1794 50  0000 C CNN
F 2 "" H 7250 1800 50  0001 C CNN
F 3 "" H 7250 1800 50  0001 C CNN
	1    7250 1600
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push K103
U 1 1 5EB5E43F
P 7250 2050
F 0 "K103" H 7250 2335 50  0000 C CNN
F 1 "UP" H 7250 2244 50  0000 C CNN
F 2 "" H 7250 2250 50  0001 C CNN
F 3 "" H 7250 2250 50  0001 C CNN
	1    7250 2050
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push K104
U 1 1 5EB5E445
P 7250 2500
F 0 "K104" H 7250 2785 50  0000 C CNN
F 1 "DOWN" H 7250 2694 50  0000 C CNN
F 2 "" H 7250 2700 50  0001 C CNN
F 3 "" H 7250 2700 50  0001 C CNN
	1    7250 2500
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push K105
U 1 1 5EB61471
P 7250 2900
F 0 "K105" H 7250 3185 50  0000 C CNN
F 1 "OVERDRIVE" H 7250 3094 50  0000 C CNN
F 2 "" H 7250 3100 50  0001 C CNN
F 3 "" H 7250 3100 50  0001 C CNN
	1    7250 2900
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push K106
U 1 1 5EB61477
P 7250 3350
F 0 "K106" H 7250 3635 50  0000 C CNN
F 1 "SELECT" H 7250 3544 50  0000 C CNN
F 2 "" H 7250 3550 50  0001 C CNN
F 3 "" H 7250 3550 50  0001 C CNN
	1    7250 3350
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push K107
U 1 1 5EB6540F
P 7950 1150
F 0 "K107" H 7950 1435 50  0000 C CNN
F 1 "HOME" H 7950 1344 50  0000 C CNN
F 2 "" H 7950 1350 50  0001 C CNN
F 3 "" H 7950 1350 50  0001 C CNN
	1    7950 1150
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push K108
U 1 1 5EB65415
P 7950 1600
F 0 "K108" H 7950 1885 50  0000 C CNN
F 1 "START" H 7950 1794 50  0000 C CNN
F 2 "" H 7950 1800 50  0001 C CNN
F 3 "" H 7950 1800 50  0001 C CNN
	1    7950 1600
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push K109
U 1 1 5EB6541B
P 7950 2050
F 0 "K109" H 7950 2335 50  0000 C CNN
F 1 "SQUARE" H 7950 2244 50  0000 C CNN
F 2 "" H 7950 2250 50  0001 C CNN
F 3 "" H 7950 2250 50  0001 C CNN
	1    7950 2050
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push K110
U 1 1 5EB65421
P 7950 2500
F 0 "K110" H 7950 2785 50  0000 C CNN
F 1 "TRIANGLE" H 7950 2694 50  0000 C CNN
F 2 "" H 7950 2700 50  0001 C CNN
F 3 "" H 7950 2700 50  0001 C CNN
	1    7950 2500
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push K111
U 1 1 5EB65427
P 7950 2900
F 0 "K111" H 7950 3185 50  0000 C CNN
F 1 "CROSS" H 7950 3094 50  0000 C CNN
F 2 "" H 7950 3100 50  0001 C CNN
F 3 "" H 7950 3100 50  0001 C CNN
	1    7950 2900
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push K112
U 1 1 5EB6542D
P 7950 3350
F 0 "K112" H 7950 3635 50  0000 C CNN
F 1 "CIRCLE" H 7950 3544 50  0000 C CNN
F 2 "" H 7950 3550 50  0001 C CNN
F 3 "" H 7950 3550 50  0001 C CNN
	1    7950 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 1600 7600 1600
Wire Wire Line
	7450 2050 7600 2050
Wire Wire Line
	7450 2500 7600 2500
Wire Wire Line
	7750 2900 7600 2900
Wire Wire Line
	7450 3350 7600 3350
Wire Wire Line
	7450 1150 7600 1150
Wire Wire Line
	7600 1150 7600 1600
Connection ~ 7600 1150
Wire Wire Line
	7600 1150 7750 1150
Connection ~ 7600 1600
Wire Wire Line
	7600 1600 7750 1600
Wire Wire Line
	7600 1600 7600 2050
Connection ~ 7600 2050
Wire Wire Line
	7600 2050 7750 2050
Wire Wire Line
	7600 2050 7600 2500
Connection ~ 7600 2500
Wire Wire Line
	7600 2500 7750 2500
Wire Wire Line
	7600 2500 7600 2900
Connection ~ 7600 2900
Wire Wire Line
	7600 2900 7450 2900
Wire Wire Line
	7600 2900 7600 3350
Connection ~ 7600 3350
Wire Wire Line
	7600 3350 7750 3350
$Comp
L power:GND #PWR027
U 1 1 5EB9ABF4
P 7600 3350
F 0 "#PWR027" H 7600 3100 50  0001 C CNN
F 1 "GND" H 7605 3177 50  0000 C CNN
F 2 "" H 7600 3350 50  0001 C CNN
F 3 "" H 7600 3350 50  0001 C CNN
	1    7600 3350
	1    0    0    -1  
$EndComp
Text GLabel 6450 1150 0    50   Input ~ 0
K101
Text GLabel 6450 1600 0    50   Input ~ 0
K102
Text GLabel 6450 2500 0    50   Input ~ 0
K104
Text GLabel 6450 2050 0    50   Input ~ 0
K103
Text GLabel 6450 2900 0    50   Input ~ 0
K105
Text GLabel 6450 3350 0    50   Input ~ 0
K106
Text GLabel 8300 3350 2    50   Input ~ 0
K112
Text GLabel 8300 2900 2    50   Input ~ 0
K111
Text GLabel 8300 2500 2    50   Input ~ 0
K110
Text GLabel 8300 2050 2    50   Input ~ 0
K109
Text GLabel 8300 1600 2    50   Input ~ 0
K108
Text GLabel 8300 1150 2    50   Input ~ 0
K107
Text Notes 10050 4150 0    50   ~ 0
JP1 JP2 Model\n  x   0  PS3\n  0   1  Wii\n  1   1  XBox
$Comp
L Connector:TestPoint TP9
U 1 1 5EC088E7
P 6600 1450
F 0 "TP9" H 6658 1568 50  0000 L CNN
F 1 "TestPoint" H 6658 1477 50  0000 L CNN
F 2 "" H 6800 1450 50  0001 C CNN
F 3 "~" H 6800 1450 50  0001 C CNN
	1    6600 1450
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP10
U 1 1 5EC092C5
P 6600 1900
F 0 "TP10" H 6658 2018 50  0000 L CNN
F 1 "TestPoint" H 6658 1927 50  0000 L CNN
F 2 "" H 6800 1900 50  0001 C CNN
F 3 "~" H 6800 1900 50  0001 C CNN
	1    6600 1900
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP11
U 1 1 5EC09C3F
P 6600 2350
F 0 "TP11" H 6658 2468 50  0000 L CNN
F 1 "TestPoint" H 6658 2377 50  0000 L CNN
F 2 "" H 6800 2350 50  0001 C CNN
F 3 "~" H 6800 2350 50  0001 C CNN
	1    6600 2350
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP12
U 1 1 5EC0A5AE
P 6600 2750
F 0 "TP12" H 6658 2868 50  0000 L CNN
F 1 "TestPoint" H 6658 2777 50  0000 L CNN
F 2 "" H 6800 2750 50  0001 C CNN
F 3 "~" H 6800 2750 50  0001 C CNN
	1    6600 2750
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP13
U 1 1 5EC0AF82
P 6600 3200
F 0 "TP13" H 6658 3318 50  0000 L CNN
F 1 "TestPoint" H 6658 3227 50  0000 L CNN
F 2 "" H 6800 3200 50  0001 C CNN
F 3 "~" H 6800 3200 50  0001 C CNN
	1    6600 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 1150 6600 1150
$Comp
L Connector:TestPoint TP8
U 1 1 5EC07D2C
P 6600 1000
F 0 "TP8" H 6658 1118 50  0000 L CNN
F 1 "TestPoint" H 6658 1027 50  0000 L CNN
F 2 "" H 6800 1000 50  0001 C CNN
F 3 "~" H 6800 1000 50  0001 C CNN
	1    6600 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 1000 6600 1150
Connection ~ 6600 1150
Wire Wire Line
	6600 1150 7050 1150
Wire Wire Line
	6450 1600 6600 1600
Wire Wire Line
	6600 1450 6600 1600
Connection ~ 6600 1600
Wire Wire Line
	6600 1600 7050 1600
Wire Wire Line
	6450 2050 6600 2050
Wire Wire Line
	6600 2050 6600 1900
Wire Wire Line
	6600 2050 7050 2050
Connection ~ 6600 2050
Wire Wire Line
	6450 2500 6600 2500
Wire Wire Line
	6600 2350 6600 2500
Connection ~ 6600 2500
Wire Wire Line
	6600 2500 7050 2500
Wire Wire Line
	6450 2900 6600 2900
Wire Wire Line
	6600 2750 6600 2900
Connection ~ 6600 2900
Wire Wire Line
	6600 2900 7050 2900
Wire Wire Line
	6450 3350 6600 3350
Wire Wire Line
	6600 3200 6600 3350
Connection ~ 6600 3350
Wire Wire Line
	6600 3350 7050 3350
$Comp
L Connector:TestPoint TP14
U 1 1 5EC507E0
P 8200 1000
F 0 "TP14" H 8258 1118 50  0000 L CNN
F 1 "TestPoint" H 8258 1027 50  0000 L CNN
F 2 "" H 8400 1000 50  0001 C CNN
F 3 "~" H 8400 1000 50  0001 C CNN
	1    8200 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 1150 8200 1150
Wire Wire Line
	8200 1000 8200 1150
Connection ~ 8200 1150
Wire Wire Line
	8200 1150 8300 1150
$Comp
L Connector:TestPoint TP15
U 1 1 5EC61EDB
P 8200 1450
F 0 "TP15" H 8258 1568 50  0000 L CNN
F 1 "TestPoint" H 8258 1477 50  0000 L CNN
F 2 "" H 8400 1450 50  0001 C CNN
F 3 "~" H 8400 1450 50  0001 C CNN
	1    8200 1450
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP16
U 1 1 5EC628D7
P 8200 1900
F 0 "TP16" H 8258 2018 50  0000 L CNN
F 1 "TestPoint" H 8258 1927 50  0000 L CNN
F 2 "" H 8400 1900 50  0001 C CNN
F 3 "~" H 8400 1900 50  0001 C CNN
	1    8200 1900
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP17
U 1 1 5EC631FD
P 8200 2350
F 0 "TP17" H 8258 2468 50  0000 L CNN
F 1 "TestPoint" H 8258 2377 50  0000 L CNN
F 2 "" H 8400 2350 50  0001 C CNN
F 3 "~" H 8400 2350 50  0001 C CNN
	1    8200 2350
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP18
U 1 1 5EC63B10
P 8200 2750
F 0 "TP18" H 8258 2868 50  0000 L CNN
F 1 "TestPoint" H 8258 2777 50  0000 L CNN
F 2 "" H 8400 2750 50  0001 C CNN
F 3 "~" H 8400 2750 50  0001 C CNN
	1    8200 2750
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP19
U 1 1 5EC64457
P 8200 3200
F 0 "TP19" H 8258 3318 50  0000 L CNN
F 1 "TestPoint" H 8258 3227 50  0000 L CNN
F 2 "" H 8400 3200 50  0001 C CNN
F 3 "~" H 8400 3200 50  0001 C CNN
	1    8200 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 1600 8200 1600
Wire Wire Line
	8200 1450 8200 1600
Connection ~ 8200 1600
Wire Wire Line
	8200 1600 8300 1600
Wire Wire Line
	8150 2050 8200 2050
Wire Wire Line
	8200 1900 8200 2050
Connection ~ 8200 2050
Wire Wire Line
	8200 2050 8300 2050
Wire Wire Line
	8150 2500 8200 2500
Wire Wire Line
	8200 2350 8200 2500
Connection ~ 8200 2500
Wire Wire Line
	8200 2500 8300 2500
Wire Wire Line
	8150 2900 8200 2900
Wire Wire Line
	8200 2750 8200 2900
Connection ~ 8200 2900
Wire Wire Line
	8200 2900 8300 2900
Wire Wire Line
	8150 3350 8200 3350
Wire Wire Line
	8200 3200 8200 3350
Connection ~ 8200 3350
Wire Wire Line
	8200 3350 8300 3350
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5ECCF039
P 1200 4400
F 0 "#FLG0102" H 1200 4475 50  0001 C CNN
F 1 "PWR_FLAG" V 1200 4528 50  0000 L CNN
F 2 "" H 1200 4400 50  0001 C CNN
F 3 "~" H 1200 4400 50  0001 C CNN
	1    1200 4400
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 5ECCF9D0
P 1200 4400
F 0 "#PWR0105" H 1200 4150 50  0001 C CNN
F 1 "GND" V 1205 4272 50  0000 R CNN
F 2 "" H 1200 4400 50  0001 C CNN
F 3 "" H 1200 4400 50  0001 C CNN
	1    1200 4400
	0    1    1    0   
$EndComp
$Comp
L power:VBUS #PWR0104
U 1 1 5ECCE6C1
P 1200 4250
F 0 "#PWR0104" H 1200 4100 50  0001 C CNN
F 1 "VBUS" V 1215 4377 50  0000 L CNN
F 2 "" H 1200 4250 50  0001 C CNN
F 3 "" H 1200 4250 50  0001 C CNN
	1    1200 4250
	0    -1   -1   0   
$EndComp
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5ECCD5DF
P 1200 4250
F 0 "#FLG0101" H 1200 4325 50  0001 C CNN
F 1 "PWR_FLAG" V 1200 4378 50  0000 L CNN
F 2 "" H 1200 4250 50  0001 C CNN
F 3 "~" H 1200 4250 50  0001 C CNN
	1    1200 4250
	0    1    1    0   
$EndComp
$Comp
L power:PWR_FLAG #FLG0104
U 1 1 5ECDF40C
P 1200 4550
F 0 "#FLG0104" H 1200 4625 50  0001 C CNN
F 1 "PWR_FLAG" V 1200 4678 50  0000 L CNN
F 2 "" H 1200 4550 50  0001 C CNN
F 3 "~" H 1200 4550 50  0001 C CNN
	1    1200 4550
	0    1    1    0   
$EndComp
$Comp
L power:GNDA #PWR0106
U 1 1 5ECF4E97
P 1200 4550
F 0 "#PWR0106" H 1200 4300 50  0001 C CNN
F 1 "GNDA" V 1205 4423 50  0000 R CNN
F 2 "" H 1200 4550 50  0001 C CNN
F 3 "" H 1200 4550 50  0001 C CNN
	1    1200 4550
	0    1    1    0   
$EndComp
Wire Wire Line
	1750 4950 2000 4950
Wire Wire Line
	1500 4950 1750 4950
Connection ~ 1750 4950
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 5ECD735A
P 1750 4950
F 0 "#FLG0103" H 1750 5025 50  0001 C CNN
F 1 "PWR_FLAG" H 1750 5123 50  0000 C CNN
F 2 "" H 1750 4950 50  0001 C CNN
F 3 "~" H 1750 4950 50  0001 C CNN
	1    1750 4950
	1    0    0    -1  
$EndComp
$EndSCHEMATC