/* Scheduling dengan round robin versi slide kuliah*/
/* Ngakan Putu Ariastu, 11 Desember 2017 */

#include <stdio.h>
#include <stdlib.h>

/* data type to store schedule data */
typedef struct schedule {
	int arrival;		//store arrival time
	int service;		//store service time required
	int finish;			//store process finish time
	int remain;			//store remaining service time required
	float weighted;		//store weighted turnaround
}schedule;



int main ()
{
	int i,j;
	schedule proc[30];
	int tot_time=0;
	int target;
	int quant,quant_count;
	int n_data,found;
	float m,weighted_m;
	
	
	/* read many of data process */
	printf("input n data : ");
	scanf("%d",&n_data);
	printf("\n");
	
	/* read process arrival and service time */
	printf("input data arrival and service: ");
	for (i=0;i<n_data;i++)
	{
		scanf("%d %d",&proc[i].arrival,&proc[i].service);
		tot_time += proc[i].service; 
		proc[i].remain =  proc[i].service;
	}
	printf ("%d\n",tot_time);
	
	/* read time quantum used */
	printf("input time quantum : ");
	scanf("%d",&quant);
	printf("\n");
	printf ("-----------------------------------\n");
	
	
	/* start Round Robin Process */
	
	target = 0;
	quant_count =0 ;
	
	/* increment process per time until total time */
	/* choosen becaus RR preemptive process */
	for (i=0;i<tot_time;i++)
	{	
		/* if allocated time of process has runout */ 
		if ((quant_count == quant) && (i!=tot_time-1))
		{	
			/* choose next target alphabetically */
			target++;
			found = 0;
			/* check if current chosen process has arrive and still not finished */
			while (found == 0)
			{	
				if (target == n_data)
					target = 0;
		
				if ((proc[target].arrival <= i) && (proc[target].remain > 0))
					found = 1;
				else 
					target ++;
				
			}
			quant_count =0 ; //reset time quantum count
		}
		
		/* print current process */
		printf("%d\n", target);
		
		/* reduce remaining time required by current process */
		proc[target].remain--;
		quant_count ++; //increase time quantu count
		
		/* if process finished before time quantum runout*/
		if (proc[target].remain==0) 
		{
			/*store finish time and calculate weighted turnaround */	
			proc[target].finish = i+1;
			proc[target].weighted = (float)(proc[target].finish-proc[target].arrival)/(float)proc[target].service;
			
			/*for last process */
			if (i != tot_time-1)
			{	
				/* choose next target alphabetically */
				target++;
				found = 0;
				/* check if current chosen process has arrive and still not finished */		
				while (found == 0)
				{	
					if (target == n_data)
						target = 0;
				
					if ((proc[target].arrival <= i) && (proc[target].remain > 0))
						found = 1;
					else 
						target ++;
				}
			}
			quant_count = 0 ;
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

