/* Scheduling dengan round robin versi buku */
/* Ngakan Putu Ariastu, 12 November 2017 */

#include <stdio.h>
#include <stdlib.h>

/* data type to store schedule data */
typedef struct schedule {
	int arrival;		//store arrival time
	int service;		//store service time required
	int finish;			//store process finish time
	int remain;			//store remaining service time required
	int queued;			//queued status, 1 if already queued otherwise 0
	float weighted;		//store weighted turnaround
}schedule;

/* creat linklist data */
typedef struct node{
    int data;
    struct node* link;
} node;

/* create queue data structure */
typedef struct typeQueue{
     node* head;
     node* tail;
}typeQueue;

/* FUNCTION AND PROCEDURE DEFINE */
void enQueue (int data, typeQueue *queue);	//put data into the queue
int deQueue (typeQueue *queue);	//get front data from queue
void Print(typeQueue *queue); //Print queue member


int main ()
{
	int i,j;
	schedule proc[30];
	int tot_time=0;
	int target;
	int quant,quant_count;
	int n_data;
	float m,weighted_m;
	typeQueue A;
    A.head = NULL;//inisialisasi nilai awal
    A.tail = NULL;
	
	/* read many data to be processed */
	printf("input n data : ");
	scanf("%d",&n_data);
	printf("\n");
	
	/* read process arrival and service time */
	printf("input data arrival and service: ");
	for (i=0;i<n_data;i++)
	{
		scanf("%d %d",&proc[i].arrival,&proc[i].service);
		tot_time += proc[i].service; //get total time for process 
		proc[i].remain =  proc[i].service;
	}
	printf ("%d\n",tot_time);
	
	/* read time quantum used */
	printf("input time quantum : ");
	scanf("%d",&quant);
	printf("\n");
	printf ("-----------------------------------\n");
	
	
	/* start Round Robin Process */
	quant_count = quant;
	enQueue(0,&A);
	target = deQueue(&A);
	proc[0].queued = 1;
	
	/* increment process per time until total time */
	/* choosen because RR is preemptive */
	for (i=0;i<tot_time;i++)
	{	
		/* check data availability at current time */
		for (j=0; j< n_data; j++)
		{
			/* put data into the ready queue */
			if ((proc[j].arrival == i) && (proc[j].remain!=0) && (proc[j].queued != 1)) 
			{	
				enQueue(j,&A);
				proc[j].queued = 1;
			}
		}
		printf ("in queue1 :" );
		Print(&A);
		
		/* if max time allocated process has runout*/
		if ((quant_count == quant) && (i!=tot_time-1))
		{	
			/* put current process into queue */
			enQueue(target,&A);
			printf ("in queue2 :" );
			Print(&A);
			
			/* get next process from queue */
			target= deQueue(&A);
			quant_count =0 ; //reset quntum time count
		}
		
		printf ("in queue3 :" );
		Print(&A);
		/* print current process */
		printf("%d\n", target);
		
		/* reduce remaining time required by current process */
		proc[target].remain--;
		quant_count ++; //increase time quantum count 
		
		/* if current process already finished */
		if (proc[target].remain==0) 
		{
			/*store finish time and calculate weighted turnaround */	
			proc[target].finish = i+1;
			proc[target].weighted = (float)(proc[target].finish-proc[target].arrival)/(float)proc[target].service;
			
			/* get next process in the queue */
			if (i!=tot_time-1)
				target = deQueue(&A);
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

void enQueue (int data, typeQueue *queue){
    struct node* temp = (struct node*)malloc(sizeof(node)); //membuat suatu pemyimpanan nilai sementara
    temp->data = data; //mengisi nilai pada pointer yg dituju
    temp->link = NULL;
    if(queue->head == NULL && queue->tail == NULL){ //apabila queue masih kosong
		queue->head = temp;
		queue->tail = temp;
		return;
	}
	queue->tail->link = temp;   //apabila queue tidak kosong
	queue->tail = temp;

}

void cutQueue (int data, typeQueue *queue){
    struct node* temp = (struct node*)malloc(sizeof(node)); //membuat suatu pemyimpanan nilai sementara
    temp->data = data; //mengisi nilai pada pointer yg dituju
    temp->link = NULL;
	//potong antrian queue ke depan 
    if(queue->head == NULL && queue->tail == NULL){ //apabila queue masih kosong
		queue->head = temp;
		queue->tail = temp;
		return;
	}
	struct node* temp2 = (struct node*)malloc(sizeof(node));
	temp2 = queue->head;
	queue->head = temp;
	queue->head->link = temp2;
	

}

int deQueue (typeQueue *queue){
   struct node* temp = queue->head; //mengalokasikan pointer head pada temp
   int x = queue->head->data;
	if(queue->head == NULL) {//apabila queue kosong
		printf("Queue is Empty\n");
		return 9999;
	}
	if(queue->head == queue->tail) { //jika queue hanya satu elemen
		queue->head = NULL;
		queue->tail = NULL;
	}
	else {
		queue->head = queue->head->link; //menggeser nilai head
	}
	free(temp); //mengosongkan memory pointer head sebelumnya
	return x;
}

void Print(typeQueue *queue) {
	struct node* temp;
	if(queue->head == NULL) {//apabila queue kosong
		printf("Queue is Empty\n");
	}
	else 
	{	temp = queue->head;;
		while(temp != NULL) {
			printf("%d ",temp->data);
			temp = temp->link;
		}
		printf("\n");
	}
}