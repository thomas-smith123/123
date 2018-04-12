#include "stm32f10x.h"
#include "bsp_sdio_sdcard.h"
#include "bsp_usart1.h"	
#include "ff.h"
#include "bsp_iis.h"
#define FILE_NAME_LEN 	50			//文件名长度，如果检测到文件名超过50 则丢弃这个文件 
#define MUSIC_NAME_LEN 	24			//LCD显示的文件名的最大长度
#define _DF1S	0x81

	FATFS fs;                  // Work area (file system object) for logical drive
	FRESULT res;
	UINT br;					  /*读取出的字节数，用于判断是否到达文件尾*/
	FIL fsrc;          		 // file objects
	FILINFO finfo;			 /*文件信息*/
	DIR dirs;
	uint16_t count = 0;
	
	char lfn[255];   	  /*为支持长文件的数组，[]最大支持255*/
	char j = 0;	  
	char path[300] = {""}; /* MicroSD卡根目录 */	
	char *result1, *result2, *result3, *result4;
	
	BYTE buffer[2048];          /* 存放读取出的文件数据 */
int main(void)
{
		finfo.lfname = lfn; 		  /*为长文件名分配空间*/
		finfo.lfsize = sizeof(lfn);   /*空间大小*/
		I2S_Bus_Init();
   /* USART1 config */
		USART1_Config();
		printf("\r\n this is a fatfs test demo \r\n");
	
		/* Sdio Interrupt Config */
		NVIC_Configuration();
			 
    /* Unregister work area prior to discard it */

	f_mount(0, &fs);			                         /* 挂载文件系统到0区 */  
	
	if (f_opendir(&dirs,path) == FR_OK) 	          /* 打开根目录 */
	{
//		printf(  " \r\n FR_OK \r\n");
		while (f_readdir(&dirs, &finfo) == FR_OK)    	/* 依次读取文件名 */
		{			
		if ( finfo.fattrib & AM_ARC )        /* 判断是否为存档型文档 */
			{
				if(finfo.lfname[0] == NULL && finfo.fname !=NULL)  /*当长文件名称为空，短文件名非空时转换*/
					finfo.lfname =finfo.fname;	
				if( !finfo.lfname[0] )	 /* ??????????????,?? */
					break;  				
				printf(  " \r\n fliename: %s \r\n",finfo.lfname );
			}		
		}	
	}
//	file_scan(path);
	f_close(&fsrc);
	f_mount(0, NULL);
//		

		while(1);
}


