/*
 * RoboticArmDriver.h
 *
 *  Created on: 08/10/2014
 *      Author: laso
 */

#ifndef ROBOTICARMDRIVER_H_
#define ROBOTICARMDRIVER_H_

#include <libusb.h>
#define VID 0x1267
#define PID 0
#define CTRL_IN  (LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_ENDPOINT_IN)
#define CTRL_OUT (LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_ENDPOINT_OUT)
#include <string>
#include <exception>

using namespace std;

namespace lasote {

	class RoboticArmDriver {
		public:
			RoboticArmDriver();
			virtual ~RoboticArmDriver();
			void setup_device();
			void light(bool on);
			void turn_base(bool right); //LEFT or RIGHT
			void motor1(bool up); // UP or DOWN
			void motor2(bool up); // UP or DOWN
			void motor3(bool up); // UP or DOWN
			void clamp(bool open); // OPEN or CLOSE
			void stop();

		protected:
			libusb_device_handle *dev_handle;
			libusb_context *ctx;

			// All control traces with this data
			static const  uint8_t bmRequestType = CTRL_OUT;
			static const uint8_t bRequest = 0x06;
			static const uint16_t wValue = 0x0100;
			static const uint16_t wIndex = 0;
			static const uint16_t wLength = 3;
			static const unsigned int timeout = 5000; //in ms

			void init_library_and_device(int vid, int pid);
			void release_library_and_device();
			void send_control_transfer();
			void send_control_transfer(uint8_t bmRequestType, uint8_t bRequest, uint16_t wValue, uint16_t wIndex, unsigned char* data, uint16_t wLength, unsigned int timeout);
	};

	class UsbException: public exception{
		public:
			string desc;
			UsbException(string desc) : desc(desc){}
			~UsbException() throw(){

			}
			virtual const char* what() const throw(){
				return desc.c_str();
			}
			//Change the code for custom exception
	};


} /* namespace lasote */
#endif /* ROBOTICARMDRIVER_H_ */
