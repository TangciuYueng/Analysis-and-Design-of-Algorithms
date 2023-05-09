#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
/*
* unordered_map中为了使用tuple<T1, T2, T3>作为key
* 需要的哈希函数准备
*/
template<typename T>
inline void hash_combine(std::size_t& seed, const T& val) {
	seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template<typename T>
inline void hash_val(std::size_t& seed, const T& val) {
	hash_combine(seed, val);
}

template<typename T, typename... Types>
inline void hash_val(std::size_t& seed, const T& val, const Types &... args) {
	hash_combine(seed, val);
	hash_val(seed, args...);
}

template<typename... Types>
inline std::size_t hash_val(const Types &... args) {
	std::size_t seed = 0;
	hash_val(seed, args...);
	return seed;
}
// tuple<T1, T2, T3>哈希函数
struct tuple_hash {
	template<class T1, class T2, class T3>
	std::size_t operator()(const std::tuple<T1, T2, T3>& p) const {
		return hash_val(std::get<0>(p), std::get<1>(p), std::get<2>(p));
	}
};
/*
* num_of_ways: 方法数
* combines: 该方法数对应的(走一步的次数， 走两步的次， 消耗卡路里)的集合
*/
struct Node {
	long long num_of_ways;
	vector<tuple<int, int, int>> combines;
	Node() {
		this->num_of_ways = 0;
	}
	Node(const long long& num, vector<tuple<int, int, int>>& v) {
		this->num_of_ways = num;
		this->combines = v;
	}
};

long long stairs(int m, int n) {
	// 不符合要求的输入数据
	if (m <= 0 || n <= 0)
		return 0;
	// 特殊情况只上一个台阶
	if (m == 1) {
		if (n >= 1)
			return 1;
		else
			return 0;
	}
	// 特殊情况只上二个台阶
	if (m == 2) {
		if (n >= 3)
			return 2;
		else if (n >= 2)
			return 1;
		else
			return 0;
	}
	// dp[i].num_of_ways为上到第i个台阶的方法数
	// dp[i].combines为上到第i个台阶的对应的(走一步的次数， 走两步的次数， 消耗卡路里)的集合
	Node dp0, dp1, dp2;
	// 设置上前两个台阶初始值
	dp0.num_of_ways = 1;
	dp0.combines.emplace_back(tuple<int, int, int>{ 1, 0, 1 });
	dp1.num_of_ways = 2;
	dp1.combines.emplace_back(tuple<int, int, int>{2, 0, 2});
	dp1.combines.emplace_back(tuple<int, int, int>{0, 1, 3});
	// 定义每层台阶对应的unordered_map
	// unordered_map 的hash[i] 存储
	// ((走一步的次数，走两步的次数，消耗卡路里)， 该组合对应的方法数)键值对
	unordered_map<tuple<int, int, int>, int, tuple_hash> hash0, hash1, hash2;
	++hash0[tuple<int, int, int> { 1, 0, 1 }];
	++hash1[tuple<int, int, int> { 2, 0, 2 }];
	++hash1[tuple<int, int, int> { 0, 1, 3 }];

	for (int i = 2; i < m; ++i) {
		// 第i层的方法数 = 第i - 1层方法数 + 第i - 2层方法数
		dp2.num_of_ways = dp0.num_of_ways + dp1.num_of_ways;
		// 清空dp2中向量，不需要上一层的干扰
		dp2.combines.clear();
		// 清空hash2中的键值对
		hash2.clear();
		// 存储((走一步的次数，走两步的次数，消耗卡路里)，bool)键值对
		unordered_map<tuple<int, int, int>, bool, tuple_hash> is_used;

		// 从上一层走一步上来
		for (auto& temp : dp1.combines) {
			int first = get<0>(temp);
			int second = get<1>(temp);
			int third = get<2>(temp);
			// 第i层增加新的(走一步的次数，走两步的次数，消耗卡路里)
			tuple<int, int, int> new_tuple = tuple<int, int, int>{ first + 1, second, third + 1 };

			// 没有使用过，目前new_tuple对应方法数 = 上一层temp的方法数
			if (is_used.find(new_tuple) == is_used.end()) {
				dp2.combines.emplace_back(new_tuple);
				hash2[new_tuple] = hash1[temp];

				is_used[new_tuple] = false;
			}
			// 使用过，增加一种
			else {
				++hash2[new_tuple];
			}

		}


		// 从上两层走上来
		for (auto& temp : dp0.combines) {
			int first = get<0>(temp);
			int second = get<1>(temp);
			int third = get<2>(temp);
			// 第i层增加新的(走一步的次数，走两步的次数，消耗卡路里)
			tuple<int, int, int> new_tuple = tuple<int, int, int>{ first, second + 1, third + 3 };
			// 没有使用过，目前new_tuple对应方法数 = 上一层temp的方法数
			// 这里将is_used[new_tuple] = false意义为区分从上一层走上来是否已经出现同样的new_tuple
			if (is_used.find(new_tuple) == is_used.end()) {
				dp2.combines.emplace_back(new_tuple);
				hash2[new_tuple] += hash0[temp];

				is_used[new_tuple] = false;
			}
			// 从上一层走上来出现同样的tuple，dp[i].combines无需增加
			else if (is_used[new_tuple] == false) {

				hash2[new_tuple] += hash0[temp];

				is_used[new_tuple] = true;
			}
			// 从上两层走上来出现过同样的tuple
			else {
				++hash2[new_tuple];
			}
		}
		// 剔除n不符合的
		auto it = hash2.begin();
		while (it != hash2.end()) {
			if (get<2>(it->first) > n) {
				dp2.num_of_ways -= it->second;
				hash2.erase(it++);
			}
			else {
				it++;
			}
		}

		// 循环使用变量
		dp0.num_of_ways = dp1.num_of_ways;
		dp0.combines = dp1.combines;
		hash0 = hash1;

		dp1.num_of_ways = dp2.num_of_ways;
		dp1.combines = dp2.combines;
		hash1 = hash2;
	}

	return dp2.num_of_ways;
}

int main() {

	int m, n;
	// 输入合法性判断
	while (1) {
		cout << "input: ";
		cin >> m >> n;
		if (cin.fail()) {
			cout << "INPUT ERROR" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else
			break;
	}
	cout << "output: " << stairs(m, n) << endl;
	cout << "press any key to exit" << endl;
	cin.ignore(1024, '\n');
	cin.get();

	
	return 0;
}