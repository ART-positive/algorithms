// разбиение строки на минимальное число полиндромов за O(n*log(n))
// https://codeforces.com/blog/entry/19193

//Поиск длиннейшей подстроки-палиндрома O(n)
string longestPalindrome(const string &s){
    vector<char> s2(s.size() * 2 + 1, '#');
    //создаем псевдостроку с границами в виде символа '#'
    for(int i = 0; i != s.size(); ++i){
        s2[i*2 + 1] = s[i];
    }

    int p[s2.size()];
    int r, c, index, i_mir;
    int maxLen = 1;
    i_mir = index = r = c = 0;

    for(int i = 1; i != s2.size() - 1; ++i){
        i_mir = 2*c-i;

        // Если мы попадаем в пределы радиуса прошлого результата,
        // то начальное значение текущего радиуса можно взять из зеркального результата
        p[i] = r > i ? min(p[i_mir], r-i) : 0;

        while(i > p[i] && (i + p[i] + 1) < s2.size() && s2[i - p[i] - 1] == s2[i + p[i] + 1])
            ++p[i];

        if(p[i] + i > r){
            c = i;
            r = i + p[i];
        }

        if(maxLen < p[i]){
            maxLen = p[i];
            index = i;
        }
    }

    // Отображаем найденные позиции на оригинальную строку
    return s.substr((index-maxLen)/2, maxLen);
}

//Количество всех полиндромных подпоследовательностей O(n^2)
int countPS(string &s) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Every single character is a palindrome,
    // so initialize diagonal elements
    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }

    // Fill the table for substrings of length greater than 1
    for (int length = 2; length <= n; length++) {
        for (int i = 0; i <= n - length; i++) {
            int j = i + length - 1;
            if (s[i] == s[j]) {
                dp[i][j] = dp[i+1][j] + dp[i][j-1] + 1;
            } else {
                dp[i][j] = dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1];
            }
        }
    }

    return dp[0][n-1];
}

// длина наибольшей полиндромной подпоследовательности O(n^2)
int lps(const string &s){
    int n = s.size();

    // Create two vectors: one for the current state (dp)
    // and one for the previous state (dpPrev)
    vector<int> dp(n), dpPrev(n);

    // Loop through the string in reverse (starting from the end)
    for (int i = n - 1; i >= 0; --i){

        // A single character is always a palindrome of length 1
        dp[i] = 1;

        // Loop through the characters ahead of i
        for (int j = i + 1; j < n; ++j){

            // If the characters at i and j are the same
            if (s[i] == s[j]){

                // Add 2 to the length of the palindrome between them
                dp[j] = dpPrev[j - 1] + 2;
            }
            else{

                // Take the maximum between excluding either i or j
                dp[j] = max(dpPrev[j], dp[j - 1]);
            }
        }

        // Update dpPrev to the current state of dp
        // for the next iteration
        dpPrev = dp;
    }

    // Answer is the length of longest palindromic subsequence
    // in entire string
    return dp[n - 1];
}

// выводит максимальный полиндром из подпоследовательности на [l, r] за предпосчёт f - O(n^2), prnt - O(n)
string s = "GEEKSFORGEEKS";
int dp[1000][1000];
//Функция f вычисляет длину палиндрома наибольшей длины, который можно получить из строки s[i .. j] и запоминает это значениек в dp[i][j].
int f(int i, int j) {
  if (i > j) return 0;
  if (i == j) return 1;
  if (dp[i][j] != -1) return dp[i][j];
  if (s[i] == s[j])
    return dp[i][j] = f(i + 1, j - 1) + 2;
  else
    return dp[i][j] = max(f(i + 1, j), f(i, j - 1));
}
//Функция print выводит палиндром наибольшей длины, который можно получить из строки s[i .. j]. Используются ранее вычиленные значения массива dp.
void prnt(int i, int j) {
  if (i > j) return;
  if (i == j){
    cout<< s[i];
    return;
  }
  if (s[i] == s[j]){
    cout<< s[i];
    prnt(i + 1, j - 1);
    cout<< s[j];
  }
  else{
    if (dp[i + 1][j] > dp[i][j - 1])
      prnt(i + 1, j);
    else
      prnt(i, j - 1);
  }
}
//memset(dp, -1, sizeof(dp));
//f(1, s.size());
//prnt(1, s.size()); //[l, r]

// количество всех подполиндромов длины k за O(n*n*k)
ll solve(string &s,ll i,ll j,ll k,vector<vector<vector<ll>>> &dp){
    if(k == 0) return 1;
    if(i > j) return 0;
    if(dp[i][j][k] != -1){
        return dp[i][j][k];
    }
    if(k == 1){
        return dp[i][j][k] = j - i + 1;
    }
    ll ans = 0;
    if(i < j && s[i] == s[j]){
        ans = solve(s,i+1,j-1,k-2,dp);
    }
    ans += solve(s,i+1,j,k,dp) + solve(s,i,j-1,k,dp) - solve(s,i+1,j-1,k,dp);
    return dp[i][j][k] = ans;
}
//vector<vector<vector<ll>>> dp(n,vector<vector<ll>>(n,vector<ll>(k+1,-1)));
//ll ans = solve(s,0,n-1,k,dp); //s - string, n = s.size();
