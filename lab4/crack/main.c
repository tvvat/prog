#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <time.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <openssl/des.h>
#include <openssl/aes.h>


#define MAXLEN_3DES 4173
#define MAXLEN_AES128 4181
#define MAXLEN_AES192 4189
#define MAXLEN_AES256 4197

#define MINLEN_3DES 78
#define MINLEN_AES128 86
#define MINLEN_AES192 94
#define MINLEN_AES256 102


#define short_options "v"
const struct option long_options[] = {
		{"verbose", no_argument, NULL, 'v'},
		{NULL,0,NULL,0}
	};


void analysis_input(int argc, char *argv[],char fname,int *flag) {


	int rez = getopt_long(argc,argv,short_options,long_options,NULL);
	while ((rez) != -1)
	{
		switch(rez)
		{  
			case 'v': {
				*flag=1;
				break;
			};
			case '?':  {
				printf("found unknown option\n");
				break;
			};
			
		
		}
		rez = getopt_long(argc,argv,short_options,long_options,NULL);
	}
	
	*fname=argv[argc-1];
}
	
	
	
int check(FILE *verifiable, char *fname) {

	int len = strlen(fname);
	char *extension = ".enc";
	char fextension[4];
	
	fextension[0] = *(fname+len-4);
	fextension[1] = *(fname+len-3);
	fextension[2] = *(fname+len-2);
	fextension[3] = *(fname+len-1);
	
	if(strcmp(extension,fextension)!=0)
	{
		printf(" extension  must .enc");
		return 1;
	}
	
	int code_error = 0;
	char *text = (char*)malloc(1000000); ;
	len=str(verifiable,&text);	
	if((*(text) != 'E') || (*(text + 1) != 'N') || (*(text + 2) != 'C'))
		return 1;
	
	
	
	if( *(text + 3) == '0' )  
		printf ("HMAC_MD5");
	else
	if (*(text + 3)  == '1')
		printf ("HMAC_SHA1");
	else
		return 1;
	int type=-1;
	char s[1];
	s[0]=*(text + 4);
	type=atoi(s);
	
	switch(type)
		{  
			case 0: {
				printf (",3DES\n");
				break;
			};
			case 1:  {
				printf (",AES128\n");
				break;
			};
			case 2:  {
				printf (",AES128\n");
				break;
			};
			case 3:  {
				printf (",AES128\n");
				break;
			};
			case type :  {
				printf (",incorrect type");
				return 1;
	
			};
		}
	
		
	int min,max;
	if(type == 0) {
	 	min = MINLEN_3DES;
	 	max = MAXLEN_3DES;
	}
	else
	if(type == 1) {
	 	min = MINLEN_AES128;
	 	max = MAXLEN_AES128;
	}
	else
	if(type == 2) {
	 	min = MINLEN_AES192 ;
	 	max = MAXLEN_AES192;
	 
	}
	 else
	if(type == 3) {
	 	min = MINLEN_AES256;
	 	max = MAXLEN_AES256;
	 
	}
	 
	if ((len > max) || (len < min)) 
		return 1;
	return 0;
}
 
int main (int argc, char *argv[]) {
	
	char *fname;
	int flag=0;
	
	analysis_input(argc,argv,fname,&flag);
	
	FILE *verifiable = fopen(fname, "r");
	if( !verifiable )
	{
	 	printf ("program don t faund file %s ",fname);	
	 	printf ("example ./crack -v md5_3des_01020304.enc\n");
	 	return 0;
	}
	else
	{	
		int tmp;
	 	tmp = check ( verifiable, fname);
	 		
	 	if (tmp == 1)
	 		printf ("The file contains incorrect information\n");
	 	else
	 		{
	 		
	 		
	 		
	 		}
	
	
	}
	
	return 0;
}	

