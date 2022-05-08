#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#define fast ios::sync_with_stdio(false); cin.tie(0);
#define foru(i, k, n) for (int i = k; i < n; i++)
#define ford(i, k, n) for (int i = k; i >= n; i--)
#define ff first
#define ss second

#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>
#include <stack>
#include <set>
#include <map>
#include <deque>
#include <queue>
#include <intrin.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<ll> vi;

const int sz = 2e5 + 5;
int a[sz], b[sz], n;

bool ok(int k) {
    int cur = 1;
    foru(i, 0, n) {
        if (a[i] >= cur - 1 && b[i] >= k - cur) {
            cur++;
        }
        if (cur > k)
            return true;
    }
    return false;
}

void solve() {
    cin >> n;
    foru(i, 0, n)cin >> a[i] >> b[i], swap(a[i], b[i]);
    int l = 1, r = n, mid, bst = 1;
    while (l <= r) {
        mid = (l + r + 1) / 2;
        if (ok(mid)) {
            bst = mid;
            l = mid + 1;
        }
        else r = mid - 1;
    }
    cout << bst << '\n';
}

int main() {
    fast;
    int t;
    cin >> t;
    while (t--)solve();
    return 0;
}