#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int mxn = 20007;
int a[mxn];
int p[mxn];
int b[mxn];
int find_lis(int lo, int len){
	int u, v;
	int ans = 0;
	b[ ans++] = lo;
	for (int i = lo+1; i < lo + len; i++) {
		if (a[ b[ ans-1] ] < a[i]) {
			p[i] = b[ ans - 1 ];
			b[ ans++] = i;
			continue;
		}
		for (u = 0, v = ans-1; u < v;)  {
			int c = (u + v) / 2;
			if (a[b[c]] < a[i]) u=c+1; else v=c;
		}
		if (a[i] < a[b[u]]) {
			if (u > 0) p[i] = b[u-1];
			b[u] = i;
		}	
	}
	return ans;
}
int main()
{
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=0; i  < n; i++){
			cin>>a[i];
			a[i+n] = a[i];
		}
		vector< pair<int, int> > v;
		for(int i=0; i < n; ++i)
		v.push_back( make_pair( a[i], i ) );
		sort( v.begin(), v.end() );
		int best = 1;
		for(int i=0; i < min(108, (int)v.size()); i++)
			best = max( best, find_lis(v[i].second, n));		
		cout<<best<<endl;
	}
	return 0;
}
 
