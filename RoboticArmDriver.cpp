/*
 * RoboticArmDriver.cpp
 *
 *  Created on: 08/10/2014
 *      Author: laso
 */

#include "lasote/usb_robotic_arm/RoboticArmDriver.h"
#include <iostream>

#define DEBUG_LEVEL 3

namespace lasote {


	RoboticArmDriver::RoboticArmDriver() : dev_handle(0), ctx(0) {

	}

	RoboticArmDriver::~RoboticArmDriver() {
		this->release_library_and_device();
	}

	void RoboticArmDriver::setup_device(){
		int ret; //for return values
		//Init interface
		this->init_library_and_device(VID, PID);
	}

	void RoboticArmDriver::stop(){
		unsigned char data[3];
		data[0] = 0; data[1] = 0; data[2] = 0;
		this->send_control_transfer(bmRequestType, bRequest, wValue, wIndex, data, wLength, timeout);
	}

	void RoboticArmDriver::light(bool on){
		unsigned char data[3];
		data[0] = 0;
		data[1] = 0;
		if(on) data[2] = 0xFF; else	data[2] = 0;

		this->send_control_transfer(bmRequestType, bRequest, wValue, wIndex, data, wLength, timeout);
	}

	void RoboticArmDriver::turn_base(bool right){
		unsigned char data[3];
		data[0] = 0;
		if(right) data[1] = 1; else	data[1] = 2;
		data[2] = 0;

		this->send_control_transfer(bmRequestType, bRequest, wValue, wIndex, data, wLength, timeout);
	}

	void RoboticArmDriver::motor1(bool up){
		unsigned char data[3];
		if(up) data[0] = 0x40; else	data[0] = 0x80;
		data[1] = 0; data[2] = 0;

 		this->send_control_transfer(bmRequestType, bRequest, wValue, wIndex, data, wLength, timeout);
	}

	void RoboticArmDriver::motor2(bool up){
		unsigned char data[3];
		if(up) data[0] = 0x10; else	data[0] = 0x20;
		data[1] = 0; data[2] = 0;

		this->send_control_transfer(bmRequestType, bRequest, wValue, wIndex, data, wLength, timeout);
	}

	void RoboticArmDriver::motor3(bool up){
		unsigned char data[3];
		if(up) data[0] = 0x04; else	data[0] = 0x08;
		data[1] = 0; data[2] = 0;

		this->send_control_transfer(bmRequestType, bRequest, wValue, wIndex, data, wLength, timeout);
	}

	void RoboticArmDriver::clamp(bool open){
		unsigned char data[3];
		if(open) data[0] = 0x02; else data[0] = 0x01;
		data[1] = 0; data[2] = 0;

		this->send_control_transfer(bmRequestType, bRequest, wValue, wIndex, data, wLength, timeout);
	}

	// PRIVATE METHODS
	void RoboticArmDriver::send_control_transfer(uint8_t bmRequestType, uint8_t bRequest, uint16_t wValue, uint16_t wIndex, unsigned char* data, uint16_t wLength, unsigned int timeout){
		int res = libusb_control_transfer(dev_handle, bmRequestType, bRequest, wValue, wIndex, (unsigned char*) data, wLength, timeout);

		if (res < 0) {
			throw UsbException("Init Error: " + res); //there was an error
		}
		else if ((unsigned int) res < 1) {
			throw UsbException("Short Read: " + res); //there was an error
		}
	}

	void RoboticArmDriver::init_library_and_device(int vid, int pid){
		int r; //for return values
		r = libusb_init(&ctx); //initialize the library for the session we just declared
		if(r < 0) {
			throw UsbException("Init Error: " + r); //there was an error
		}
		libusb_set_debug(ctx, DEBUG_LEVEL); //set verbosity level to 3, as suggested in the documentation

		this->dev_handle = libusb_open_device_with_vid_pid(ctx, vid, pid); //these are vendorID and productID I found for my usb device
		if(dev_handle == 0){
			throw UsbException("Cannot open device, try with sudo");
		}

		if(libusb_kernel_driver_active(dev_handle, 0) == 1) { //find out if kernel driver is attached
			cout << "Kernel Driver Active" << endl;
			if(libusb_detach_kernel_driver(dev_handle, 0) == 0) //detach it
				throw UsbException("Kernel Driver Detached!");
		}

		r = libusb_set_configuration(dev_handle, 1);
		if (r < 0) {
			throw UsbException("libusb_set_configuration error: " + r);
		}

		r = libusb_claim_interface(dev_handle, 0); //claim interface 0 (the first) of device (mine had jsut 1)
		if(r < 0) {
			throw UsbException("Cant claim interface! err:" +  r);
		}
	}


	void RoboticArmDriver::release_library_and_device(){
		//Release interface
		int r; //for return values
		r = libusb_release_interface(dev_handle, 0); //release the claimed interface
		if(r != 0) {
			throw UsbException("Cannot release interface");
		}

		//Close library
		libusb_close(dev_handle); //close the device we opened
		libusb_exit(ctx); //needs to be called to end the
	}

} /* namespace lasote */
