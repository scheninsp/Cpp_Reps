//kruskal minimum generation tree of weighted graph

//input: [nVertex, adjacency matrix in one row, ] 
//4 1 2 3 4 2 5 6 7 3 6 5 8 4 7 8 5

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;

const int NMAX = 256;

struct edge{
    int from,to;
    int cost,yes;
}e[NMAX*NMAX];

int n;
int s[NMAX];  //mst set
int height[NMAX];  

bool cmp(edge s1,edge s2)
{
    return s1.cost < s2.cost;
}

int find_set(int x)             
{
    int r = x;
    while(r != s[r]){
        r = s[r];
    }
    while(x != r){
        int j = s[x];
        s[x] = r;
        x = j;
    }
    return r;
}

void kruskal(int nEdge)
//
{
    sort(e, e+nEdge, cmp);
	
    int ans = 0;
    for(int i = 0;i < nEdge;i++){
        int x = find_set(e[i].from);
        int y = find_set(e[i].to);
        if(x == y){
            continue;
        }
        if(height[x] == height[y]){
            height[x]++;
            s[y] = x;
        }
        else{
            if(height[x] < height[y]){
                s[x] = y;
            }
            else{
                s[y] = x;
            }
        }
        ans += e[i].cost;
    }
	
    printf("%d\n",ans);
}

void main()
{
    scanf("%d",&nVertex);
	memset(e,0,sizeof(e));
	
	int i = 0;
	for(int k = 1;k <= nVertex;k++){
		for(int j = 1;j <= nVertex;j++){
			int num;
			scanf("%d",&num);
			if(k>=j){
				continue;
			}
			e[i].cost = num;
			e[i].from = k;
			e[i].to = j;
			i++;
		}
	}
	
	for(int k = 1;k <= NMAX;k++){
		s[k] = k;
		height[k] = 0;
	}
	
	int m;
	scanf("%d",&m);
	while(m--){
		
		int x,y;
		scanf("%d%d",&x,&y);
		x = find_set(x);
		y = find_set(y);
		
		if(x == y){
			continue;
		}
		if(height[x] == height[y]){
			height[x]++;
			s[y] = x;
		}
		else{
			if(height[x] < height[y]){
				s[x] = y;
			}
			else{
				s[y] = x;
			}
		}
	}
	
	kruskal(i);
	
	getchar();
    return 0;
}


