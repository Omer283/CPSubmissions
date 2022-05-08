#define MOD 998244353
#define fast ios::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define foru(i, k, n) for (int i = k; i < n; i++)
#define ford(i, k, n) for (int i = k; i >= n; i--)
#define pb push_back
#define mp make_pair
#define has(mpp, x) mpp.find(x) != mpp.end()
#define nohas(set, x) mpp.find(x) == mpp.end()
#define inc(mpp, x) {if(has(mpp, x)) mpp[x]++; else mpp.insert(mp(x,1));}
#define decc(mpp, x) {if(has(mpp, x)) {if(mpp[x] > 1) mpp[x]--; else mpp.erase(x);}}
#define F first
#define S second
#define um unordered_map
#define us unordered_set
#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include <iomanip>
#include <set>
#include <unordered_set>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <numeric>
#include <bitset>
using namespace std;
const int INF = 1 << 29;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
inline int two(int n) { return 1 << n; }
ll extgcd(ll a, ll b, ll& x, ll& y) { if (b == 0) { x = 1; y = 0; return a; } else { int g = extgcd(b, a%b, y, x); y -= a / b * x; return g; } }
ll modpow(ll a, ll b) { ll res = 1; a %= MOD; for (; b; b >>= 1) { if (b & 1)res = res * a%MOD; a = a * a%MOD; }return res; }
struct custom_hash {
	static uint64_t splitmix64(uint64_t x) {
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}

	size_t operator()(uint64_t x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x + FIXED_RANDOM);
	}
};
struct DisjointSet {
	us<int> fathers;
	vi f, sz;
	DisjointSet(int size) {
		f.resize(size);
		sz.resize(size);
		foru(i, 0, size) {
			f[i] = i;
			sz[i] = i;
			fathers.insert(i);
		}
	}
	int father(int src) {
		while (src != f[src])src = f[src];
		return src;
	}
	bool unite(int a, int b) {
		int fa = father(a), fb = father(b);
		if (sz[fa] < sz[fb])swap(fa, fb);
		if (fa == fb)return false;
		f[fb] = fa;
		sz[fa] = max(sz[fa], sz[fb] + 1);
		return true;
	}
};
struct frac {
	ll a, b;
	frac(int x, int y) {
		if (!y) {
			a = 0;
			b = 0;
		}
		else if (!x) {
			a = 0;
			b = 1;
		}
		else {
			bool neg = (x >= 0) ^ (y >= 0);
			x = abs(x);
			y = abs(y);
			int g = gcd(x, y);
			a = x / g; b = y / g;
			if (neg)a = -a;
		}
	}
	const bool operator<=(const frac& other) const {
		return (a*other.b <= b * other.a);
	}
	const bool operator>=(const frac& other) const {
		return(a*other.b >= b * other.a);
	}
	const bool operator==(const frac& other) const {
		return (*this <= other && *this >= other);
	}
	const bool operator<(const frac& other) const {
		return (a*other.b < b * other.a);
	}
	const bool operator>(const frac& other) const {
		return(a*other.b > b * other.a);
	}
};
struct pt {
	ll x, y;
	pt(): x(0), y(0) {}
	pt(int a, int b): x(a), y(b) {}
	frac slope(pt other) {
		return frac(y - other.y, x - other.x);
	}
	frac offset(pt other) {
		if (x == other.x)return frac(x, 1);
		return frac(y*other.x - other.y*x, other.x - x);
	}
};
struct line {
	frac m, b;
	line() : m(frac(0,0)), b(frac(0,0)) {}
	line(pt p, pt q) : m(p.slope(q)), b(p.offset(q)) {}
	line(frac slope, frac offset): m(slope), b(offset) {}
	const bool operator<=(const line& other) const {
		if (this->m == other.m) return this->b <= other.b;
		return this->m <= other.m;
	}
	const bool operator>=(const line& other) const {
		if (this->m == other.m) return this->b >= other.b;
		return this->m >= other.m;
	}
	const bool operator<(const line& other) const {
		if (this->m == other.m) return this->b < other.b;
		return this->m < other.m;
	}
	const bool operator>(const line& other) const {
		if (this->m == other.m) return this->b > other.b;
		return this->m > other.m;
	}
	const bool operator==(const line& other) const {
		return (this->m == other.m) && (this->b == other.b);
	}
	
};
struct fen{
	vector<ll> fenwick;
	int size;
	fen(int sz) {
		size = sz;
		fenwick.resize(size);
		foru(i, 0, size)fenwick[i] = 0;
	}
	fen(vll arr) {
		size = arr.size();
		fenwick.resize(size);
		foru(i, 0, size)fenwick[i] = 0;
		foru(i, 0, size)update(i, arr[i]);
	}
	void update(int index, ll add) {
		for (int k = index; k < size; k |= (~k & -~k)) {
			fenwick[k] += add;
		}
	}
	ll query(int to) {
		ll sum = 0;
		for (int curr = to + 1; curr > 0; curr ^= (curr & -curr)) {
			sum += fenwick[curr - 1];
		}
		return sum;
	}
	ll rangeQuery(int from, int to) {
		if (!from)return query(to);
		return query(to) - query(from - 1);
	}
	void print() {
		foru(i, 0, size) cout << query(i) << " ";
		cout << endl;
	}
};
struct pretree {
	vll prefix;
	pretree(vll arr) {
		int sz = arr.size();
		prefix.resize(sz, 0);
		foru(i, 0, sz) {
			if (!i)prefix[i] = arr[i];
			else prefix[i] = prefix[i - 1] + arr[i];
		}
	}
	ll query(int i, int j) {
		j = min((size_t)j, prefix.size() - 1);
		if (i > j)return 0;
		if (!i)return prefix[j];
		return prefix[j] - prefix[i - 1];
	}
};
struct segmentree {
	vll segment;
	segmentree(vll arr) {
		int size = arr.size();
		segment.resize(2 * size);
		for (int k = 0; k < size; k++)
			segment[size + k] = arr[k];
		for (int k = size - 1; k > 0; k--)
			segment[k] = segment[2 * k] + segment[2 * k + 1];
	}
	void update(int index, ll val) {
		int size = segment.size();
		int t = index + size;
		segment[t] = val;
		while (t > 1) {
			t /= 2;
			segment[t] = segment[2 * t] + segment[2 * t + 1];
		}
	}
	ll query(int fromIncluded, int toNotIncluded) {
		int size = segment.size();
		ll sum = 0;
		fromIncluded += size;
		toNotIncluded += size;
		while (fromIncluded < toNotIncluded) {
			if (fromIncluded % 2 == 1) {
				sum += segment[fromIncluded];
				fromIncluded++;
			}
			if (toNotIncluded % 2 == 1) {
				sum += segment[toNotIncluded - 1];
				toNotIncluded--;
			}
			fromIncluded /= 2;
			toNotIncluded /= 2;
		}
		return sum;
	}
};
struct trienode {
	char c;
	int cnt, alphabet;
	vector<trienode*> sons;
	trienode() : c(0), cnt(1), alphabet(0) {
		sons.resize(0);
	}
	trienode(char ch, int ab): c(ch), cnt(1), alphabet(ab){
		sons.resize(alphabet);
	}
};
struct trie {
	trienode* head;
	int words, alphabet;
	char firstLetter;
	trie() : head(new trienode()), words(0), alphabet(0), firstLetter(0) { head->cnt = 1; }
	trie(int ab, char first) : head(new trienode('#', ab)), words(0), alphabet(ab), firstLetter(first) { head->cnt = 1; }
	bool insert(string word) {
		int sz = word.length();
		trienode* iter = head;
		foru(i, 0, sz) {
			if (!(iter->sons)[word[i] - firstLetter]) {
				(iter->sons)[word[i] - firstLetter] = new trienode(word[i], alphabet);
			}
			else {
				(iter->sons)[word[i] - firstLetter]->cnt++;
			}
			iter = (iter->sons)[word[i] - firstLetter];
		}
		words++;
		return true;
	}
	int find(string word) {
		int sz = word.size();
		trienode* iter = head;
		foru(i, 0, sz) {
			if ((iter->sons)[word[i] - firstLetter] == nullptr) return 0;
			iter = (iter->sons)[word[i] - firstLetter];
		}
		return iter->cnt;
	}
	bool remove(string word) {
		int sz = word.size();
		trienode* iter = head, *tmp;
		if (!find(word)) return false;
		foru(i, 0, sz) {
			if (!(iter->sons)[word[i] - firstLetter]) return false;
			tmp = iter;
			iter = (iter->sons)[word[i] - firstLetter];
			iter->cnt--;
			if (!iter->cnt) (tmp->sons)[word[i] - firstLetter] = nullptr;
			if (!tmp->cnt) delete tmp;
		}
		if (!iter->cnt) delete iter;
		words--;
		return true;
	}
};
ll mult(ll a, ll b) {
	return ((a % MOD) * (b % MOD)) % MOD;
}
ll add(ll a, ll b) {
	return ((a % MOD) + (b % MOD)) % MOD;
}
ll subtract(ll a, ll b) {
	if (a >= b)return (a - b) % MOD;
	return add(a, -b + ((b - a) / MOD + 1) * MOD);
}
vll divisors(ll n) {
	vll ans;
	for (ll i = 1; i * i <= n; i++) {
		if (n%i) {
			ans.pb(i);
			if (i*i != n)ans.pb(n / i);
		}
	}
	return ans;
}
int customLog(ll b, ll x) {
	int res = -1;
	while (x) {
		res++;
		x /= b;
	}
	return res;
}

string toBinary(int num) {
	string res = "";
	foru(i, 0, 30) {
		res.pb('0' + num % 2);
		num /= 2;
	}
	reverse(res.begin(), res.end());
	return res;
}

ll n;
ll arr[300001], result[300001];
trie t(2, '0');
int main() {
	fast;
	ifstream in("input.txt");
	ofstream out("output.txt");
	cin >> n;
	foru(i, 0, n)cin >> arr[i];
	int k;
	foru(i, 0, n) {
		cin >> k;
		t.insert(toBinary(k));
	}
	foru(i, 0, n) {
		string s = toBinary(arr[i]);
		int curr = 0;
		trienode* iter = t.head;
		foru(j, 0, 30) {
			curr <<= 1;
			switch (s[j]) {
			case '0':
				if (iter->sons[0]) {
					iter = iter->sons[0];
				}
				else {
					curr++;
					iter = iter->sons[1];
				}
				break;
			case '1':
				if (iter->sons[1]) {
					iter = iter->sons[1];
				}
				else {
					curr++;
					iter = iter->sons[0];
				}
				break;
			}
		}
		cout << curr << " ";
		t.remove(toBinary(curr^arr[i]));
	}
	return 0;
}