#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <time.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <openssl/des.h>
#include <openssl/aes.h>

#define MD5 0
#define SHA1 1

#define DES3 0
#define AES128 1
#define AES192 2
#define AES256 3

#define MAXLEN_3DES 4173
#define MAXLEN_AES128 4181
#define MAXLEN_AES192 4189
#define MAXLEN_AES256 4197

#define MINLEN_3DES 78
#define MINLEN_AES128 86
#define MINLEN_AES192 94
#define MINLEN_AES256 102


#define PASSWORD_LEN 4

#define LEN_CHAR 256

#define NONCE_LEN 64

#define V_L_3DES 8
#define V_L_AES128 16
#define V_L_AES192 16
#define V_L_AES256 16

#define KEY_L_3DES 24
#define KEY_L_AES128 16
#define KEY_L_AES192 24
#define KEY_L_AES256 32


#define HMAC_MD5_LEN 16
#define HMAC_SHA1_LEN 20


#define short_options "v"

const struct option long_options[] = {
		{"verbose", no_argument, NULL, 'v'},
		{NULL,0,NULL,0}
	};


unsigned int v_int(char *a)
{	
	unsigned int res = 0;
  	for (int i = 0; i < strlen(a); i++)
  	{
    		res *= 16;
   		unsigned int k= 0;
    		if (a[i] >= '0' && a[i] <= '9')
    			k = a[i] - '0';
    		else 
   		if (a[i] >= 'a' && a[i] <= 'f')
      			k = a[i] - 'a' + 10;
    	
    		else {
    			printf("%c wrong value\n", a[i]);
      			return 0;
    		}
    		
    	res += k;
  	}
  return res;

} 

void chek_fname(char *fname) {
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
		
	}

}


void analysis_input(int argc, char *argv[],char **fname,int *flag) {


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
	chek_fname(*fname);
	
}


/**int check (FILE *verifiable, char *fname, int *func_enc, int *func_h, int *iv_len,unsigned char *TEXT, int *len, unsigned char *iv, unsigned char *nonce) {

	int max,min;
	printf("fdsf");
	verifiable = fopen(fname, "r");
	printf("fdsf");
	extension = "ENC";
	printf("fdsf");
	char *tmp=malloc(3);
	printf("fdsf");
	fread(tmp, sizeof(unsigned char), 3, verifiable);
	printf("fdsf");
	if(strcmp(tmp,extension) != 0)
		return 1;
	
	printf("HMAC_");
	fread(func_enc, sizeof (int), 1, verifiable);
	printf("fdsf");
	if  (*func_enc == MD5 ) 
		printf("MD5");
	else
	if (*func_enc == SHA1 ) 
	 	printf("SHA1");
	else
		return 1;
	printf("fdsf");
	fread(func_h, sizeof(int), 1, verifiable);
	if( *func_h == DES3) {
		*iv_len = V_L_3DES;
		printf("fdsf");
	 	min = MINLEN_3DES;
	 	max = MAXLEN_3DES;
	 	
	 	//printf (",3DES\n");
	 	printf("fdsf");
	}
	else
	if(*func_h == AES128) {
		*iv_len = V_L_AES128;
		
	 	min = MINLEN_AES128;
	 	max = MAXLEN_AES128;
	 	
	 	printf (",AES128\n");
	 }
	else
	if( *func_h ==AES192) {
		*iv_len = V_L_AES192;
		
	 	min = MINLEN_AES192;
	 	max = MAXLEN_AES192;
	 	
	 	printf (",AES192\n");
	 }
	else
	if( *func_h == AES256) {
		*iv_len = V_L_AES256;
		
	 	min = MINLEN_AES256;
	 	max = MAXLEN_AES256;
	 	printf (",AES256\n");
	 }
	else
		{return 1;printf("fdsf");}
	printf("fdsf");
	
	printf("fdsf");	
	
	
	printf("fdsf");		
	fread(nonce, sizeof(unsigned char ), NONCE_LEN, verifiable);
  	
		printf("fdsf");		
  	fread(iv, sizeof(unsigned char ),  *iv_len, verifiable);
  	
		printf("fdsf");	
  	int tmp1 = *iv_len + NONCE_LEN + 1 + 1 + 3;
  	char tmp2;
  	 for(*len = 0; fread(&tmp2, sizeof(unsigned char), 1, verifiable) == 1; *len++)
    	TEXT[(*len)] = (unsigned char) tmp2;

	if ((*len+tmp1 > max) || (*len+tmp1 < min)) 
		return 1;
		
	
  	
	return 0;
}
**/
int input_data (unsigned char *func_enc,int *key_len,int *len, int *iv_len, unsigned char *iv, unsigned char *nonce,unsigned char *ctext,FILE *in) {
	

  char letter;

  fread(&letter, sizeof( unsigned char), 1, in);
  fread(&letter, sizeof( unsigned char), 1, in);
  fread(&letter, sizeof( unsigned char), 1, in);

 fread(func_enc, sizeof(unsigned char), 1, in);
  unsigned char ci_type;
   fread(&ci_type, sizeof(unsigned char), 1, in);
	
  fread(nonce, sizeof(unsigned char), NONCE_LEN, in);
	for(int i = 0; i < NONCE_LEN; i++) 
    		printf( "%02x", nonce[i]);
  		
  fread(iv, sizeof(unsigned char),* iv_len, in);
	for(int i = 0; i <* iv_len; i++) 
    		printf("%02x", iv[i]);
  printf("\n");
  
	(*len) = 0; 
  while (!feof(in)){
  fread(&letter, sizeof(char), 1, in), 
    ctext[(*len)] = (unsigned char) letter;
    printf("%x",ctext[(*len)]);
    (*len)++;
    }
 return 0;
}
 
int main (int argc, char *argv[]) {
	
	char *fname;
	unsigned char func_enc ;
	int func_h ;
	int flag;
	analysis_input(argc, argv, &fname, &flag);
	
	FILE *verifiable = fopen(fname, "r");
	if( !verifiable )
	{
	 	printf ("program don t faund file %s ",fname);	
	 	printf ("example ./crack -v md5_3des_0a0b0cff.enc\n");
	 	return 0;
	}
	else
	{	int key_len;
		int iv_len;
		int code_error;
		unsigned char *ctext = malloc(100000);
		int len;
		unsigned char key[key_len];
	 	unsigned char iv[iv_len];
	 	unsigned char nonce[NONCE_LEN];
	 	
	 	code_error = input_data (&func_enc,&key_len,&len, &iv_len,iv,nonce,ctext,verifiable);
	 	 
	 	if ( code_error == 1)
	 		printf ("The file contains incorrect information\n");
	 	else
	 	{
	 		
	 		
	 		
	 	}
	
	}
	//fclose(verifiable);
	return 0;
}	

