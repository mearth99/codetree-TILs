#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Move {
    int y, x;
};

int N, M;
vector<vector<int>> arr;
vector<Move> market;
vector<Move> man;
vector<int> now;
int ncnt = 1;

int dy[4] = { -1,0,0,1 };
int dx[4] = { 0,-1,1,0 };
struct BFQ {
    int y, x, start_dir;
};

int visit[16][16];

int BFS(int num) {
    fill(&visit[0][0], &visit[15][15], 0);
    queue<BFQ> q;
    int sy = man[num].y;
    int sx = man[num].x;
    int ey = market[num].y;
    int ex = market[num].x;
    visit[sy][sx] = 1;
    for (int i = 0; i < 4; i++) {
        //초기 dir을 알기 위한 움직임
        int ny = sy + dy[i];
        int nx = sx + dx[i];
        if (ny >= 0 && ny < N && nx >= 0 && nx < N && arr[ny][nx] != -1) {
            visit[ny][nx] = 1;
            q.push({ ny,nx,i });
        }
    }
    while (!q.empty()) {
        int y = q.front().y;
        int x = q.front().x;
        int dir = q.front().start_dir;
        if (y == ey && x == ex) 
            return dir;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (ny >= 0 && ny < N && nx >= 0 && nx < N && arr[ny][nx] != -1 && !visit[ny][nx]) {
                visit[ny][nx] = 1;
                q.push({ ny,nx,dir });
            }
        }
    }
    printf("심각한 에러");
    return -1;
}
void BFSCAMP(int num) {
    fill(&visit[0][0], &visit[15][16], 0);
    int sy = market[num].y;
    int sx = market[num].x;
    visit[sy][sx] = 1;
    queue<BFQ> q;
    q.push({ sy,sx,0 });
    int mincost = 0x7fffffff;
    vector<pair<int, int>> check;
    while (!q.empty()) {
        int y = q.front().y;
        int x = q.front().x;
        int cost = q.front().start_dir; // start_dir을 cost로 활용
        if (arr[y][x] == 1) {
            if (mincost >= cost) {
                mincost = min(cost, mincost);
                check.push_back({ y,x });
            }
            else {
                int ry = 100, rx = 100;
                for (auto it : check) {
                    if (it.first < ry) {
                        ry = it.first;
                        rx = it.second;
                    }
                    else if (it.first == ry && it.second < ry)
                        ry = it.second;
                }
                arr[ry][rx] = -1;
                man[num] = {ry,rx};
                return;
            }
        }
        q.pop();
        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (ny >= 0 && ny < N && nx >= 0 && nx < N && arr[ny][nx] != -1 && !visit[ny][nx]) {
                visit[ny][nx] = 1;
                q.push({ ny,nx, cost+1 });
            }
        }
    }
}

vector<int> one() {
    vector<int> output;
    for (auto it : now) {
        output.push_back(BFS(it));
    }
    return output;
}

void solution() {
    cin >> N >> M;
    arr.resize(N, vector<int>(N));
    for (auto& h : arr) {
        for (auto& w : h)
            cin >> w;
    }
    market.resize(M + 1);
    man.resize(M+1);
    for (int i = 1; i <= M; i++) {
        cin >> market[i].y >> market[i].x;
        market[i].y--;
        market[i].x--;
    }
    int output = 0;
    while (ncnt < M + 1) {
        vector<int> deletelist;
        //1 vector<int>를 리턴한다. //man에 해당하는 이동방향.
        vector<int> dirs = one();
        //2 vector<int>를 man에 더해서 실제로 이동시킨다. => 편의점이면 그 편의점을 막는다. 그리고 now에서 지운다.
        for (int i = 0; i < dirs.size(); i++) {
            int idx = now[i];
            man[idx].y += dy[dirs[i]];
            man[idx].x += dx[dirs[i]];
            if (market[idx].y == man[idx].y && market[idx].x == man[idx].x) {
                arr[market[idx].y][market[idx].x] = -1;
                deletelist.push_back(now[i]);
            }
        }
        for (auto it : deletelist) {
            now.erase(remove(now.begin(), now.end(), it));
        }
        //3 ncnt에 해당하는 사람을 목적지와 가장 가까운 베이스 캠프에 이동시키고, 베이스 캠프를 봉인한다.
        now.push_back(ncnt);
        BFSCAMP(ncnt++);
        output++;
    }
    while (!now.empty()) {
        vector<int> deletelist;
        //1 vector<int>를 리턴한다. //man에 해당하는 이동방향.
        vector<int> dirs = one();
        //2 vector<int>를 man에 더해서 실제로 이동시킨다. => 편의점이면 그 편의점을 막는다. 그리고 now에서 지운다.
        for (int i = 0; i < dirs.size(); i++) {
            int idx = now[i];
            man[idx].y += dy[dirs[i]];
            man[idx].x += dx[dirs[i]];
            if (market[idx].y == man[idx].y && market[idx].x == man[idx].x) {
                arr[market[idx].y][market[idx].x] = -1;
                deletelist.push_back(now[i]);
            }
        }
        for (auto it : deletelist) {
            now.erase(remove(now.begin(), now.end(), it));
        }
        output++;
    }
    cout << output;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solution();
    return 0;
}