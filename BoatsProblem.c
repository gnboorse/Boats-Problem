#include <stdio.h>

/* written for C Programming Term Project, G. N. Boorse

This program solves for the optimal load configuration
by incrementing a variable m from 0 to 127 and using
the binary representation of that m to indicate which
indices to select for the sum from the LOADS array.

For instance, when m = 96 (or 0b1100000), the 
algorithm will select the first two items from the
LOADS array. When m = 100 (0b1100100) the first two
and the fifth. This is an easy way of getting the
combinations of all of the cargo loads.

The boat_ms and boat_sums arrays keep track of which 
m and sum values have been achieved before, making sure
the algorithm can't find the same value twice.

*/
//constants
const int BOAT_CARRY_LIMIT = 300;
const int NUM_LOADS = 7;
const int LOADS[7] = {220,130,120,100,90,90,60};

//prototypes for later
void displaySum(int m);
int calculateSum(int m);
int kthBitOfN(int k, int n);

//main program
void main()
{	
	//some declarations
	int boat_ms[2] = {0, 0};
	int boat_sums[2] = {0, 0};
	
	int lowest_difference = LOADS[NUM_LOADS-1];
	
	//loop over both boats
	int i;
	for (i = 0; i < 2; i++)
	{
		//highest sum and m value for this loop
		int highest_sum = 0;
		int highest_m = 0;
		int m; //loop over all of the ms
		for (m = 0; m < 128; m++)
		{
			
			//1. perform a check as to whether or not we've used any
			//   part of this solution m before.
			
			int can_use = 1; 
			
			int c;
			for (c = 0; c < 2; c++) 
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
		printf("For boat %i, best solution is: ", i+1);
		displaySum(highest_m);
		boat_ms[i] = highest_m;
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


