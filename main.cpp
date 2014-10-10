#include <iostream>
#include <libusb.h>
#include "RoboticArmDriver.h"
#include <stdio.h>
#include <unistd.h>

using namespace std;
using namespace lasote;

#define ACTION_TIME 1
#define SHORT_ACTION_TIME 500000

int main() {
	
	bool light = false;

	try{
		RoboticArmDriver driver;
		driver.setup_device();
		while(1){
			char c = getchar();
			switch(c){
				case 'l':
					light = !light; driver.light(light);  break;
				case 'w':
					driver.clamp(false); usleep(SHORT_ACTION_TIME); driver.stop(); break;
				case 's':
					driver.clamp(true); usleep(SHORT_ACTION_TIME); driver.stop(); break;
				case 'e':
					driver.motor3(false); sleep(ACTION_TIME); driver.stop(); break;
				case 'd':
					driver.motor3(true); sleep(ACTION_TIME); driver.stop(); break;
				case 'r':
					driver.motor2(false); sleep(ACTION_TIME); driver.stop(); break;
				case 'f':
					driver.motor2(true); sleep(ACTION_TIME); driver.stop(); break;
				case 'u':
					driver.motor1(true); sleep(ACTION_TIME); driver.stop(); break;
				case 'j':
					driver.motor1(false); sleep(ACTION_TIME); driver.stop(); break;
				case 'i':
					driver.turn_base(true); sleep(ACTION_TIME); driver.stop(); break;
				case 'k':
					driver.turn_base(false); sleep(ACTION_TIME); driver.stop(); break;

			}
		}
	}
	catch(const UsbException& e){
		cout << "ERROR!!" << endl;
		cout << e.what() << endl;
	}


	return 0;
}
