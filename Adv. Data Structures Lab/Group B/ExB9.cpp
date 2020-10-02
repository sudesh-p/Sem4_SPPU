#include<iostream>
#include<list>
using namespace std ;
class node
{	
	public:
	node*next;
	char data;
};
class graph : public node 
	{	
		private :
			int  i , j , v , l ; 
			char *vertex , s , d , a[100][100] ; 
			node *head[90] ;
		public :
			                  graph()   
                    {
                              for(int i=0;i<20;i++)
                              {	
                                        for(int j=0;j<20;j++)
                                                  a[i][j]='0';
                              }
                    }
                    void create()
                    {
                    	
                              cout<<"enter the number of vertices in the graph\n";
                             	cin>>v;                   
                             	a[0][0]='\0';
                             	for(int i=1;i<=v;i++)
                             	{
       				cin>>a[0][i];
       				a[i][0]=a[0][i];
                             	}
                     }
        void add_edge()
          {
                     	
			cout<<"enter the source of the edge \n";
			cin>>s;
			cout<<"enter the destination of the edge \n";
			cin>>d;
			for(int l=1;l<=v;l++)
			{
				if(a[l][0]==s)
				{
					for(int j=1;j<=v;j++)
					{
						if(a[0][j]==d)
						{
							a[l][j]=a[j][l]='1';
						}
					}
				}
			}
		}
	void adjacency()
		{	
			node*p;node *temp=NULL;
			for(int i=1;i<=v;i++)	
			{
				p=new node;
				p->next=NULL;
				p->data=a[0][i];
				head[i]=p;
			}
			for(int k=1;k<=v;k++)
			{	
				for(int j=1;j<=v;j++)
				{
					if(a[k][j]=='1')
					{
						p= new node;
						p->next=NULL;
						p->data=a[0][j];
						if(head[k]->next==NULL)
							head[k]->next=p;
						else
						{
							temp=head[k];
							while(temp->next!=NULL)
								temp=temp->next;
							temp->next=p;
						}
					}
				}
			}
			for( int i = 1 ; i <= v; i++ )
          		{ 
          			if( head[i] == NULL )
          		          {
          		          	cout<<" adjacency list not present " << endl ;  
          		                    break;   
          		          }
          		          else
          		          { 
          		         		cout << "\v" << head[i]->data ;
          		                    temp = head[i] -> next ;
          		                    while ( temp != NULL )
          		                    {  
          		                   		cout<<" -> "<<temp->data;
          		         		          temp=temp->next; 
          		                    }
          			}
					        cout << endl ;
			}
		}
				void display () 
					{
						for ( i = 0 ; i <= v ; i++ )
							{
								for ( j = 0 ; j <= v ; j++ )
									{
										cout << a[i][j] << "  " ;
									}
								cout << endl ;
							}
					}	
	};
int main () 
	{
		graph k;
		int j ;
	k.create();
	do{
		cout<<"enter 1. to add the edges in the graph " << endl ;
		cout<<"enter 2. to display the graph using adjacency matrix " << endl ;
		cout<<"enter 3. to display the graph using adjacency list " << endl ;
		cout<<"enter 0. to exit the program " << endl ;
		cin>>j;
		switch(j)
		{
			case 1:
				k.add_edge();
				break;
			case 2:
					k.display();
					break;
			case 3 :
					k.adjacency();
					break ;
		}
	}while(j!=0);		
	}	
	
	
/*
Output :
ds2803@d-s-2803-virtualbox:~/Downloads$ g++ B9.cpp
ds2803@d-s-2803-virtualbox:~/Downloads$ ./a.out
enter the number of vertices in the graph
4
a
b
c
d
enter 1. to add the edges in the graph 
enter 2. to display the graph using adjacency matrix 
enter 3. to display the graph using adjacency list 
enter 0. to exit the program 
1
enter the source of the edge 
a
enter the destination of the edge 
b
enter 1. to add the edges in the graph 
enter 2. to display the graph using adjacency matrix 
enter 3. to display the graph using adjacency list 
enter 0. to exit the program 
1
enter the source of the edge 
b
enter the destination of the edge 
c
enter 1. to add the edges in the graph 
enter 2. to display the graph using adjacency matrix 
enter 3. to display the graph using adjacency list 
enter 0. to exit the program 
1
enter the source of the edge 
c
enter the destination of the edge 
d
enter 1. to add the edges in the graph 
enter 2. to display the graph using adjacency matrix 
enter 3. to display the graph using adjacency list 
enter 0. to exit the program 
1
enter the source of the edge 
d
enter the destination of the edge 
a
enter 1. to add the edges in the graph 
enter 2. to display the graph using adjacency matrix 
enter 3. to display the graph using adjacency list 
enter 0. to exit the program 
2
  a  b  c  d  
a  0  1  0  1  
b  1  0  1  0  
c  0  1  0  1  
d  1  0  1  0  
enter 1. to add the edges in the graph 
enter 2. to display the graph using adjacency matrix 
enter 3. to display the graph using adjacency list 
enter 0. to exit the program 
3

a -> b -> d

b -> a -> c

c -> b -> d

d -> a -> c
enter 1. to add the edges in the graph 
enter 2. to display the graph using adjacency matrix 
enter 3. to display the graph using adjacency list 
enter 0. to exit the program 
0
*/	
