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

#define short_options "edp:i:o:h:a:n:f:"

const struct option long_options[] = {
		{"enc", no_argument, NULL, 'e'},
		{"dec", no_argument, NULL, 'd'},
		{"finput", required_argument, NULL, 'f'},
		{"output",  required_argument, NULL, 'o'},
		{"hmac", required_argument, NULL, 'h'},
		{"alg",  required_argument, NULL, 'a'},
		{"iv",  required_argument, NULL, 'i'},
		{"nonce",  required_argument, NULL, 'n'},
		{"pass",  required_argument, NULL, 'p'},
		{NULL,0,NULL,0}
	};




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


void func_uns( unsigned char *res, char *a,int len) {

	unsigned int tmp = v_int(a);
	
	for(int i = len-1;i >= 0;i--) {
		
		*(res+i) = tmp % LEN_CHAR;
		tmp /= LEN_CHAR;
		
	}
	
}

int analysis_input(int argc, char *argv[], int *func_enc,unsigned char *func_h, unsigned char *func_algo,char **input,char **output, unsigned char *iv, int *iv_len, int *key_len, unsigned char *nonce, unsigned char *pas, int *flag_pas, int *flag_iv, int *flag_nonce) {

	int rez = getopt_long(argc,argv,short_options,long_options,NULL);
	while ((rez) != -1)
	{
		switch(rez)
		{  
			case 'i': {
				func_uns( iv, optarg, *iv_len);
				*flag_iv = 1;
				break;
			};
			case 'e':  {
				*func_enc = 0;

				break;
			};
			case 'd': {
				*func_enc = 1;
				break;
			};
			case 'f': {
				*input = optarg;
				break;
			};
			case 'o': {
				*output = optarg;
				break;
			};
			case 'h': {
				if(atoi( optarg) == MD5)
					*func_h = MD5;
				else
				if(atoi( optarg) == MD5)
				 	*func_h = SHA1;
				else
					return 1;
				break;
				
			};
			case 'a': {
				if(strcmp( optarg, "3des" )== 0 ) {
					*iv_len = V_L_3DES;
	 				*func_algo = DES3;
	 				*key_len = KEY_L_3DES;
				}
				else
				if(strcmp( optarg, "aes128") == 0) {
					*iv_len = V_L_AES128;
	 				*func_algo = AES128;
	 				*key_len = KEY_L_AES128;
	 			}
				else
				if(strcmp( optarg, "aes192") == 0 ) {
					*iv_len = V_L_AES192;
	 				*func_algo = AES128;
	 				*key_len = KEY_L_AES192;
	 			}
				else
				if(strcmp( optarg, "aes256") == 0) {
					*iv_len = V_L_AES256;
	 				*func_algo = AES128;
	 				*key_len = KEY_L_AES256;
	 			}
				else
					return 1;
				
				break;
				
			};
			case 'n': {
				*flag_nonce = 1;
				func_uns( nonce, optarg, NONCE_LEN);
				break;
			};
			case 'p': {
				*flag_pas = 1;
				func_uns( pas, optarg, PASSWORD_LEN);
				break;
			};
			case '?':  {
				printf("found unknown option\n");
				break;
			};
		
		}
		rez = getopt_long(argc,argv,short_options,long_options,NULL);
	}
	
	return 0;
}

int input_data (unsigned char *func_algo, unsigned char *func_h, int *key_len,int *len, int *iv_len, unsigned char *iv, unsigned char *nonce,unsigned char *ctext,FILE *in) {
	
	
	char *extension = "ENC";
	char *tmp = malloc(3);
	
	fread(tmp, sizeof(unsigned char), 3, in);
	
	if(strcmp(tmp,extension) != 0)
		return 1;
	printf("HMAC_");
 	fread(func_h, sizeof(unsigned char), 1, in);
 	
 	if  (*func_h == MD5 ) 
		printf("MD5");
	else
	if (*func_h == SHA1 ) 
	 	printf("SHA1");
	else
		return 1;
		
   	fread(func_algo, sizeof(unsigned char), 1, in);
	
	int min ,max;
	
	if(*func_algo == DES3) {
		*iv_len = V_L_3DES;
	 	min = MINLEN_3DES;
	 	max = MAXLEN_3DES;
	 	*key_len = KEY_L_3DES;
	 	printf (",3DES\n");
	}
	else
	if(*func_algo == AES128) {
		*iv_len = V_L_AES128;
	 	min = MINLEN_AES128;
	 	max = MAXLEN_AES128;
	 	*key_len = KEY_L_AES128;
	 	printf (",AES128\n");
	 }
	else
	if( *func_algo ==AES192) {
		*iv_len = V_L_AES192;
	 	min = MINLEN_AES192;
	 	max = MAXLEN_AES192;
	 	*key_len = KEY_L_AES192;
	 	printf (",AES192\n");
	 }
	else
	if( *func_algo == AES256) {
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


void file8null(unsigned char  **TEXT, int len) {

	int tmp = len + 8;
	unsigned char *TEXTtmp = (char *) malloc((tmp) * sizeof(char));
	 
	for (int i = 0;i < tmp; i++)
		*(TEXTtmp + i) = 0;	
	
    	memcpy(TEXTtmp + 8, *TEXT, tmp - 8);
    	
    	*TEXT=TEXTtmp;
	
}

void read_text(unsigned char  **intext, int *len, FILE *in) {
	unsigned char  text[MAXLEN_AES192];
  	char tmp; 
	(*len) = 0; 
  	while ( !feof(in) ) {
  	
  		fread(&tmp, sizeof(char), 1, in), 
    		text[(*len)] = (unsigned char) tmp;
    		
    		(*len)++;
   	}
   		
   	(*len)--;

	*intext = text;

}

void func_gen(unsigned char *a, int len) {
	
	for (int i = 0; i < len; i++)
    		*(a+i) = (unsigned char )( rand() % LEN_CHAR);
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
void des3_encrypt(unsigned char *text, int len, unsigned char *iv, unsigned char *key, unsigned char *outputtext) {
  	DES_cblock key1, key2, key3;
	DES_key_schedule ks1, ks2, ks3;

	memcpy(key1, key, 8);
	memcpy(key2, key + 8, 8);
	memcpy(key3, key + 16, 8);

	DES_set_key((DES_cblock *) key1, &ks1);
	DES_set_key((DES_cblock *) key2, &ks2);
	DES_set_key((DES_cblock *) key3, &ks3);

	DES_ede3_cbc_encrypt(text, outputtext, len, &ks1, &ks2, &ks3, (DES_cblock *) iv, DES_ENCRYPT);
    		
}

void aes_encrypt(unsigned char *text, size_t len, unsigned char *iv, unsigned char *key, unsigned char *outputtext, int key_len) {
	AES_KEY akey;
	AES_set_encrypt_key (key, key_len*8, &akey);
	AES_cbc_encrypt (text, outputtext, len, &akey, iv, AES_ENCRYPT);
}

void functionprint(unsigned char *outputtext, int func_h, int iv_len, char *fname, unsigned char *nonce, unsigned char *iv,  int ID_algo, int len) {
	FILE * output= fopen(fname, "w");
	
	fprintf(output, "ENC%c", func_h);

  	fprintf(output, "%c", ID_algo);

  	for(int i = 0; i < NONCE_LEN; i++) 
    		fprintf(output, "%c", nonce[i]);
  		

 	for(int i = 0; i < iv_len; i++) 
    		fprintf(output, "%c", iv[i]);
  

  	for(int i = 0; i < len; i++) 
    		fprintf(output, "%c", outputtext[i]);
    		
  



}
int main (int argc, char *argv[]) {
	char *fname_input = malloc(80);
	char *fname_output = malloc(80);
	int func_enc = -1;
	unsigned char func_h = 77;
	unsigned char func_algo = 77;
	int flag_nonce = 0;
	int flag_iv = 0;
	int flag_pas = 0;
	unsigned char iv[V_L_MAX];
	unsigned char nonce[NONCE_LEN];
	unsigned char password[PASSWORD_LEN];
	int iv_len;
	int key_len;
	
	
	int codeerror = 0;	
	codeerror=analysis_input(argc, argv, &func_enc, &func_h, &func_algo, &fname_input, &fname_output, iv, &iv_len, &key_len, nonce, password,  &flag_pas,  &flag_iv,  &flag_nonce);
	if (codeerror) {
		printf("please try again");
		printf ("example : ./crypter -e -p 00000000 -h md5 -a aes128 -i  00000000000000000000000000000000 -f md5_aes128_00000000.enc\n");
		return 0;
	}
	
	int tmp=MAXLEN_AES256;
	unsigned char *intext = (char *) malloc((tmp) * sizeof(char));
	int len=0;
	unsigned char iv2[iv_len];
	
	
	
	
	FILE *in = fopen(fname_input, "r");
	if( !in )
	{
	 	printf ("program don t faund file %s\n ",fname_input);	
	 	printf ("example : ./crypter -e -p 00000000 -h md5 -a aes128 -i  00000000000000000000000000000000 -f md5_aes128_00000000.enc\n");
	 	return 0;
	}
	else
	{ 	
		if (func_enc == 1) {
			
			codeerror = input_data (&func_algo, &func_h, &key_len,&len, &iv_len,iv,nonce,intext,in);
			if ( codeerror == 1) {
	 			printf ("The file contains incorrect information\n");
	 			return 0;
	 		}
	
		
		}
		else if(func_enc == 0) {
			
			read_text(&intext, &len, in);
			
			file8null(&intext, len);
			
			len+=8;
			
			
			if (!flag_nonce)
      				func_gen(nonce, NONCE_LEN);
   			if (!flag_iv)
      				func_gen(iv, iv_len);
   			
			memcpy(iv2, iv, iv_len);
		
		
		
		}
		else {
		
			printf("u mast write : enc or dec\n");
			return 0;
		}
		
		
  		unsigned char key[key_len];
		
		if(func_h  == MD5)
			function_md5 (nonce, password, key, key_len);
		else
		if(func_h  == SHA1)
			function_sha1 (nonce, password, key, key_len);
		else {
			
			printf("u mast write : md5 or sha1\n");
			return 0;
		}
		
		
		unsigned char outputtext[len];
		
		if (func_enc ) {
		
			if (key_len == 24) 
      				des3_decrypt (intext, len, iv, key, outputtext);
   			else 
     				aes_decrypt (intext, len, iv, key, outputtext, key_len );
			
			for (int j = 0; j < 8; j++) 
     				if (outputtext[j] != 0){
        			printf("Incorrect password, please, try again.\n");
        			return 0;
     				}
     				
     			FILE * output= fopen(fname_output, "w");
    			
			for(int i = 8; i < len; i++) {
     					 fprintf(output, "%c", outputtext[i]);
    			}
  
		
		}
		else {
			
			if (key_len == 24) 
      				des3_encrypt (intext, len, iv, key, outputtext);
   		
   			else 
     				aes_encrypt (intext, len, iv, key, outputtext, key_len );
     			
			functionprint (outputtext, func_h, iv_len, fname_output, nonce, iv2, func_algo, len);	
		
		
		
		}
		
	
	}

	return 0;
}
