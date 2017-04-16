#include <bits/stdc++.h>
using namespace std;
 
struct Point
{
    int x, y;
};

int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y)*(r.x - q.x)-(q.x - p.x)*(r.y - q.y); 
    if (val == 0) 
    return 0; 
    if(val > 0)
    return 1;
    return 2;
}

void convexHull(Point points[], int n)
{
    if (n < 3) return;
    vector<Point> hull;
    int l = 0;
    
    for (int i = 1; i < n; i++){
        if (points[i].x < points[l].x)
            l = i;
    }
    
    int p = l, q;
    
    do
    {
        hull.push_back(points[p]);
        q = (p+1)%n;
        
        for (int i = 0; i < n; i++)
        {
           if (orientation(points[p], points[i], points[q]) == 2)
               q = i;
        }
        
        p = q;
    }while (p != l);  
    
    for (int i = 0; i < hull.size(); i++)
    {
        cout << "(" << hull[i].x << ", "<< hull[i].y << ")\n";
    }
}

int main()
{
    int n;
    cin>>n;
    Point *P= new Point[n];
    
    for(int i=0;i<n;i++)
    {
       cin>>P[i].x>>P[i].y;
    }
    
    float t0 = clock();
    convexHull(P, n);
    float t1 = clock();
    cout<<"Total time is"<<(t1-t0)/CLOCKS_PER_SEC<<" seconds"<<endl;
    return 0;
}
