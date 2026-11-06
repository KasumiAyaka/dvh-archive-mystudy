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

std::vector<std::string> StringSplit(std::string str);
std::vector<std::string> StringSplit_with_tab(std::string str);


void SetList(std::string input, std::set<Key>& list);
void ShifterBasetrack(std::string input, std::set<Key>& list, std::string output);
void ShifterBasetrack2(std::string input, std::set<Key>& list, std::string output);

int main(int argc, char** argv) {
	if (argc != 5) {
		fprintf(stderr, "Usage:prg muon.txt list_auto.txt list_manual.txt output_file\n");
		fprintf(stderr, "output: flg-manu flg-outo muoninfo\n");
		exit(1);
	}

	std::string in_basetrack = argv[1];//muon_ecc5_including_multi_w_cosmic
	std::string in_list = argv[2];//OSS basetrack
	std::string in_list_manual = argv[3];//output
	std::string output_file = argv[4];//output
	auto start = std::chrono::system_clock::now();//for measure working time

	std::cout << "set list" << std::endl;

	std::set<Key> list;
	SetList(in_list, list);
	std::string tmp = "tmp.txt";

	ShifterBasetrack(in_basetrack, list, tmp);
	list.clear();
	std::set<Key> listm;
	SetList(in_list_manual, listm);
	ShifterBasetrack2(tmp, listm, output_file);

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
void SetList(std::string input, std::set<Key>& list) {
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
		std::cout << k.pl << std::endl;

		list.insert(k);
	}
	std::cout << "set list" << std::endl;
}

void ShifterBasetrack(std::string input, std::set<Key>& list, std::string output) {
	std::ifstream ifs(input);
	if (!ifs) {
		std::cerr << "error" << std::endl;
		exit(1);
	}


	int count = 0;
	std::string str;					//1strein into
	std::vector<std::string> str_v;		//input 1 ward
	std::string buffer;
	//tree->ReadFile(input.Data(), "gid/I:cid/I:npl/I:nseg/I:ax/D:ay/D:pl0/I:rawid0/I:ax0/D:ay0/D:x0/D:y0/D:pl1/I:rawid1/I:ax1/D:ay1/D:x1/D:y1/D");

	Key k;
	std::ofstream ofs(output);
	int c = 0;
	while (std::getline(ifs, str)) {
		str_v = StringSplit_with_tab(str);
		k.pl = std::stoi(str_v[0]);//groupid==eventid
		k.id = std::stoi(str_v[6]);//pl003or004


		if (list.find(k) != list.end()) {//ECC stop

			ofs << std::right << std::fixed
				<< std::setw(3) << std::setprecision(0) << 1 << " "
				<<str
				/*
				<< std::setw(3) << std::setprecision(0) << k.id << " "//muon flg
				<< std::setw(20) << std::setprecision(0) << std::stoi(str_v[0]) << " "//Rawid
				<< std::setw(4) << std::setprecision(0) << std::stoi(str_v[1]) << " "//pl
				<< std::setw(10) << std::setprecision(4) << std::stod(str_v[2]) << " "//ax
				<< std::setw(10) << std::setprecision(4) << std::stod(str_v[3]) << " "//ay
				<< std::setw(10) << std::setprecision(1) << std::stod(str_v[4]) << " "//x
				<< std::setw(10) << std::setprecision(1) << std::stod(str_v[5]) << " "//y
				*/
				<< std::endl;
		}
		else {//edgeout / penetrate
			ofs << std::right << std::fixed
				<< std::setw(3) << std::setprecision(0) << -1 << " "
				<< str
				/*
				<< std::setw(3) << std::setprecision(0) << k.id << " "//muon flg
				<< std::setw(20) << std::setprecision(0) << std::stoi(str_v[0]) << " "//Rawid
				<< std::setw(4) << std::setprecision(0) << std::stoi(str_v[1]) << " "//pl
				<< std::setw(10) << std::setprecision(4) << std::stod(str_v[2]) << " "//ax
				<< std::setw(10) << std::setprecision(4) << std::stod(str_v[3]) << " "//ay
				<< std::setw(10) << std::setprecision(1) << std::stod(str_v[4]) << " "//x
				<< std::setw(10) << std::setprecision(1) << std::stod(str_v[5]) << " "//y
				*/
				<< std::endl;
		}
	}

}

void ShifterBasetrack2(std::string input, std::set<Key>& list, std::string output) {
	std::ifstream ifs(input);
	if (!ifs) {
		std::cerr << "error" << std::endl;
		exit(1);
	}


	int count = 0;
	std::string str;					//1strein into
	std::vector<std::string> str_v;		//input 1 ward
	std::string buffer;
	//tree->ReadFile(input.Data(), "gid/I:cid/I:npl/I:nseg/I:ax/D:ay/D:pl0/I:rawid0/I:ax0/D:ay0/D:x0/D:y0/D:pl1/I:rawid1/I:ax1/D:ay1/D:x1/D:y1/D");

	Key k;
	std::ofstream ofs(output);
	int c = 0;
	while (std::getline(ifs, str)) {
		str_v = StringSplit_with_tab(str);
		k.pl = std::stoi(str_v[1]);//groupid==eventid
		k.id = std::stoi(str_v[7]);//pl003or004


		if (list.find(k) != list.end()) {//ECC stop

			ofs << std::right << std::fixed
				<< std::setw(3) << std::setprecision(0) << 1 << " "
				<< str
				/*
				<< std::setw(3) << std::setprecision(0) << k.id << " "//muon flg
				<< std::setw(20) << std::setprecision(0) << std::stoi(str_v[0]) << " "//Rawid
				<< std::setw(4) << std::setprecision(0) << std::stoi(str_v[1]) << " "//pl
				<< std::setw(10) << std::setprecision(4) << std::stod(str_v[2]) << " "//ax
				<< std::setw(10) << std::setprecision(4) << std::stod(str_v[3]) << " "//ay
				<< std::setw(10) << std::setprecision(1) << std::stod(str_v[4]) << " "//x
				<< std::setw(10) << std::setprecision(1) << std::stod(str_v[5]) << " "//y
				*/
				<< std::endl;
		}
		else {//edgeout / penetrate
			ofs << std::right << std::fixed
				<< std::setw(3) << std::setprecision(0) << -1 << " "
				<< str
				/*
				<< std::setw(3) << std::setprecision(0) << k.id << " "//muon flg
				<< std::setw(20) << std::setprecision(0) << std::stoi(str_v[0]) << " "//Rawid
				<< std::setw(4) << std::setprecision(0) << std::stoi(str_v[1]) << " "//pl
				<< std::setw(10) << std::setprecision(4) << std::stod(str_v[2]) << " "//ax
				<< std::setw(10) << std::setprecision(4) << std::stod(str_v[3]) << " "//ay
				<< std::setw(10) << std::setprecision(1) << std::stod(str_v[4]) << " "//x
				<< std::setw(10) << std::setprecision(1) << std::stod(str_v[5]) << " "//y
				*/
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