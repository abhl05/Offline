#include <iostream> 
using namespace std;
#define int long long
typedef long long ll;

const int N = 1e7 + 43;
int arr[N];

signed main() {
    int n, b, m;
    cin >> n >> b;
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cin >> m;
    int k = n/b;
    for(int i = 0; i < n && m; i++) {
        if(arr[i] == 0) {
            bool flag = true;
            if(i%k != 0 && i > 0) {
                if(arr[i-1] == 2 || arr[i-1] == 1) flag = false;
            }
            if(i%k != k-1 && i < n-1) {
                if(arr[i+1] == 2) flag = false;
            }
            if(flag) m--;
        }
    }

    cout << (m == 0 ? "true" : "false")  << endl;

    return 0;
}