#How to upgrate keil project to vs2015 project
- First, finish all project settings using keil.
- Then, run keil2vs.exe

'''Project name'''

Use the file name (*) of *.uvproj

'''Project path'''

Use your *.uvproj location.

For example, the path of this project is 

...\...\Navigation\Codes\Car_Controller\Project\project.uvproj

'''System path'''

Use ...\Keil_v5\ARM\RV31\INC

- Open project.dsp, upgrate to .sln file with vs2015.

- Add these three files into @include path

'''...\Keil_v5\ARM\RV31\INC'''

'''...\Keil_v5\ARM\CMSIS\Include'''

'''...\Keil_v5\ARM\INC\ST\STM32F10x'''

- Finally, you need to slightly change the file stm32f10x.h

Find this line:

		#include <stdint.h>

Use these codes below instead/
		
		#ifdef MVC_VER
			#include "VSPatch.h"
		#else
			#include <stdint.h>
		#endif
