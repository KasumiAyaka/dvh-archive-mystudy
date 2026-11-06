// 2023/9/5
// kasumi
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <set>
#include <map>
#include<utility>//make_pair
#include <chrono>
#include<algorithm>
#include<iomanip>

struct Key {
	int pl, id;
};
bool operator<(const Key& lhs, const Key& rhs) {
	return std::tie(lhs.pl, lhs.id) < std::tie(rhs.pl, rhs.id);
}

struct ShifterTrack {
	int RawId, pl;
	double ax, ay, x, y;
};

std::vector<std::string> StringSplit(std::string str);
std::vector<std::string> StringSplit_with_tab(std::string str);


void SetList(std::string input, std::map<int,int>& list);
void ShifterBasetrack(std::string input, std::map <int,int>& list, std::string output);

int main(int argc, char** argv) {
	if (argc != 4) {
		fprintf(stderr, "Usage:prg in_shifter-basetrack.txt list.txt output_file\n");
		exit(1);
	}

	std::string in_basetrack = argv[1];//muon_ecc5_including_multi_w_cosmic
	std::string in_list = argv[2];//OSS basetrack
	std::string output_file = argv[3];//output
	auto start = std::chrono::system_clock::now();//for measure working time

	std::map<int,int> list;
	SetList(in_list, list);
	ShifterBasetrack(in_basetrack, list, output_file);


	{
		auto end = std::chrono::system_clock::now();
		auto dur = end - start;
		auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
		std::cout << msec << " milli sec \n";
		if (msec / 1000 < 1001) {
			std::cout << msec / 1000 << "sec\n";
		}
		else if (msec / 1000 / 60 < 60) {
			std::cout << msec / 1000 / 60 << "min" << msec % 1000 << "sec\n";
		}
		else if (msec / 1000 / 3600 < 24) {
			std::cout << msec / 1000 / 60 / 60 << "h" << msec % 60000 << "m\n";
		}
		//getchar();


	}
}
void SetList(std::string input, std::map <int, int>& list) {
	std::ifstream ifs(input);
	if (!ifs) {
		std::cerr << "error" << std::endl;
		exit(1);
	}

	std::string str;					//1strein into
	std::vector<std::string> str_v;		//input 1 ward
	std::string buffer;
	Key k;//RawId flg
	while (std::getline(ifs, str)) {
		str_v = StringSplit_with_tab(str);
		k.pl = std::stoi(str_v[0]);//Rawid
		k.id = std::stoi(str_v[1]);//flg

		list.insert(std::make_pair(k.pl,k.id));
	}

}

void ShifterBasetrack(std::string input, std::map <int, int>& list, std::string output) {
	std::ifstream ifs(input);
	if (!ifs) {
		std::cerr << "error" << std::endl;
		exit(1);
	}

	int count = 0;
	std::string str;					//1strein into
	std::vector<std::string> str_v;		//input 1 ward
	std::string buffer;


	Key k;
	std::ofstream ofs(output);
	int c = 0;
	while (std::getline(ifs, str)) {
		str_v = StringSplit_with_tab(str);
		k.pl = std::stoi(str_v[0]);
		k.id = std::stoi(str_v[1]);

		
		if (list.find(k.pl) != list.end()) {

			ofs << std::right << std::fixed
				<< std::setw(3) << std::setprecision(0) << 1 << " "
				<< std::setw(3) << std::setprecision(0) << k.id << " "//muon flg
				<< std::setw(20) << std::setprecision(0) << std::stoi(str_v[0]) << " "//Rawid
				<< std::setw(4) << std::setprecision(0) << std::stoi(str_v[1]) << " "//pl
				<< std::setw(10) << std::setprecision(4) << std::stod(str_v[2]) << " "//ax
				<< std::setw(10) << std::setprecision(4) << std::stod(str_v[3]) << " "//ay
				<< std::setw(10) << std::setprecision(1) << std::stod(str_v[4]) << " "//x
				<< std::setw(10) << std::setprecision(1) << std::stod(str_v[5]) << " "//y
				<< std::endl;
		}
		else {
			ofs << std::right << std::fixed
				<< std::setw(3) << std::setprecision(0) << -1 << " "
				<< std::setw(3) << std::setprecision(0) << k.id << " "//muon flg
				<< std::setw(20) << std::setprecision(0) << std::stoi(str_v[0]) << " "//Rawid
				<< std::setw(4) << std::setprecision(0) << std::stoi(str_v[1]) << " "//pl
				<< std::setw(10) << std::setprecision(4) << std::stod(str_v[2]) << " "//ax
				<< std::setw(10) << std::setprecision(4) << std::stod(str_v[3]) << " "//ay
				<< std::setw(10) << std::setprecision(1) << std::stod(str_v[4]) << " "//x
				<< std::setw(10) << std::setprecision(1) << std::stod(str_v[5]) << " "//y
				<< std::endl;
		}
	}

}





std::vector<std::string> StringSplit_with_tab(std::string str) {
	std::vector<std::string> v;

	std::vector<std::string> str_v = StringSplit(str);
	for (int i = 0; i < str_v.size(); i++) {
		std::stringstream ss{ str_v[i] };
		std::string buf;
		while (std::getline(ss, buf, '\t')) {
			if (buf != "") {
				v.push_back(buf);
			}
		}
	}
	return v;
}

std::vector<std::string> StringSplit(std::string str) {
	std::stringstream ss{ str };	//convert string to stringstream
	std::vector<std::string> v;		//def(senngen)
	std::string buf;

	while (std::getline(ss, buf, ' ')) {
		if (buf != "") {
			v.push_back(buf);
		}
	}
	return v;
}