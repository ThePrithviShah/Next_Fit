#include<stdio.h>
#include<conio.h>
#include<string.h>

//Password is "nextfit"

void welcome()
{
	printf("\n\t\t\t**************************");
	printf("\n\t\t\tNEXT FIT MEMORY ALLOCATION");
	printf("\n\t\t\t**************************");
}
void acceptnm(int a[],int n)
{
	int i;

	FILE *fptr;
	fptr=fopen("NEXTFIT.TXT","w");

	for(i=0;i<n;i++)
		scanf("%d",&a[i]);
	for(i=0;i<n;i++)
		fprintf(fptr,"MEMORY HOLE %d. %d \n",i+1,a[i]);

	fclose(fptr);
}
void acceptnp(int a[],int n)
{
	int i;

	FILE *fptr;
	fptr=fopen("NEXTFIT.TXT","a");
	fseek(fptr,0,SEEK_END);

	for(i=0;i<n;i++)
		scanf("%d",&a[i]);
	for(i=0;i<n;i++)
		fprintf(fptr,"PROCESS %d. %d \n ",i+1,a[i]);

	fclose(fptr);
}

void bdisplay(int a[],int n)
{
	int i;

	printf("\n\n");
	for(i=0;i<n;i++)
		printf("\t%d",a[i]);
}
void bdisplaynm(int a[],int n)
{
	int i;

	FILE *fptr;
	fptr=fopen("NEXTFIT.TXT","a");
	fseek(fptr,0,SEEK_END);

	printf("\n\n");
	for(i=0;i<n;i++)
		printf("\t%d",a[i]);
	for(i=0;i<n;i++)
		fprintf(fptr,"AFTER ALLOCATING PROCESS, MEMORY HOLES: %d.  %d \n",i+1,a[i]);

	fclose(fptr);
}
void init(int arr[], int size, int var)
{
	int i;

	for(i = 0;i < size;i++)
	   arr[i] = var;
}
void next_fit(int psize[],int np,int msize[],int nm)
{
	int i,j,itot=0,etot=0,temp[30],flag[30],temp1[30],p_start;

	FILE *fptr;
	fptr=fopen("NEXTFIT.TXT","a");
	fseek(fptr,0,SEEK_END);

	clrscr();
	welcome();

	init(flag, 30, 0);
	for(i=0;i<nm;i++)
		temp[i]=msize[i];       //copy all the elements to temp
	p_start = 0;		//setting pointer location to 0
	i =j= 0;			//i for procssor and j for memory
	while(i != np)
	{
		if( temp[j]==msize[j] && psize[i] <= temp[j])
		{
			itot+=temp[j]-psize[i];	  //to calculate internal frag
			temp[j]-=psize[i];	//to modify the value of memory size
			p_start = j;		//put pointer to that memory position
			i++;		//increase the value of i i.e., next processor
		}
		if(j == nm)		  //to check that it has not come to end
			j= 0;	//if j as reached at end then according to nextfit pointer should go up
		else
			j++;
		if(p_start == j)	  //since if memory is occupied then it should not be checked
		{
			flag[i] = 1;
			i++;
		}
	}
	for(j=0;j<nm;j++)
	{
		if(msize[j] == temp[j])
		{
			etot+=msize[j];
		}

	}

	printf("\n\nPROCESSES:");
	bdisplay(psize,np);
	printf("\n\nBEFORE ALLOCATION OF MEMORY HOLES;");
	bdisplay(msize,nm);
	printf("\n\nAFTER ALLOCATION OF MEMORY HOLES;");
	bdisplaynm(temp,nm);
	printf("\n\nTOTAL SUM OF INTERNAL FRAGMENTATION: %d",itot);
	printf("\n\nTOTAL SUM OF EXTERNAL FRAGMENTATION: %d",etot);
	fprintf(fptr,"\nTOTAL SUM OF INTERNAL FRAGMENTATION: %d",itot);
	fprintf(fptr,"\nTOTAL SUM OF EXTERNAL FRAGMENTATION: %d",etot);
	fclose(fptr);
}
int security()
{
	char pwd[40],ch;
	int i;
	for( i=0;i<40;i++)
	pwd[i]='\0';

	clrscr();
	printf("\n\t\t\tROUTINE SECURITY CHECK-UP");
	printf("\n\t\t\t*************************");
	printf("\n\n\t\t\tEnter the security code: ");
	i=0;
	ch=getch();
	while(ch != 13) //character 13 is enter key
	{

		pwd[i]= ch;
		printf("*");
		i++;
		ch  = getch();

	}
	if(strcmp(pwd,"nextfit")==0)
		return 1;
	else
		return 0;
}

void main()
{

	FILE *fptr;
	int np,nm,psize[30],msize[30];
	char name[10],c,ans;
	int ch,opt,count=1;
	clrscr();
	once:
	ch=security();
	if(ch==0)
	  { printf("\n\t\t\t*****Access Denied!! *****");
	  getch();
	  goto once;

	  }
	  else
	  printf("\n\n\n\t\t\tENJOY THE PROGRAM!!");
	  getch();

	answer:
	clrscr();

	welcome();

	printf("\n\nENTER NUMBER OF MEMORY HOLES:\n");
	scanf("%d",&nm);

	printf("\nENTER THE NUMBER OF PROCESSORS:\n");
	scanf("%d",&np);
	fptr=fopen("NEXTFIT.TXT","a");
	fseek(fptr,0,SEEK_END);
	fprintf(fptr,"\n NUMBER OF MEMORY HOLES= %d",nm);
	fprintf(fptr,"\n NUMBER OF PROCESSORS= %d",np);
	fclose(fptr);
	printf("\nENTER SIZES OF MEMORY HOLES:\n");
	acceptnm(msize,nm);
	printf("\nENTER SIZE OF PROCESSES:\n");
	acceptnp(psize,np);

	next_fit(psize,np,msize,nm);
	getch();
	clrscr();
	welcome();
	check:
	printf("\n\n\n\tWOULD YOU LIKE TO ACCESS IT AGAIN?(Y/N)");
	scanf("%s",&ans);
	if(ans=='Y'||ans=='y')
		goto answer;
	else if(ans=='N' || ans=='n')
		goto end;
	else
		goto check;
	end:
	getch();
}
