#include "WinUSB.h"


WinUSB::WinUSB()
{
}


WinUSB::~WinUSB()
{
}

#define USB_VID         0x07E4          //USB的产商ID
#define USB_PID         0x07E4          //USB的产品ID

#define EP0ADDR         0x01            //Write端口0地址，通道0
#define EP1ADDR         0x81            //Read 端口1地址，通道1
//#define EP2ADDR         0x02            //Write端口2地址，通道2
//#define EP3ADDR         0x86            //Read 端口3地址，通道3

#define USB_TIMEOUT     10000           //传输数据的时间延迟

libusb_context* m_libusb_context;

void LIBUSB_CALL WinUSB::completeCallback(libusb_transfer *xfer)
{
	WinUSB *driver = (WinUSB *)xfer->user_data;

	switch (xfer->status)
	{
	case LIBUSB_TRANSFER_COMPLETED:

		if (xfer->actual_length > 0){

			driver->recv_len = xfer->actual_length;
			//memcpy(driver->recv_buf_tmp, xfer->buffer, xfer->actual_length);
			//printf("%s\n", driver->recv_buf_tmp);
			driver->total_len += driver->recv_len;
		}


		break;
	case LIBUSB_TRANSFER_CANCELLED:
		
		return;
		break;
	case LIBUSB_TRANSFER_NO_DEVICE:
		
		break;
	case LIBUSB_TRANSFER_TIMED_OUT:
		
		break;
	case LIBUSB_TRANSFER_ERROR:
		
		break;
	case LIBUSB_TRANSFER_STALL:
		
		driver->close();

		break;
	case LIBUSB_TRANSFER_OVERFLOW:
		
		break;
	default:
		break;
	}

	if (driver->is_open)
	{
		int r = libusb_submit_transfer(xfer);
		if (r < 0){
			//"fail to re-submit transfer";

		}
	}

}



int WinUSB::open(int vid, int pid)
{

	int error = 0, i = 0;
	dev_handle = NULL;


	ret = libusb_init(&m_libusb_context);
	if (ret < 0) {

		//"failed to initialise libusb"

		error = 1;
		goto init_fail;
	}
	else{
		//"initialise libusb success"
	}

	//    dev_handle = libusb_open_device_with_vid_pid(m_libusb_context, vid, pid);
	//    if (dev_handle == NULL) {
	//        DBG("Cannot open device\n");
	//    }
	//    else {
	//        DBG("Device Opened\n");
	//    }

	ret = libusb_get_device_list(m_libusb_context, &devs);
	if (ret < 0)
	{
		//"get usb device list error when open"
		error = 1;
		goto get_list_fail;
	}
	else{
		//"libusb_get_device_list success"
	}

	while ((dev = devs[i++]) != NULL)
	{
		//"start to get device descriptor"
		ret = libusb_get_device_descriptor(dev, &desc);
		if (ret < 0) {
			//"failed to get device descriptor"
			error = 1;
			goto fail;
		}
		else{
			
			if (desc.idVendor == vid && desc.idProduct == pid)
			{

				ret = libusb_open(dev, &dev_handle);
				if (ret < 0)
				{
					dev_handle = NULL;
					//"fail to open usb device"
					error = 1;
					goto open_fail;
				}
				else{
					//"libusb_open success"
					break;
				}
			}
		}
	}
	libusb_free_device_list(devs, 1);

	if (dev_handle == NULL)
	{
		//"fail find device"
		error = 1;
		goto find_device_fail;
	}

	ret = libusb_get_active_config_descriptor(dev, &cfg);
	if (ret < 0){
		//"Fail to get device config_descriptor"
		error = 1;
		goto get_config_fail;
	}
	else{
		//"libusb_get_active_config_descriptor success"
	}

	for (int j = 0; j < cfg->bNumInterfaces; j++){
		const struct libusb_interface_descriptor *interface_desc = (cfg->interface + j)->altsetting;

	}

	libusb_free_config_descriptor(cfg);

	ret = libusb_detach_kernel_driver(dev_handle, 0);
	if (ret < 0){
		//"Fail to libusb_detach_kernel_driver"
	}

	ret = libusb_claim_interface(dev_handle, 0);
	if (ret < 0){
		//"Fail to libusb_claim_interface"
	}

	m_xfer = libusb_alloc_transfer(0);

	libusb_fill_bulk_transfer(m_xfer,
		dev_handle,
		EP1ADDR, // Endpoint ID
		recv_buf,
		RECV_LEN,
		WinUSB::completeCallback,
		this,
		0
		);

	if (m_xfer){
		ret = libusb_submit_transfer(m_xfer);
		if (ret < 0){
			//"fail to re-submit transfer"
			libusb_free_transfer(m_xfer);
			m_xfer = 0;
			error = 1;
			goto fail;
		}
	}


	usb_thread.start();
	is_open = true;

	return 0;


fail:
	libusb_cancel_transfer(m_xfer);
get_config_fail:
open_fail :
	libusb_close(dev_handle);
	  get_list_fail:
		  libusb_free_device_list(devs, 1);
	  find_device_fail:
	  init_fail :
		  libusb_exit(m_libusb_context);
				return error;
}

void WinUSB::send(unsigned char *data,int len)
{
	if (is_open)
	{
		libusb_bulk_transfer(dev_handle, EP0ADDR, data, len, NULL, 0xFFFF);
	}

}

int WinUSB::close(void)
{

	usb_thread.close();
	usb_thread.stop();

	if (m_xfer){
		libusb_cancel_transfer(m_xfer);
		m_xfer = NULL;
	}

	libusb_release_interface(dev_handle, 0);

	libusb_close(dev_handle);

	if (m_libusb_context){
		libusb_exit(m_libusb_context);
		m_libusb_context = NULL;
	}
	is_open = false;

	return 0;
}
