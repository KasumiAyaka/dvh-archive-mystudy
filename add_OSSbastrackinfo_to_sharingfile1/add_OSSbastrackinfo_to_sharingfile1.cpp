// 
// 2023/9/4
// kasumi
// 
//PL/ISS-rawid/OSS-rawid/fixed-rawid/tracker-rawid/
//spotA*100+spotB/zone1/raw1/zone2/raw2
//unix time/t-track id/BM bunch/entry in daily file/BM nplane
//charge/BM mom/chi2_shifter[4]/eventid(í Çµî‘çÜ)/PM track type
//ECC track type
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

struct StopList {
	int pl, id,cid,rawid;
};

std::vector<std::string> StringSplit(std::string str);
std::vector<std::string> StringSplit_with_tab(std::string str);


void SetList(std::string input, std::multimap<Key, StopList>& list);
void ReadSharingFile(std::string input, std::multimap<Key, StopList>& list, std::string output);

int main(int argc, char** argv) {
	if (argc != 4) {
		fprintf(stderr, "Usage:prg in_sharingfile stop_list output_file\n");
		exit(1);
	}

	std::string in_sf = argv[1];//muon_ecc5_including_multi_w_cosmic
	std::string in_list = argv[2];//OSS basetrack
	std::string output_file = argv[3];//output
	auto start = std::chrono::system_clock::now();//for measure working time

	std::multimap<Key, StopList> list;
	SetList(in_list,list);
	ReadSharingFile(in_sf, list, output_file);


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
void SetList(std::string input, std::multimap<Key, StopList>& list) {
	std::ifstream ifs(input);
	if (!ifs) {
		std::cerr << "error" << std::endl;
		exit(1);
	}

	std::string str;					//1strein into
	std::vector<std::string> str_v;		//input 1 ward
	std::string buffer;

	Key k;
	StopList st;
	while (std::getline(ifs, str)) {
		str_v = StringSplit_with_tab(str);
		st.id = std::stoi(str_v[0]);
		st.cid = std::stoi(str_v[1]);
		st.pl = std::stoi(str_v[2]);
		st.rawid = std::stoi(str_v[3]);

		k.pl = std::stoi(str_v[2]);
		k.id = std::stoi(str_v[0]);//eventid

		list.insert(std::make_pair(k, st));
	}

}

void ReadSharingFile(std::string input, std::multimap<Key, StopList>& list,std::string output) {
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
		k.pl = std::stoi(str_v[7]);
		k.id = std::stoi(str_v[11]);//eventid
		
		//std::cout << k.pl << " " << k.id << std::endl;
		if (list.find(k) != list.end()) {
			ofs << 1 << " " << str << std::endl;
			c++;
		}
		else {
			ofs << -1 << " " << str << std::endl;
		}
	}
	std::cout << c << std::endl;

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