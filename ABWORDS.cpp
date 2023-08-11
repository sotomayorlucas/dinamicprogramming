#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

bool isSimilar(const string& word1, const string& word2) {
    int n = word1.size();
    int m = word2.size();

    // Base case: empty words are similar
    if (n == 0 && m == 0)
        return true;

    // Base case: words have different lengths
    if (n != m)
        return false;

    vector<vector<bool>> dp(n, vector<bool>(n, false));
    dp[0][0] = true;

    for (int len = 1; len <= n; len++) {
        for (int i = 0; i < n - len + 1; i++) {
            int j = i + len - 1;
            
            // Check if the first and last characters match
            if (word1[i] == word2[i] && word1[j] == word2[j]) {
                // Recursive cases
                if (len == 1 || dp[i + 1][j - 1])
                    dp[i][j] = true;

                for (int k = i + 1; k < j; k++) {
                    if ((dp[i][k - 1] && dp[k + 1][j]) ||
                        (dp[i][j - k + i - 1] && dp[k][j]))
                        dp[i][j] = true;
                }
            }
        }
    }

    return dp[0][n - 1];
}

int computeDiversity(const vector<string>& words) {
    int diversity = 0;
    unordered_set<string> uniqueWords;

    for (const string& word : words) {
        bool isUnique = true;
        for (const string& uniqueWord : uniqueWords) {
            if (isSimilar(word, uniqueWord)) {
                isUnique = false;
                break;
            }
        }
        if (isUnique) {
            diversity++;
            uniqueWords.insert(word);
        }
    }

    return diversity;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<string> words(n);
        for (int i = 0; i < n; i++)
            cin >> words[i];

        int diversity = computeDiversity(words);
        cout << diversity << "\n";

        if (t > 0)
            cout << "\n";  // Separar los casos de prueba con una línea vacía
    }

    return 0;
}
