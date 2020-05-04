#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
typedef struct node //This is the nide which contains name of audio file and its adress is stored in the array
{
    char str[50];
    int priority;
}Node;
int n;
//The array is  storing the node address hence its of type Node.
//For know(current purpose) we are taking twenty songs as maximum limit.
//Minimum can be anything based on users wish.

//Function to insert songs based on internal priority
void insert1(Node *a,FILE *fp,int j);

//Function to insert the songs into the array based on priority given
void insert2(Node *a,FILE *fp);

//Function is used to check whether priority is repeated or not
int check_priority(Node *a,int p);

//Heapify Function to convert it into max heap based on higest priority given to lowest value.
void heapify(Node *a, int m);

//Sort function to implement an proper order playlist of songs
//which uses the maximum value at top and then places it at the end
void sort(Node *a , int n);

//To delete the first song in the heap
void delete(Node *a);

//Function to Display the priortised playlist on screen with its priority
void display(Node *a);

//Function to play the music based on playlist implementation.
void play_music(Node *a);

//Function to Destroy the heap
void destroy(Node *a);

//main function inside which the whole thing is instantiated
int main()
{
    int i,j,p;char ch;
    while(1)
    {
        FILE *fp=fopen("songs.csv","r");
        if(fp==NULL)
        {
            printf("did not open");
            exit(0);
        }
        n=5;
        Node array[5];
        for(int i=0; i<5; i++)
            array[i].priority=0;
        printf("Which context do you prefer for the priority playlist\n");
        printf("\n'1.' To use the inbuilt priorities.\n'2.' To Enter your priorities.\n");
        printf("Enter your choice:");
        scanf("%d",&i);
        if(i==1)
        {
            printf("\n1.Genre\n2.Mood\n3.Occassion\n4.Interest\n");
            printf("Enter the type of priority:");
            scanf("%d",&j);
            if(j==1 || j==2 || j==3 || j==4)
                insert1(array,fp,j);
            else
            {
                printf("Invalid Input.\n");
                break;
            }
        }
        else if(i==2)
            insert2(array,fp);
        else
        {
            printf("Invalid Input.\n");
            break;
        }
        sort(array,n);
        int c=0;
        while(!c)
        {
            printf("\na.Display the playlist\nb.Delete a song from the Playlist\nc.Play_Music\nd.Exit the program\n");
            printf("Enter the choice:");
            fflush(stdin);
            ch=getchar();
            switch(ch)
            {
                case 'a':display(array);
                     break;

                case 'b':delete(array);
                         break;

                case 'c':play_music(array);
                     break;

                case 'd':destroy(array);
                     exit(0);

                default:printf("Invalid Input\n");
                break; 
            }
        }
        printf("\nEnter the value of c:");
        scanf("%d",&c);
    }
    return 0;
} 

//Function to insert songs based on internal priority
void insert1(Node *a,FILE *fp,int j)
{
    char line[200];int i=0;int k=1;
    fgets(line,200,fp);
    while(fgets(line,200,fp))
    {
        strcpy(a[i].str,strtok(line,","));
        char *word=strtok(NULL,",");
        while(word && k!=j)
        {
            word=strtok(NULL,",");
            k++;
        }
        if(k==j)
        {    
            a[i].priority=atoi(word);
            i++;
            k=1;
        }
    }
    display(a);
}

//Function to insert the songs into the array based on priority given by user
void insert2(Node *a,FILE *fp)
{
    char line[200],*word;int i=0,k;
    fgets(line,200,fp);
    while(fgets(line,200,fp))
    {
        strcpy(a[i].str,strtok(line,","));
        printf("Enter the priority for the song %s:",a[i].str);
        scanf("%d",&k);
        if(!check_priority(a,k))
        {
            printf("Enter the alternate priority for the song %s:",a[i].str);
            scanf("%d",&k);
        }
        a[i].priority=k;
        i++;
    }
      display(a);
}

//Function is used to check whether priority is repeated or not
int check_priority(Node *a ,int p)
{
    for(int i=0; i<n; i++)
    {
        if(a[i].priority==p)
            return 0;
        if(a[i].priority==0)
            return 1;
    }
}

//Heapify Function to convert it into max heap based on higest priority given to lowest value.
void heapify(Node *a, int m)
{
    int i,j;
    Node key;
    for(int k=1;k<=m;k++)
    {
        i=k;
        j=(i-1)/2;
        key=a[i];
        while(i>0 && key.priority > a[j].priority)
        {
            a[i]=a[j];
            i=j;
            j=(i-1)/2;
        }
        a[i]=key;
    }
}

void heapify1(Node *a, int m)
{
    int i,j;
    Node key;
    for(int k=1;k<=m;k++)
    {
        i=k;
        j=(i-1)/2;
        key=a[i];
        while(i>0 && key.priority < a[j].priority)
        {
            a[i]=a[j];
            i=j;
            j=(i-1)/2;
        }
        a[i]=key;
    }
}

//Sort function to implement an proper order playlist of songs
//which uses the maximum value at top and then places it at the end
void sort(Node *a, int m)
{
   for(int i=0;i<m;i++)
   {
       heapify(a,m-i-1);
       Node temp=a[0];
       a[0]=a[m-i-1];
       a[m-i-1]=temp;
   }
}

//To delete first song int the heap
void delete(Node *a)
{
   Node key;
   key=a[0];
   a[0]=a[n-1];
   --n;
   heapify1(a,n-1);
   sort(a,n-1);
   printf("\nFirst song in the priority list is deleted.\n");
}

//Function to Display the priortised playlist on screen with its priority
void display(Node *a)
{
    int i;
    printf("\nThe playlist is:\n");
    
    for(i=0;i<n;i++)
       printf("%d. %s %d\n",i+1,a[i].str,a[i].priority);
    printf("\n");
  
}

//Function to play the music based on playlist implementation.
void play_music(Node *a)
{
    int i=0;int j;
    while(i<n)
    {
        char *s=a[i].str;
        char str[]="start D://DS_Material//DS_Project//";
        strcat(str,s);
        system(str);
        printf("Enter 0 to stop or 1 to continue:");
        scanf("%d",&j);
        if(j==0)
            break;
        i=(i+1)%n;
    }
}

//Function to Destroy the heap
void destroy(Node *a)
{
    free(a);
}
