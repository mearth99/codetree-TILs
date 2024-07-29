#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<algorithm>
#include<bitset>
using namespace std;

/*
* 문제 설명 및 링크
*/
/*
* 소감
*/

struct Tree {
	vector<int> vect;
	int pid, mid, color, maxdep;
};

Tree tree[100001];
vector<int> rootnode;
void AddNode(int mid, int pid, int color, int maxdep) {
	if (pid != -1 && tree[pid].maxdep != 1) {
		tree[pid].vect.push_back(mid);
		tree[mid].maxdep = min(maxdep, tree[pid].maxdep - 1);
		tree[mid].mid = mid;
		tree[mid].pid = pid;
		tree[mid].color = color;
		int temp_pid = pid;
	}
	else if(pid==-1){
		rootnode.push_back(mid);
		tree[mid].maxdep = maxdep;
		tree[mid].mid = mid;
		tree[mid].pid = pid;
		tree[mid].color = color;
	}
}
void ChgColor(int mid, int color) {
	queue<int> q;
	q.push(mid);
	while (!q.empty()) {
		int target = q.front(); q.pop();
		tree[target].color = color;
		for (auto it : tree[target].vect)
			q.push(it);
	}
}
void LokColor(int mid) {
	cout << tree[mid].color << '\n';
}
pair<int, bitset<6>> DFSColor(int mid) {
	int sum = 0;
	bitset<6> bit;
	if (!tree[mid].vect.empty()) {
		for (auto it : tree[mid].vect) {
			pair<int, bitset<6>> cur = DFSColor(it);
			sum += cur.first;
			bit |= cur.second;

		}
		bit[tree[mid].color] = 1;
		int gap = bit.count();
		return { sum + gap * gap,bit };
	}
	else {
		bit[tree[mid].color] = 1;
		return { 1, bit };
	}
}
int AllColor() {
	int sum = 0;
	bitset<6> bit;
	for (auto it : rootnode) {
		pair<int,  bitset<6>> cur = DFSColor(it);
		sum += cur.first;
		bit |= cur.second;
	}
	return sum;
}


void solution() {
	int Q;
	cin >> Q;
	while (Q--) {
		int cmd;
		cin >> cmd;
		switch (cmd) {
			int m_id, p_id, color, max_dep;
		case 100:
			cin >> m_id >> p_id >> color >> max_dep;
			AddNode(m_id, p_id, color, max_dep);
			break;
		case 200:
			cin >> m_id >> color;
			ChgColor(m_id, color);
			break;
		case 300:
			cin >> m_id;
			LokColor(m_id);
			break;
		case 400:
			cout << AllColor() << '\n';
			break;
		}
	}
}

int main() {

	cin.tie(NULL); ios_base::sync_with_stdio(false);
	solution();
	return 0;
}