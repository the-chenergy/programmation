/* Solution to Frankenstein's Monster, a problem from NUS Competitive
   Programming.

   I made the first ever accepted submission to this problem on Kattis
   (https://open.kattis.com/problems/frankensteinsmonster). Before my acceptance
   there were some 300 incorrect submissions made by 6 other (rather hard-core)
   users. This file is a rewrite of my original solution, where I added
   commentaries and removed a ton of debugging junk.

   The problem admittedly looks incredibly intimidating upon first look. Chess
   has been known in general to be very complex and rich, especially where there
   can be outrageously huge numbers of possibilities achieved in just a few
   moves. However, in this problem, much of that complexity has been taken out
   by the mere number of pieces on board and the lack of pawns and therefore
   promotions. Particularly when considering the number of possible positions
   brought by just three pieces, there could only be 64**3 = 2**18 of them,
   directly enabling a complete search to be used to evaluate all positions.

   In concept though, this problem is very similar to the Cop vs Robber problem
   a.k.a. Cat vs Mouse problem. You have a graph and two players alternating
   making moves. You define some positions to be decided won or lost, and you
   try to find for any given position whether it's drawn or won for one player.
   Upon constructing the state space, this problem is known to have an O(V + E)
   DP solution. V is the number of states (usually O(nodes in the graph **
   number of players)), and E is the total number of transitions (or about O(V *
   average number of legal moves from one position)). For instance, in our case,
   if the black king and two white queens were present, each queen would have
   at most about 27 options, making the total runtime O(27 * 64**3) (replace 27
   with the real average, but that's the upper bound).

   Read below to see how I did it. There might exist opportunities for
   optimizations but I'm too tired to think about those now. */

#include <bits/stdc++.h>
using namespace std;

int main() {
    using Square = complex<int>;
    using Pos = array<Square, 3>;

    /* A position can be described by the locations of the 3 pieces,
       {black_king, white_piece1, white_piece2}. Two pieces may share the same
       square, which represents a capture. */
    char pieces[3] = {'K'};
    Pos init_pos = {};

    /* Read the initial position. */
    for (int i = 0, y = 7; y >= 0; y--) {
        for (int x = 0; x <= 7; x++) {
            char c;
            cin >> c;
            if (c == '.') continue;
            if (c == 'k') {
                init_pos[0] = {x, y};
            } else {
                i++;
                pieces[i] = c;
                init_pos[i] = {x, y};
            }
        }
    }

    /* Helper function to move a piece, optionally allowing it to "go through"
       other pieces for the purpose of checking what squares it's attacking.

       (The problem statement said a piece's movement cannot be obstructed, but
       not its attack. This means pieces do attack through other pieces and
       kings cannot enter those X-ray-visioned squares either.)

       A callback is invoked for each move generated. The callback can return 1
       to halt the move search (useful when one needed move has been found, e.g.
       a capture). */
    auto move_piece = [&](Pos& pos, int i, int thru, auto&& callback) -> int {
        auto src = pos[i];

        auto move_in_dirs = [&](initializer_list<Square> dirs) -> int {
            int unlimited = pieces[i] != 'K' && pieces[i] != 'N';
            for (auto d : dirs) {
                int steps = 1;
                do {
                    auto dest = src + steps * d;
                    if (dest.real() < 0 || dest.real() > 7 || dest.imag() < 0 ||
                        dest.imag() > 7) {
                        break;
                    }
                    if (i && !thru && dest == pos[i == 1 ? 2 : 1]) {
                        /* A white piece moves into another white piece. */
                        if (dest != pos[0]) {
                            break;
                            /* If black king is also there, then black had
                               captured the other white piece, and now we allow
                               this white move to be valid for the purpose of
                               checking whether black's capture was safe (which
                               is not because now white is capturing the
                               black king). */
                        }
                    }
                    if (callback(dest)) return 1;
                    if (i && dest == pos[0]) {
                        /* A white piece moves into the black king. */
                        break;
                    }
                    steps++;
                } while (unlimited);
            }
            return 0;
        };

        if (pieces[i] == 'N') {
            return move_in_dirs({
                    {1, 2},
                    {2, 1},
                    {2, -1},
                    {1, -2},
                    {-1, -2},
                    {-2, -1},
                    {-2, 1},
                    {-1, 2},
            });
        }

        if (pieces[i] != 'B') {
            if (move_in_dirs({{0, 1}, {1, 0}, {0, -1}, {-1, 0}})) return 1;
        }
        if (pieces[i] != 'R') {
            return move_in_dirs({{1, 1}, {1, -1}, {-1, -1}, {-1, 1}});
        }

        return 0;
    };

    /* Helper function to check if piece i is being attacked. */
    auto piece_attacked = [&](Pos& pos, int i) -> int {
        if (i) {
            auto d = pos[i] - pos[0];
            return abs(d.real()) <= 1 && abs(d.imag()) <= 1;
        }
        for (int j : {1, 2}) {
            int found = move_piece(pos, j, 1, [&](Square dest) -> int {
                return dest == pos[0];
            });
            if (found) return 1;
        }
        return 0;
    };

    /* Helper function to generate all legal moves from a position for a side.
       The callback receives the moved piece's index, its target square, and the
       resulting new position. */
    auto move_pos = [&](Pos& pos, int side, auto&& callback) -> int {
        initializer_list<int> black = {0}, white = {1, 2};
        for (int i : side ? black : white) {
            int halted = move_piece(pos, i, 0, [&](Square dest) -> int {
                auto new_pos = pos;
                new_pos[i] = dest;
                if (pieces[i] == 'K' && piece_attacked(new_pos, i)) {
                    return 0;
                    /* The problem statement only mentioned that the king must
                       not move to a square being attacked but didn't say that
                       the move must not leave the king in check (like in the
                       normal rules). So if the initial position has a white
                       king in check, white is allowed to move their other
                       piece (as long as that's not a king walking into check)
                       and is not obligated to move the king away. */
                }
                return callback(i, dest, new_pos);
            });
            if (halted) return 1;
        }
        return 0;
    };

    /* Perform our main search to evaluate each state. (A state constitutes a
       position and a side, whose turn it is.) */

    const int bits_per_square = 6, num_pos = 1 << (bits_per_square * 3);

    /* Records the positions that can reach a particular position after one
       legal move. */
    static vector<int> rev_nei[num_pos][2];
    /* Used by the BFS to know when a state becomes a losing state due to all of
       its out-neighbors determined to be winning. */
    static int deg[num_pos][2], vis[num_pos][2];
    /* Records the best result from each state (1 win, 0 draw, -1 loss). */
    static int res[num_pos][2];
    /* Records the doomsday clock (minimum remaining half-moves with best play)
       for each state. */
    static int tim[num_pos][2];

    deque<pair<int, int>> bfs; /* {pos, side} */

    /* Helper functions to add states to the search. */

    auto pos_to_id = [&](Pos& pos) -> int {
        int id = 0;
        for (int i : {0, 1, 2}) {
            int p = pos[i].real() * 8 + pos[i].imag();
            id |= p << (bits_per_square * i);
        }
        return id;
    };
    auto pos_from_id = [&](int id) -> Pos {
        Pos pos;
        for (int i : {0, 1, 2}) {
            int p = id >> (bits_per_square * i) & ((1 << bits_per_square) - 1);
            pos[i] = {p / 8, p % 8};
        }
        return pos;
    };
    auto mark_won = [&](int pos_id, int side, int t) -> void {
        if (vis[pos_id][side]) return;
        vis[pos_id][side] = 1;
        res[pos_id][side] = 1;
        tim[pos_id][side] = t;
        bfs.push_front({pos_id, side});
    };
    auto mark_lost = [&](int pos_id, int side, int t, int known = 0) -> void {
        if (vis[pos_id][side]) return;
        tim[pos_id][side] = max(tim[pos_id][side], t);
        if (known || !--deg[pos_id][side]) {
            vis[pos_id][side] = 1;
            res[pos_id][side] = -1;
            bfs.push_back({pos_id, side});
        }
    };

    /* Initialize the search by finding the reversed moves for each position as
       well as the end states (the known won or lost positions). */
    const int init_id = pos_to_id(init_pos);
    for (int pos_id = 0; pos_id < num_pos; pos_id++) {
        Pos pos = pos_from_id(pos_id);

        if (pos[0] == pos[1] || pos[0] == pos[2]) {
            /* Any capture will result in black winning. (Capturing the black
               king is not prohibited by the problem's rules, but that leaves
               black in stalemate.) */
            mark_won(pos_id, 1, 0);
            mark_lost(pos_id, 0, 0, 1);
            continue;
        }

        /* Populate the reversed neighbors. */
        for (int side : {0, 1}) {
            move_pos(pos, side, [&](int, Square, Pos& new_pos) -> int {
                deg[pos_id][side]++;
                int new_id = pos_to_id(new_pos);
                rev_nei[new_id][side].push_back(pos_id);
                return 0;
            });
        }

        if (pos_id != init_id && !deg[pos_id][1]) {
            /* Black cannot move (checkmated or stalemated); the game has
               decided.

               The problem's rules say a player can only be checkmated on their
               turn, so we exclude the initial position from this check because
               initially it's white to move and not black's turn. (White has not
               won and must still move in case the game does start with a
               checkmate.) */
            if (piece_attacked(pos, 0)) {
                mark_won(pos_id, 0, 0);
                mark_lost(pos_id, 1, 0, 1);
            } else {
                mark_won(pos_id, 1, 0);
                mark_lost(pos_id, 0, 0, 1);
            }
        }
    }

    /* Propagate the state graph with results reasoned from the known states.
       The general idea here is, a state is winning if it can lead to at least
       one losing state, and it's losing if it can only lead to winning states.
       So if a state is losing, we can mark all of its reversed neighbors as
       winning. If it's winning, we can use the `deg` array to keep track of how
       many out-neighbors to go until all of a state's out-neighbors are
       determined winning. */
    while (bfs.size()) {
        auto [pos, side] = bfs.front();
        bfs.pop_front();
        for (int old_pos : rev_nei[pos][!side]) {
            if (res[pos][side] < 0) {
                mark_won(old_pos, !side, tim[pos][side] + 1);
            } else {
                mark_lost(old_pos, !side, tim[pos][side] + 1);
            }
        }
    }

    /* Play the game. */

    Pos cur_pos = init_pos;
    int cur_id = init_id;

    if (res[cur_id][0] <= 0) {
        cout << "no-win\n";
        exit(0);
    }

    cout << "win\n" << tim[cur_id][0] / 2 + 1 << "\n";
    while (1) {
        /* Make the best next move. */
        int won = 0;
        auto process_move = [&](int i, Square dest, Pos& new_pos) -> int {
            int new_id = pos_to_id(new_pos);
            if (res[new_id][1] >= 0 || tim[new_id][1] >= tim[cur_id][0]) {
                return 0;
            }

            auto square_string = [&](Square s) -> string {
                return {char(s.real() + 'a'), char(s.imag() + '1')};
            };
            auto src = cur_pos[i];
            cout << pieces[i] << " " << square_string(src) << " "
                 << square_string(dest) << "\n";
            won = !tim[new_id][1];
            cur_pos = new_pos;
            return 1;
        };
        move_pos(cur_pos, 0, process_move);
        if (won) break;

        /* Read the opponent's move. */
        string s;
        cin >> s >> s >> s;
        cur_pos[0] = {s[0] - 'a', s[1] - '1'};
        cur_id = pos_to_id(cur_pos);
    }
}
