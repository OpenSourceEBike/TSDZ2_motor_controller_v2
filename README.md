This project is not in development anymore. Instead, the idea is to use a small cheap VESC and install it inside the TSDZ2 motor, or outside, in a DIY way. Then a very small ESP32-C3 board, running high level Python firmware, read the sensors and send the commands to VESC to control the motor -- this is already done for other EBike motors lke Bafang M500 motor, or to Xiaomi M365 scooters or even more powerful 2000W microscooters as Fiido Q1S, see here:

**[https://opensourceebike.github.io](https://opensourceebike.github.io)**

<img width="500" src="https://opensourceebike.github.io/build_EBike_Bafang_M500/build_EBike_board/EBike_board-7.jpg">

<img width="500" src="https://opensourceebike.github.io/build_EBike_Bafang_M500/build_EBike_board/EBike_board-8.jpg">

<img width="500" src="https://opensourceebike.github.io/build_EBike_Bafang_M500/build_EBike_board/EBike_board-9.jpg">

<img width="500" src="https://opensourceebike.github.io/build_EBike_Bafang_M500/build_EBike_board/EBike_board-10.jpg">

<img width="500" src="https://raw.githubusercontent.com/OpenSourceEBike/EBike_EScooter_modular_DIY/6aad16155386fc06487ee748e54e567ec3f17f46/images/bici_small.jpg">

***

This repository has technical documentation about TSDZ2 motor controller V2 as also very initial, unfinished and not tested, OpenSource firmware for it.

To build the current firmware, call "make" on the command line (tested on Linux). This [Makefile](https://github.com/OpenSourceEBike/TSDZ2_motor_controller_v2/blob/master/Makefile) is where is defined which sources files are used to build the firmware.

You can buy the [TSDZ2 motor controller V2 on Enerprof](https://enerprof.de/).

Forum messages:
* [Discussion at Endless Sphere](https://endless-sphere.com/forums/viewtopic.php?f=30&t=111287)  
* [Discussion at Pedelecforum](https://www.pedelecforum.de/forum/index.php?threads/neue-tsdz2-controller-open-source.86546)

Important documentation:
* **[Hardware page](Documentation/readme.md)**
* **[How to flash and debug the firmware](Documentation/how_to_develop.md)**

Microcontroller XMC1300:
* [XMC1300 datasheet](Documentation/XMC1300_datasheet.pdf)
* [XMC1300 reference manual](Documentation/XMC1300_reference_manual.pdf)
* [XMC1300 math coprocessor](Documentation/Infineon-IP_MATH_XMC1000-TR-v01_02-EN.pdf)
* [XMC1300 FOC paper from Infineon](Documentation/Infineon-AP32370_PMSM_FOC_for_XMC1000-AN-v01_00-EN.pdf) 
* [XMC1300FOC DAVE sample code](Documentation/PMSM_FOC_EXAMPLE_XMC13.zip) 
* [Visual Studio Code Linux installation](https://github.com/OpenSourceEBike/TSDZ2_wireless/blob/master/EBike_wireless_TSDZ2/documentation/development-flash_and_debug_firmware.md)

Technical characteristics of TSDZ2 electric motor:
- there are 2 different motors, one that is 36V and other 48V
- motor voltage: 36V or 48V
- no load speed: 4000 RPM for both motors
- motor resistance: 36V motor has 0.094 ohm, 48V motor has 0.125 ohm
- motor inductance: 36V motor has 76uH, 48V motor has 135uH
- pole pair: 8 for both motors
