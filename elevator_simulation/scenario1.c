//SCENARIO 1

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
	int travelTime;
    int waitTime;
    int waitFloor;} People;

//declare function
void generate_people(People* passenger, int total_count);
void elevator_run(int n);
void sortarray(People* passenger, int total_count);
void swap(People* firstVal, People *secondVal);
void caltime(People* passenger, int total_count);
int generate_stats(ElevatorRun runs);

//int time();
//int statistics();

int main(){
    elevator_run(1000);
    printf("The average total time is %0.2f.\n",average_total_time);
    printf("The maximum total time is %d seconds.\n",maximum_total_time);
    printf("The minimumm total time is %d seconds.\n",minimum_total_time);
    printf("The average time per passenger is %0.2f seconds.\n",average_tpp);
}

void elevator_run(int n){
    ElevatorRun runs[n]; //create an array of 1000 structs of typr elevator run
    runs->total_time = 0; //initialize the 1st entry of the array to 0
    maximum_total_time = runs->total_time; //initialize max as the 1st entry of the array
    minimum_total_time = runs->total_time; //initialize max as the 1st entry of the array
    average_total_time = 0;
    int sum_total_time = 0;
    float sum_tpp = 0;

    for (int t = 0; t<n; t++){
        int total_count = (rand() % CAPACITY)+1; //generate no. of passengers in elevator
        People passenger[total_count]; //declare an array of type struct people
        generate_people(passenger, total_count); //generate passenger list containing exit floor, travel time and wait time
        (runs+t)->total_time = passenger[total_count-1].waitTime + passenger[total_count -1].travelTime; //calculate total run time for an elevator
        //calculate average run time per passenger for each elevator run
        int sum = 0;
        for (int i = 0;i<total_count; i++)
        { 
            sum = sum + passenger[i].waitTime + passenger[i].travelTime;
        } 
        ((runs+t)->average_time) = sum/total_count;

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
    //printf("%d/n",sum);
}

void generate_people(People* passenger,int total_count)
{   int i;
    //srand((unsigned)time(NULL));
    //People passenger[total_count];
    for(i = 0; i<total_count; i++){
        (passenger+i)->person_no = i+1;
		(passenger+i)->ExitFloor = (rand() % MAXFLOORS) + 1;
        (passenger+i)->travelTime = moveTime* (passenger[i].ExitFloor);
		(passenger+i)->waitTime = 0;
        (passenger+i)->waitFloor =0;
    };
    sortarray(passenger, total_count);
    caltime(passenger, total_count);
    /*
    for(i=0;i<total_count;i++){
        printf("passenger %d is going to floor %d with total travel time %d seconds. \n", passenger[i].person_no, passenger[i].ExitFloor, passenger[i].travelTime + passenger[i].waitTime);
    };
    */
}

//sort array of structs 

void sortarray(People *passenger, int total_count){
    for(int i=0; i<total_count; i++){
        for(int j=i+1; j<total_count;j++){
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
void caltime(People *passenger, int total_count){
    for (int k = 1; k<total_count; k++){
        if((passenger+k-1)->ExitFloor < (passenger+k)->ExitFloor)
        {
        (passenger +k)-> waitFloor = ((passenger + k - 1) -> waitFloor) +1;
        }
        else{
        (passenger +k)-> waitFloor = (passenger + k - 1) -> waitFloor;
        }
    (passenger + k)->waitTime = stopTime * ((passenger + k)->waitFloor); 
    }
}