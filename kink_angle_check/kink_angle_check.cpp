// 2023/9/4
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
#include<cmath>

struct Key {
	int pl, id;
};
bool operator<(const Key& lhs, const Key& rhs) {
	return std::tie(lhs.pl, lhs.id) < std::tie(rhs.pl, rhs.id);
}

struct StopList {
	int pl, id, cid, rawid;
};
struct ChainHeader {
	int chainid, nseg, pos0, pos1;
};
bool operator<(const ChainHeader& lhs, const ChainHeader& rhs) {
	return std::tie(lhs.chainid, lhs.nseg, lhs.pos0, lhs.pos1) 
		< std::tie(rhs.chainid, rhs.nseg, rhs.pos0, rhs.pos1);
}

struct Track {
	int pos, groupid, rawid, vph;
	double ax, ay, x, y, z;
	int a, b, c, d;
	double p, q;
};
struct Mfile {
	ChainHeader h;
	Track t;
};
struct Output {
	double ang0,ang1;
	double pl0, pl1;

};
std::vector<std::string> StringSplit(std::string str);
std::vector<std::string> StringSplit_with_tab(std::string str);

void ReadMfile(std::string input, std::string output);

int main(int argc, char** argv) {
	if (argc != 3) {
		fprintf(stderr, "Usage:prg in output_file\n");
		exit(1);
	}

	std::string input = argv[1];//muon_ecc5_including_multi_w_cosmic
	std::string output = argv[2];//output
	auto start = std::chrono::system_clock::now();//for measure working time

	ReadMfile(input, output);

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
void ReadMfile(std::string input,std::string output) {
	std::ifstream ifs(input);
	if (!ifs) {
		std::cerr << "error" << std::endl;
		exit(1);
	}
	std::ofstream ofs(output);

	std::string str;					//1strein into
	std::vector<std::string> str_v;		//input 1 ward
	std::string buffer;

	int count = 0;
	int cnt = 0;
	ChainHeader h;
	Track t;
	Mfile mfe,mwt;
	int tr = 0;
	int pl = 0;
	double ax, ay, child,deno, theta;
	double wt = -100.0, fe = -100.0;
	int wpl, fpl;
	std::multimap<ChainHeader, Output> map;

	while (std::getline(ifs, str)) {
		str_v = StringSplit_with_tab(str);
		//std::cout << str_v.size() << std::endl;
		if (count < 5) {
			count++;
			continue;
		}

		if (str_v.size() == 4) {
			h.chainid = std::stoi(str_v[0]);
			h.nseg = std::stoi(str_v[1]);
			h.pos0 = std::stoi(str_v[2]);
			h.pos1 = std::stoi(str_v[3]);
			wt = -100.0;
			fe = -100.0;

		}
		else if (str_v.size() == 15) {
			t.pos = std::stoi(str_v[0])/10;
			t.groupid = std::stoi(str_v[1]);
			t.rawid = std::stoi(str_v[2]);
			t.vph = std::stoi(str_v[3]);
			t.ax = std::stod(str_v[4]);
			t.ay = std::stod(str_v[5]);
			t.x = std::stod(str_v[6]);
			t.y = std::stod(str_v[7]);
			t.z = std::stod(str_v[8]);
			t.a = std::stoi(str_v[9]);
			t.b = std::stoi(str_v[10]);
			t.c = std::stoi(str_v[11]);
			t.d = std::stoi(str_v[12]);
			t.p = std::stod(str_v[13]);
			t.q = std::stod(str_v[14]);
			//std::cout << pl<<" "<<t.pos << std::endl;

			if (pl + 1 == t.pos ) {
				//std::cout << "ok?" << std::endl;
				if (tr > 0) {//request pl-continuity
					child = ax * t.ax + ay * t.ay + 1;
					deno = std::sqrt(ax * ax + ay * ay + 1) * std::sqrt(t.ax * t.ax + t.ay * t.ay + 1);
					theta = std::acos(child / deno);
					//std::cout << pl << " " << t.pos << " " << std::endl;
					//std::cout << child << " " << deno << " " << theta << " " << std::endl;
				}

				if (t.pos % 2 == 1) {//Fe
					if (theta > fe) {
						fe = theta;
						mfe.t = t;
						mfe.h = h;
						//	std::cout << mfe.h.pos1 << std::endl;
					}
				}
				else {//water
					if (theta > wt) {
						wt = theta;
						mwt.h = h;
						mwt.t = t;
					}
				}
			}
			tr++;
			ax = t.ax;
			ay = t.ay;
			pl = t.pos;
		}

		if (tr == h.nseg) {
			ofs << 0<<" "<<mfe.t.pos << " " << mfe.t.groupid << " " << mfe.t.rawid << " "
				<< mfe.t.ax << " "<< mfe.t.ay << " " 
				<< mfe.t.x << " " << mfe.t.y << " " << fe << " "
				<< mfe.h.nseg << " " << mfe.h.pos0 << " " << mfe.h.pos1 << " " 
				<< std::endl;

			ofs << 1<<" "<<mwt.t.pos << " " << mwt.t.groupid << " " << mwt.t.rawid << " " << mwt.t.ax << " "
				<< mwt.t.ay << " " << mwt.t.x << " " << mwt.t.y << " " << wt << " "
				<< mwt.h.nseg << " " << mwt.h.pos0 << " " << mwt.h.pos1 << " " << std::endl;
			//std::cout << count << std::endl;
			tr = 0;
		}
		count++;
	}

	//for (auto itr = map.begin(); itr != map.end(); itr++) {
	//	std::cout << itr->second.rawid << std::endl;
	//}
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