#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int perebor(FILE *out,int k,int lenght_str)
{ 
	int n=k;
	int IP[4]={0,0,0,0};
	int c[3];
	int count=0;
	int count2=0;
	int count3=0;
	int count4=0;
	int j;
	char *str=(char*)malloc((lenght_str-n)*sizeof(int));
	for(int i=0;i<lenght_str-n;i++)
	*(str+i)='a';
	
		int a;
		a=n-3;//вычитаем три точки и три числа которые точно должны быть заняты помимо еще одной позиции
		a=a-3;
		if (a<=3)
		
		{
			if (a==1)
			{	while(count<10000)
				{
				j=count/1000;
				IP[0]=j%10;
				j=count/100;
				IP[1]=j%10;
				j=count/10;
				IP[2]=j%10;
				//j=j/10;
				IP[3]=count%10;
				if (count!=0)
				for(int i=0;i<lenght_str-n;i++)
	
				fprintf(out,"%c",*(str+i));
				fprintf(out,"%d.%d.%d.%d\n",IP[0],IP[1],IP[2],IP[3]);
				count++;
				}	
			}
				
				
			
			if (a==2)
			{ 	count=0;
				while(count<100000)
				{
					j=count/10000;
					IP[0]=j%10;
					j=count/100;
					IP[1]=j%10;
					
					j=count/10;
					IP[2]=j%10;
					
					//j=j/10;
					IP[3]=count%100;
					if(IP[3]<10)
						IP[3]+=10;
					if (count!=0)
					for(int i=0;i<lenght_str-n;i++)
	
						fprintf(out,"%c",*(str+i));
					fprintf(out,"%d.%d.%d.%d\n",IP[0],IP[1],IP[2],IP[3]);
					count++;
				}	
				count=0;
				while(count<100000)
				{
					j=count/10000;
					IP[0]=j%10;
					j=count/100;
					IP[1]=j%10;
					
					j=count/10;
					IP[2]=j%100;
					if(IP[2]<10)
						IP[2]+=10;
					//j=j/10;
					IP[3]=count%10;
					if (count!=0)
					for(int i=0;i<lenght_str-n;i++)
	
						fprintf(out,"%c",*(str+i));
					fprintf(out,"%d.%d.%d.%d\n",IP[0],IP[1],IP[2],IP[3]);
					count++;
				}		
				count=0;
				while(count<100000)
				{
					j=count/10000;
					IP[0]=j%10;
					j=count/100;
					IP[1]=j%100;
					if(IP[1]<10)
						IP[1]+=10;
					j=count/10;
					IP[2]=j%10;
					//j=j/10;
					IP[3]=count%10;
					if (count!=0)
					for(int i=0;i<lenght_str-n;i++)
	
						fprintf(out,"%c",*(str+i));
					fprintf(out,"%d.%d.%d.%d\n",IP[0],IP[1],IP[2],IP[3]);
					count++;
				}		
				count=10000;
				while(count<100000)
				{
					j=count/1000;
					IP[0]=j%100;
					j=count/100;
					IP[1]=j%10;
					j=count/10;
					IP[2]=j%10;
					//j=j/10;
					IP[3]=count%10;
					if (count!=0)
					for(int i=0;i<lenght_str-n;i++)
	
						fprintf(out,"%c",*(str+i));
					fprintf(out,"%d.%d.%d.%d\n",IP[0],IP[1],IP[2],IP[3]);
					count++;
				
				}
			}
			if (a==3)
			{
					
				count=0;
				while(count<1000000)
				{
					j=count/100000;
					IP[0]=j%10;
					j=count/10000;
					IP[1]=j%10;
					
					j=count/1000;
					IP[2]=j%10;
					
					//j=j/10;
					IP[3]=count%1000;
					if(IP[3]<100)
						IP[3]+=100;
					if (IP[0]<256 && IP[1]<256 && IP[2]<256 && IP[3]<256)
					{if (count!=0)
					for(int i=0;i<lenght_str-n;i++)
	
						fprintf(out,"%c",*(str+i));
					fprintf(out,"%d.%d.%d.%d\n",IP[0],IP[1],IP[2],IP[3]);}
					count++;
				}
				count=0;
				while(count<1000000)
				{
					j=count/100000;
					IP[0]=j%10;
					j=count/10000;
					IP[1]=j%10;
					
					j=count/10;
					IP[2]=j%1000;
					if(IP[2]<100)
						IP[2]+=100;
					//j=j/10;
					IP[3]=count%10;
					if (IP[0]<256 && IP[1]<256 && IP[2]<256 && IP[3]<256)
					{
					if (count!=0)
					for(int i=0;i<lenght_str-n;i++)
	
						fprintf(out,"%c",*(str+i));
					fprintf(out,"%d.%d.%d.%d\n",IP[0],IP[1],IP[2],IP[3]);
					}
					count++;
				}
				count=0;
				while(count<1000000)
				{
					j=count/100000;
					IP[0]=j%10;
					j=count/100;
					IP[1]=j%1000;
					if(IP[1]<100)
						IP[1]+=100;
					j=count/10;
					IP[2]=j%10;
					
					//j=j/10;
					IP[3]=count%10;
					if (IP[0]<256 && IP[1]<256 && IP[2]<256 && IP[3]<256){
					if (count!=0)
					for(int i=0;i<lenght_str-n;i++)
	
						fprintf(out,"%c",*(str+i));
					fprintf(out,"%d.%d.%d.%d\n",IP[0],IP[1],IP[2],IP[3]);}
					count++;
				}count=0;
				while(count<1000000)
				{
					j=count/1000;
					IP[0]=j%1000;
					if(IP[0]<100)
						IP[0]+=100;
					j=count/100;
					IP[1]=j%10;
					
					j=count/10;
					IP[2]=j%10;
					
					//j=j/10;
					IP[3]=count%10;
					if (IP[0]<256 && IP[1]<256 && IP[2]<256 && IP[3]<256){
					if (count!=0)
					for(int i=0;i<lenght_str-n;i++)
	
						fprintf(out,"%c",*(str+i));
					fprintf(out,"%d.%d.%d.%d\n",IP[0],IP[1],IP[2],IP[3]);}
					count++;
				}	
				while(count<1000000)
				{
					j=count/10000;
					IP[0]=j%100;
					if(IP[0]<100)
						IP[0]+=100;
					j=count/100;
					IP[1]=j%100;
					if(IP[1]<100)
						IP[1]+=100;
					j=count/10;
					IP[2]=j%10;
					
					//j=j/10;
					IP[3]=count%10;
					if (IP[0]<256 && IP[1]<256 && IP[2]<256 && IP[3]<256){
					if (count!=0)
					for(int i=0;i<lenght_str-n;i++)
	
						fprintf(out,"%c",*(str+i));
					fprintf(out,"%d.%d.%d.%d\n",IP[0],IP[1],IP[2],IP[3]);}
					count++;
				}
				while(count<1000000)
				{
					j=count/10000;
					IP[0]=j%100;
					if(IP[0]<100)
						IP[0]+=100;
					j=count/1000;
					IP[1]=j%100;
					
					j=count/10;
					IP[2]=j%10;
					
					//j=j/10;
					IP[3]=count%10;
					if (IP[0]<256 && IP[1]<256 && IP[2]<256 && IP[3]<256){
					if (count!=0)
					for(int i=0;i<lenght_str-n;i++)
	
						fprintf(out,"%c",*(str+i));
					fprintf(out,"%d.%d.%d.%d\n",IP[0],IP[1],IP[2],IP[3]);}
					count++;
				}	
			}
						
			
		}
	
	
	
}
int IPmask(FILE *f,FILE *out)
{ 
	int tf=0;
	char *res;
	//char *fname;
	int n=0,i=0;
	res= (char*)malloc(1* sizeof(int));
	*(res+i)=fgetc(f);
        while ( *(res+i)!=EOF)
        {       
        	if(*(res+i)=='\n')
        	{	fprintf(out,"\n");
        		i=0;
        	}	
        	else
        		if (*(res+i)!='0') 
        			
        		
        		{
        			while (*(res+i)=='1')
        			{	tf=1;
        				n++;
        				i++;
        				res= (char*)realloc(res, (i+1) * sizeof(int));
					*(res+i)=fgetc(f);
					
        			}
        			perebor(out,n,i);
        			n=0;
        			
        		}
        		else
        			fprintf(out,"a");
        		
        	if(*(res+i)!='\n') 
        		fprintf(out,"a");
        	i++;
		res= (char*)realloc(res, (i+1) * sizeof(int));
		*(res+i)=fgetc(f);
        }
        
        
     
 return 0;
}

int bin10 (char *s,int n,FILE *out)
{
 	int res=0;
   	int k=1,step=0;
   	int j=0;
   	
 	for ( int i = n-2; i >=0; --i )
	{      j++;
	

      		if (s[i]=='1')
      	
      			{ if(j==0)res++;
      			else 
      			{ 	step=j;
      				while(step>0)
      					{k*=2;step--;}
      			res+=k;k=1;
      			}
      		
      			}
      		
   	}
   	return res;
}
 
void maskstr2(FILE *f,FILE *out)
{

	
	int i=0;
	char *a=(char*)malloc(1* sizeof(int));
	*(a+i)=fgetc(f);
	
	while(*(a+i)!=EOF)
	{	a= (char*)realloc(a, (i+1) * sizeof(int));
		while(*(a+i)!='\n')
		{
			i++;
			a= (char*)realloc(a, (i+1) * sizeof(int));
			*(a+i)=fgetc(f);
		}
		int n=i;
		int k=0;
		i=0;
		
				
			
	     	int l;
		
		l=bin10(a,n,out);
		
		fprintf(out,"%x",l);
		
		i=0;n=0;
		a= (char*)realloc(a, (i+1) * sizeof(int));
			*(a+i)=fgetc(f);
			fprintf(out,"\n");
		
	}
	
}
int maskstr( char *a,FILE *f,FILE *out,char atxt[])
{	
	int j=0;
	int i=0,k=0,kt=0,tf=0;
	*(a+i)=fgetc(f);
	int IP[4]={-1,-1,-1,-1};
	char c[3];
	
	while ( *(a+i)!=EOF)
	{  	
		if (kt==4)
  		 {	
  		 	if (IP[0]<256 && IP[1]<256 && IP[2]<256 && IP[3]<256)
  		 	{
  		  		while(k>1)
  		  		{	
  		  			
  		  			*(atxt+j)='1';
  		  			j++;
  		  			atxt=(char*)realloc(atxt, (j+1) * sizeof(int));
  		  			
  		  			k--;
  		  	
  		  		}		
  		  	} else
  		 		 while(k>0)
  		  		{
  		  			
  		  			*(atxt+j)='0';
  		  			j++;
  		  			atxt=(char*)realloc(atxt, (j+1) * sizeof(int));
  		  			
  		  			k--;
  		  	
  		  		}
  		  	
  		  
  			kt=0;
  			k=0;
  			
  		  	*(atxt+j)='0';
  		  	j++;
  		  	atxt=(char*)realloc(atxt, (j+1) * sizeof(int));
  			c[0]=' ';
  			c[1]=' ';
  			c[2]=' ';
  		}
		tf=0;
	        if (kt!=4)
			if(!('0'<=(*(a+i))&&(*(a+i))<='9')&&(*(a+i)!='.')) 
			{
				kt=0;
				while(k>0)
  		  		{
  		  			
  		  			*(atxt+j)='0';
  		  			j++;
  		  			atxt=(char*)realloc(atxt, (j+1) * sizeof(int));
  		  			
  		  			k--;
  		  	
  		  		}
  		  		k=0;
  		  		c[0]=' ';
  		  		c[1]=' ';
  		  		c[2]=' ';
  			}
	
	
	
	
	
	
		if (*(a+i)=='\n')
		{ 
			k=0;
			kt=0;
			tf=1;
			
  		  	*(atxt+j)='\n';
  		  	j++;
  		  	atxt=(char*)realloc(atxt, (j+1) * sizeof(int));
			i++;
			a= (char*)realloc(a, (i+1) * sizeof(int));
			*(a+i)=fgetc(f);
		}
	        else
	        {	if('0'<=*(a+i)&&*(a+i)<='9')
	        	{
	        		c[2]=*(a+i);
	        		i++;
	        		k++;
				a= (char*)realloc(a, (i+1) * sizeof(int));
				*(a+i)=fgetc(f);
				if (*(a+i)=='\n')
				{ 	
					if (kt==4)
  					 {	
  		 				if (IP[0]<256 && IP[1]<256 && IP[2]<256 && IP[3]<256)
  		 				{
  		  					while(k>1)
  		  					{	
  		  			
  		  						*(atxt+j)='1';
  		  						j++;
  		  						atxt=(char*)realloc(atxt, (j+1) * sizeof(int));
  		  			
  		  						k--;
  		  	
  		  					}		
  		  				} else
  		 		 			while(k>0)
  		  					{
  		  			
  		  						*(atxt+j)='0';
  		  						j++;
  		  						atxt=(char*)realloc(atxt, (j+1) * sizeof(int));
  		  			
  		  						k--;
  		  	
  		  					}
  		  	
  		  
  							kt=0;
  							k=0;
  			
  		  					*(atxt+j)='0';
  		  					j++;
  		  					atxt=(char*)realloc(atxt, (j+1) * sizeof(int));
  							c[0]=' ';
  							c[1]=' ';
  							c[2]=' ';
  					}
					tf=1;
					
					k=0;
					kt=0;
				
					
  		  			*(atxt+j)='\n';
  		  			j++;
  		  			atxt=(char*)realloc(atxt, (j+1) * sizeof(int));
					i++;
					a= (char*)realloc(a, (i+1) * sizeof(int));
					*(a+i)=fgetc(f);
				}
				else
	        		{	if((*(a+i)=='.')||(kt==3))
					{
						IP[kt]=atoi(c);
						kt++;
						
						k++;
		 			}
		 			else
		 			{
		 				if('0'<=(*(a+i))&&(*(a+i))<='9' && tf==0)
		 				{	
		 					c[1]=*(a+i);
		 					i++;
	        					k++;
							a= (char*)realloc(a, (i+1) * sizeof(int));
							*(a+i)=fgetc(f);
							if (*(a+i)=='\n')
							{ 	
								if (kt==4)
  		 						{	
  		 							if (IP[0]<256 && IP[1]<256 && IP[2]<256 && IP[3]<256)
  		 							{
  		  								while(k>1)
  		  								{	
  		  			
  		  									*(atxt+j)='1';
  		  									j++;
  		  									atxt=(char*)realloc(atxt, (j+1) * sizeof(int));
  		  			
  		  									k--;
  		  	
  		  								}		
  		  							} else
  		 		 						while(k>0)
  		  								{
  		  			
  		  									*(atxt+j)='0';
  		  									j++;
  		  									atxt=(char*)realloc(atxt, (j+1) * sizeof(int));
  		  			
  		  									k--;
  		  	
  		  								}
  		  	
  		  
  									kt=0;
  									k=0;
  			
  		  							*(atxt+j)='0';
  		  							j++;
  		  							atxt=(char*)realloc(atxt, (j+1) * sizeof(int));
  									c[0]=' ';
  									c[1]=' ';
  									c[2]=' ';
  								}
								tf=1;
								
  		  						k=0;
								kt=0;
								
								*(atxt+j)='\n';
  		  						j++;
  		  						atxt=(char*)realloc(atxt, (j+1) * sizeof(int));
								i++;
								a= (char*)realloc(a, (i+1) * sizeof(int));
								*(a+i)=fgetc(f);
							}
							else
							{
								if((*(a+i)=='.')||(kt==3))
								{
									IP[kt]=atoi(c);
									kt++;
									
									k++;
		 						}
		 						else
		 						{ 
		 							if('0'<=(*(a+i))&&(*(a+i))<='9' && tf==0)
		 							{
		 						
		 								k++;
		 								c[0]=*(a+i);
		 								a= (char*)realloc(a, (i+1) * sizeof(int));
										*(a+i)=fgetc(f);
										if (*(a+i)=='\n')
										{ 	
											
											
											
											if (kt==4)
  		 									{	
  		 										if (IP[0]<256 && IP[1]<256 && IP[2]<256 && IP[3]<256)
  		 										{
  		  											while(k>1)
  		  											{	
  		  			
  		  												*(atxt+j)='1';
  		  												j++;
  		  												atxt=(char*)realloc(atxt, (j+1) * sizeof(int));
  		  			
  		  												k--;
  		  	
  		  											}		
  		  										} else
  		 		 									while(k>0)
  		  											{
  		  			
  		  												*(atxt+j)='0';
  		  												j++;
  		  												atxt=(char*)realloc(atxt, (j+1) * sizeof(int));
  		  			
  		  												k--;
  		  	
  		  											}
  		  	
  		  
  												kt=0;
  												k=0;
  			
  		  										*(atxt+j)='0';
  		  										j++;
  		  										atxt=(char*)realloc(atxt, (j+1) * sizeof(int));
  												c[0]=' ';
  												c[1]=' ';
  												c[2]=' ';
  											}	
											tf=1;
											while(k>0)
  		 									 {
  		  										*(atxt+j)='0';
  		  										j++;
  		  										atxt=(char*)realloc(atxt, (j+1) * sizeof(int));
  		  										k--;
  		  	
  		  									}
  		  									k=0;
											kt=0;
											*(atxt+j)='\n';
  		  									j++;
  		  									atxt=(char*)realloc(atxt, (j+1) * sizeof(int));
											i++;
											a= (char*)realloc(a, (i+1) * sizeof(int));
											*(a+i)=fgetc(f);
										}
										else
		 								if((*(a+i)=='.')||(kt==3))
										{	
											IP[kt]=atoi(c);
											kt++;
											k++;
		 								}
		 							}
		 				
		 				
		 						}
		 			        }
		 			
		 			}
		 			}	
		 		}
	        	}
	        	else
	        	*(atxt+j)='0';
  		  	j++;
  		  	atxt=(char*)realloc(atxt, (j+1) * sizeof(int));
	        	
	         }	
	         if(tf==0)
	         {	i++;
			a= (char*)realloc(a, (i+1) * sizeof(int));
			*(a+i)=fgetc(f);
		
		}
		else tf=0;
			
	}
	for (i=0;i<j;i++)
	printf("%c",*(atxt+i));
	
	return i;
}

int main(int argc, char** argv)
{
	
	char* atxt=(char*)malloc(1* sizeof(int));;
	
	char *str;
	char* fname = (char*)malloc(99);
	char* fname1 = (char*)malloc(99); 
	char* fname2 = (char*)malloc(99); 
	int n=1,i=0;
	str= (char*)malloc(n* sizeof(int));
	scanf("%s",fname1);
	scanf("%*c");
	scanf("%s",fname);
	FILE *s=fopen(fname1, "r");
	FILE *v0=fopen(fname, "w");
	scanf("%*c");
	scanf("%s",fname2);
	
	
	
	
	int l=maskstr(str,s,v0,atxt);
	printf("%d",l);
	for (i=0;i<l;i++)
	printf("%c",*(atxt+i));
	fclose(v0);
	v0=fopen(fname, "r");
	FILE *v=fopen(fname2, "w");
	maskstr2(v0,v);
	fprintf(v,"\n");
	fclose(v0);
	v0=fopen(fname, "r");
	IPmask(v0,v);
	
	
	return 0;
}
