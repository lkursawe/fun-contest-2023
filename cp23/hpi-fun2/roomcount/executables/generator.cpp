#include <testlib.h>
#include <bits/stdc++.h>

using namespace std;


const string_view SAMPLE1 = R"(5 8
1 2
1 3
2 3
2 4
2 5
3 4
3 5
4 5
)";

const string_view SAMPLE2 = R"(5 4
3 1
2 5
4 2
4 5
)";

int maxLengthTestcase(int maxSize) {
  int n = maxSize;
  int m = n - 1;

  cout << n << " " << m << endl;

  for (int i = 1; i <= m; i++) {
    cout << i << " " << i + 1 << endl;
  }
  return m;
}

int maxWidthTestcase(int maxSize) {
  int n = sqrt(2 * maxSize);
  int m = n * (n-1) / 2;

  cout << n << " " << m << endl;

  for (int i = 1; i < n; i++) {
    for (int j = i + 1; j <= n; j++) {
      cout << i << " " << j << endl;
    }
  }
  return m;
}

int minTestcase() {
  cout << "2 1" << endl;
  cout << "1 2" << endl;
  return 1;
}

int minTwoComponentsTestcase() {
  cout << "3 1" << endl;
  cout << "2 3" << endl;
  return 1;
}

void intervalGraph(vector<int> &intervalStarts, int intervalLength, vector<pair<int, int>> &edges) {
  vector<int> startIndices(intervalStarts.size());
  iota(startIndices.begin(), startIndices.end(), 0);
  sort(startIndices.begin(), startIndices.end(), [&intervalStarts](int idx1, int idx2) {
    return intervalStarts[idx1] < intervalStarts[idx2];
  });
  for (int i = 0; i < startIndices.size(); i++) {
    int end = intervalStarts[startIndices[i]] + intervalLength;
    int iterator = i + 1;
    while (iterator < startIndices.size() && intervalStarts[startIndices[iterator]] < end) {
      edges.push_back({startIndices[i] + 1, startIndices[iterator] + 1});
      iterator++;
    }
  }
}

int randomTestcase(int intervalLength, int n, int maxStart) {
  vector<int> intervalStarts;
  for (int i = 0; i < n; i++) {
    intervalStarts.push_back(rnd.next(0, maxStart));
  }
  vector<pair<int, int>> edges;
  intervalGraph(intervalStarts, intervalLength, edges);
  shuffle(edges.begin(), edges.end());

  cout << n << " " << edges.size() << endl;
  for (auto& edge : edges) {
    cout << edge.first << " " << edge.second << endl;
  }
  return edges.size();
}

template <class F>
void testcase(string name, string desc, F f) {
    ofstream desc_file(name + ".desc");
    desc_file << desc;
    string in_file = name + ".in";
    freopen(in_file.c_str(), "w", stdout);
    int m = f();
    desc_file << ", m = " << m;
}

void predefined(string name, string desc, string_view content) {
    ofstream desc_file(name + ".desc");
    desc_file << desc;
    string in_file = name + ".in";
    freopen(in_file.c_str(), "w", stdout);
    cout << content;
}

void sample(int num, string_view content) {
    auto num_str = toString(num);
    predefined("sample" + num_str, "Sample #" + num_str, content);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    rnd.setSeed(7889991971352209491ll);

    sample(1, SAMPLE1);
    sample(2, SAMPLE2);

    for (int i = 0; i < 10; i++) {
      int n = rnd.next(100, 1000);
      int intervalLength = rnd.next(5, 150);
      testcase("random_testcase_" + to_string(i),
               "random testcase with interval length = " + to_string(intervalLength) + ", n = " + to_string(n),
               [&n, &intervalLength]() -> int { return randomTestcase(intervalLength, n, n * n / 100); });
    }

    int maxSize = 100000;
    testcase("max_size_length",
             "max length testcase with n = " + to_string(maxSize),
             [&maxSize]() -> int { return maxLengthTestcase(maxSize); });

    testcase("max_size_width",
             "max width testcase with n = " + to_string(maxSize),
             [&maxSize]() -> int { return maxWidthTestcase(maxSize); });

    testcase("max_size_random",
             "max size random testcase with n = " + to_string(maxSize / 10),
             [&maxSize]() -> int { return randomTestcase(100, maxSize / 10, maxSize); });

    testcase("min_size", "min testcase with n = 2", []() -> int { return minTestcase(); });

    testcase("min_two_components", "min testcase with n = 3", []() -> int { return minTwoComponentsTestcase(); });

    return 0;
}
