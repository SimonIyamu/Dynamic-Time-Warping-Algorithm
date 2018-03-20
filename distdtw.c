#include <stdio.h>
#include <stdlib.h>
#include "dtwInterface.h"
#include <time.h>

int main(int argc,char *argv[]){
	clock_t start, end;
	start = clock();
	int i,j;
	double *A,*B,c,curr,class,class0,min_dis;
	int plh8ostr,plh8ostest,length,lengthtest,fails=0,series;


	switch(argc){
		case 1:	  c=1.0/0.0;
			  break;
		case 2:	  c=atoi(argv[1]);
			  if(c<0){
				  printf("Error:Expected positive int appointment\n");
				  return 1;
			  }
			  break;
		default:  printf("Error:Expected one or zero appointments\n");
			  return 1;
			  break;
	}

	scanf("%d %d",&plh8ostr,&length);			/* plh8ostr is the amount of series in the training set(greek)*/
	double **training;					/* Training is an array with two dimensions which contains the training set.*/
	training=malloc(plh8ostr*sizeof(double));
	if(training==NULL){
		printf("Memory Error\n");
		return 1;
	}
	for(i=0;i<plh8ostr;i++){
		training[i]=malloc((length+1)*sizeof(double));
		if(training[i]==NULL){
		}
		for(j=0;j<=length;j++)				/* The first double of each line represents its class*/
			scanf("%lf",&training[i][j]);
	}
	
	scanf("%d %d",&plh8ostest,&lengthtest);			/* Same goes for the test set,but */
	if(lengthtest!=length){					/* check if test set's series have the same length as those of the training set*/
		printf("Error: The time series must be of the same length.\n");
		return 2;
	} 
	double **test;
	test=malloc(plh8ostest*sizeof(double));
	if(test==NULL){
		printf("Memory Error\n");
		return 1;
	}
	for(i=0;i<plh8ostest;i++){
		test[i]=malloc((length+1)*sizeof(double));
		if(test[i]==NULL){
			printf("Memory Error\n");
			return 1;
		}
		for(j=0;j<=length;j++)
			scanf("%lf",&test[i][j]);	
	}

	for(j=0;j<plh8ostest;j++){
		class0=test[j][0];				/*class0 is the initial class of line j*/
		min_dis=dtw(&test[j][1],length,&training[0][1],length,c); /*we are looking for the minimum dtw distance*/
		class=training[0][0];
		for(i=1;i<plh8ostr;i++){
			curr=dtw(&test[j][1],length,&training[i][1],length,c);
			if(curr<min_dis){
				min_dis=curr;
				class=training[i][0];
				series=i;
			}
		}
		printf("Series %d (class %.0f) is nearest (distance %f) to series %d (class %.0f)\n",
			j+1,class0,min_dis,series+1,class);						/* +1 because 0 is the 1st*/
		
		if(class!=class0){
			fails++;
			test[j][0]=class;
		}
	}
	fprintf(stderr,"Error rate: %.3f\n",(double)fails/(double)plh8ostest);




	for(i=0;i<plh8ostr;i++)
		free(training[i]);
	free(training);
	
	for(i=0;i<plh8ostest;i++)
		free(test[i]);
	free(test);
	end = clock();
	printf("CPU time: %f secs\n",((double) (end - start))/ CLOCKS_PER_SEC);
	return 0;
	
}
