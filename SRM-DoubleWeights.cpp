#include <iostream>
#include<stdio.h>
#include <string>
#include <string.h>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>
#include <list>
#include <set>
#include <functional>
using namespace std;
const int inf = 98765432;
int D[25];
int p[25];
stack<int> st;
#define max(a,b) (a>b ? a:b)
void parents_find(int x){
	st.push(x);
	if (x == 0){
		return;
	}
	
	parents_find(p[x]);
}
struct Edge{
	int end;
	int w1;
	int w2;
	Edge(int end, int w1, int w2) :end(end), w1(w1), w2(w2){

	}
};
vector<Edge> v[20];
class DoubleWeights{
	
public:
	int minimalCost(vector <string> weight1, vector <string> weight2){
		int n = weight1.size();
		for (int i = 1; i < n; i++){
			D[i] = inf;
		}
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				if (weight1[i][j] == '.'){
					continue;
				}
				int w1_end;
				int w2_end;
				w1_end = weight1[i][j] - '0';
				w2_end = weight2[i][j] - '0';
				v[i].push_back(Edge(j, w1_end, w2_end));
			
			}
		} // for i
		queue<int> q;
		q.push(0);
		while (!q.empty()){
			int front = q.front();
			q.pop();
			for (int i = 0; i < v[front].size(); i++){
				int end = v[front][i].end;
				int w1 = v[front][i].w1;
				int w2 = v[front][i].w2;
				parents_find(front);
				int sum_w1 = 0;
				int sum_w2 = 0;
				int first_node = st.top();
			
				st.pop();
				while(!st.empty()){
					int st_end = st.top();
					st.pop();
					for (int j = 0; j<v[first_node].size(); j++){
						if (v[first_node][j].end == st_end){
							sum_w1 += v[first_node][j].w1;
							sum_w2 += v[first_node][j].w2;
						}
					}
					first_node = st_end;
				}
				if (D[end] > (sum_w1 + w1) * (sum_w2 + w2)){
					D[end] = (sum_w1 + w1) * (sum_w2 + w2);
					//cout << end << ": " << "w1 , w2 "<< w1 <<" " << w2 <<" "<< D[end] << endl;
					p[end] = front;
					q.push(end);
				}
			}
		}
		if (D[1] != inf){
			return D[1];
		}
		else{
			return -1;
		}
	}// minimal cost func
};
int main() {
	DoubleWeights p;
	vector<string> v1;
	vector<string> v2;
	v1.push_back("..14");
	v1.push_back("..94");
	v1.push_back("19..");
	v1.push_back("44..");
	v2.push_back("..94");
	v2.push_back("..14");
	v2.push_back("91..");
	v2.push_back("44..");
	cout << p.minimalCost(v1, v2);


}
