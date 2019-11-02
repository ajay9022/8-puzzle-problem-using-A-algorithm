#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct node{
    int dist = -1;
    int m[3][3] = {0};
    node(int d){
        dist = d;
    }
};
node g(0);
void print(node &p){
    cout<<p.dist<<endl;
    for(int i=0;i<3;++i){
        for(int j=0;j<3;++j){
            cout<<p.m[i][j]<<" ";
        }cout<<endl;
    }
}
int manhatten(node t){
    int dist = 0;
    for(int i=0;i<3;++i){
        for(int j=0;j<3;++j){
            int x = t.m[i][j];
            if(x==0) dist+= abs(i-2) + abs(j-2);
            if(x==1) dist+= i+j; 
            else if (x == 2) dist+= i + abs(j-1);
            else if (x == 3) dist+= i + abs(j-2);
            else if (x == 4) dist+= abs(i-1) + j;
            else if (x == 5) dist+= abs(i-1) + abs(j-1);
            else if (x == 6) dist+= abs(i-1) + abs(j-2);
            else if (x == 7) dist+= abs(i-2) + abs(j);
            else if (x == 8) dist+= abs(i-2) + abs(j-1);
            
        }
    }

    return t.dist = dist;
}
string to_str(node a){
    string s;
    for(int i=0;i<3;++i){
        for(int j=0;j<3;++j){
            s += to_string(a.m[i][j]);
        }
    }
    return s;
}
node* create(string s){
    node *temp = new node(0);
    int k=0;
    for(int i=0;i<3;++i){
        for(int j=0;j<3;++j){
            temp->m[i][j] = s[k++];
        }
    }
    temp->dist = manhatten(*temp);
    return temp;
}
pair<int,int> find0pos(node *p){
    for(int i=0;i<3;++i){
        for(int j=0;j<3;++j){
            if(p->m[i][j]==0){
                return make_pair(i,j);
            }
        }
    }
    return make_pair(-1,-1);
}
vector<node *> all_states(node *p){
    // cout<<"all_states\n";
    pair<int,int> xy = find0pos(p);
    int x = xy.first, y = xy.second;
    int xx[] = {0,0,1,-1};
    int yy[] = {-1,1,0,0};
    int i=0;
    vector<node *> v;
    while(i<4){
        if (x + xx[i] >= 0 && y + yy[i]>=0 && x + xx[i] < 3 && y + yy[i] < 3){
            node* n = new node(0);
            for(int i=0;i<3;++i){
                for(int j=0;j<3;++j){
                    n->m[i][j] = p->m[i][j];
                }
            }
            n->m[x][y] = p->m[xx[i]+x][yy[i]+y];
            n->m[xx[i]+x][y+yy[i]] = p->m[x][y];
            n->dist = manhatten(*n);
            // print(*n);
            v.push_back(n);
        }
        ++i;
    }
    return v;
}
bool comp(node &a, node &b){
    return a.dist > b.dist;
}
string init;
map<string, string> par;
string bfs(node a){
    
    priority_queue<node, vector<node>, decltype((comp))> q(comp);
    string a_str = to_str(a);
    q.push(a);
    map<string,int> vis;
    

    vis[a_str] = 1;
    int count = 0;
    while(!q.empty()){
        node p = q.top();
        ///print(p);
        // cout<<"-----------\nthis\n";
        
        // print(p);
        // cout << "-----------\n";
        q.pop();
        ++count;
        // cout<<count<<endl;
        /* if(count==5){
            exit(0);
        } */

        // pair<int,int> xy = find0pos(p);
        // int x = xy.first, y = xy.second;
        vector<node *> v= all_states(&p);
        //cout << "v.size()" << v.size() << endl;
        string parent = to_str(p);
        for(auto &node_i : v){
            //cout<<"into\n";
            string child = to_str(*node_i);//child
            if(!vis[child]){
                
                if(node_i->dist==0){
                    par[child] = parent;
                    
                    return child;
                }
                
                q.push(*node_i);
                
                par[child] = parent;
                // cout<<child<<" -> "<<parent<<endl;
                vis[child] = 1;
            }
        }
    }
    return "-1";
}
int main(){
    cout<<"Initial State : \n";
    
    node a(0);
    a.m[0][0] = 1;
    a.m[0][1] = 0;
    a.m[0][2] = 3;
    a.m[1][0] = 4;
    a.m[1][1] = 2;
    a.m[1][2] = 6;
    a.m[2][0] = 7;
    a.m[2][1] = 5;
    a.m[2][2] = 8;
    a.dist = manhatten(a);
    init = to_str(a);
    // cout<<"a.dist"<<a.dist<<endl;
    print(a);
    g.m[0][0] = 1;
    g.m[0][1] = 2;
    g.m[0][2] = 3;
    g.m[1][0] = 4;
    g.m[1][1] = 5;
    g.m[1][2] = 6;
    g.m[2][0] = 7;
    g.m[2][1] = 8;
    g.m[2][2] = 0;

    string goal = bfs(a);

    
    // cout<<"---\n";
    // cout<<goal<<endl;
     while (par[goal] != ""){
        int k=0;
        for(int i=0;i<3;++i){
            for(int j=0;j<3;++j){
                cout<<goal[k++];
            }cout<<endl;
        }cout<<endl;
        goal = par[goal];
        // cout<<goal<<endl;
        
    }
    int k=0;
    for(int i=0;i<3;++i){
        for(int j=0;j<3;++j){
            cout<<init[k++];
        }cout<<endl;
    }cout<<endl;
    
        return 0;
}