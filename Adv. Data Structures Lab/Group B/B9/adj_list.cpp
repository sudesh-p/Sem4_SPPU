/*
Write a function to get the number of vertices in an undirected graph and its edges. You may assume that no edge is input twice. 
i. Use adjacency list representation of the graph and find runtime of the function 	 
*/
#include<iostream>
using namespace std;

class graph
{
   typedef struct node
	{
		int data;
		struct node *next;
	}Node;
   Node *New,*temp,*list[10];
 public:
   		graph();
        void create();
        void display();
	void addNode(int, int);
        
};
 
graph::graph()
{
 int i;
 for(i=0;i<10;i++)
  {
	  list[i]=new Node;
       list[i]->data=0; 
	  list[i]->next=NULL;
  }
}

void graph::addNode(int s, int d) {
  New=new Node;
  New->data=d;
  New->next=NULL;
  if(list[s]->next==NULL)
	{
	  list[s]->data=s;
	  list[s]->next=New;
     }
  else
   {
     temp=list[s]->next;
	while(temp->next!=NULL)
     {
       temp=temp->next;
     }
   temp->next=New;
   }
}

void graph::create()
{
 int s,d;
 char ans;
 do
 {
  cout<<"\n\tEnter the source vertices: ";
  cin>>s;
  cout<<"\n\tEnter the destination vertices: ";
  cin>>d;
 
  addNode(s,d);
  addNode(d,s);
	 
  cout<<"Do you want to continue: ";
  cin>>ans;
 }while(ans=='y');

}


void graph::display()
{
 int i;
 cout<<"\n\t**** Adj. List *****\n";
 for(i=1;list[i]->data!=0;i++)
   {
     cout<<"_";
	cout<<"\n|"<<list[i]->data<<"| -> ";
	for(temp=list[i]->next;temp!=NULL;temp=temp->next)
       {
		cout<<temp->data<<" ->";
	  }
	cout<<"NULL\n";
     
   }
  cout<<" _\n";
}
   
 main()
{
 int s;
 graph gr;
 int ch;
 char ans;
 do
  {
   cout<<"\n\t***** Adjacency List *****";
   cout<<"\n\t1.Create\n\t2. Display\n\t3. Exit\n\t.....Enter Your Choice: ";
   cin>>ch;
    switch(ch)
     {
      case 1:
             gr.create();
             break;
      case 2:
             gr.display();
             break;
      case 3: 
 	     break;
      default:
	     cout<<"Inavlid choice!";
    }
   cout<<"Do you want to continue: ";
   cin>>ans;      
  }while(ans=='y');
}


/* op


***** Adjacency List *****
        1.Create
        2. Display
        3. Exit
        .....Enter Your Choice: 1 

        Enter the source vertices: 1

        Enter the destination vertices: 2
Do you want to continue: y

        Enter the source vertices: 1

        Enter the destination vertices: 3
Do you want to continue: y

        Enter the source vertices: 1 

        Enter the destination vertices: 4
Do you want to continue: y

        Enter the source vertices: 2

        Enter the destination vertices: 4
Do you want to continue: y

        Enter the source vertices: 3

        Enter the destination vertices: 4
Do you want to continue: y

        Enter the source vertices: 3

        Enter the destination vertices: 5
Do you want to continue: y

        Enter the source vertices: 4

        Enter the destination vertices: 5
Do you want to continue: n
Do you want to continue: y

        ***** Adjacency List *****
        1.Create
        2. Display
        3. Exit
        .....Enter Your Choice: 2

        **** Adj. List *****
_
|1| -> 2 ->3 ->4 ->NULL
_
|2| -> 1 ->4 ->NULL
_
|3| -> 1 ->4 ->5 ->NULL
_
|4| -> 1 ->2 ->3 ->5 ->NULL
_
|5| -> 3 ->4 ->NULL
 _
Do you want to continue: n
