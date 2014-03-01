#include <stdio.h>

int main(void)
{
	FILE *fp;
	int a,b;
	char temp;
	printf("Please input two numbers:");
	printf("\n");
	scanf("%d %d",&a,&b);
    temp = getchar();
    int c;
	c = a*b;
	printf("%d*%d=%d",a,b,c);
    //printf("\n");
	char getenter;
	while((getenter = getchar()) != '\n');
	printf("Please input file name:");
	printf("\n");
    char filename[50];
	gets(filename);
    char filepath[50];
	sprintf(filepath,"%s.txt",filename);
	fp = fopen(filepath,"wb");
	char context[50];
	sprintf(context,"%d*%d=%d",a,b,c);
	//context[sizeof(context)] = '\0';
	//fwrite(context,sizeof(context),1,fp);
	fputs(context,fp);
	fclose(fp);
	return 0;
}