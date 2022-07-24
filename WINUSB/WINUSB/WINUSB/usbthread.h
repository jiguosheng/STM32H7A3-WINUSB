#ifndef USBTHREAD_H
#define USBTHREAD_H
 
#include "libusb.h"
#include "Thread.h" 

class USBThread : public Thread
{
private:
	bool is_loop;
protected:
	virtual void process();
public:
    USBThread();
    void run();
    void close();
};

#endif // USBTHREAD_H
