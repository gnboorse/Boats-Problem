# Boats-Problem
Load distribution problem for different cargo weights 
There are seven loads as follows: 220  130  120  100  90  90  60  
and two boats that each can hold a maximum cargo of 300. 

The boats cannot be overloaded. Find the maximum load that can be carried 
in each boat.

Solution is: 120 + 90 + 90 = 300    and 130 + 100 + 60 = 290


This approach uses bitwise operations on a number increasing from 0-127
and using those combinations, then selects loads for a sum. The most
optimal sum is then selected
