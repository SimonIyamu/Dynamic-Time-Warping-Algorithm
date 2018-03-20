//Copyright 2016, Simon Iyamu Perisanidis, All rights reserved.
#include <stdlib.h>
#include <stdio.h>
#include "dtwInterface.h"

#ifdef REC

double dtw(double *A,int i,double *B,int j,double c){
	int imeionj;			/* |i-j| */
	if(i-j>0)
		imeionj=i-j;
	else
		imeionj=-(i-j);
	

	if (imeionj>c)
		return 1.0/0.0;
	else{
		if(i==1 && j==1){
			return d(*A,*B);
		}else if(i>1 && j==1)		/* -1 because we start counting from 0 */
			return d(*(A+i-1),*B) + dtw(A,i-1,B,1,c);
		else if(i==1 && j>1)
			return d(*A,*(B+j-1)) + dtw(A,1,B,j-1,c);
		else if(i>1 && j>1){
			return d(*(A+i-1),*(B+j-1)) + min(  dtw(A,i-1,B,j,c), dtw(A,i,B,j-1,c), dtw(A,i-1,B,j-1,c)  );
		}
	}
}

#else

double dtw(double *A,int i,double *B,int j,double c){
	double **D,rtrn;		/* D is an array of two dimensions where the dtw distances are saved*/
	int x,y,imeionj;
	D=malloc(j*sizeof(double));
	if(D==NULL){
		printf("Memory Error\n");
		return 1;
	}
	for(x=0;x<j;x++){
		D[x]=malloc(i*sizeof(double));
		if(D[x]==NULL){
			printf("Memory Error\n");
			return 1;
		}
	}

	if(c==1.0/0.0){				/*If theres no c limit*/
	
		D[0][0]=d(A[0],B[0]);		/* d is not inf in the diagwnios */
		
		for(x=1;x<i;x++){
			if(x<=c)
				D[0][x]=d(A[x],B[0])+D[0][x-1];			/*The first line of the array gets completed */
			else
				D[0][x]=1.0/0.0;
		}
		
		for(y=1;y<j;y++){						/* The first row of the array gets completed*/
			if(y<=c)
				D[y][0]=d(A[0],B[y])+D[y-1][0];
			else
				D[y][0]=1.0/0.0;
		}
		
		for(y=1;y<j;y++){				/* The rest array gets completed*/
			for(x=1;x<i;x++){
				if(x-y>0)
					imeionj=x-y;
				else
					imeionj=-(x-y);

				if(imeionj<=c)
					D[y][x]=d(*(A+x),*(B+y))+min( D[y][x-1], D[y-1][x], D[y-1][x-1] );
				else
					D[y][x]=1.0/0.0;
			}
		}
	}else{
		
		for(y=c+1,x=0;y<j;y++,x++){			/* Fills the perimeter of the window with inf */
				D[y][x]=1.0/0.0;
				D[x][y]=1.0/0.0;
		}

		D[0][0]=d(A[0],B[0]);		/* d is not inf in the diagwnios */
		

		for(x=1;x<=c;x++){					/* First line */
				D[0][x]=d(A[x],B[0])+D[0][x-1];
		}
		
		for(y=1;y<=c;y++){					/* and first row */
				D[y][0]=d(A[0],B[y])+D[y-1][0];
		}
													/* The rest array gets completed */	
		for(y=1;y<=c;y++){									/* This is for the part of the array that*/
			for(x=1;x<=y+c;x++){								/* has a constant beginning for x*/
				D[y][x]=d(*(A+x),*(B+y))+min( D[y][x-1], D[y-1][x], D[y-1][x-1] );
			}
		}

		for(y=c+1;y<j;y++){									/* In the rest array the place where x*/
			for(x=y-c;x<=y+c && x<i;x++){							/* starts changes in every loop  */
				D[y][x]=d(*(A+x),*(B+y))+min( D[y][x-1], D[y-1][x], D[y-1][x-1] );
			}
		}
	}

	rtrn=D[j-1][i-1];
	for(y=0;y<j;y++)
		free(D[y]);
	free(D);
	return rtrn;

}

#endif

double min(double x,double y,double z){
	if(x<=y && x<=z)
		return x;
	else if(y<x && y<=z)
		return y;
	else
		return z;
}

double d(double a,double b){
	return (a-b)*(a-b);
}

