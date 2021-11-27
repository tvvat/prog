#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
//#include <conio.h>
#include <string.h>
#include <time.h>
#define short_options "vm:edk:i:ght"
const struct option long_options[] = {
		{"version",no_argument,NULL,'v'},
		
		{"key",required_argument,NULL,'k'},
		{"iv",required_argument,NULL,'i'},
		{"debug",no_argument,NULL,'g'},
		{"help",no_argument,NULL,'h'},
		{"time",no_argument,NULL,'t'},
		{NULL,0,NULL,0}
	};
char *fkey;
char *fp;
int l;
unsigned int *re;
unsigned int *re2;
unsigned int *re3;

char * StrRemWord(char * str, char * word)
{
    long pos;
    long sLen = strlen(str);
    long wLen = strlen(word);
    char * sub;
    sub = strstr(str,word);
    while(sub)
    {
        pos = sLen - strlen(sub);
        strcpy(&str[pos],&str[pos + wLen + 1]);
        str[sLen - wLen] = '\0';
        sLen = strlen(str);
        sub = strstr(str,word);
    }
    return str;
}	
void vvod(int argc,char *argv[],int option_index)
 {  	
	int rez=getopt_long(argc,argv,short_options,long_options,NULL);
	while ((rez)!=-1)
	{
		switch(rez)
		{  
			case 'h' :{
					printf("hello!\n");
					printf("that prog help u encryption or decryption text in the file \n");
					
					printf("for example :./cipher -k path_to_file_with_key.txt path_to_file_with_ciphertext.txt\n");
					
					break;
				}
			case 'k': {
				fkey=StrRemWord(optarg,"path_to_file_with");
				fp=StrRemWord(argv[argc-1],"path_to_file_with");;
				
				break;
			};
			case '?':  {
				printf("found unknown option\n");
				break;
			};
			
		
		}
		rez=getopt_long(argc,argv,short_options,long_options,NULL);
	}
	
 }
 char* str(FILE * p,char * s){
	int i=0;
	*(s+i)=fgetc(p);
	while (*(s+i)!=EOF)
	{	
		 if (*(s+i)!='\n')
		 {	i++;
		 
		 	s= (char*)realloc(s, (i+1) * sizeof(char));
			*(s+i)=fgetc(p);
		 }
		else  *(s+i)=fgetc(p);
	}
	
	 l=i;
	return s;
	

}
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
      			k= a[i] - 'a' + 10;
    	
    		else{
    	
      		printf("%c wrong value\n", a[i]);
      		return 0;
    	}
    	res += k;
  	}
  return res;

}
void vvod_reg(char * s){
	int i=0;
	char* a=(char*)malloc(3);
	a[2]='\0';
	int j=0;
	 for(i=0;i<14;i+=2)
	 	{ a[0]=s[i];
	 	a[1]=s[i+1];
        	re[j]=v_int(a);
        	j++;
        	}
        j=0;
          for(i=14;i<32;i+=2)
	 	{ a[0]=s[i];
	 	a[1]=s[i+1];
        	re2[j]=v_int(a);
        	j++;
        	}
        j=0;
         for(i=32;i<54;i+=2)
	 	{ a[0]=s[i];
	 	a[1]=s[i+1];
        	re3[j]=v_int(a);
        	j++;
        	}
}
unsigned int func_reg(unsigned int *reg,int size){
	unsigned int a=0, b = 0, c=0, p=0;
	a = *(reg + (size-7));
  	b = *(reg + (size-5));
  	c = *(reg + (size-3));
  	printf("a=%x a=%x a=%x\n",a,b,c);
  	p = a^b^c^0x1;
  	return p;

}
void shift(unsigned int  new,unsigned int *reg,int size)
{
	for (int i=0;i<size-1;i++){
    	*(reg+i) =*(reg+i+1);
  	}
	*(reg+size-1)=new;

}
unsigned int gama(int a, int b,int c)
{ 	unsigned int res = 0, mod = 1;
	mod=mod<<8;
printf("re a=%x re a=%x re a=%x\n",re[a],re2[b],re3[c]);
  	res = (((re[a]*re2[b]*re3[c])%mod)+((re[a]*re2[b])%mod)+((re[a]*re3[c])%mod)+1)%mod;
  	return res;
}
void function(char*a1)
{	char*s=(char*)malloc(3); 
	s[2]='\0';
	int i=0;
	unsigned  int text;
	while(i<l)
	{ 	s[0]=a1[i];
		s[1]=a1[i+1];
		text=v_int(s);
		unsigned int g;
		g=func_reg(re,7);
		shift(g,re,7);
		g=func_reg(re2,9);
		shift(g,re2,9);
		g=func_reg(re3,11);
		shift(g,re3,11);
		g=gama(6,8,10);
		text=text^g;
		printf("%02x\n",text);
		 i+=2;
	}
	
}
int main (int argc, char *argv[]){
	vvod(argc,argv,0);
	FILE *pkey=fopen(fkey, "r");
	FILE *p=fopen(fp, "r");
	re=malloc(7*sizeof(int));
	re2=malloc(9*sizeof(int));
	re3=malloc(11*sizeof(int));
	char*a= (char*)malloc(54*sizeof(char));
	char*a1= (char*)malloc(10000000*sizeof(char));
	if(!p)
	{
	 	printf("program don t faund file %s ",fp);	
	 	printf ("u can use -help\n");
	 	return 0;
	 }
	 else
	 {	if(!pkey)
	 	{ 	printf("program don t faund file %s ",fkey);	
	 		printf ("u can use -help\n");
	 		return 0;
	 	}
	 	else
	 	{	
	 		a=str(pkey,a);
	 		a1=str(p,a1);
	 		vvod_reg(a);
	 		function(a1);
	 		
	
	 	}
	 
	 
	 }



	return 0;
}
