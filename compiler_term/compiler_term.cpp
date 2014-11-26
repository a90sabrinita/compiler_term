//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h> 
#include <iostream>

void print(char *buf, int count){
	for(int i=0;i<count;i++)
	{
		printf("%c",buf[i]);
	}
}

int main(int argc, char *argv[])
{
	char buffer[100];
	int count=0, buffer_count=0;
	int par_count=0, left_count=0;

	
	if(argc>1)
	{
		
		for(count=1;count<argc;count++)
		{
			for(int i=0;i<strlen(argv[count]);i++)
			{
				buffer[buffer_count]=argv[count][i];
				buffer_count++;
				if(argv[count][i]=='(')
				{
					left_count++;
					par_count++;
				}
				else if(argv[count][i]==')')
				{
					par_count--;
				}
				if(par_count<0){
					printf("parenthesis error");
					system("pause");
					return 0;
				}
			}
		}
	}
	
	int done=0,par_temp=0, temp;
	int left_right=0; // 0-> left 1-> right
	
	int op=0; // 1 -> + 2 -> - 3 -> * 4 -> /
	while(done==0){
		int total=0,left_val=0,right_val=0;
		//printf("string: ");
		//print(buffer,buffer_count);
		//printf("\n");
		int replace_position;
		for(int i=0;i<buffer_count;i++){
			//printf("%c\n", buffer[i]);
			if(buffer[i]=='('){
				par_temp++;
				//printf("par temp: %d\n",par_temp);
				//printf("left count: %d\n",left_count);
				if(par_temp==left_count){
					temp=i+1;
					par_temp++;
				}
			}
		}
		replace_position=temp;
		//printf("temp : %d",temp);
		buffer[temp-1]=' ';
		int neg=0;
		while(buffer[temp]!=')'){
			
			if(buffer[temp]=='+'){
				//printf("plus");
				buffer[temp]=' ';
				op=1;
				left_right=1;
			}
			else if(buffer[temp]=='-' && op==0 && left_val==0){//first number is negative
				buffer[temp]=' ';
				neg=1;
			}
			else if(buffer[temp]=='-' && op==0 && left_val!=0){//it's an operator
				buffer[temp]=' ';
				op=2;
				left_right=1;
			}
			else if(buffer[temp]=='-' && op!=0 && left_val!=0){//second number is negative
				buffer[temp]=' ';
				neg=1;
			}
			else if(buffer[temp]=='*'){
				buffer[temp]=' ';
				op=3;
				left_right=1;
			}
			else if(buffer[temp]=='/'){
				buffer[temp]=' ';
				op=4;
				left_right=1;
			}
			if(buffer[temp]!=' ' && buffer[temp-1]!='+'&& buffer[temp-1]!='*'&& buffer[temp-1]!='/' ){
				char value[100]={0};
				int check=0,y=0;
				for(int j=0;j<buffer_count-temp;j++){//read number
					if(isdigit(buffer[temp+j])){
						//printf("number is %c\n",buffer[temp+j]);
						value[check]=buffer[temp+j];
						buffer[temp+j]=' ';
						y=j;
						check++;
					}
					else{
						break;
					}
				}
				temp+=y;
				//printf("value[0] : %c\n",value[0]);
				if(left_right==0){
					left_val=atoi(value);
					if(neg==1){
						left_val=left_val*(-1);
						neg=0;
					}
				}
				//printf("left value : %d\n",left_val);
				if(left_right==1){
					right_val=atoi(value);
					if(neg==1){
						right_val=right_val*(-1);
						neg=0;
					}
				}
				//printf("right value : %d\n",right_val);
			}
			if(op!=0 && left_val!=0 && right_val!=0){
				//printf("op : %d\n",op);
				switch(op){
				case 1: total=left_val+right_val;break;
				case 2:total=left_val-right_val;break;
				case 3:total=left_val*right_val;break;
				case 4:total=left_val/right_val;break;
				//default: 
				}
				op=0;
				char test[100];
				_snprintf_s(test,100,"%d",total);
				//printf("length : %d",strlen(test));
				
				for(int k=0;k<strlen(test);k++){
					buffer[replace_position+k]=test[k];
				}
				left_val=total;
				right_val=0;
			}
			temp++;
		}
		buffer[temp]=' ';
		left_right=0;
		
		
		par_temp=0;
		left_count--;
		if(left_count<=0){
			done=1;//all parentheses handled
			printf("RESULT   :   %d\n",total);
			//printf("yes");
		}
	}
	
	system("pause");
}