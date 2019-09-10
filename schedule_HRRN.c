/* Scheduling dengan Highest Response Ratio Next*/
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
	float resp_ratio; //store current response ratio
}schedule;

int main ()
{
	int i,j;
	schedule proc[30];
	int tot_time=0, time;
	int target;
	int quant,quant_count;
	int n_data;
	float m, weighted_m;
	
	/* read how many data to be processed */
	printf("input n data : ");
	scanf("%d",&n_data);
	printf("\n");
	
	/* input the data */
	printf("input data arrival and service: ");
	for (i=0;i<n_data;i++)
	{
		scanf("%d %d",&proc[i].arrival,&proc[i].service);
		tot_time += proc[i].service;  //get total time required
		proc[i].remain =  proc[i].service;
	}
	printf ("%d\n",tot_time);
	printf("\n");
	printf ("-----------------------------------\n");
	
	/* Start HRRN scheduling process */ 
	target = 0;
	time =0;
	
	/* do process based on how many data */
	/* choosen because HRRN is non preemptive */
	for (i=0 ; i < n_data; i++) 
	{	
		/* print current process processed */
		printf("%d\n", target);
		
		/* set remaining time required of the process to zero */
		proc[target].remain = 0;
		
		/* time accumulated by current process */
		time += proc[target].service;
		
		/*store finish time and calculate weighted turnaround */
		proc[target].finish = time; 
		proc[target].weighted = (float)(proc[target].finish-proc[target].arrival)/(float)proc[target].service;
		
		/* calculate current response ratio of all process */
		for (j=0; j< n_data; j++)
		{
			proc[j].resp_ratio = (float)((time - proc[j].arrival) + proc[j].service)/(float)proc[j].service;
			if ((proc[j].remain >0) && (proc[j].resp_ratio >0))
				printf("%d: %f, ",j, proc[j].resp_ratio );
		}
		printf("\n");
		
		/* choose arbitrary process which remain is not zero */
		for (j=0; j< n_data; j++)
		{
			if (proc[j].remain > 0)
			{	
				target = j;
				break;
			}
		}
		
		/* search & select process with highest response ratio within range of current time */
		for (j=0; j< n_data; j++)
		{
			if ((proc[j].arrival <= time) && (proc[j].remain!=0) ) 
			{	
				if (proc[j].resp_ratio > proc[target].resp_ratio)
					target = j;
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

