#include<iostream>
#include<algorithm>
#include<math.h>
#include<string>
#include<stdio.h>
using namespace std;

struct node{
int low,high,max_high;
node *l; //l=left
node *r; //r=right
};

node* InsertNode(node *rootNode,int l,int h)
{
    if(rootNode==NULL)
    {
        node* temp = new node();
    temp->low = l;
    temp->high = h;
    temp->max_high = h;
    temp->l = NULL;
    temp->r = NULL;

        rootNode = temp;
    }
    else if(l > rootNode->low )
    {
        rootNode->max_high = max(rootNode->high,h);
        rootNode->r = InsertNode(rootNode->r,l,h);
    }
    else
    {
        rootNode->max_high = max(rootNode->high,h);
        rootNode->l = InsertNode(rootNode->l,l,h);
    }
    return rootNode;

}

node* SearchTree(node *rootNode,int l,int h)
{
    if (rootNode == NULL)
            return NULL;
        if (rootNode->low<=h && rootNode->high>=l)
            return rootNode;
        if (rootNode->l != NULL && (rootNode->l)->max_high >= l)
            return SearchTree(rootNode->l, l, h);
        return SearchTree(rootNode->r, l, h);

}
void ModifyNode(node* node1, node* node2){
	node1->low=node2->low;
	node1->high=node2->high;
}
void DeleteNode(node* current,node* rootNode, node* parent, bool head){
	int child=0;
	bool l=false, r=false;
	if(current->low <= parent->low) l=true;
	else r=true;

	if(current->l) child++;
	if(current->r) child++;

	if(child==0){
		if(head){
			parent=NULL;
			return;
		}
		if(l) parent->l=NULL;
		else parent->r=NULL;
	}
	else if(child==1){
		if(head){
			if(current->l) rootNode=rootNode->l;
			else rootNode=rootNode->r;
			return;
		}
		if(l){
			if(current->r) parent->l=current->r;
			else parent->l=current->l;
		}
		else{
			if(current->r) parent->r=current->r;
			else parent->r=current->l;
		}
	}
	else{
		node* temp=current;
		temp=temp->l;
		if(temp->r){
			while(temp->r){
				parent=temp;
				temp=temp->r;
			}
			ModifyNode(current, temp);
			parent->r=NULL;
		}
		else{
			ModifyNode(current, temp);
			DeleteNode(temp, rootNode,current, false);
		}
	}
}
node* DeleteNode(node* rootNode,node* temp_node)
{
    node* current=new node();
    current = rootNode;
	node *parent= new node();
	parent = rootNode;
	//initially eleminating the case when we have to Delete the root node itself
	while(true){
		if(current==NULL){
			cout<<"The interval you requested to Delete does not exist"<<endl;
			break;
		}
		if(temp_node->low < current->low){
			parent=current; current=current->l;
		}
		else if(temp_node->low > current->low){
			parent=current; current=current->r;
		}
		else{
			DeleteNode(current,rootNode, parent, false);
			break;
		}
	}
}

int main()
{
 node *rootNode = NULL;
 cout<<"Enter the number of intervals to be inserted.."<<endl;
 int n,l,h;
 cin>>n;
 for(int i=1;i<=n;i++)
 {

     cin>>l>>h;
     rootNode = InsertNode(rootNode,l,h);
 }
 cout<<rootNode->low<<endl;
 cout<<"Enter the number of Search queries.."<<endl;
 cin>>n;
 for(int i=1;i<=n;i++)
 {
     cin>>l>>h;
     node *temp = new node();
     temp = SearchTree(rootNode,l,h);
     if(temp)
     {
         cout<<"Overlapping interval is : "<<temp->low<<" "<<temp->high<<endl;
     }
     else
        cout<<"No Overlapping Interval was found.."<<endl;
 }
 cout<<"Enter the number of nodes to Delete.."<<endl;
 cin>>n;
 for(int i=1;i<=n;i++)
 {
    cin>>l>>h;
    node* temp = new node();
    temp->low = l;
    temp->high = h;
    temp->max_high = h;
    temp->l = NULL;
    temp->r = NULL;

    DeleteNode(rootNode,temp);
    cout<<"The requested interval has been deleted.."<<endl;
 }
 return 0;
}
