#include <iostream> 
using namespace std;
#define int long long
typedef long long ll;

int n, k;
const int N = 1e7 + 43;
int arr[N];

bool good(int m) {
    int cursum = 0;
    int assigned = 1;
    for(int i = 0; i < n; i++) {
        if(arr[i] > m) return false;
        if(cursum + arr[i] > m) {
            assigned++;
            cursum = 0;
        }
        cursum += arr[i];
    }
    return assigned <= k;
}

signed main() {
    cin >> n >> k;
    int sum = 0, max = -1;
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
        sum += arr[i];
        if(arr[i] > max) max = arr[i];
    }
    if(n < k) {
        cout << -1 << endl;
        return 0;
    }
    int l = max-1, r = sum;
    while(r-l > 1) {
        int m = l + (r-l)/2;
        if(good(m)) r = m;
        else l = m;
    }

    cout << r << endl;
    return 0;
}