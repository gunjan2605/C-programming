#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "gates.h"


void read_data(Flight* ptr_flight);
void print_test(Flight* ptr_flight); 
void sortMode(Flight* ptr_flight);
void insertionSort(Flight* ptr_flight);
void mergeSort(Flight* ptr_flight, int l, int r);
void merge(Flight* ptr_flight, int l,int mid, int r);
void countSort(Flight* ptr_flight);
void result(Flight* ptr_flight);

int main(int argc, char* argv[]) //
{ 
   char* condition = argv[1];
   
   Flight flight_array[MAX_SIZE];
   read_data(flight_array);
   sortMode(flight_array); //sort such that arrivals appear before departure
   
   if(argc == 1)
   {
      insertionSort(flight_array);
   }
   else if (condition[0]=='m')
   {
      printf("Using merge sort\n");
      mergeSort(flight_array, 0, MAX_SIZE-1);
   }
   else if (condition[0]=='c')
   {
      countSort(flight_array);
   }

   //print_test(flight_array);
   result(flight_array);
}

void read_data(Flight* ptr_flight){
   FILE* ptr;
   ptr = fopen("flights_file.csv","r");
   const char str1[2] = ",";
   char *token;
   const char str2[4] = "ATL";
   char str3[4];
   int i;
   int j;
  	if(ptr != NULL)
   {
      char line[28];
      char words[6][5];
      j = 0;
      while((fgets(line, sizeof line, ptr)!=NULL)&&(j<MAX_SIZE))
      {
         i = 0;
         token = strtok(line, str1);
         while(token!=NULL)
         {
            strcpy(words[i], token);
            i++;
            token = strtok(NULL,str1);
         } 
         if (strcmp(words[2],str2)==0)
         {
            (ptr_flight + j)-> mode = -1; //departure 
            (ptr_flight + j)-> time = atoi(words[4]);
         }
         else
         {
            (ptr_flight + j)-> mode = 1; //arrival 
            (ptr_flight + j)-> time = atoi(words[5]);
         }
         j++;
      }
      fclose(ptr);
   }
   else
   {
      perror("flights_file.csv");
   }
}

void print_test(Flight* ptr_flight)
{
   for (int i=0; i<MAX_SIZE;i++)
   {
      printf("%d,%d \n", (ptr_flight + i)-> mode, (ptr_flight + i)->time);
   }
}

void sortMode(Flight* ptr_flight)
{
   int i;
   int j;
   Flight key;
   //sort mode arrivals first
   for(i=0; i<MAX_SIZE; i++)
   {
      key = *(ptr_flight + i);
      for(j = i-1; j>=0 && (*(ptr_flight + j)).mode < key.mode; j--) //sort in descending order for mode
      {
         *(ptr_flight + j + 1) = *(ptr_flight + j); 
      }
      *(ptr_flight + j + 1) = key;
   }   
}

void insertionSort(Flight* ptr_flight)
{
   printf("Using insertion sort\n");
   int i, j; 
   Flight key; 
   //sort by time
   for(i=0; i<MAX_SIZE; i++)
   {
      key = *(ptr_flight + i);
      for(j = i-1; j>=0 && (*(ptr_flight + j)).time > key.time; j--)
      {
         *(ptr_flight + j + 1) = *(ptr_flight + j); 
      }
      *(ptr_flight + j + 1) = key;
   } 
}

void mergeSort(Flight* ptr_flight, int l, int r)
{
   int mid;
   float sum;
   if(l<r)
   {
      sum = (l+r)/2;
      mid = floor(sum);
      mergeSort(ptr_flight, l, mid);
      mergeSort(ptr_flight, mid + 1, r);
      merge(ptr_flight,l,mid,r);
   }
   else{}
}

void merge(Flight* ptr_flight, int l,int mid, int r)
{
   Flight temp[r-l+1];
   int i = l, j = mid + 1, k=0;
   
   while(i<=mid && j<=r)
   {
      if((*(ptr_flight + i)).time <= (*(ptr_flight + j)).time)
      {
         temp[k] = *(ptr_flight + i); 
         k++; i++;
      }
      else
      {
         temp[k] = *(ptr_flight + j);
         k++; j++;
      }
   }

   while(i<=mid)
   {
      temp[k] = (*(ptr_flight + i));
      k++; i++;
   }

   while(j<=r)
   {
      temp[k] = (*(ptr_flight + j));
      k++; j++;
   }

   for(i = l; i<=r; i++)
   {
      *(ptr_flight + i) = temp[i-l];
   }

}

void countSort(Flight* ptr_flight)
{
   printf("Using counting sort\n");
   //maximum of array 
   int max, i ,j,m; 
   max = -10000; //initialize max as a very large number 
   for (i = 0; i<MAX_SIZE; i++){
      if((*(ptr_flight + i)).time > max){
         max = (*(ptr_flight + i)).time; 
      }
   }
   //count array of size max + 1
   int count[max + 1]; 
   //result array 
   Flight temp[MAX_SIZE];
   //initialize count array to 0
   for(i = 0; i<=max; i++)
   {
      count[i] = 0;
   }
   //count number of times i appears in A
   for(j = 0; j<MAX_SIZE; j++)
   {
      count[(*(ptr_flight + j)).time]++;
   } 
   //cumulative sum
   for(i = 1; i<=max; i++)
   {
      count[i] = count[i] + count[i-1];
   }
   for(j = MAX_SIZE-1; j>=0; j--)
   {
      m = count[(*(ptr_flight + j)).time]; 
      temp[m-1] = *(ptr_flight + j); 
      count[(*(ptr_flight + j)).time]--;
   }
   //copy temp to original array
   for(i = 0; i<MAX_SIZE; i++)
   {
      *(ptr_flight + i) = temp[i];
   }  
}


void result(Flight* ptr_flight)
{
   int sum[MAX_SIZE];
   int i;
   sum[0] = ptr_flight -> mode; 
   for (i=1; i<MAX_SIZE; i++){
      sum[i] = sum[i-1] + (*(ptr_flight + i)).mode;
   }
   //max of array
   int max; 
   max = -10000; //initialize max as a very large number 
   for (i = 0; i<MAX_SIZE; i++){
      if(sum[i]>max){
         max = sum[i]; 
      }
   }
   //min of array
   int min; 
   min = 10000; //initialize max as a very large number 
   for (i = 0; i<MAX_SIZE; i++){
      if(sum[i]<min){
         min = sum[i]; 
      }
   }   
   //print min, max and number of gates 
   printf("The total gates required are %d and the total aircrafts required to be parked are %d \n", max-min, -min);
}
