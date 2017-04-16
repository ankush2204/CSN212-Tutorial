#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int x, y;
};

bool comp(Node a, Node b)
{  
    return (a.x<b.x);
}

int determinant(Node p, Node q, Node r)
{   
    return (q.y - p.y)*(r.x - q.x)-(q.x - p.x)*(r.y - q.y);
}

void findPartialHull(vector<Node> &arr, vector<Node> &result, Node p1, Node pn)
{
    vector<Node> s1 = vector<Node>();   
    
    for (vector<Node>::iterator it = arr.begin(); it < arr.end(); it++)
    {  
        if (determinant(p1,pn,*it) > 0)
            s1.push_back(*it); 
    }
    
    if (s1.empty())
    {    
        result.push_back(p1);
    } 
    
    else 
    {    
        float maxDist = 0;  
        Node pmax; 
        float dist; 
        float length = sqrt(pow(p1.x - pn.x, 2) + pow(p1.y - pn.y, 2)); 
        
        for (vector<Node>::iterator it = s1.begin(); it < s1.end(); it++)
        {
            dist = determinant(p1,pn,*it) / length; 
            if (dist > maxDist)
            {    
                maxDist = dist;
                pmax = *it;
            }
        }
        
        vector<Node> s11 = vector<Node>();  
        vector<Node> s12 = vector<Node>();  
        
        for (vector<Node>::iterator it = s1.begin(); it < s1.end(); it++)
        {
            if (determinant(p1,pmax,*it) > 0)
            {  
                s11.push_back(*it);
            } 
            else if (determinant(pmax,pn,*it) > 0)
                s12.push_back(*it);
        }
        findPartialHull(s11, result, p1, pmax); 
        findPartialHull(s12, result, pmax, pn); 
    }
}

int main()
{
    int n;
    cin>>n;
    vector<Node> P = vector<Node>(); 
    vector<Node> upper = vector<Node>();    
    vector<Node> lower = vector<Node>();    
    
    for (int i=0;i<n;i++)
    {   
        Node p;
        cin>>p.x>>p.y;
        P.push_back(p);
    }
    
    float t0 = clock();
    sort(P.begin(),P.end(),comp); 
    findPartialHull(P, upper, P[0], P[n-1]);   
    findPartialHull(P, lower, P[n-1], P[0]);   
    sort(upper.begin(),upper.end(),comp); 
    sort(lower.begin(),lower.end(),comp);
    float t1 = clock();
    
    for (vector<Node>::iterator it = upper.begin(); it < upper.end(); it++)
    {  
        cout <<"("<< (*it).x<< ", " << (*it).y<<")" << endl;
    }
    
    for (vector<Node>::iterator it = lower.end()-1; it >= lower.begin(); it--)
    {
        cout <<"("<< (*it).x<< ", " << (*it).y<<")" << endl;
    }
    
    cout << "Total time is" << (t1-t0)/CLOCKS_PER_SEC << " seconds" << endl;
    return 0;
}