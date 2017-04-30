#include <stdio.h>
#include <math.h>



/* written for C Programming Term Project, G. N. Boorse

 - const variables are program inputs and can be set to any
valid numbers.

 - 

*/


//constants
const int BOAT_CARRY_LIMIT = 300;

//have to be careful that this is not greater than:
// 2^NUM_LOADS > sizeof(int)
const int NUM_LOADS = 10; 

const int NUM_BOATS = 4;

const int LOADS[10] = {220,170,130,130,120,120,100,90,90,60};


//prototypes for later
void displaySum(int m);
int calculateSum(int m);
int kthBitOfN(int k, int n);

//main program
void main()
{	
	//some declarations
	int boat_ms[NUM_BOATS];
	int boat_sums[NUM_BOATS];
	
	//main iterator value
	int i;
	
	//first zero fill both lists
    for (i = 0; i < NUM_BOATS; i++)
    {
        boat_ms[i] = 0;
        boat_sums[i] = 0;
    }	
	
	//this keeps track of the current smallest difference between
	//a running sum and the previous difference
	//set to be the smallest item in the list to begin with
	int lowest_difference = LOADS[NUM_LOADS-1];
	
	//loop over the boats
	for (i = 0; i < NUM_BOATS; i++)
	{
		//highest sum and m value for this loop
		int highest_sum = 0;
		int highest_m = 0;
		int m; //loop over all of the ms
		for (m = 0; m < (1 << NUM_LOADS); m++) // (1 << NUM_LOADS) == 2 ^ NUM_LOADS
		{
			
			//1. perform a check as to whether or not we've used any
			//   part of this solution m before.
			
			int can_use = 1; //boolean value of what we can do here
			
			int c;
			for (c = 0; c < NUM_BOATS; c++) 
			{
				//this is a simple check to see if any bits are shared
				//between any previous m values and the current one
				int j;
				for (j = 0; j < NUM_LOADS; j++)
				{
					if (kthBitOfN(j, m) == kthBitOfN(j, boat_ms[c]) && kthBitOfN(j, m))
					{
						can_use = 0; //return false if there are shared bits
					}
				}
			}
			
			if (can_use) //this is an entirely new solution
			{
				//2. calculate the sum and see if it is within bounds
				int current_sum = calculateSum(m);
				
				if (current_sum <= BOAT_CARRY_LIMIT)
				{
					//sum is within bounds
					
					if (current_sum > highest_sum)
					{
						//this sum is also a record high so far in the loop
						//store sum and m values
						highest_sum = current_sum;
						highest_m = m;	
					}
				}
			}
		}
		printf("For boat %i, best solution is: ", i+1); //print output here
		displaySum(highest_m); //nice display of boat loads
		boat_ms[i] = highest_m; //set new boat_ms and boat_sums
		boat_sums[i] = highest_sum;
	}
	
	
}
//calculates the sum based on LOADS array and indices
int calculateSum(int m)
{
	int current_sum = 0;
	
	int j;
	for (j = 0; j < NUM_LOADS; j++)
	{
		
		if (kthBitOfN(j, m) == 1)
		{
			current_sum += LOADS[j]; //calculate the sum
		}
		
	}
	return current_sum;
}

//displays the sum and its parts in a human readable format
void displaySum(int m) 
{
	int j;
	int sum = 0;
	for (j = 0; j < NUM_LOADS; j++)
	{
		
		if (kthBitOfN(j, m) == 1)
		{
			printf("%i, ", LOADS[j]);
			sum += LOADS[j];
		}
	}
	printf(" sum = %i\n", sum);
}

//simple bitwise calculate to get kth bit of n
int kthBitOfN(int k, int n)
{
	return (n >> k) & 1;
}


