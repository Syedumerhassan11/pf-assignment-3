#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int validateEmail(char* email){
	int i=strlen(email),j=0,z=0;
	for(int k=0;k<i;k++){
		if(email[k]=='@'){
			j++;
		}
	}
	for(int k=0;k<i;k++){
		if(email[k]=='.'){
			if(j>0){
				z++;
			}
		}
	}
	if(j!=1){
		return 0;
	}else if(z==0){
		return 0;
	}
	return 1;
}

int main(void){
	int size=50;
	char *email;
	email=(char *)malloc(size * sizeof(char));
	if(email==NULL){
		printf("\n Memory allocation failed ");
		return 0;
	}
	printf("\n Enter Email Address : ");
	fgets(email,size,stdin);
	email[strcspn(email,"\n")]='\0';
	int i=validateEmail(email);
	if(i==1){
		printf("\n Valid email");
	}else{
		printf("\n Invalid Email");
	}
	free(email);
}
