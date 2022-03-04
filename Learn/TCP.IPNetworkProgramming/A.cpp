#include <bits/stdc++.h>

using namespace std;

// struct Node {
//   int key, value;

//   Node *pre, *suf;

//   Node(int _key = 0, int _value = 0) : key(_key), value(_value), pre(nullptr), suf(nullptr) {}
// };

// class LRUCache {
// public:

//   Node *head, *tail;

//   int size, cap;

//   unordered_map<int, Node*> mp;

//   LRUCache(int capacity) {
//     size = 0, cap = capacity;
//     head = new Node(), tail = new Node();
//     head->suf = tail;
//     tail->pre = head;
//   }

//   int get(int key) {
//     // 
//     if (!mp.count(key)) {
//       return -1;
//     }
//     // 
//     auto cur = mp[key];
//     remove(cur);
//     addToHead(cur);
//     // 
//     return cur->value;
//   }

//   void addToHead(Node *cur) {
//     head->suf->pre = cur;
//     cur->suf = head->suf;
//     head->suf = cur;
//     cur->pre = head;
//   }

//   void remove(Node *cur) {
//     cur->pre->suf = cur->suf;
//     cur->suf->pre = cur->pre;
//   }

//   void put(int key, int value) {
    
//     if (mp.count(key)) {
//       auto cur = mp[key];
//       cur->value = value;
//       remove(cur);
//       addToHead(cur);
//     } else {
//       size++;
//       Node *cur = new Node(key, value);
//       mp[key] = cur;
//       addToHead(cur);
//       if (size > cap) {
//         removeTail();
//       }
//     }
    
//   }

//   void removeTail() {
//     auto cur = tail->pre;
//     cur->pre->suf = tail;
//     tail->pre = cur->pre;
//     mp.erase(cur->key);
//     delete cur;
//   }
// };

// int main() {
//   int cap;
//   cin >> cap;
//   LRUCache a(cap);
//   while (true) {
//     int op, key, value;
//     cin >> op >> key;
//     if (op == 1) { // get;
//       cout << a.get(key) << endl;
//     } else {
//       cin >> value;
//       a.put(key, value);
//     }
//   }
//   return 0;
// }

const int N = 1e5 + 10;

int head[N], to[N], nex[N], value[N], cnt = 1;

int ans, in[N], n, m;

void add(int x, int y, int w) {
  to[cnt] = y;
  nex[cnt] = head[x];
  value[cnt] = w;
  head[x] = cnt++;
}

void dfs(int rt, int fa, int val) {
  ans = max(ans, val);
  for (int i = head[rt]; i; i = nex[i]) {
    if (to[i] == fa) {
      continue;
    }
    dfs(to[i], rt, val + value[i]);
  }
}

int main() {
  cin >> n >> m;
  for (int i = 1, u, v, w; i <= m; i++) {
    cin >> u >> v >> w;
    add(u, v, w);
    in[v]++;
  }
  ans = 0;
  for (int i = 1; i <= n; i++) {
    if (!in[i]) {
      dfs(i, 0, 0);
    }
  }
  cout << ans << endl;
  return 0;
}

/*
Q：编程题2
运用你所掌握的数据结构，设计和实现一个  LRU (最近最少使用) 缓存机制 。
实现 LRUCache 类：
LRUCache(int capacity) 以正整数作为容量 capacity 初始化 LRU 缓存
int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
void put(int key, int value) 如果关键字已经存在，则变更其数据值；
如果关键字不存在，则插入该组「关键字-值」。
当缓存容量达到上限时，它应该在写入新数据之前删除最久未使用的数据值，从而为新的数据值留出空间。
进阶：你是否可以在 O(1) 时间复杂度内完成这两种操作？需要注意线程安全问题

Q：编程题3
在微服务的架构下，公司内部会有非常多的独立服务。
服务之间可以相互调用，往往大型应用调用链条很多也很长，我们需要找出耗时最大的链条进行优化。（假设服务同时调用其依赖的下游服务）
例如：
A服务依赖B服务，平均调用延迟100ms，记为(A, B, 100)
其他依赖和延迟如下：
(A, C, 200)
(A, F, 100)
(B, D, 100)
(D, E, 50)
(C, G, 300)
那么服务A有三条调用链：A-B-D-E，A-C-G，A-F，平均延迟250，500，100
延迟最大的调用链是A-C-G，延迟为500ms
输入：
[(A, B, 100), (A, C, 200), (A, F, 100), (B, D, 100), (D, E, 50), (C, G, 300)]
输出：
500
PS：输入可以硬编码，无需实现字符串解析

7 6
1 2 100
1 3 200
1 6 100
2 4 100
4 5 50
3 7 300
*/