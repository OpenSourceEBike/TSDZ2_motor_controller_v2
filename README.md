   
This repository has technical documentation about TSDZ2 motor controller V2 as also very initial, unfinished and not tested, OpenSource firmware for it.

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
