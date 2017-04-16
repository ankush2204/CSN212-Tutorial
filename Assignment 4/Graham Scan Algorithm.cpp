#include <bits/stdc++.h>
using namespace std;
 
struct Node
{
    int x, y;
};
Node p0;

Node nextToTop(stack<Node> &S)
{
    Node p = S.top();
    S.pop();
    Node rs = S.top();
    S.push(p);
    return rs;
}
int swap(Node &p1, Node &p2)
{
    Node temp = p1;
    p1 = p2;
    p2 = temp;
}
int distSq(Node p1, Node p2)
{
    return (p1.x - p2.x)*(p1.x - p2.x)+(p1.y - p2.y)*(p1.y - p2.y);
}

int orientation(Node p, Node q, Node r)
{
    int val = (q.y - p.y)*(r.x - q.x)-(q.x - p.x)*(r.y - q.y); 
    if (val == 0) 
    return 0; 
    if(val > 0)
    return 1;
    return 2; 
}
int compare(const void *vp1, const void *vp2)
{
   Node *p1 = (Node *)vp1;
   Node *p2 = (Node *)vp2;
   int o = orientation(p0, *p1, *p2);
   if (o == 0)
     return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;
   return (o == 2)? -1: 1;
}
void convexHull(Node Nodes[], int n)
{
   int ymin = Nodes[0].y, min = 0;
   for (int i = 1; i < n; i++)
   {
     int y = Nodes[i].y;
     if ((y < ymin) || (ymin == y &&
         Nodes[i].x < Nodes[min].x))
        ymin = Nodes[i].y, min = i;
   }
   swap(Nodes[0], Nodes[min]);
   p0 = Nodes[0];
   qsort(&Nodes[1], n-1, sizeof(Node), compare);
   int m = 1; 
   
   for (int i=1; i<n; i++)
   {
       while (i < n-1 && orientation(p0, Nodes[i],Nodes[i+1]) == 0)
          i++;
       Nodes[m] = Nodes[i];
       m++;  
   }
   
   if (m < 3) return;
   
   stack<Node> S;
   S.push(Nodes[0]);
   S.push(Nodes[1]);
   S.push(Nodes[2]);
   
   for (int i = 3; i < m; i++)
   {
      while (orientation(nextToTop(S), S.top(), Nodes[i]) != 2)
         S.pop();
      S.push(Nodes[i]);
   }
   
   while (!S.empty())
   {
       Node p = S.top();
       cout << "(" << p.x << ", " << p.y <<")" << endl;
       S.pop();
   }
}

int main()
{
    int n;
    cin>>n;
    Node *P= new Node[n];
    for(int i=0;i<n;i++)
    {
       cin>>P[i].x>>P[i].y;
    }
    
    float t0 = clock();
    convexHull(P, n);
    float t1 = clock();
    cout<<"Total time is "<<(t1-t0)/CLOCKS_PER_SEC<<" seconds"<<endl;
    return 0;
}
