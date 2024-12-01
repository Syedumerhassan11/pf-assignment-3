#include<stdio.h>
#include<stdlib.h>

struct Employee{
	int *ratings;
	int totalScore;
};

int validation(int n){
	if(n<1 || n>10){
		printf("\n Invalid input try again : ");
		scanf("%d",&n);
		return validation(n);
	}
	return n;
}

void inputEmployees(struct Employee *e,int numberEmployees,int period){
	for(int i=0;i<numberEmployees;i++){
		e[i].ratings=(int *)malloc(period * sizeof(int));
	}
	for(int i=0;i<numberEmployees;i++){
		int total=0;
		for(int j=0;j<period;j++){
		    printf("\n Enter employee %d rating for period %d : ",i+1,j+1);
			scanf("%d",&e[i].ratings[j]);
			e[i].ratings[j]=validation(e[i].ratings[j]);
			total+=e[i].ratings[j];
		}
		e[i].totalScore=total;
	}
}

void displayPerformance(struct Employee *e,int numberEmployees,int period){
	for(int i=0;i<numberEmployees;i++){
		for(int j=0;j<period;j++){
		    printf("\n employee %d rating for period %d : %d",i+1,j+1,e[i].ratings[j]);	
		}
	}
}

int findHighestRatedPeriod(struct Employee *e,int numberEmployees,int period){
	float arr[period];
	for(int i=0;i<period;i++){
		int total=0;
		for(int j=0;j<numberEmployees;j++){
			total+=e[j].ratings[i];
		}
		arr[i]=total/numberEmployees;
	}
	float max=arr[0];
	int index=0;
	for(int i=0;i<period;i++){
		if(max<arr[i]){
			max=arr[i];
			index=i;
		}
	}
	return index;
}

int findEmployeeOfTheYear(struct Employee *e,int numberEmployees,int period){
	float arr[numberEmployees];
	for(int i=0;i<numberEmployees;i++){
		int total=0;
		for(int j=0;j<period;j++){
		    total+=e[i].ratings[j];
		}
		arr[i]=total/period;
	}
	float max=arr[0];
	int index=0;
	for(int i=0;i<numberEmployees;i++){
		if(max<arr[i]){
			max=arr[i];
			index=i;
		}
	}
	return index;
}
int findWorstRatedEmployee(struct Employee *e,int numberEmployees,int period){
	float arr[numberEmployees];
	for(int i=0;i<numberEmployees;i++){
		int total=0;
		for(int j=0;j<period;j++){
		    total+=e[i].ratings[j];
		}
		arr[i]=total/period;
	}
	float min=arr[0];
	int index=0;
	for(int i=1;i<numberEmployees;i++){
		if(min>arr[i]){
			min=arr[i];
			index=i;
		}
	}
	return index;
}

void freeMemory(struct Employee *e,int numberEmployees){
	for(int i=0;i<numberEmployees;i++){
		free(e[i].ratings);
	}
	free(e);
}
int main(void){
	int n,m;
	printf("Enter Number of employees : ");
	scanf("%d",&n);
	printf("Enter Number of periods : ");
	scanf("%d",&m);
	getchar();
	struct Employee *e;
	e=(struct Employee*)malloc(n * sizeof(struct Employee));
	if(e==NULL){
		printf("\n Memory Allocation Failed");
		return 0;
	}
	inputEmployees(e,n,m);
	displayPerformance(e,n,m);
	findWorstRatedEmployee(e,n,m);
	  int highestRatedPeriod = findHighestRatedPeriod(e, n, m);
    printf("\nThe highest-rated period is: %d\n", highestRatedPeriod + 1);

    // Find and display the employee of the year
    int employeeOfTheYear = findEmployeeOfTheYear(e, n, m);
    printf("\nEmployee of the Year is Employee %d\n", employeeOfTheYear + 1);

    // Find and display the worst-rated employee
    int worstRatedEmployee = findWorstRatedEmployee(e, n, m);
    printf("\nThe worst-rated employee is Employee %d\n", worstRatedEmployee + 1);

    // Free dynamically allocated memory
    freeMemory(e, n);

}
