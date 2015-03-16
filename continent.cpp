#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Grid {
public:
	Grid(int m, int n, int* cont) : m_(m), n_(n){
		continent_.resize(m);
		for (int i = 0; i < m; ++i) {
			continent_[i].resize(n);
		}
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				continent_[i][j] = cont[i * n + j];
			}
		}
		index_p_ = 0;
		index_a_ = 0;
	}
	vector<pair<int, int>> GetGrid() {
		InitBFS();
	}
	void print() {
		for (int i = 0; i < m_; ++i) {
			for (int j = 0; j < n_; ++j) {
				cout << continent_[i][j] << " ";
			}
			cout << endl;
		}
	}

private:
	int m_, n_;
	int index_p_, index_a_;
	vector<vector<int>> continent_;
	vector<pair<int, int>> pacific_;
	vector<pair<int, int>> atlantic_;
	map<pair<int, int>, bool> m_pacific_;
	map<pair<int, int>, bool> m_atlantic_;
	void InitBFS() {
		for (int i = 0; i < n_; ++i) {
			pacific_.push_back(make_pair(0, i));
			m_pacific_[pacific_.back()] = true;
			atlantic_.push_back(make_pair(m_ - 1, i));
			m_pacific_[atlantic_.back()] = true;
		}
		for (int i = 0; i < m_; ++i) {
			pacific_.push_back(make_pair(i, 0));
			m_pacific_[pacific_.back()] = true;
			atlantic_.push_back(make_pair(i, n_ - 1));
			m_pacific_[atlantic_.back()] = true;
		}
	}
	void BFS() {
		while (index_p_ < pacific_.size()) {
			int first = pacific_[index_p_].first;
			int second = pacific_[index_p_].second;
			// 访问上
			if (first - 1 >= 0 &&
				m_pacific_[make_pair(first-1, second)] != true &&
				continent_[first][second] >= continent_[first-1][second]) {
				pacific_.push_back(make_pair(first - 1, second));
				m_pacific_[pacific_.back()] = true;
			}

			// 访问下
			if (first + 1 < m_ &&
				m_pacific_[make_pair(first + 1, second)] != true &&
				continent_[first][second] >= continent_[first + 1][second]) {
				pacific_.push_back(make_pair(first + 1, second));
				m_pacific_[pacific_.back()] = true;
			}

			// 访问左
			if (second - 1 >= 0 &&
				m_pacific_[make_pair(first, second - 1)] != true &&
				continent_[first][second] >= continent_[first][second - 1]) {
				pacific_.push_back(make_pair(first, second - 1));
				m_pacific_[pacific_.back()] = true;
			}

			// 访问右
			if (second + 1 < m_ &&
				m_pacific_[make_pair(first, second + 1)] != true &&
				continent_[first][second] >= continent_[first][second + 1]) {
				pacific_.push_back(make_pair(first, second + 1));
				m_pacific_[pacific_.back()] = true;
			}
		}
	}
};

int main() {
	int input[] = {1,1,2,2,5,
	               2,2,3,4,5,
                   3,1,3,6,5,
	               2,3,4,5,3,
	               1,2,4,5,6};
	Grid grid(5, 5, input);
	grid.print();
}