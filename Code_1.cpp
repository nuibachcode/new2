#include <iostream>
#include <algorithm>
#include <vector>
class Job {
	private:
		std::string code;
		double start, finish;
	public:
		Job() {
			code = "";
			start = finish = 0.0;
		}
		Job(std::string code, double start, double finish) {
			this->code = code;
			this->start = start;
			this->finish = finish;
		}
		std::string toString() {
			std::string res = "";
			res += "[Code = ";
			res += code;
			res += ", Start = ";
			res += std::to_string(start);
			res += ", finish = ";
			res += std::to_string(finish);
			res += "]";
			return res;
		}
		double timeWork() {
			return this->finish - this->start;
		}
		bool operator<(const Job& other) {
			return this->finish < other.finish;
		}
		double getStart() const {
			return this->start;
		}
		double getFinish() const {
			return this->finish;
		}
		std::string getCode() const {
			return this->code;
		}
};
double caculate(Job* jobs, int n) {
	if (n == 1) {
		return jobs[0].timeWork();
	}
	return caculate(jobs, n - 1) + jobs[n - 1].timeWork();
}
void next_config(int x[], int k, int i) {
	x[i]++;
	i++;
	while (i <= k) {
		x[i] = x[i - 1] + 1;
		i++;
	}
}
void view_config(Job* jobs, int x[], int k) {
	for (int i = 1; i <= k; ++i) {
		std::cout << jobs[x[i] - 1].getCode() << ' ';
	}
	std::cout << std::endl;
}
void listing_configs(Job* jobs, int k, int n) {
	int i, x[k + 1] = {0};
	for (int i = 1; i <= k; i++) {
		x[i] = i;
	}
	do {
		view_config(jobs, x, k);
		i = k;
		while (i > 0 && x[i] == n - k + i) {
			i--;
		}
		if (i > 0) {
			next_config(x, k, i);
		}
	} while (i > 0);
}
int main() {
	int n = 7;
	Job* jobs = new Job[7];
	jobs[0] = Job("code1", 8, 8.5);
	jobs[1] = Job("code3", 10, 11.5);
	jobs[2] = Job("code7", 14, 14.5);
	jobs[3] = Job("code2", 9, 11);
	jobs[4] = Job("code4", 11, 12.5);
	jobs[5] = Job("code5", 12, 13);
	jobs[6] = Job("code6", 13, 13.5);
	// Cau 1.1:
	std::cout << "Danh sach cac cong viec la:\n";
	for (int i = 0; i < n; ++i) {
		std::cout << jobs[i].toString() << '\n';
	}
	std::cout << "----------------------------------------------------\n";
	// Cau 1.2:
	std::cout << "Tong thoi gian thuc hien tat ca cac cong viec: " << caculate(jobs, n) << '\n';
	std::cout << "----------------------------------------------------\n";
	// Cau 2.1
	std::sort(jobs, jobs + n);
	std::vector<int> ans;
	for (int i = 0; i < n; ++i) {
		Job job = jobs[i];
		bool check = true;
		for (int j = 0; j < (int) ans.size(); ++j) {
			if (job.getFinish() >= jobs[ans[j]].getStart()
			        && job.getStart() <= jobs[ans[j]].getFinish()) {
				check = false;
				break;
			}
		}
		if (check) {
			ans.push_back(i);
		}
	}
	std::cout << "So luong cong viec thuc hien duoc nhieu nhat la: " << (int) ans.size() << '\n';
	std::cout << "Gom cac cong viec la:\n";
	for (int i = 0; i < (int) ans.size(); ++i) {
		std::cout << jobs[ans[i]].toString() << '\n';
	}
	std::cout << "----------------------------------------------------\n";
	// Cau 2.2
	n = 7;
	int r = 5;
	std::sort(jobs, jobs + n,
	[] (const Job &a, const Job &b) {
		return a.getCode() < b.getCode();
	});
	listing_configs(jobs, r, n);
	return 0;
}

