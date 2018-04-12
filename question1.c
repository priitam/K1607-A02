#include<stdio.h>
#include<pthread.h>
int a[100];
void *average_calc();
void *maxi();
void *mini();
void *display();
int x,y;
float avg1;
int n;

int main()
{
printf("\nEnter the number of elements : ");
scanf("%d",&n);
printf("\n enter elements:\n ");
for (int i=0;i<n;i++)
{printf("\nEnter %d element :",i);
scanf("%d",&a[i]);
}
pthread_t th1, th2, th3, th4;
pthread_create(&th1,NULL,average_calc,NULL);
sleep(1);
pthread_create(&th2,NULL,maxi,NULL);
sleep(1);
pthread_create(&th3,NULL,mini,NULL);
sleep(1);
pthread_create(&th4,NULL,display,NULL);
pthread_join(th1,NULL);
pthread_join(th2,NULL);
pthread_join(th3,NULL);
pthread_join(th4,NULL);

}

void *average_calc()
{
float sum=0;
for (int i=0;i<n;i++)
{
	sum=sum+a[i];
}
avg1=sum/n;
}

void *maxi()
{
x=a[0];
for (int i=1;i<n;i++)
{
if(a[i]>x)
x=a[i];
}
}
void *mini()
{
y=a[0];
for(int i=1;i<n;i++)
{
if(a[i]<y)
y=a[i];
}
}
void *display()
{
printf("\n The numbers are :  ");
for (int i=0;i<n;i++)
printf(" %d ",a[i]);
printf("\n The average of numbers : %0.2f",avg1);
printf("\n The maximum number is  : %d",x);
printf("\n The minimum number is  : %d",y);
printf("\n");
}
