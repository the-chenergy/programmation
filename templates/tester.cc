#define SYNC_IO 1
#undef LOCAL
#define LOCAL 1
#define NO_MAIN 1

#include "solution.cc"  // Change this to your solution's file name

streambuf* old_cin;
streambuf* old_cout;
streambuf* old_cerr;
stringstream my_in, my_out, my_err;
clock_t total_test_time;

void test(int test_id) {
    my_in.str(""), my_out.str(""), my_err.str("");
    my_in.clear(), my_out.clear(), my_err.clear();

    // Generate and feed input into my_in
    int n = 2;
    my_in << n << "\n";
    

    auto in_content = my_in.str();
    my_in.str(in_content);
    if (test_id != 0) cerr.rdbuf(my_err.rdbuf());
    auto start_time = clock();

    // Run solution
    solve_suite();

    total_test_time += clock() - start_time;
    cerr.rdbuf(old_cerr);
    auto out_content = my_out.str();
    my_out.str(out_content);

    // Read and validate output from my_out
    // auto actual = vector<int>();
    

    // auto expected = vector<int>();
    // if (expected == actual) return;
    // Return when test passes; handle failure and print info below
    cerr << "Input:\n"
         << in_content << "\nActual output (cout):\n"
         << out_content << "\nDebug output (cerr):\n"
         << my_err.str() << "\n";
    fprintf(stderr, "FAILED TEST #%i\n", test_id);
    // trace(expected, actual);
    exit(1);
}

int main() {
    srand(0);
    int num_tests = 1;
    // cin >> num_tests;
    old_cin = cin.rdbuf(my_in.rdbuf());
    old_cout = cout.rdbuf(my_out.rdbuf());
    old_cerr = cerr.rdbuf();
    for (int test_id = 1; test_id <= num_tests; test_id++) {
        test(test_id);
        if (__builtin_popcount(test_id) == 1 || test_id == num_tests) {
            fprintf(stderr, "Passed %i test%c (%.2LF s)\n", test_id,
                    "s"[test_id == 1],
                    ld(total_test_time) / CLOCKS_PER_SEC / test_id);
        }
    }
    return 0;
}
