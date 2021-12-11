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

int  str(FILE * p,char ** a){
	char * s=(char*)malloc(1); 
	int i = 0;
	*(s+i) = fgetc(p);
	while (*(s+i) != EOF)
	{	
		 if (*(s+i)!='\n')
		 {	
		 	i++;
		 	s = (char*)realloc(s, (i+1) * sizeof(char));
			*(s+i) = fgetc(p);
		 }
		else  
			*(s+i) = fgetc(p);
	}
	
	 *a = s;
	return i;
	

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
	
	
	
	if( ! (( *(text + 3) == '0' )|| (*(text + 3)  == '1')))
		return 1;
	int type=-1;
	char s[1];
	s[0]=*(text + 4);
		
	if(( *(text + 4) >= '0') || (*(text + 4) <= '3'))
		type=atoi(s);
	else
		return 1;
		
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
	if (argc == 2) {
	   	char *fname = argv[1];
	   	FILE *verifiable = fopen(fname, "r");
	   	if( !verifiable )
		{
	 		printf ("program don t faund file %s ",fname);	
	 		printf ("u can use -help\n");
	 		return 0;
	 	}
	 	else {	
	 		int tmp;
	 		tmp = check( verifiable, fname);
	 		
	 		if (tmp == 1)
	 			printf ("False\n");
	 		else
	 			printf ("True\n");
	 		
	 	}
	
	}
	else
		printf("ERROR, correctly: ./verifier md5_3des_0a0b0cff.enc\n");
	


	return 0;
}
