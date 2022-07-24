#include "usbthread.h"

USBThread::USBThread()
{
    is_loop = true;
}

void USBThread::process()
{
    is_loop = true;
    while(is_loop)
    {
       
        libusb_handle_events(NULL);
        msleep(1);
    }
}

void USBThread::close()
{
    is_loop = false;
}
