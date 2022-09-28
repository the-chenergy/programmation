#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ull = uint64_t;
const double PI = 3.141592653589793;
struct node {
  vector<node*> nx = vector<node*>(26, nullptr);
  int i_word = -1;
};
const vector<array<int, 2>> DIRS = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0},
                                    {1, 0},   {-1, 1}, {0, 1},  {1, 1}};
const vector<int> SCORE = {0, 0, 0, 1, 1, 2, 3, 5, 11};
void dfs(int y, int x, node* cr, vector<vector<bool>>& vis, int word_len,
         vector<vector<int>>& board, vector<string>& words,
         vector<bool>& word_used, int& ans_score, string** ans_word,
         int& ans_ct) {
  vis[y][x] = true;
  if (cr->i_word >= 0 && !word_used[cr->i_word]) {
    word_used[cr->i_word] = true;
    string* word = &words[cr->i_word];
    ans_score += SCORE[word_len];
    int ans_len = *ans_word ? (int)(*ans_word)->size() : -1;
    if (word_len > ans_len || (word_len == ans_len && *word < **ans_word)) {
      *ans_word = word;
    }
    ++ans_ct;
  }
  for (auto [dy, dx] : DIRS) {
    int nx_y = y + dy, nx_x = x + dx;
    if (nx_y < 0 || nx_y > 3 || nx_x < 0 || nx_x > 3) continue;
    if (vis[nx_y][nx_x]) continue;
    node* nx = cr->nx[board[nx_y][nx_x]];
    if (nx) {
      dfs(nx_y, nx_x, nx, vis, word_len + 1, board, words, word_used, ans_score,
          ans_word, ans_ct);
    }
  }
  vis[y][x] = false;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n_words;
  cin >> n_words;
  vector<string> words(n_words);
  node* head = new node();
  for (int i_word = 0; i_word < n_words; ++i_word) {
    cin >> words[i_word];
    string& word = words[i_word];
    node* cr = head;
    for (int i = 0; i < (int)word.size(); ++i) {
      int ch = word[i] - 'A';
      if (!cr->nx[ch]) cr->nx[ch] = new node();
      cr = cr->nx[ch];
      if (i == (int)word.size() - 1) cr->i_word = i_word;
    }
  }
  int n_games;
  cin >> n_games;
  while (n_games--) {
    vector<vector<int>> board(4, vector<int>(4));
    for (int y = 0; y < 4; ++y) {
      for (int x = 0; x < 4; ++x) {
        char ch;
        cin >> ch;
        board[y][x] = ch - 'A';
      }
    }
    vector<bool> word_used(n_words);
    int ans_score = 0;
    string* ans_word = nullptr;
    int ans_ct = 0;
    for (int sy = 0; sy < 4; ++sy) {
      for (int sx = 0; sx < 4; ++sx) {
        node* start = head->nx[board[sy][sx]];
        if (!start) continue;
        vector<vector<bool>> vis(4, vector<bool>(4));
        dfs(sy, sx, start, vis, 1, board, words, word_used, ans_score,
            &ans_word, ans_ct);
      }
    }
    cout << ans_score << " " << *ans_word << " " << ans_ct << "\n";
  }
}
