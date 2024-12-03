#include <iostream>
#include <vector>
using namespace std;

int q;
vector<int> index;
vector<vector<int>> mount;

int search(int h) {
    if(mount.size()==0)
        return 0;
    int s=0,e=mount.size()-1;
    int idx=mount.size();
    while(s<=e) {
        int m=(s+e)/2;
        if(h<=mount[m].back()) {
            idx=m;
            e=m-1;
        } else {
            s=m+1;
        }
    }
    return idx;
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

    cin>>q;
    while(q--) {
        int o;cin>>o;
        if(o==100){
            int n;cin>>n;
            for(int i=0;i<n;i++) {
                int h;cin>>h;
                int idx=search(h);
                index.push_back(idx);
                if(idx==mount.size())
                    mount.push_back({});
                mount[idx].push_back(h);
            }
        }
        if(o==200){
            int h;cin>>h;
            int idx=search(h);
            index.push_back(idx);
            if(idx==mount.size())
                mount.push_back({});
            mount[idx].push_back(h);
        }
        if(o==300){
            int idx=index.back();
            index.pop_back();
            mount[idx].pop_back();
            if(mount.back().size()==0)
                mount.pop_back();
        }
        if(o==400){
            int m_idx;cin>>m_idx;
            m_idx-=1;
            cout<<(index[m_idx]+mount.size())*1000000+mount.back()[0]<<"\n";
        }
    }

    return 0;
}