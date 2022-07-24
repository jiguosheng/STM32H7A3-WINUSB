#pragma once

#include "stdio.h"
#include "string.h"
#include "libusb.h"
#include "usbthread.h"

#define CANDLE_MAX_DEVICES 32


#define RECV_LEN    65535//4096

class WinUSB
{
private:
	int recv_len_count = 0;
	int ret;

	unsigned char recv_buf[RECV_LEN];
	unsigned char recv_buf_tmp[RECV_LEN + 1];
	int recv_len;
	bool is_open;
	libusb_device **devs, *dev;
	libusb_device_handle *dev_handle = NULL;
	struct libusb_device_descriptor desc;
	libusb_config_descriptor *cfg = NULL;
	struct libusb_transfer* m_xfer;

	USBThread usb_thread;
public:
	WinUSB();
	~WinUSB();
	int open(int vid, int pid);
	int close(void);
	static void LIBUSB_CALL completeCallback(libusb_transfer *xfer);
	void send(unsigned char *data, int len);

	int total_len = 0;
};


