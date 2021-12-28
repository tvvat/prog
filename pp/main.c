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
#include <math.h>

int* walsh_ad(unsigned int* f, int quantity) {
	unsigned int u = 0, a = 0;
	int k = 0;
	int s = 0;
	int tmp=1, tmpquantity;
	
	tmp<<= quantity;
	
	int* summ = (int*)malloc(tmp* sizeof(int));
	for (int i = 0; i < tmp; i++) {
		s = 0;
		a = 0;
		for (int j= 0; j < tmp; j++) {
			unsigned int res = a & u;
			unsigned int r = 0;
			while (res > 0) {
				r += res % 2;
				res = res / 2;
			}
			r = r % 2;
			
			if ((f[j] ^ (r)) == 0) {
				s+= 1;
			}
			else {
				s+= -1;
			}
			
			summ[i] = s;
			a++;
			
		}
		u++;
	}
	return summ;
}
int pow2(int n ) {
	
	int res = 1;
	if (n==-1)
	return 0;
	else
	return res<<n;


}

int quantity_x(int len) {

	int res=0;
	while(len>0) {
		res++;
		len>>=1;
	}
	return (res-1);

}
void analysis_input(int *a, char *funck, int *weight) {
	
	for(int i = 0;i < strlen(funck); i++) {
		char 	tmp[1];
		tmp[0]=*(funck+i);
		a[i]=atoi(tmp);
		if (a[i]) 
			*weight = *weight + 1;
		
	}
	
		
		


}

void triangle(int *a,int len,int *anf) {
int tmp=len;
	for(int i = 1;i < tmp + 1; i++) {

		for(int j = 0;j < len - 1; j++) {
			
			a[j]=a[j] ^ a[j+1];
			if( !j)
				anf[i]=a[j];
			printf("%x",a[j]);	
			
		}
		printf("\n");
		len--;
	}

}
void anfprint(int *anf,int len,int quantity) {
	int x;
	
	int i;
	for( i = 0;i<len;i++) {
		if (anf[i] && (i != 0)) {
			int j=quantity;
			for(x = i;x > 0;x /=2){
				if (x%2) {
					printf("x%x",j);
				
				
				}
				j--;
			}
			printf("^");
		}
		
	}
	printf("1\n");
}

void sknf(int *vector, int len, int quantity) {
	int x, i;
	int tmp = quantity;
	for( i = 0;i < len; i++) {
		if ( ! *(vector + i) ) {
			printf ("(");
			int j = quantity;
			for(x = i;quantity > 0; quantity--, x /= 2){
				
				if (x%2 == *(vector+i)) {
					printf ("x%x", j);
					if ( !(quantity - 1 == 0) ) 
						printf ("+");
				
				}
				else {
					printf ("(not x%x)", j);
					 if ( !(quantity - 1 == 0) ) 
					 	printf ("+");
				}
				j--;
			}
			quantity = tmp;
			printf (")");
		
		}
		
	}

	
	printf ("\n");
}
void sdnf(int *vector, int len, int quantity) {
	int x, i;
	int tmp = quantity;
	for( i = 0;i < len; i++) {
		if ( *(vector +i ) ) {
			if (!(i == 0) ) printf("+");
			int j = quantity;
			for(x = i; quantity > 0; quantity--, x /=2){
				
				if (x%2 == *(vector+i)) {
					printf("x%x",j);
					
				
				}
				else {
					printf("(not x%x)",j);
					 
				}
				j--;
				
			}
			quantity = tmp;
			
			
		}
			
		
	}

	
	printf("\n");
}

void fictitious(int *vector,int len,int quantity) {
	int fict[quantity] ;
	for (int j = 0; j < quantity; j++)
		fict[j] = 0;
	int k ;
	int tmp = quantity ;
	for ( quantity-1 ;quantity >= 0; quantity--) {
	
		int lenfict = len >> (quantity+1) ;
		int i = 0, j = lenfict;
		
		while(j < len) {
			int sum=0;
			if ( *( vector+ i) != *( vector+ j) ) {
				fict[quantity] = 1;
			break;
			}
			
			if ( i + 1 == j) {
				
				i= j + lenfict;
				j= i + lenfict;
				
			}
			else {
				i++;
				j++;
			
			}
			
			
			
		}
		
		
			
		
		

	}
	
	for (int j = tmp - 1; j>= 0; j--)
		if (!fict[j]) 
		 	printf ("fictitious :x%d\n",j+1);
	
	
	
	printf("\n");
	
}
void nonlinearity_function(int *w, int len, int quantity) {
	int max = 0;
	for (int j = 0; j <len; j++)
		if (abs(w[j])> max) 
		 max=abs(w[j]);
		
	int tmp=1;
	
	tmp<<=( quantity - 1);
	printf("nonlinearity_function:%d",(tmp-max/2));



}
void cor_im(int *w, int len, int quantity) {
	int tmp=1;
	
	tmp<<=( quantity );
	int weight[quantity];
	int m = 0;
	for ( int i = 1 ; i< tmp ; i++ ) {
		int vector = i ;
		int weight_vec = 0;
		while (vector > 0) {
			if (vector % 2) 
				weight_vec++;
			vector/=2;
		}
		if ( *(w + i) != 0) 
		 	weight[weight_vec] += 1; 
		else
			weight[weight_vec] += 0;
		
	
	}
	tmp = 0;
	for ( int  i = 1;i <  quantity ; i++)
		if (  weight[i] != 0) {
			if (i == 1)
				printf("the function is not correlationally immune");
			
			break;
		}
		else {
			m++;
			tmp = 1;
		}
	if ( tmp ) {
	
	printf("correlationally immune: %d",m);
	}
	


}
int main (int argc, char *argv[]) {

	char *funck=argv[argc-1];
	int len=strlen(funck);
	int vector[len];
	int anf[len];
	int weight ;
	
	int quantity=quantity_x(len);
	 
	analysis_input(vector, funck, &weight);
	printf("weight=%x\n",weight);
	if (  len / 2 == weight) 
		printf("equally probable\n");
	else
		printf("are not equally probable\n");
		
	triangle(vector, len, anf);
	
	
	printf("anf:\n");
	
	anfprint(anf, len, quantity);
	
	printf("sknf:\n");
	analysis_input(vector, funck, &weight);
	sknf(vector, len, quantity);
	
	printf("sdnf:\n");
	analysis_input(vector, funck, &weight);
	sdnf(vector, len, quantity);

	analysis_input(vector, funck, &weight);
	fictitious(vector, len, quantity);
	
	analysis_input(vector, funck, &weight);
	
	int* w= (int*)malloc(len* sizeof(int));
	
	w = walsh_ad (vector, quantity);
	
	
		printf ("walsh:\n");
	for (int j = 0; j <len; j++)
		printf ("%d\n",w[j]);
	printf("\n");
	
	nonlinearity_function(w, len,quantity);
	printf("\n");
	cor_im(w, len,quantity);
	
	
	return 0;

}
