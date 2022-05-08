#define fast ios::sync_with_stdio(false); cin.tie(0)
#define foru(i, k, n) for (int i = k; i < n; i++)
#define ford(i, k, n) for (int i = k; i >= n; i--)
#define pb push_back
#define mp make_pair

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int sz = 3e5;
ll cnt[sz];


void solve() {
	ll n, x, y, z;
	cin >> n;
	foru(i, 0, 101)cnt[i] = 0;
	foru(i, 0, n) {
		cin >> x;
		cnt[x]++;
	}
	ll lw = 0, hg = 0;
	bool low = 1;
	foru(i, 0, 101) {
		if (low) {
			if (cnt[i] >= 2) {
				lw++;
				hg++;
			}
			else if (cnt[i] == 1) {
				low = 0;
				hg++;
			}
			else break;
		}
		else {
			if (cnt[i])hg++;
			else break;
		}
	}
	cout << lw + hg << endl;
}


int main() {
	fast;
	int t;
	cin >> t;
	while (t--)solve();
	return 0;
}