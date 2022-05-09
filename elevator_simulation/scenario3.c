//SCENARIO 2

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CAPACITY 18
#define MAXFLOORS 20
#define stopTime 15
#define moveTime 3

//Statistic variables 
float average_total_time;
int minimum_total_time;
int maximum_total_time;
float average_tpp; 

//struct for elevator run stats; total time; average time per person

typedef struct elevator {
    int total_time;
    float average_time;} ElevatorRun;

// structure to store data for a single elevator: person number, Exit floor, time and pointer to next item
typedef struct people {
	int person_no;
	int ExitFloor;
    int elevatorNumber;
	int travelTime;
    int waitTime;
    int waitFloor;} People;

//declare function
void generate_people(People* passenger,People* passenger_e1, People* passenger_e2,int total_count, int* total_count_e1, int* total_count_e2, int maxFloor1);
void elevator_run(int n, int maxFloor1);
void sortarray(People* passenger, int* total_count);
void swap(People* firstVal, People *secondVal);
void caltime(People* passenger, int* total_count);
int generate_stats(ElevatorRun runs);

//int time();
//int statistics();

int main(){
    for (int p = 7; p<17; p++)
    {
        int maxFloor1 = p;
        elevator_run(1000, maxFloor1);
        printf("%d\n", maxFloor1);
        printf("The average total time is %0.2f.\n",average_total_time);
        printf("The maximum total time is %d seconds.\n",maximum_total_time);
        printf("The minimumm total time is %d seconds.\n",minimum_total_time);
        printf("The average time per passenger is %0.2f seconds.\n",average_tpp);
    }
}

void elevator_run(int n, int maxFloor1)
{
    ElevatorRun runs[n]; //create an array of 1000 structs of typr elevator run
    runs->total_time = 0; //initialize the 1st entry of the array to 0
    maximum_total_time = runs->total_time; //initialize max as the 1st entry of the array
    minimum_total_time = runs->total_time; //initialize max as the 1st entry of the array
    average_total_time = 0;
    int sum_total_time = 0;
    float sum_tpp = 0;
    int total_count = 0;
    int total_count_e1 = 0;
    int total_count_e2 = 0; 

    for (int t = 0; t<n; t++)
    {
        int total_count = (rand() % CAPACITY)+1; //generate no. of passengers in elevator
        int total_count_e1 = 0;
        int total_count_e2 = 0;
        People passenger[total_count];
        People passenger_e1[total_count]; //declare an array of type struct people for elevator 1
        People passenger_e2[total_count]; //declare an array of type struct people for elevator 2

        generate_people(passenger, passenger_e1, passenger_e2, total_count, &total_count_e1, &total_count_e2, maxFloor1); //generate passenger list containing exit floor, travel time and wait time

        int a = 0;
        int b = 0; 

        total_count_e2 = total_count - total_count_e1;

        if((total_count_e1 >0) && (total_count_e2 >0))
        {
            a = passenger_e1[total_count_e1-1].waitTime + passenger_e1[total_count_e1 -1].travelTime; //total time for elevator 1 
            b = passenger_e2[total_count_e2-1].waitTime + passenger_e2[total_count_e2 -1].travelTime; //total time for elevator 2
            (runs+t)->total_time = (a*(a>=b)) + (b*(b>a)); 
        }
        if(total_count_e1>0)
        {
            (runs+t)->total_time = passenger_e1[total_count_e1-1].waitTime + passenger_e1[total_count_e1 -1].travelTime;
        }
        
        if(total_count_e2>0)
        {
            (runs+t)->total_time = passenger_e2[total_count_e2-1].waitTime + passenger_e2[total_count_e2 -1].travelTime;
        }

        //calculate average run time per passenger for each elevator run
        int sum = 0;
        int i = 0;
        for (i = 0;i<total_count_e1; i++)
        { 
            sum = sum + passenger_e1[i].waitTime + passenger_e1[i].travelTime;
        } 
        for (i = 0;i<total_count_e2; i++)
        { 
            sum = sum + passenger_e2[i].waitTime + passenger_e2[i].travelTime;
        } 
        (runs+t)->average_time = sum/total_count;

        //elevator stats
        //get maximum run time
        if(maximum_total_time<(runs+t)->total_time){
            maximum_total_time = (runs+t)->total_time; 
        }
        //get minimum run time
        if(t==0){
            minimum_total_time = (runs+t)->total_time;
        }
        if(minimum_total_time>(runs+t)->total_time){
            minimum_total_time = (runs+t)->total_time;
        }

        //get sum of total elevator run times for 1000 runs
        sum_total_time = sum_total_time + ((runs + t)->total_time);

        //get sum of average passenger run times for 1000 runs
        sum_tpp = sum_tpp + ((runs + t)->average_time);
    }
    average_total_time = sum_total_time/n;
    average_tpp = sum_tpp/n;
}

void generate_people(People* passenger,People* passenger_e1, People* passenger_e2, int total_count,int* total_count_e1, int* total_count_e2, int maxFloor1)
{   
    int i;
    //srand((unsigned)time(NULL));
    //People passenger[total_count];
    for(i = 0; i<total_count; i++)
    {
        (passenger+i)->person_no = i+1;
		(passenger+i)->ExitFloor = (rand() % MAXFLOORS) + 1;
        (passenger+i)->elevatorNumber = 1*((passenger+i)->ExitFloor <= maxFloor1) + 2*((passenger+i)->ExitFloor > maxFloor1);
        (passenger+i)->travelTime = moveTime* (passenger[i].ExitFloor);
		(passenger+i)->waitTime = 0;
        (passenger+i)->waitFloor =0;

    };

    //separate to 2 elevators
    for(i=0; i<total_count; i++)
    {
        if(passenger[i].elevatorNumber == 1)
        {
            *(passenger_e1 + *(total_count_e1)) = passenger[i];
            (*total_count_e1)++; 
        }
        else
        {
            *(passenger_e2 + *(total_count_e2)) = passenger[i];
            (*total_count_e2)++; 
        }
    }

    sortarray(passenger_e1, total_count_e1);
    sortarray(passenger_e2, total_count_e2);

    caltime(passenger_e1, total_count_e1);
    caltime(passenger_e2, total_count_e2);

    /*
    for(i=0;i<total_count;i++){
        printf("passenger %d is going to floor %d with total travel time %d seconds. \n", passenger[i].person_no, passenger[i].ExitFloor, passenger[i].travelTime + passenger[i].waitTime);
    };
    */
}

//sort array of structs 

void sortarray(People *passenger, int* total_count){
    for(int i=0; i<(*total_count); i++){
        for(int j=i+1; j<(*total_count);j++){
            if((passenger + i)->ExitFloor > (passenger + j)->ExitFloor){
                swap(passenger +i, passenger +j);
            }
        }
        
    }
}

void swap(People* firstVal, People *secondVal){
    People tempVal = *(firstVal);
	*(firstVal) = *(secondVal);
	*(secondVal) = tempVal;
}


// calculate time for each passenger 
void caltime(People *passenger, int *total_count){
    for (int p = 1; p<(*total_count); p++){
        if((passenger+p-1)->ExitFloor < (passenger+p)->ExitFloor)
        {
        (passenger +p)-> waitFloor = ((passenger + p - 1) -> waitFloor) +1;
        }
        else{
        (passenger +p)-> waitFloor = (passenger + p - 1) -> waitFloor;
        }
    (passenger + p)->waitTime = stopTime * ((passenger + p)->waitFloor); 
    }
}