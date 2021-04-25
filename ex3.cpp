#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#define POP_SIZE 4
#define RANDOMVAR 20
using namespace std;

typedef struct Chrom{ // creating chrom structure
  short int bit[6];
  int fit;
}chrom;

int x(chrom popcurrent)        	//x function that evaluate the value of a given chrom
{
 int z;
   z=(popcurrent.bit[0]*1)+(popcurrent.bit[1]*2)+(popcurrent.bit[2]*4)+(popcurrent.bit[3]*8)+(popcurrent.bit[4]*16);
   if(popcurrent.bit[5]==1)
   z=z*(-1);                  	// z=sum of the ( bits * their weights) with the sign value
    return(z);                	//return the value of z
 }                             	// end x function

int y(int x)          		// the y function that we check for it's maximum value takes x value
{
 int y;
   y=(x*x)+4;            	//
   return(y);
}
void *evpop(chrom popcurrent[POP_SIZE]){
  int i, j, value;

  for(j = 0;j < POP_SIZE;j++){
    for (i = 0; i < count; i++) {
      popcurrent[j].bit[i]= rand() %2; // random value only 0 or 1
    }

    value=x(popcurrent[j]); //get the value of the chrom as integer
    popcurrent
  }
}
void *pickchroms(chrom popcurrent[POP_SIZE])   	// pickchroms takes a pointer to array of chroms
{
 int i,j;
   chrom temp;                            	//temp chrome to use in sorting
    for(i=0;i<3;i++)               		//sorting the given set due to fitness
       for(j=0;j<3;j++)
         {
             if(popcurrent[j+1].fit>popcurrent[j].fit)
               {
                 temp=popcurrent[j+1];
                 popcurrent[j+1]=popcurrent[j];
                 popcurrent[j]=temp;

               }   
         }

  return(0);
}
void *crossover(chrom popnext[POP_SIZE]) // crossover function takes a pointer to array of chromes
{
 int random;
   int i;
   random=rand();                                  	//random cross over point
   random=((random%5)+1);                    		// cross point should be between (1 - 5)
   for(i=0;i<random;i++)                     	//crossing the bits below the cross point index
     {
       popnext[2].bit[i]=popnext[0].bit[i];        	//child 1 cross over
         popnext[3].bit[i]=popnext[1].bit[i];     	// child 2 cross over
      }

 for(i=random;i<6;i++)                        	// crossing the bits beyond the cross point index
     {
       popnext[2].bit[i]=popnext[1].bit[i];     	// child 1 cross over
       popnext[3].bit[i]=popnext[0].bit[i];       	// chlid 2 cross over
      }

      for(i=0;i<4;i++)
       popnext[i].fit=y(x(popnext[i]));     	// calculating the fitness values for the new set

  return(0);
   }
int main(){

}
