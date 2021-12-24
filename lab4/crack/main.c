#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <time.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <openssl/des.h>
#include <openssl/aes.h>
#include <limits.h>

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
#define V_L_MAX 16

#define KEY_L_3DES 24
#define KEY_L_AES128 16
#define KEY_L_AES192 24
#define KEY_L_AES256 32


#define HMAC_MD5_LEN 16
#define HMAC_SHA1_LEN 20

#define HMAC_MAX_LEN 20


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

int input_data (unsigned char *func_enc, unsigned char *func_h, int *key_len,int *len, int *iv_len, unsigned char *iv, unsigned char *nonce,unsigned char *ctext,FILE *in) {
	
	
	char *extension = "ENC";
	char *tmp = malloc(3);
	
	fread(tmp, sizeof(unsigned char), 3, in);
	
	if(strcmp(tmp,extension) != 0)
		return 1;
	printf("HMAC_");
 	fread(func_enc, sizeof(unsigned char), 1, in);
 	
 	if  (*func_enc == MD5 ) 
		printf("MD5");
	else
	if (*func_enc == SHA1 ) 
	 	printf("SHA1");
	else
		return 1;
		
   	fread(func_h, sizeof(unsigned char), 1, in);
	
	int min ,max;
	
	if(*func_h == DES3) {
		*iv_len = V_L_3DES;
	 	min = MINLEN_3DES;
	 	max = MAXLEN_3DES;
	 	*key_len = KEY_L_3DES;
	 	printf (",3DES\n");
	}
	else
	if(*func_h == AES128) {
		*iv_len = V_L_AES128;
	 	min = MINLEN_AES128;
	 	max = MAXLEN_AES128;
	 	*key_len = KEY_L_AES128;
	 	printf (",AES128\n");
	 }
	else
	if( *func_h ==AES192) {
		*iv_len = V_L_AES192;
	 	min = MINLEN_AES192;
	 	max = MAXLEN_AES192;
	 	*key_len = KEY_L_AES192;
	 	printf (",AES192\n");
	 }
	else
	if( *func_h == AES256) {
		*iv_len = V_L_AES256;
	 	min = MINLEN_AES256;
	 	max = MAXLEN_AES256;
	 	*key_len = KEY_L_AES256;
	 	printf (",AES256\n");
	 }
	else
		return 1;
		
	printf ("\nNONCE: ");
	
  	fread(nonce, sizeof(unsigned char), NONCE_LEN, in);
  	
	for(int i = 0; i < NONCE_LEN; i++) 
    		printf( "%02x", nonce[i]);
    	
	printf ("\nIV: ");
	
  	fread(iv, sizeof(unsigned char),* iv_len, in);
  	
	for(int i = 0; i < *iv_len; i++) 
    		printf("%02x", iv[i]);
    	
    	printf ("\nCT: ");
    	
  	char tmp1; 
	(*len) = 0; 
  	while ( !feof(in) ) {
  	
  		fread(&tmp1, sizeof(char), 1, in), 
    		ctext[(*len)] = (unsigned char) tmp1;
    		
    		(*len)++;
   	}
   		
   	(*len)--;
   	
	for(int i = 0; i < *len; i++) 
    		printf( "%02x", ctext[i]);
    	
   	int t = NONCE_LEN + 5 + *key_len + *iv_len;
   	
   	if ((*len + t> max) || (*len + t< min)) 
   		return 1;
		
	
	printf ("\n");
	
	return 0;
}

void func_psswrd(unsigned char *res,int a) {

	
	for(int i = PASSWORD_LEN-1;i >= 0;i--) {
		
		*(res+i) = a % LEN_CHAR;
		a /= LEN_CHAR;
		
	}

}
void des3_decrypt(unsigned char *text, int len, unsigned char *iv, unsigned char *key, unsigned char *outputtext) {
  	DES_cblock key1, key2, key3;
	DES_key_schedule ks1, ks2, ks3;

	memcpy(key1, key, 8);
	memcpy(key2, key + 8, 8);
	memcpy(key3, key + 16, 8);

	DES_set_key((DES_cblock *) key1, &ks1);
	DES_set_key((DES_cblock *) key2, &ks2);
	DES_set_key((DES_cblock *) key3, &ks3);

	DES_ede3_cbc_encrypt(text, outputtext, len, &ks1, &ks2, &ks3, (DES_cblock *) iv, DES_DECRYPT);
    		
}

void aes_decrypt(unsigned char *text, size_t len, unsigned char *iv, unsigned char *key, unsigned char *outputtext, int key_len) {
	
  	AES_KEY akey;
	AES_set_decrypt_key(key, key_len*8, &akey);
	AES_cbc_encrypt(text, outputtext, len, &akey, iv, DES_DECRYPT);
}


static inline unsigned char *hmac_md5(unsigned char *text,
    size_t text_len, unsigned char *key, size_t key_len, unsigned char *md)
{
	static unsigned char m[16];
	MD5_CTX context;
	unsigned char k_ipad[65];	
	unsigned char k_opad[65];	
	unsigned char tk[16];
	int i;

	if (md == NULL)		
		md = m;
	if (key_len > 64) {
		MD5_CTX tctx;

		MD5_Init(&tctx);
		MD5_Update(&tctx, key, key_len);
		MD5_Final(tk, &tctx);

		key = tk;
		key_len = 16;
	}
	
	memset(k_ipad, 0x36, sizeof k_ipad);
	memset(k_opad, 0x5c, sizeof k_opad);

	for (i = 0; i < key_len; i++) {
		k_ipad[i] ^= key[i];
		k_opad[i] ^= key[i];
	}
	
	MD5_Init(&context);	
	MD5_Update(&context, k_ipad, 64);	
	MD5_Update(&context, text, text_len);
	MD5_Final(md, &context);	
	
	MD5_Init(&context);	
	MD5_Update(&context, k_opad, 64);	
	MD5_Update(&context, md, 16);	
	MD5_Final(md, &context);	

	return md;
}

static inline unsigned char *hmac_sha1(const unsigned char *text,
    size_t text_len, const unsigned char *key, size_t key_len,
    unsigned char *md)
{
	static unsigned char m[20];
	SHA_CTX context;
	unsigned char k_ipad[65];	
	unsigned char k_opad[65];	
	unsigned char tk[20];
	int i;

	if (md == NULL)		
		md = m;

	
	if (key_len > 64) {
		SHA_CTX tctx;

		SHA1_Init(&tctx);
		SHA1_Update(&tctx, key, key_len);
		SHA1_Final(tk, &tctx);
		key = tk;
		key_len = 20;
	}
	

	memset(k_ipad, 0x36, sizeof k_ipad);
	memset(k_opad, 0x5c, sizeof k_opad);

	
	for (i = 0; i < key_len; i++) {
		k_ipad[i] ^= key[i];
		k_opad[i] ^= key[i];
	}
	
	SHA1_Init(&context);	
	SHA1_Update(&context, k_ipad, 64);	
	SHA1_Update(&context, text, text_len);	
	SHA1_Final(md, &context);	
	
	SHA1_Init(&context);	
	SHA1_Update(&context, k_opad, 64);	
	SHA1_Update(&context, md, 20);	
	SHA1_Final(md, &context);	

	return md;
}

void function_md5(unsigned char *nonce, unsigned char *password, unsigned char *key, int key_len) {
	
	unsigned char hmac[HMAC_MD5_LEN];
	
	hmac_md5(nonce, NONCE_LEN, password, PASSWORD_LEN, hmac);
	
	memcpy(key, hmac, HMAC_MD5_LEN); 
	
	int def =  HMAC_MD5_LEN - key_len;
	if(def > 0) {
        	unsigned char tmphmac[HMAC_MD5_LEN];
        
        	hmac_md5(hmac, HMAC_MD5_LEN, password, PASSWORD_LEN, tmphmac);
        	memcpy(key + HMAC_MD5_LEN, tmphmac, def);
	}

}


void function_sha1(unsigned char *nonce, unsigned char *password, unsigned char *key, int key_len) {
	
	unsigned char hmac[HMAC_SHA1_LEN];
	
	hmac_sha1(nonce, NONCE_LEN, password, PASSWORD_LEN, hmac);
	
      	if ( HMAC_SHA1_LEN >  key_len ) 
		memcpy(key, hmac, key_len);
	else {
		memcpy(key, hmac, HMAC_MD5_LEN); 
		
		int def = key_len - HMAC_MD5_LEN;
		
		unsigned char tmphmac[HMAC_MD5_LEN];
        
        	hmac_sha1(hmac, HMAC_MD5_LEN, password, PASSWORD_LEN, tmphmac);
        	memcpy(key + HMAC_MD5_LEN, tmphmac, def);
	
	
	}
      
}


 void fprin(unsigned char *password, clock_t start, clock_t current, clock_t previous, int flag, unsigned char  *text, int  len,int num_pwrd) {
  	current = clock();
  	double time;
  	printf("Found: ");
  	for (int i = 0; i < PASSWORD_LEN; i++) {
    		printf("%02hhx", password[i]);
  	}

  	if ( flag ) {
    		time= (double) (current - start) / CLOCKS_PER_SEC;
    		printf(" | Average speed: %6.0f c/s\n", (num_pwrd / time));
 	}


  	

 	printf("\nMessage's text in HEX is: \n\n");
 	for (int i = 8; i < len; i++) {
    		printf("%02x", text[i]);
  	}

 	 printf("\n\n");

  	
  	
 }
 
void func_crak(unsigned char func_enc, unsigned char func_h, int key_len, int len, int iv_len, unsigned char *iv, unsigned char *nonce, unsigned char *ctext, int flag) {
	 		
 	unsigned char password[PASSWORD_LEN];
  	unsigned char text[len];
 	unsigned char key[key_len];
  	double time_in_seconds = 0;
  	int firstnull = 0;
  	int i ;
  	
	if ( flag )
		 printf("Current: 00000000 - 0000ffff\n");
		
	clock_t start = clock();
  	clock_t current = clock();
  	clock_t previous = clock();
  	
  	unsigned char iv_2[iv_len];
  	

  memcpy(iv_2, iv, iv_len);
  
  	for (i = 0; i <= UINT_MAX ; i++) {
  		memcpy(iv, iv_2, iv_len);
		func_psswrd(password, i);
		
		if ((!(i & 0xffff)) && ( flag ) && (i != 0)) {

     			previous = current;
      			current = clock();
			if ( flag )
			 	printf("Current: %08x - %08x | ", i, (i + 0xffff));
	
			time_in_seconds = (double) (current - previous) / CLOCKS_PER_SEC;
      			printf("Current speed: %6.0f c/s | ", (0x10000 / time_in_seconds));

      			
		}
		
		if(func_enc == MD5)
			function_md5 (nonce, password, key, key_len);
		else
			function_sha1 (nonce, password, key, key_len);
		
		if (key_len == 24) 
      			des3_decrypt (ctext, len, iv, key, text);
   		
   		else 
     			aes_decrypt (ctext, len, iv, key, text, key_len );
	
    		for (int j = 0; j < 8; j++) {
      			if (text[j] == 0)
        			{firstnull = 1;
        			}
        		
      			else {	
      				firstnull = 0;
      				break;
      			}
      			
      			
    		}


    		if (firstnull)
     	 		break;
     	 	printf("\n");
  
  	}
  		
  		
  	fprin(password, start, current, previous, flag, text, len, i);
  	
  	
}
	
int main (int argc, char *argv[]) {
	
	char *fname;
	unsigned char func_enc ;
	unsigned char func_h;
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
	 	unsigned char iv[V_L_MAX];
	 	unsigned char nonce[NONCE_LEN];
	 	code_error = input_data (&func_enc, &func_h, &key_len,&len, &iv_len,iv,nonce,ctext,verifiable);
	 	 
	 	if ( code_error == 1)
	 		printf ("The file contains incorrect information\n");
	 	else
	 	{ 	
	 	 	printf("\nStart cracking\n\n\n");
	 	 	
	 	 	
    			func_crak(func_enc, func_h, key_len, len, iv_len, iv, nonce, ctext, flag);
	 			
	 		
	 		
	 	}
	
	}
	//fclose(verifiable);
	return 0;
}	

