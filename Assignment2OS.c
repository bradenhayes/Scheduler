//INCLUDED LIBRARIES
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Assignment2.h"

//INITILIZING ALL CODE
struct PCB *processes, temp;
int numberOfProcesses=0;
int totalTurnaroundTime=0;
int totalWaitingTime=0;
int tick=0;
int mem1 , mem2, mem3 , mem4  ;
int memtemp1 , memtemp2 , memtemp3, memtemp4;
void whichScheduler();
void fcfs();
void roundRobin();
int runKernel();
void priority();
void calculations();
void parseInput();
void list_PCB_init();
int metrics(int totalTurnaroundTime,int totalWaitingTime);
void memoryAllocation();
void memoryMetrics();
//main function 
int main(int argc, char* argv[]){

FILE* file = fopen("input.txt", "r");//opens the input file that will also be used in our parse file function
char line[MEMORY];
while(fgets(line,sizeof(line),file)){
    numberOfProcesses++; //while the number of lines in the file add, eg, say there are 5 files in the file, it will give us five proceeses
}
processes = (PCB *)malloc(numberOfProcesses);
    fclose(file); // closes file

 parseInput(); //parse file to get the nessesary info for the schedulars


whichScheduler(); //runs which schedular which will prompt the user, and ask which scheaduler the user would like to run
memoryAllocation();
}

void memoryAllocation(){
//to simulate space of 1 Gb of user space available, divided in four portions
int i=0;
	while(true){
		if(i==0){ //for the first case it is divided in to diffrent portions then the second
			 mem1 = 500;
			 mem2 = 250;
			 mem3 = 150;
		     mem4 = 100;
			 //creating temp variables
             memtemp1 = mem1;
             memtemp2 = mem2;
             memtemp3 = mem3;
             memtemp4 = mem4;
			
			 //running whichscheadular now that memory has been allocated
			 whichScheduler();
			 i++;
		}
		if(i==1){
			mem1= 300;
			mem2 = 300;
			mem3 =350;
			mem4=50;
            memtemp1 = mem1;
            memtemp2 = mem2;
            memtemp3 = mem3;
            memtemp4 = mem4;
			whichScheduler();
			return;
		}

    }

}

void whichScheduler(){//to determine which scheaduler to run

    char input[10];
    int totalTurnaroundTime;
    while(true){

        printf("\n Type the scheduler that you wish to use: FCFS, Priority or RoundRobin: "); //prints to the console to ask the user which scheaduler they would like to run
        scanf("%s", &input); //user puts an input and by using the scan we compare and then run which ever the following classes
        if(strcmp(input,"FCFS")==0 ){ //compares the string to see if they match if not it will print again
            fcfs();//runs fcfs
        }
        else if(strcmp(input,"Priority")==0){//compares strings
            priority();
        }
        else if(strcmp(input,"RoundRobin")==0){//compares strings
            roundRobin();
        }
        else{ //if non of the following strings repeat
          printf("Enter one of the following: FCFS, Priority or RoundRobin ");
        }


    }
}

void parseInput(){ //parses the input file to grab the data needed to be used in the schedulers

    const char delimeter[2]= " "; //by making the string two spaces, which are inbetween the numbers of our input file it knows to move one
    char *token; //creating a token
    char *data; //becomes equal to the 
    int counter = 0;
    int i =0;
    char line[MEMORY];

    FILE *file = fopen("input.txt","r");//reading the input file
    while(fgets(line,sizeof(line),file)){//while theres data in the file
        data = line;
        token = strtok(data,delimeter);



    while( token != NULL )//while the token is 
		{
			int x = atoi(token);//converts token in to an integer x 

		    if(counter == 0)
		    {
				processes[i].pid = x; 
			}
			else if(counter == 1)
			{
				processes[i].arrivalTime= x;
			}
			else if(counter == 2)
			{
				processes[i].totalCPUTime = x;
			}
			else if(counter == 3)
			{
				processes[i].ioFrequency = x;
			}
			else if(counter ==4){
    			processes[i].ioDuration= x;
    		}
    		else if(counter ==5){
        		processes[i].priority = x;
    		}
			token = strtok(NULL, delimeter); 
			counter++;//up the counter to go back to grab the data on the same line
		}
		processes[i].state=READY;//makes the states ready as they have not been run yet
		counter = 0;//counter back to 0
		i++;//run thorugh the next line of the file
    }
    fclose(file); //closes file
}

void fcfs(){

//Sorting array so that lowest arrival time is first and last arrival time is last
for(int i=0;i<numberOfProcesses;++i){
    for(int j=i+1;j<numberOfProcesses;++j){
        if (processes[i].arrivalTime<processes[j].arrivalTime){
            temp=processes[i];
            processes[i]=processes[j+1];
            processes[j+1]=temp;


        }
    }

}

runKernel();//runs kernel
}
void priority(){
//sorting array by priority eg. if there is 1 its the top priority, if its 5 which is that last its the least prioritized
  for(int i=0;i<numberOfProcesses;++i){

      for(int j=i+1;j<numberOfProcesses;++j){
          if (processes[i].priority<processes[j].priority){
              temp=processes[i];
              processes[i]=processes[j];
              processes[j]=temp;

			}

      }
  }

  runKernel();//runs kernel  
}
void roundRobin(){
int i,time,flag=0,time_quantum=100; //time quantum 100 because it should only run for 100ms
for(time=0,i=0;numberOfProcesses!=0;) 
  { 
    if(processes[i].totalCPUTime<=time_quantum && processes[i].totalCPUTime>0) //if total cputime less then 100ms(HARD LIMIT) it will stop
    { 
      time+=processes[i].totalCPUTime; //adding to time to then be used as another parameter
      processes[i].totalCPUTime=0; //back to zero cause its run
      flag=1; //by using flags we difirentiate statements
    } 
    else if(processes[i].totalCPUTime>0) 
    { 
      processes[i].totalCPUTime-=time_quantum; //minus cpu time to the now time remaining
      time+=time_quantum; 
    } 
    if(processes[i].totalCPUTime==0 && flag==1) 
    { 
      numberOfProcesses--;//if it meets the requirements we know that it has run so the number of processes go down 
      flag=0;//set flag back to 0 
    } 
    if(i==numberOfProcesses-1) {
      i=0; //this is to say that we have run out of processes
	}
    else if(processes[i+1].arrivalTime<=time) {
      i++; //if not keep running throught the processes
	}
    else {
      i=0;
	} 
		 runKernel();
  } 
} 

int runKernel(){
	int currentProcessTime=0; //initilizes currentProcessTime to 0
	int memoryPicked=0;

while(true){ //while True

    	int processTerminated = 0; //
    	for(int i=0;i<numberOfProcesses;i++){
       		if(processes[i].state == TERMINATED){
            	processTerminated++;//keeps track of the number of terminated processes
        	}
	if(processTerminated == numberOfProcesses){ //if the numbers are equal we know that the function is done running
        metrics(totalTurnaroundTime, totalWaitingTime); //pass to meterics to calculate the needed data
    	free(processes);//free the processes
   		return 0;
}
}

for(int i=0;i<numberOfProcesses;i++)
{

    if(processes[i].state==READY){ //when the state is ready

        if(processes[i].arrivalTime > tick){// if the arrival time is greater keep running cause it hasnt arrived yet
            tick++;


        }
if  (processes[i].memoryNeeded > (mem1 || mem2 ||mem3||mem4)){

            printf("%s","There is not enough memory for all processes to run");
            //fprintf(file,"%s", "There is not enough memory for all processes to run");
            return 0;
        }

		//calculating the total memory
         if(mem1>processes[i].memoryNeeded ){
                mem1 = mem1 - processes[i].memoryNeeded;

            }
            else if (mem2 > processes[i].memoryNeeded){
                mem2 = mem2- processes[i].memoryNeeded;


            }
            else if (mem3 > processes[i].memoryNeeded){
                mem3 = mem3- processes[i].memoryNeeded;

            }

            else if (mem4 > processes[i].memoryNeeded){
                mem4 = mem4 - processes[i].memoryNeeded;

            }
			tick=0;
			printf("\nMemory information for process:  %i", i);
			//  fprintf(file,"Memory information for process = %i", i);
            memoryMetrics();//runs the memory metrics to print the nessesary data
			//set tick back to zero
            processes[i].state=RUNNING;//change state to running
					if(processes[i].ioFrequency==tick){
						i++;
						for(int j=0;j<processes[i-1].ioDuration;j++){
							tick++;
						}
					}

        	 }//end of STATE IS READY
		

        if(processes[i].totalCPUTime< (processes[i].arrivalTime)){//while the arrival time is greater increase the tick
            tick++;
        }
		processes[i].state=TERMINATED;//state is now terminated
		tick=0;//tick back to zero

		//claculating the nessesary parameters to be passsed to metrics
		currentProcessTime += processes[i].totalCPUTime;
		totalTurnaroundTime +=(currentProcessTime - processes[i].arrivalTime);
		totalWaitingTime += processes[i].totalCPUTime;
}
}

}
int metrics(int totalTurnaroundTime,int totalWaitingTime){
//both totalTurnaroundTime and totalWaitingTime are arguments passed down by the runKernel class

	FILE *file = fopen("output.txt","w"); //opening output file to then write in it

	if(file==NULL){ //if there is no file throws an error
		printf("Error opening output.txt\n");
		return 0; //returns
	}
	//Initilizing variables to be used to calculate average turnaround, throughput and wait time
	float totalTime = 0;
	float throughput = 0;
	float averageTurnaround=0;
	float avgWaitingTime = 0;

    averageTurnaround = totalTurnaroundTime / numberOfProcesses; //calculates the average turnaround time by total divided by the number of processes
	printf("\nAverage Turnaround = %f", averageTurnaround); //prints it for the user 
	fprintf(file, "\nAverage Turnaround = %f", averageTurnaround);//also prints it to the file

	for(int i = 0; i < numberOfProcesses; i++) //calculates the totalTime by adding all the total Cpu times
	{
		totalTime += processes[i].totalCPUTime;
	}
	throughput = numberOfProcesses/totalTime;//calculates the average throughput time by total divided by the number of processes
	printf("\nThroughput = %f", throughput);//prints it for the user 
    fprintf(file,"\nAverage throughput = %f", throughput);//also prints it to the file

	avgWaitingTime = totalWaitingTime/numberOfProcesses;//calculates the average waitTime time by total divided by the number of proce
	printf("\nAverage Waiting Time = %f", avgWaitingTime);//prints it for the user 
    fprintf(file,"\nAverage avgWaitingTime = %f", avgWaitingTime);//also prints it to the file
	fclose(file);//closes the file
}
void memoryMetrics(){

//Initilizing variables to be used to calculate totalMemoryUsed, totalMemoryAvailable and totalUsableMemory
     int totalMemoryUsed= 0 ;
     int totalMemoryAvailable = 0;
     int totalUsableMemory = 0;

    FILE *file = fopen("output.txt","w");//opening file to write too

	if(file==NULL){
		printf("Error opening output.txt\n");//throw error if you cant open
		return;
	}


    totalMemoryUsed = 1000 - (mem1 +mem2 +mem3 +mem4); //Calculating the total memory used everytime a new process starts
    printf("\nTotal Memory available = %i", totalMemoryUsed);
    //fprintf(file,"\nTotal memory used so far: = %i", totalMemoryUsed);


	//The following sequence of if and else statements will tell what partions have been used, what partions are free and it will calculate the total usable memory everytime a new process starts
    if(mem1 != memtemp1 ){ 
        printf("\n%s", "Memory partion 1 has been used ");
        fprintf(file,"%s","Memory partition 1 has been used");   
    }
    else{ 
        printf("\n%s", "Memory partion 1 is free"); 
        //fprintf(file,"%s","Memory partition 1 is free \n");
        totalUsableMemory += mem1;
    }
    if(mem2!= memtemp2){
        printf("\n%s", "Memory partion 2 has been used");
        fprintf(file,"%s","Memory partition 2 has been used \n");
    }
    else{
        printf("\n%s", "Memory partion 2 is free");
        //fprintf(file,"%s","Memory partition 2 is free \n");
    	totalUsableMemory+= mem2;
    }
        

    if(mem3!= memtemp3){
        printf("\n%s", "Memory partion 3 has been used");
        fprintf(file,"%s","Memory partition 3 has been used \n");
    }
    else{

     printf("\n%s", "Memory partion 3 is free");
     //fprintf(file,"%s","Memory partition 3 is free \n");
     totalUsableMemory  += mem3;
    }

    if(mem4!= memtemp4){
        printf("\n%s", "Memory partion 4 has been used");
        fprintf(file,"%s","Memory partition 4 has been used \n");
    }
    else
    {
        printf("%s", "Memory partion 4 is free");
    // fprintf(file,"%s","Memory partition 4 is free \n");
      totalUsableMemory += mem4;
    }
    
    totalMemoryAvailable = mem1 +mem2 +mem3 + mem4 ;//calculate total memory used and print
    printf("\nTotal Memory used= %i", totalMemoryAvailable);//prints
	printf("\nTotal Usable memory available = %i", totalUsableMemory);//prints 
    //  fprintf(file,"\nTotal Usable memory available: = %i", totalUsableMemory);//prints to output file
    //  fprintf(file,"\nTotal memory used so far: = %i", totalMemoryUsed);//prints to output file
    fclose(file);//close file so it can be accessesd by the other metrics

}
