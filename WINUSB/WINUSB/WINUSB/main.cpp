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
		printf("开启USB成功\n");
	}
	else
	{
		printf("开启USB失败\n");
	}

	/*startTime = clock();//计时开始

	while (winusb.total_len < 1000000)
	{
		
	}
	
	endTime = clock();//计时结束

	printf("运行时间:%fs\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);
	printf("效率:%fKB/s\n", winusb.total_len / 1024.0  / ((double)(endTime - startTime) / CLOCKS_PER_SEC));*/

	startTime = clock();//计时开始

 	
 	{
		winusb.send((unsigned char*)"HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32\
									HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32\
									HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32\
									HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32\
									HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32HELLOstm32\n",63);//超过63字节会严重丢包
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
	printf("关闭USB\n");

	endTime = clock();//计时结束

	printf("运行时间:%fs\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);
	printf("效率:%fKB/s\n", winusb.total_len / 1024.0 / ((double)(endTime - startTime) / CLOCKS_PER_SEC ));

	printf("%fKB,Byte:%d\n", winusb.total_len / 1024.0,winusb.total_len);

	while (1);
}
