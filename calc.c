#include <stdio.h>
#include "operators.h"

int main(){
	FILE *fp = NULL;
	int operand1, operand2;
	char operator = ' ';
	int line = 0;
	double (*calculator)(int, int);

	fp = fopen("read.txt","r");
	if(fp!=NULL){
		fscanf(fp, "%d", &line);
	
		for(int i=0; i<line; i++) {
			if((fscanf(fp, "%d %c %d",&operand1, &operator, &operand2)) == EOF) break;
			switch(operator) {
				case '+':
				calculator = add;
				break;
				case '-':
				calculator = minus;
				break;
				case '*':
				calculator = mul;
				break;
				case '/':
				calculator = div;
				break;
			}		
			
			printf("%d %c %d = %lf\n",
				 operand1, operator, operand2, calculator(operand1, operand2));
		}
	}
	return 0;
}
