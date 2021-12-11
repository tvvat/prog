#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <time.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <openssl/des.h>
#include <openssl/aes.h>

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

#define Text "I don't understand why there should be a random text here maybe a song : Like Bonnie and Clyde, we'll rob banks, in winter we'll get on a bike, in summer we'll get on a sled. Let's have a joke: we'll spend the night in the cemetery, plant a field of cannabis, and there we'll arrange a pasture"

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

void creat_fname_with_a_cipher(char *func_enc , char *func_h, char *password, char **fname) {

	*fname=strcat(*fname, func_enc);
	*fname=strcat(*fname, "_");
	*fname=strcat(*fname, func_h);
	*fname=strcat(*fname, "_");
	*fname=strcat(*fname, password);
	*fname=strcat(*fname, ".enc");
}

void file8null(unsigned char  **TEXT) {

	char *s = "00000000";
	int tmp = strlen(Text)+8;
	char *TEXTtmp = (char *) malloc((tmp) * sizeof(char));
	TEXTtmp = strcat(TEXTtmp, s);
	TEXTtmp = strcat(TEXTtmp, Text);
	*TEXT = (unsigned char *)TEXTtmp;
}

void definition_input(char *func_h,int  *iv_len,int *key_len,int *id_algo) {
	
	if (strcmp(func_h,"3des") == 0) {
		*id_algo = 0;
		*iv_len = V_L_3DES;
		*key_len = KEY_L_3DES;
		
	}
			
	if(strcmp(func_h,"aes128") == 0) {
		*id_algo = 1;
		*iv_len = V_L_AES128;
		*key_len = KEY_L_AES128;
		
	}
	
	if(strcmp(func_h,"aes192") == 0) {
		*id_algo = 2;
		*iv_len = V_L_AES192;
		*key_len = KEY_L_AES192;
		
	}
	
	if(strcmp(func_h,"aes256")==0) {
		*id_algo = 3;
		*iv_len = V_L_AES256;
		*key_len = KEY_L_AES256;
		
	}

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
	
	int def = key_len - HMAC_MD5_LEN;
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


void func_psswrd(unsigned char *res, char *a) {

	unsigned int tmp = v_int(a);
	
	for(int i = PASSWORD_LEN-1;i >= 0;i--) {
		
		*(res+i) = tmp % LEN_CHAR;
		tmp /= LEN_CHAR;
		
	}

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
	AES_set_encrypt_key (key, key_len, &akey);
	AES_cbc_encrypt (text, outputtext, len, &akey, iv, AES_ENCRYPT);
}

void functionprint(unsigned char *outputtext, char *func_enc, int key_len, int iv_len, char *fname, unsigned char *nonce, unsigned char *iv, unsigned char *key, int ID_algo, int len) {
	FILE * output= fopen(fname, "w");

  	if (strcmp(func_enc, "md5") == 0) 
    		fprintf(output, "ENC%d", 0);
  	else 
    		fprintf(output, "ENC%d", 1);

  	
  	fprintf(output, "%x", ID_algo);

  	for(int i = 0; i < NONCE_LEN; i++) 
    		fprintf(output, "%02x", nonce[i]);
  		

 	for(int i = 0; i < iv_len; i++) 
    		fprintf(output, "%02x", iv[i]);
  

  	for(int i = 0; i < len; i++) 
    		fprintf(output, "%02x", outputtext[i]);
  



}
int main (int argc, char *argv[]) {
	
	if (argc!=4)
		printf("you entered the wrong options ,please look correctly: ./gen 0a0b0cff md5 3des\n");
	else
	{	
		unsigned char password[PASSWORD_LEN];
		
		func_psswrd(password, argv[1]);
		int ID_algo;
		char *func_enc = argv[2];
		char *func_h = argv[3];
		
		if((strcmp(func_enc, "md5") != 0) && (strcmp(func_enc, "sha1") != 0))
		{	
			printf("you entered %s, correctly: ./gen 0a0b0cff md5 3des\n", func_enc);
			return 0;
		}
		
		
		if((strcmp(func_h, "3des") != 0) && (strcmp(func_h, "aes128") != 0) && (strcmp(func_h, "aes192") != 0) && (strcmp(func_h, "aes256") != 0)) 
		{
			printf("you entered %s, correctly: ./gen 0a0b0cff md5 3des\n", func_h);
			return 0;
		}
		
		unsigned char *TEXT = malloc( strlen(Text)+8*sizeof(char));;
		file8null(&TEXT);
		
		srand(time(NULL));
		 
		int iv_len, key_len ;
		definition_input (func_h, &iv_len, &key_len, &ID_algo);
		
		unsigned char nonce[NONCE_LEN];
		unsigned char iv[iv_len];
		func_gen(nonce, NONCE_LEN);
		func_gen(iv, iv_len);
		
		unsigned char key[key_len];
		
		if(strcmp(func_enc,"md5")==0)
			function_md5 (nonce, password, key, key_len);
		else
			function_sha1 (nonce, password, key, key_len);
		
		unsigned char outputtext[strlen(Text)+8];
		
		if (key_len == 24) 
      			des3_encrypt (TEXT, strlen(Text)+8, iv, key, outputtext);
   		
   		else 
     			aes_encrypt (TEXT, strlen(Text)+8, iv, key, outputtext, key_len );

     		char *fname = (char *)malloc(54*sizeof(char));
		creat_fname_with_a_cipher (func_enc, func_h, argv[1], &fname);
		printf ("%s", fname);
		functionprint (outputtext, func_enc, key_len, iv_len, fname, nonce, iv, key, ID_algo, strlen(Text)+8);	
		
	}

	return 0;
}
