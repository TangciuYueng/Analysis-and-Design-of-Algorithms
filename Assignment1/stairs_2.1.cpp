#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
/*
* unordered_map��Ϊ��ʹ��tuple<T1, T2, T3>��Ϊkey
* ��Ҫ�Ĺ�ϣ����׼��
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
// tuple<T1, T2, T3>��ϣ����
struct tuple_hash {
	template<class T1, class T2, class T3>
	std::size_t operator()(const std::tuple<T1, T2, T3>& p) const {
		return hash_val(std::get<0>(p), std::get<1>(p), std::get<2>(p));
	}
};
/*
* num_of_ways: ������
* combines: �÷�������Ӧ��(��һ���Ĵ����� �������ĴΣ� ���Ŀ�·��)�ļ���
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
	// ������Ҫ�����������
	if (m <= 0 || n <= 0)
		return 0;
	// �������ֻ��һ��̨��
	if (m == 1) {
		if (n >= 1)
			return 1;
		else
			return 0;
	}
	// �������ֻ�϶���̨��
	if (m == 2) {
		if (n >= 2)
			return 1;
		else
			return 0;
	}

	// dp[i].num_of_waysΪ�ϵ���i��̨�׵ķ�����
	// dp[i].combinesΪ�ϵ���i��̨�׵Ķ�Ӧ��(��һ���Ĵ����� �������Ĵ����� ���Ŀ�·��)�ļ���
	vector<Node> dp(m + 1);
	// ������ǰ����̨�׳�ʼֵ
	dp[1].num_of_ways = 1;
	dp[1].combines.emplace_back(tuple<int, int, int>{ 1, 0, 1 });
	dp[2].num_of_ways = 2;
	dp[2].combines.emplace_back(tuple<int, int, int>{2, 0, 2});
	dp[2].combines.emplace_back(tuple<int, int, int>{0, 1, 3});
	// ����ÿ��̨�׶�Ӧ��unordered_map
	// unordered_map ��hash[i] �洢
	// ((��һ���Ĵ������������Ĵ��������Ŀ�·��)�� ����϶�Ӧ�ķ�����)��ֵ��
	vector< unordered_map<tuple<int, int, int>, int, tuple_hash> > hash(m + 1);
	++hash[1][tuple<int, int, int> { 1, 0, 1 }];
	++hash[2][tuple<int, int, int> { 2, 0, 2 }];
	++hash[2][tuple<int, int, int> { 0, 1, 3 }];

	for (int i = 3; i <= m; ++i) {
		// ��i��ķ����� = ��i - 1�㷽���� + ��i - 2�㷽����
		dp[i].num_of_ways = dp[i - 1].num_of_ways + dp[i - 2].num_of_ways;
		// �洢((��һ���Ĵ������������Ĵ��������Ŀ�·��)��bool)��ֵ��
		unordered_map<tuple<int, int, int>, bool, tuple_hash> is_used;

		// ����һ����һ������
		for (auto& temp : dp[i - 1].combines) {
			int first = get<0>(temp);
			int second = get<1>(temp);
			int third = get<2>(temp);
			// ��i�������µ�(��һ���Ĵ������������Ĵ��������Ŀ�·��)
			tuple<int, int, int> new_tuple = tuple<int, int, int>{ first + 1, second, third + 1 };

			// û��ʹ�ù���Ŀǰnew_tuple��Ӧ������ = ��һ��temp�ķ�����
			if (is_used.find(new_tuple) == is_used.end()) {
				dp[i].combines.emplace_back(new_tuple);
				hash[i][new_tuple] = hash[i - 1][temp];

				is_used[new_tuple] = false;
			}
			// ʹ�ù�������һ��
			else {
				++hash[i][new_tuple];
			}

		}


		// ��������������
		for (auto& temp : dp[i - 2].combines) {
			int first = get<0>(temp);
			int second = get<1>(temp);
			int third = get<2>(temp);
			// ��i�������µ�(��һ���Ĵ������������Ĵ��������Ŀ�·��)
			tuple<int, int, int> new_tuple = tuple<int, int, int>{ first, second + 1, third + 3 };
			// û��ʹ�ù���Ŀǰnew_tuple��Ӧ������ = ��һ��temp�ķ�����
			// ���ｫis_used[new_tuple] = false����Ϊ���ִ���һ���������Ƿ��Ѿ�����ͬ����new_tuple
			if (is_used.find(new_tuple) == is_used.end()) {
				dp[i].combines.emplace_back(new_tuple);
				hash[i][new_tuple] += hash[i - 2][temp];

				is_used[new_tuple] = false;
			}
			// ����һ������������ͬ����tuple��dp[i].combines��������
			else if (is_used[new_tuple] == false) {

				hash[i][new_tuple] += hash[i - 2][temp];

				is_used[new_tuple] = true;
			}
			// �����������������ֹ�ͬ����tuple
			else {
				++hash[i][new_tuple];
			}
		}
		// �޳�n�����ϵ�
		auto it = hash[i].begin();
		while (it != hash[i].end()) {
			if (get<2>(it->first) > n) {
				dp[i].num_of_ways -= it->second;
				hash[i].erase(it++);
			}
			else {
				it++;
			}
		}
	}
	// Ѱ���������Ŀ�·���Ӧ��tuple
	tuple<int, int, int> max_calorie{ 0,0, 0 };
	for (auto& t : dp[m].combines) {
		if (get<2>(t) > get<2>(max_calorie)) {
			max_calorie = t;
		}
	}
	// �ҵ�������϶�Ӧ�ķ�����
	return hash[m][max_calorie];
}

int main() {
	int m, n;
	// ����Ϸ����ж�
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