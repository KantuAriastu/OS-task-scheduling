/* Scheduling dengan Shortest remaining time Next*/
/* Ngakan Putu Ariastu, 12 November 2017 */

#include <stdio.h>
#include <stdlib.h>


/* create datatype to store schedule */
typedef struct schedule {
	int arrival; //arrival time of process
	int service; //service time required (burst)
	int remain; //remaining time of service required
	int finish; //the process finish time 
	float weighted; //weighted turnaround
}schedule;



int main ()
{
	int i,j,k;
	schedule proc[30];
	int tot_time=0;
	int target;
	int quant,quant_count;
	int n_data;
	float m,weighted_m;
	
	/* read how many data to be processed */
	printf("input n data : ");
	scanf("%d",&n_data);
	printf("\n");
	
	/* input the data */
	printf("input data arrival and service: ");
	for (i=0;i<n_data;i++)
	{
		scanf("%d %d",&proc[i].arrival,&proc[i].service);
		tot_time += proc[i].service; //get total time
		proc[i].remain =  proc[i].service;
	}
	printf ("%d\n",tot_time);
	printf ("-----------------------------------\n");
	
	/* start SRT scheduling process */
	target = 0;
	
	/* increment process per time until total time */
	/* choosen becaus SRT is preemptive process */
	for (i=0;i<tot_time;i++)
	{	
		/* check if new data is arrive */
		for (j=0; j< n_data; j++)
		{
			if (proc[j].arrival == i)
			{	
				printf("data arrive interrupt -> ");
				for (k=0; k<=j; k++)
				{
					if (proc[k].remain>0)
						printf("%d: %d, ",k,proc[k].remain);
					
					/* change process to process with shortest remaining */ 
					if ((proc[k].remain>0) && (proc[k].remain < proc[target].remain))
						target = k;
					
					if (k==j)
						printf("\n");
				}
			}
			
		}
	
		/* print current process processed */
		printf("%d\n", target);
		
		/* reduce current ptocess remaining time */
		proc[target].remain--;
		
		/* if current process has finished*/
		if (proc[target].remain == 0)
		{	
			/*store finish time and calculate weighted turnaround */	
			proc[target].finish = i+1; 
			proc[target].weighted = (float)(proc[target].finish-proc[target].arrival)/(float)proc[target].service;
			
			/* choose arbitrary process which remain is not zero */
			for (j=0; j< n_data; j++)
			{
				if (proc[j].remain > 0)
				{	
					target = j;
					break;
				}
			}
			
			printf("data process done -> ");
			for (j=0; j<n_data; j++)
			{
				if ((proc[j].remain>0)&&(proc[j].arrival <= i))
						printf("%d: %d, ",j,proc[j].remain);
					
				/* change process to process with shortest remaining */ 	
				if ((proc[j].remain>0) && (proc[j].remain < proc[target].remain) && (proc[j].arrival <= i))
					target = j;
				
				if (j==n_data-1)
					printf("\n");
			}
		}
		
		
	}
	
	/* print all process arrival, service, finish,turnaround and weighted turnaround*/
	printf("arrival \t service \t finish \t turnaround \t weighted \n");
	for (i=0;i<n_data;i++)
	{
		printf("%d \t %d \t %d \t %d \t %f \n",proc[i].arrival,proc[i].service,proc[i].finish,proc[i].finish-proc[i].arrival,proc[i].weighted);
		m += (float)(proc[i].finish-proc[i].arrival);
		weighted_m += proc[i].weighted;
	}
	/* print average turnaround and average weighted turnaround */
	printf("\n average turnaround time : %f", m/(float)n_data);
	printf("\n average weighted turnaround time : %f\n", weighted_m/(float)n_data);
	
	return 0;
}
