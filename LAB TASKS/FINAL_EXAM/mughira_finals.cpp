#include <bits/stdc++.h>
using namespace std;

struct Node {
    int rating;
    string name;
    long long hp;
    Node *left, *right;
    int sz;
    Node(int r, const string &n, long long h)
        : rating(r), name(n), hp(h), left(nullptr), right(nullptr), sz(1) {}
};

int sz(Node* t){ return t ? t->sz : 0; }
void pull(Node* t){ if(t) t->sz = 1 + sz(t->left) + sz(t->right); }

Node* findNode(Node* root, int r){
    while(root){
        if(r == root->rating) return root;
        if(r < root->rating) root = root->left;
        else root = root->right;
    }
    return nullptr;
}

bool insertNode(Node* &root, int r, const string &name, long long hp){
    if(!root){
        root = new Node(r, name, hp);
        return true;
    }
    if(r == root->rating) return false;
    bool inserted;
    if(r < root->rating) inserted = insertNode(root->left, r, name, hp);
    else inserted = insertNode(root->right, r, name, hp);
    if(inserted) pull(root);
    return inserted;
}

Node* minimum(Node* root){
    if(!root) return nullptr;
    while(root->left) root = root->left;
    return root;
}
Node* maximum(Node* root){
    if(!root) return nullptr;
    while(root->right) root = root->right;
    return root;
}

Node* successor(Node* root, int X){
    Node* ans = nullptr;
    while(root){
        if(root->rating > X){ ans = root; root = root->left; }
        else root = root->right;
    }
    return ans;
}
Node* predecessor(Node* root, int X){
    Node* ans = nullptr;
    while(root){
        if(root->rating < X){ ans = root; root = root->right; }
        else root = root->left;
    }
    return ans;
}

Node* eraseNode(Node* root, int key, bool &erased){
    if(!root) return nullptr;
    if(key < root->rating){
        root->left = eraseNode(root->left, key, erased);
    } else if(key > root->rating){
        root->right = eraseNode(root->right, key, erased);
    } else {
        erased = true;
        if(!root->left && !root->right){
            delete root;
            return nullptr;
        } else if(!root->left){
            Node* r = root->right;
            delete root;
            return r;
        } else if(!root->right){
            Node* l = root->left;
            delete root;
            return l;
        } else {
            Node* succ = minimum(root->right);
            root->rating = succ->rating;
            root->name = succ->name;
            root->hp = succ->hp;
            bool dummy = false;
            root->right = eraseNode(root->right, succ->rating, dummy);
        }
    }
    pull(root);
    return root;
}

int rankLess(Node* t, int X){
    if(!t) return 0;
    if(X <= t->rating) return rankLess(t->left, X);
    return sz(t->left) + 1 + rankLess(t->right, X);
}

Node* kth(Node* t, int k){
    if(!t) return nullptr;
    int L = sz(t->left);
    if(k == L + 1) return t;
    if(k <= L) return kth(t->left, k);
    return kth(t->right, k - (L + 1));
}

int height(Node* t){
    if(!t) return -1;
    return 1 + max(height(t->left), height(t->right));
}
int leaves(Node* t){
    if(!t) return 0;
    if(!t->left && !t->right) return 1;
    return leaves(t->left) + leaves(t->right);
}

int depthOf(Node* root, int key){
    int d = 0;
    while(root){
        if(key == root->rating) return d;
        if(key < root->rating) root = root->left;
        else root = root->right;
        ++d;
    }
    return -1;
}

Node* lca(Node* root, int A, int B){
    if(!root) return nullptr;
    if(A > B) swap(A,B);
    while(root){
        if(B < root->rating) root = root->left;
        else if(A > root->rating) root = root->right;
        else return root;
    }
    return nullptr;
}

void rangePrint(Node* root, int L, int R, vector<Node*> &out){
    if(!root) return;
    if(root->rating > L) rangePrint(root->left, L, R, out);
    if(L <= root->rating && root->rating <= R) out.push_back(root);
    if(root->rating < R) rangePrint(root->right, L, R, out);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Node* root = nullptr;
    string cmd;
    while(cin >> cmd){
        if(cmd == "JOIN"){
            int r; string name; long long hp;
            cin >> r >> name >> hp;
            bool ok = insertNode(root, r, name, hp);
            if(ok) cout << "JOINED\n";
            else cout << "DUPLICATE\n";
        }
        else if(cmd == "STATUS"){
            int r; cin >> r;
            Node* p = findNode(root, r);
            if(!p) cout << "NOT FOUND\n";
            else cout << p->rating << ' ' << p->name << ' ' << p->hp << '\n';
        }
        else if(cmd == "DAMAGE"){
            int r; long long amt; cin >> r >> amt;
            Node* p = findNode(root, r);
            if(!p) cout << "NOT FOUND\n";
            else {
                p->hp = max(0LL, p->hp - amt);
                cout << "DAMAGED " << p->hp << '\n';
            }
        }
        else if(cmd == "HEAL"){
            int r; long long amt; cin >> r >> amt;
            Node* p = findNode(root, r);
            if(!p) cout << "NOT FOUND\n";
            else {
                p->hp = p->hp + amt;
                cout << "HEALED " << p->hp << '\n';
            }
        }
        else if(cmd == "NEXT"){
            int r; cin >> r;
            Node* s = successor(root, r);
            if(!s) cout << "NONE\n";
            else cout << s->rating << ' ' << s->name << ' ' << s->hp << '\n';
        }
        else if(cmd == "PREV"){
            int r; cin >> r;
            Node* p = predecessor(root, r);
            if(!p) cout << "NONE\n";
            else cout << p->rating << ' ' << p->name << ' ' << p->hp << '\n';
        }
        else if(cmd == "MATCH"){
            int r; cin >> r;
            if(!root){ cout << "EMPTY\n"; continue; }
            Node* pre = predecessor(root, r);
            Node* suc = successor(root, r);
            if(!pre && !suc) { cout << "EMPTY\n"; continue; }
            if(!pre) { cout << suc->rating << ' ' << suc->name << ' ' << suc->hp << '\n'; continue; }
            if(!suc) { cout << pre->rating << ' ' << pre->name << ' ' << pre->hp << '\n'; continue; }
            long long dpre = (long long)r - pre->rating;
            long long dsuc = (long long)suc->rating - r;
            if(dpre <= dsuc) cout << pre->rating << ' ' << pre->name << ' ' << pre->hp << '\n';
            else cout << suc->rating << ' ' << suc->name << ' ' << suc->hp << '\n';
        }
        else if(cmd == "RANGE"){
            int L,R; cin >> L >> R;
            vector<Node*> out;
            rangePrint(root, L, R, out);
            if(out.empty()) cout << "NONE\n";
            else {
                for(Node* p : out) cout << p->rating << ' ' << p->name << ' ' << p->hp << '\n';
            }
        }
        else if(cmd == "LEAVE"){
            int r; cin >> r;
            bool erased = false;
            root = eraseNode(root, r, erased);
            if(erased) cout << "LEFT\n";
            else cout << "NOT FOUND\n";
        }
        else if(cmd == "MIN"){
            Node* m = minimum(root);
            if(!m) cout << "NONE\n";
            else cout << m->rating << ' ' << m->name << ' ' << m->hp << '\n';
        }
        else if(cmd == "MAX"){
            Node* m = maximum(root);
            if(!m) cout << "NONE\n";
            else cout << m->rating << ' ' << m->name << ' ' << m->hp << '\n';
        }
        else if(cmd == "HEIGHT"){
            cout << height(root) << '\n';
        }
        else if(cmd == "LEAVES"){
            cout << leaves(root) << '\n';
        }
        else if(cmd == "RANK"){
            int X; cin >> X;
            cout << rankLess(root, X) << '\n';
        }
        else if(cmd == "KTH"){
            int k; cin >> k;
            Node* p = kth(root, k);
            if(!p) cout << "NONE\n";
            else cout << p->rating << ' ' << p->name << ' ' << p->hp << '\n';
        }
        else if(cmd == "DUEL"){
            int A,B; cin >> A >> B;
            Node* aNode = findNode(root, A);
            Node* bNode = findNode(root, B);
            if(!aNode || !bNode){ cout << "NOT FOUND\n"; continue; }
            Node* L = lca(root, A, B);
            int dA = depthOf(root, A);
            int dB = depthOf(root, B);
            int dL = L ? depthOf(root, L->rating) : 0;
            int dist = dA + dB - 2 * dL;
            cout << "DIST " << dist << '\n';
        }
        else if(cmd == "STATS"){
            int h = height(root);
            int l = leaves(root);
            cout << "HEIGHT " << h << '\n';
            cout << "LEAVES " << l << '\n';
            Node* mn = minimum(root);
            if(mn) cout << "MIN " << mn->rating << ' ' << mn->name << ' ' << mn->hp << '\n';
            else cout << "MIN NONE\n";
            Node* mx = maximum(root);
            if(mx) cout << "MAX " << mx->rating << ' ' << mx->name << ' ' << mx->hp << '\n';
            else cout << "MAX NONE\n";
        }
        else {
            string rest;
            getline(cin, rest);
        }
    }

    if(root){
        vector<Node*> stk;
        stk.push_back(root);
        while(!stk.empty()){
            Node* cur = stk.back(); stk.pop_back();
            if(cur->left) stk.push_back(cur->left);
            if(cur->right) stk.push_back(cur->right);
            delete cur;
        }
    }
    return 0;
}