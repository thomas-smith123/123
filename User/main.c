#include "stm32f10x.h"
#include "bsp_sdio_sdcard.h"
#include "bsp_usart1.h"	
#include "ff.h"
#include "bsp_iis.h"
#define FILE_NAME_LEN 	50			//�ļ������ȣ������⵽�ļ�������50 ��������ļ� 
#define MUSIC_NAME_LEN 	24			//LCD��ʾ���ļ�������󳤶�
#define _DF1S	0x81

	FATFS fs;                  // Work area (file system object) for logical drive
	FRESULT res;
	UINT br;					  /*��ȡ�����ֽ����������ж��Ƿ񵽴��ļ�β*/
	FIL fsrc;          		 // file objects
	FILINFO finfo;			 /*�ļ���Ϣ*/
	DIR dirs;
	uint16_t count = 0;
	
	char lfn[255];   	  /*Ϊ֧�ֳ��ļ������飬[]���֧��255*/
	char j = 0;	  
	char path[300] = {""}; /* MicroSD����Ŀ¼ */	
	char *result1, *result2, *result3, *result4;
	
	BYTE buffer[2048];          /* ��Ŷ�ȡ�����ļ����� */
int main(void)
{
		finfo.lfname = lfn; 		  /*Ϊ���ļ�������ռ�*/
		finfo.lfsize = sizeof(lfn);   /*�ռ��С*/
		I2S_Bus_Init();
   /* USART1 config */
		USART1_Config();
		printf("\r\n this is a fatfs test demo \r\n");
	
		/* Sdio Interrupt Config */
		NVIC_Configuration();
			 
    /* Unregister work area prior to discard it */

	f_mount(0, &fs);			                         /* �����ļ�ϵͳ��0�� */  
	
	if (f_opendir(&dirs,path) == FR_OK) 	          /* �򿪸�Ŀ¼ */
	{
//		printf(  " \r\n FR_OK \r\n");
		while (f_readdir(&dirs, &finfo) == FR_OK)    	/* ���ζ�ȡ�ļ��� */
		{			
		if ( finfo.fattrib & AM_ARC )        /* �ж��Ƿ�Ϊ�浵���ĵ� */
			{
				if(finfo.lfname[0] == NULL && finfo.fname !=NULL)  /*�����ļ�����Ϊ�գ����ļ����ǿ�ʱת��*/
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


