#include <cstdio>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <queue>
#define MAX 987654321
using namespace std;
int N, T, sumOfProd, sumOfEnergy, tempEnergy ,S[21][3], L[21][21];
bool check[21];
vector<int> list, result;

struct aNode{
	int number;
	int energy;
	bool value[21];
};
priority_queue<aNode> pq;
bool operator<(aNode t, aNode u){
	return t.energy > u.energy;
}

int dist(int x1, int y1, int x2, int y2){
	return (abs(x1 - x2) + abs(y1 - y2));
}

void roam(int index){
	if (list.size() == N){
		if (tempEnergy < sumOfEnergy){
			sumOfEnergy = tempEnergy;
			result = list;
		}
	}	
	else{
		for (int i = 1; i < N; i++){
			if (check[i]) continue;
			int dist = L[index][i] * (int)(sqrt((sumOfProd)));
			if (tempEnergy + dist >= sumOfEnergy)  continue;
			else{
				tempEnergy += dist;
				list.push_back(i);
				int burden = S[i][2];
				sumOfProd -= burden;
				check[i] = true;
				roam(i);
				check[i] = false;
				sumOfProd += burden;
				list.pop_back();
				tempEnergy -= dist;
			}
		}
	}
}

int main(){
	ifstream inStream("delivery.inp");
	ofstream outStream("delivery.out");
	inStream >> N;
	inStream >> S[0][0] >> S[0][1];
	for (int i = 1; i < N; i++){
		inStream >> S[i][0] >> S[i][1] >> S[i][2];
		sumOfProd += S[i][2];
	}
	for (int i = 0; i < N; i++){
		for (int j = i + 1; j < N; j++){
			L[i][j] = dist(S[i][0], S[i][1], S[j][0], S[j][1]);
			L[j][i] = L[i][j];
		}
	}
	check[0] = true;
	for (int i = 1; i < N; i++){
		aNode node1;
		node1.energy = L[0][i] * (int)(sqrt((sumOfProd)));
		node1.value[0] = true;
		node1.value[i] = true;
		node1.number = i;
		pq.push(node1);
	}
	int tt = sumOfProd;
	for (int i = 0; i < N-1; i++){ 
		tt -= S[i][2];
		sumOfEnergy += (L[i][i + 1] * (int)(sqrt(tt)));
	}
	list.push_back(0);
	result.clear();
	while (!pq.empty())
	{
		aNode tmp = pq.top();
		pq.pop();
		tempEnergy = tmp.energy;
		int num = tmp.number;
		check[num] = tmp.value[num];
		sumOfProd -= S[num][2];
		list.push_back(num);
		roam(num);
		list.pop_back();
		check[num] = false;
		sumOfProd += S[num][2];
	}
	for (int i = 0; i < N; i++)		outStream << result[i] + 1 << " ";
}