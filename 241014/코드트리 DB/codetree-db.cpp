#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;


int Q;
string cmd;
unordered_map<string, int> unstr;
unordered_map<int, string> unint;
struct Trie {
    Trie* next[10];
    long long tot;
    bool is_end;
    int cnt;
    ~Trie() {
        for (int i = 0; i < 10; i++)
            if (next[i]) {
                delete next[i];
                next[i] = NULL;
            }
    }
    void Insert(const string str, int v){
        Trie* node = this;
        for (auto it : str) {
            node->tot += v;
            node->cnt++;
            if (!node->next[it - '0']) 
                node->next[it - '0'] = new Trie();
            node = node->next[it - '0'];
        }
        node->tot += v;
        node->cnt++;
        node->is_end = true;
    }
    void Delete(const string str, int v) {
        Trie* node = this;
        for (auto it : str) {
            node->tot -= v;
            node->cnt--;
            node = node->next[it - '0'];
        }
        node->tot -= v;
        node->cnt--;
        node->is_end = false;
        node = NULL;
    }
    string Seek_K(int k) {
        string output = "";
        Trie* node = this;
        for (int idx = 0; idx < 10; idx++) {
            if (node->next[idx]) {
                if (node->next[idx]->cnt >= k) {
                    node = node->next[idx];
                    output += to_string(idx);
                    idx = -1;
                }
                else {
                    k -= node->next[idx]->cnt;
                }
            }
            if (node->is_end) return output;
        }
    }
    long long Seek_Sum(string str) {
        long long output = 0;
        Trie* node = this;
        int idx = 0;
        while (node) {
            if (str.length() == idx) break;
            for (int i = 0; i < str[idx] - '0'; i++) {
                if (node->next[i]) {
                    output += node->next[i]->tot;
                }
            }
            node = node->next[str[idx++] - '0'];
        }
        if (node && node->is_end) output += node->tot;
        return output;
    }
};

Trie* root[10];

void Init() {
    for (int i = 0; i < 10; i++) {
        if(root[i])
            delete root[i];
        root[i] = new Trie();
    }
    unstr.clear();
    unint.clear();
}
int Insert() {
    string name;
    int value;
    cin >> name >> value;
    if (unint.find(value) != unint.end()) return 0;
    if (unstr.find(name) != unstr.end()) return 0;
    unstr[name] = value;
    unint[value] = name;
    string svalue = to_string(value);
    root[svalue.length()-1]->Insert(svalue, value);
    return 1;
}
int Delete() {
    string name;
    cin >> name;
    if (unstr.find(name) == unstr.end()) return 0;
    int value = unstr[name];
    unstr.erase(name);
    unint.erase(value);
    string svalue = to_string(value);
    root[svalue.length() - 1]->Delete(svalue, value);
    return value;
}
string Rank() {
    int k;
    cin >> k;
    int cur = 0;
    string output = "";
    for (int idx = 0; idx < 10; idx++) {
        if (root[idx]->cnt >= k) {
            output = root[idx]->Seek_K(k);
            break;
        }
        else {
            k -= root[idx]->cnt;
        }
    }
    if (output.empty()) return "None";
    else return unint[stoi(output)];
}
long long Sum() {
    int k;
    cin >> k;
    string svalue = to_string(k);
    long long output = 0;
    for (int i = 0; i < svalue.length()-1;i++) {
        output += root[i]->tot;
    }
    return output += root[svalue.length() - 1]->Seek_Sum(svalue);
}

void solution() {
    cin >> Q;
    while (Q--) {
        cin >> cmd;
        if (cmd == "init") {
            Init();
        }else if (cmd == "insert") {
            cout << Insert() << '\n';
        }else if (cmd == "delete") {
            cout << Delete() << '\n';
        }else if (cmd == "rank") {
            cout << Rank() << '\n';
        }else if (cmd == "sum") {
            cout << Sum() << '\n';
        }
    }
}


int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    solution();
    

    return 0;
}