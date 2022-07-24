#include  <stdio.h>
#include "WinUSB.h"
#include <ctime>

#define CLOCKS_PER_SEC ((clock_t)1000)

int main()
{
	WinUSB winusb; 
	int i = 0;
	
	clock_t startTime, endTime;

	if(winusb.open(0x07E4, 0x07E4) == 0)
	{
		printf("����USB�ɹ�\n");
	}
	else
	{
		printf("����USBʧ��\n");
	}

	/*startTime = clock();//��ʱ��ʼ

	while (winusb.total_len < 1000000)
	{
		
	}
	
	endTime = clock();//��ʱ����

	printf("����ʱ��:%fs\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);
	printf("Ч��:%fKB/s\n", winusb.total_len / 1024.0  / ((double)(endTime - startTime) / CLOCKS_PER_SEC));*/

	startTime = clock();//��ʱ��ʼ

 	
 	{
		winusb.send((unsigned char*)"HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32\
									HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32\
									HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32\
									HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32\
									HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32\n",63);//����63�ֽڻ����ض���
 		i++;
 	}

	std::this_thread::sleep_for(std::chrono::seconds(10));
	winusb.send((unsigned char*)"HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32\
								HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32\
								HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32\
								HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32\
																								HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32\n", 63);

	std::this_thread::sleep_for(std::chrono::microseconds(2500));
	winusb.close();
	printf("�ر�USB\n");

	endTime = clock();//��ʱ����

	printf("����ʱ��:%fs\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);
	printf("Ч��:%fKB/s\n", winusb.total_len / 1024.0 / ((double)(endTime - startTime) / CLOCKS_PER_SEC ));

	printf("%fKB,Byte:%d\n", winusb.total_len / 1024.0,winusb.total_len);

	while (1);
}
