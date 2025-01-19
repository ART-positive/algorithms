//Пример
#define ld __float128
//#define ld long double
//#define __float128 long double
//#define endl "\n"
using ll = long long;
const int inf = 2e9;    
 
const ll MOD = 998244353;
 
using namespace std;
 
__float128 abst(__float128 x){
        return x < 0 ? x * -1 : x;  // Not ideal but no builtin for 128
    }
/*
ld calculate_expectation(long long n, long long k) {
    ld expectation = (k + 1) / 2.0; // Начальное значение E(1, k)
    for (long long i = 2; i <= n; ++i) {
        ld new_expectation = 0.0;
        long long threshold = static_cast<long long>(expectation); // Порог, где x >= E
        new_expectation += threshold * expectation; // x < E
        new_expectation += (k * (k + 1)) / 2.0 - (threshold * (threshold + 1)) / 2.0; // x >= E
        new_expectation /= k; // Делим на количество граней
        
        if((__float128)abst((__float128)(expectation - new_expectation)) < (__float128)(1e-18)) {
            expectation = new_expectation;
            break;
        }
        expectation = new_expectation;
    }
    
    return expectation;
}
 
ld calculate_expectation2(long long n, long long k) {
    ld expectation = (k + 1) / 2.0; // Начальное значение E(1, k)
    
    long long iterations = min(n, k); // Ограничиваем вычисления
    for (long long i = 2; i <= iterations; ++i) {
        double threshold = expectation; // Пороговое значение
        long long t = static_cast<long long>(threshold); // Округление вниз
        
        // Сумма для x < threshold
        ld sum_less = t * expectation; // Используем только актуальные грани
        
        // Сумма для x >= threshold
        ld sum_greater;
        if (t < n) {
            // Если t меньше n, учитываем только до n
            sum_greater = (n * (n + 1)) / 2.0 - (t * (t + 1)) / 2.0;
        } else {
            // Все остальные грани равны самому E
            sum_greater = 0;
        }
        
        // Общее новое ожидание
        expectation = (sum_less + sum_greater) / k;
        
        // Прекращаем, если ожидание стабилизировалось
        //if (fabs(expectation - threshold) < 1e-9) {
        //    break;
        //}
    }
    
    return expectation;
}
*/
ld calculate_expectation3(long long n, __float128 k) {
    ld expectation = (k + 1) / 2.0; // Начальное значение E(1, k)
    const ld epsilon = 1e-9; // Порог точности
    deque<ld> q;
    for (long long i = 2; i <= n; ++i) {
        ld new_expectation = 0.0;
        ld threshold = static_cast<long long>(expectation); // Порог, где x >= E
        new_expectation += threshold * expectation; // x < E
        new_expectation += (k * (k + 1)) / 2.0 - (threshold * (threshold + 1)) / 2.0; // x >= E
        new_expectation /= k; // Делим на количество граней
        ld p = 0;
        if(n > 1000 && !q.empty()) {
            p = q.front();
            q.pop_front();
        }
        q.push_back(new_expectation);
        if((__float128) abst( (__float128)(p - new_expectation)) < (__float128)(1e-12)) {
            return new_expectation;
        }
        expectation = new_expectation;
    }
    
    return expectation;
}
 
void solve() {
    ll n, k; cin>> n >> k;
    //if(n <= 100000000) cout << fixed << setprecision(10) << (long double)(calculate_expectation(n, k)) << endl;
    //else cout << fixed << setprecision(10) << (long double)(calculate_expectation2(n, k)) << endl;
    cout << fixed << setprecision(10) << (long double)(calculate_expectation3(n, k)) << endl;
    //cout<< (long double)(1e-10);
    //else cout << fixed << setprecision(10) << calculate_expectation2(n, k) << endl;
}
 
