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
	double ang0, ang1;
	double pl0, pl1;

};
struct ConnectChainList {
	int eventid;
	Key t0, t1;
};
bool operator<(const ConnectChainList& lhs, const ConnectChainList& rhs) {
	return std::tie(lhs.eventid, lhs.t0, lhs.t1) < std::tie(rhs.eventid, rhs.t0, rhs.t1);
}
struct CKey {
	int gid, pl, id;
};
bool operator<(const CKey& lhs, const CKey& rhs) {
	return std::tie(lhs.gid, lhs.pl, lhs.id) < std::tie(lhs.gid, lhs.pl, rhs.id);
}

struct Chain {
	Track t;
	ChainHeader h;
};


std::vector<std::string> StringSplit(std::string str);
std::vector<std::string> StringSplit_with_tab(std::string str);

void SetConnectChainList(std::string input, std::set<ConnectChainList>& list);
void ReadMfile(std::string input, std::multimap<int, Chain>& map);
void matching(std::set<ConnectChainList>& list, std::multimap<int, Chain>& map, std::string output, int times);

int main(int argc, char** argv) {
	if (argc != 5) {
		fprintf(stderr, "Usage:prg connect_list.txt muon.all output_file.txt times\n");
		exit(1);
	}

	std::string input = argv[1];
	std::string input_mfile = argv[2];
	std::string output = argv[3];//output
	int times = std::stoi(argv[4]);

	auto start = std::chrono::system_clock::now();//for measure working time

	std::set<ConnectChainList> list;
	std::multimap<int, Chain> map;
	SetConnectChainList(input, list);
	ReadMfile(input_mfile, map);
	matching(list, map, output, times);


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
void SetConnectChainList(std::string input, std::set<ConnectChainList>& list) {
	std::ifstream ifs(input);
	if (!ifs) {
		std::cerr << "error" << std::endl;
		exit(1);
	}

	std::string str;
	std::vector<std::string> str_v;
	std::string buffer;

	int count = 0;
	ConnectChainList l;
	while (std::getline(ifs, str)) {
		str_v = StringSplit_with_tab(str);

		l.eventid = std::stoi(str_v[0]);
		l.t0.pl = std::stoi(str_v[1]);
		l.t0.id = std::stoi(str_v[2]);
		l.t1.pl = std::stoi(str_v[3]);
		l.t1.id = std::stoi(str_v[4]);

		list.insert(l);
		//std::cout << l.eventid << "\t" << l.t0.pl << "\t" << l.t0.id << "\t" << l.t1.pl << "\t" << l.t1.id << std::endl;
	}
	std::cout << "list size \t" << list.size() << std::endl;

}
void ReadMfile(std::string input, std::multimap<int, Chain>& map) {
	std::ifstream ifs(input);
	if (!ifs) {
		std::cerr << "error" << std::endl;
		exit(1);
	}

	std::string str;					//1strein into
	std::vector<std::string> str_v;		//input 1 ward
	std::string buffer;

	int count = 0;
	int cnt = 0;
	ChainHeader h;
	CKey k;
	Track t0;
	Chain c;
	
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
			h.pos0 = std::stoi(str_v[2])/10;
			h.pos1 = std::stoi(str_v[3])/10;
		}
		else if (str_v.size() == 15) {
			t0.pos = std::stoi(str_v[0]) / 10;
			t0.groupid = std::stoi(str_v[1]);
			t0.rawid = std::stoi(str_v[2]);
			t0.vph = std::stoi(str_v[3]);
			t0.ax = std::stod(str_v[4]);
			t0.ay = std::stod(str_v[5]);
			t0.x = std::stod(str_v[6]);
			t0.y = std::stod(str_v[7]);
			t0.z = std::stod(str_v[8]);
			t0.a = std::stoi(str_v[9]);
			t0.b = std::stoi(str_v[10]);
			t0.c = std::stoi(str_v[11]);
			t0.d = std::stoi(str_v[12]);
			t0.p = std::stod(str_v[13]);
			t0.q = std::stod(str_v[14]);

			c.h = h;
			c.t = t0;
			k.pl = t0.pos;//pl
			k.id = t0.rawid;
			k.gid = t0.groupid;

		//	std::cout << k.gid << "\t" << k.pl << "\t" << k.id << std::endl;
			//map.insert(std::make_pair(k, c));
			map.insert(std::make_pair(t0.groupid, c));
		}
		else {
			std::cout << "error" << std::endl;
			continue;
		}
	}
	
}

void matching0(std::set<ConnectChainList>& list, std::map<CKey, Chain>& map, std::string output, int times) {
	std::ofstream ofs(output);

	CKey k0, k1;
	double child, deno, theta;

	for (auto itr = list.begin(); itr != list.end(); itr++) {

		k0.gid = itr->eventid;
		k0.id = itr->t0.id;
		k0.pl = itr->t0.pl;

		k1.gid = itr->eventid;
		k1.id = itr->t1.id;
		k1.pl = itr->t1.pl;
		std::cout << k1.gid << "\t" << k1.pl << "\t" << k1.id << std::endl;

		auto p = map.find(k0);
		auto q = map.find(k1);

		if (p == map.end() || q == map.end()) {
			std::cout << "error" << std::endl;
		}
		else {

			child = p->second.t.ax * q->second.t.ax + p->second.t.ay * q->second.t.ay + 1;
			deno = std::sqrt(p->second.t.ax * p->second.t.ax + p->second.t.ay * p->second.t.ay + 1) * std::sqrt(q->second.t.ax * q->second.t.ax + q->second.t.ay * q->second.t.ay + 1);
			theta = std::acos(child / deno);//angle difference

			ofs << std::right << std::fixed
				<< std::setw(10) << std::setprecision(0) << itr->eventid << " "//groupid
				//track0
				<< std::setw(3) << std::setprecision(0) << p->second.t.pos << " "
				<< std::setw(20) << std::setprecision(0) << p->second.t.rawid << " "
				<< std::setw(7) << std::setprecision(0) << p->second.t.vph << " "
				<< std::setw(10) << std::setprecision(4) << p->second.t.ax << " "
				<< std::setw(10) << std::setprecision(4) << p->second.t.ay << " "
				<< std::setw(10) << std::setprecision(1) << p->second.t.x << " "
				<< std::setw(10) << std::setprecision(1) << p->second.t.y << " "
				//track1
				<< std::setw(3) << std::setprecision(0) << q->second.t.pos << " "
				<< std::setw(20) << std::setprecision(0) << q->second.t.rawid << " "
				<< std::setw(7) << std::setprecision(0) << q->second.t.vph << " "
				<< std::setw(10) << std::setprecision(4) << q->second.t.ax << " "
				<< std::setw(10) << std::setprecision(4) << q->second.t.ay << " "
				<< std::setw(10) << std::setprecision(1) << q->second.t.x << " "
				<< std::setw(10) << std::setprecision(1) << q->second.t.y << " "
				//
				<< std::setw(4) << std::setprecision(0) << q->second.t.pos - p->second.t.pos - 1 << " "//skippl
				<< std::setw(2) << std::setprecision(0) << times << " "//#check
				<< std::setw(10) << std::setprecision(4) << theta << " "//diff angle //rad
				<< std::endl;
		}
	}
}
void matching(std::set<ConnectChainList>& list, std::multimap<int, Chain>& map, std::string output, int times) {
	std::ofstream ofs(output);

	int cnt = 0;
	double child, deno, theta;
	double ax0, ay0, ax1, ay1;
	Chain c0, c1;
	for (auto itr0 = list.begin(); itr0 != list.end(); itr0++) {

		auto p = map.equal_range(itr0->eventid);
		cnt = 0;
		for (auto itr = p.first; itr != p.second; itr++) {
			if (itr->second.t.pos==itr0->t0.pl&&itr->second.t.rawid==itr0->t0.id) {
				cnt++;
				c0 = itr->second;
				ax0 = itr->second.t.ax;
				ay0 = itr->second.t.ay;

			}
			else if (itr->second.t.pos == itr0->t1.pl && itr->second.t.rawid == itr0->t1.id) {
				c1 = itr->second;
				cnt++;
				ax1 = itr->second.t.ax;
				ay1 = itr->second.t.ay;


			}

		}
		if (cnt == 2) {
			child = ax0 * ax1 + ay0 * ay1 + 1;
			deno = std::sqrt(ax0 * ax0 + ay0 * ay0 + 1) * std::sqrt(ax1 * ax1 + ay1 * ay1 + 1);
			theta = std::acos(child / deno);//angle difference


			ofs << std::right << std::fixed
				<< std::setw(10) << std::setprecision(0) << c0.t.groupid << " "//groupid
				//track0
				<< std::setw(3) << std::setprecision(0) << c0.t.pos << " "
				<< std::setw(20) << std::setprecision(0) << c0.t.rawid << " "
				<< std::setw(7) << std::setprecision(0) << c0.t.vph << " "
				<< std::setw(10) << std::setprecision(4) << c0.t.ax << " "
				<< std::setw(10) << std::setprecision(4) << c0.t.ay << " "
				<< std::setw(10) << std::setprecision(1) << c0.t.x << " "
				<< std::setw(10) << std::setprecision(1) << c0.t.y << " "
				//track1
				<< std::setw(3) << std::setprecision(0) << c1.t.pos << " "
				<< std::setw(20) << std::setprecision(0) << c1.t.rawid << " "
				<< std::setw(7) << std::setprecision(0) << c1.t.vph << " "
				<< std::setw(10) << std::setprecision(4) << c1.t.ax << " "
				<< std::setw(10) << std::setprecision(4) << c1.t.ay << " "
				<< std::setw(10) << std::setprecision(1) << c1.t.x << " "
				<< std::setw(10) << std::setprecision(1) << c1.t.y << " "
				//
				<< std::setw(4) << std::setprecision(0) << itr0->t1.pl - itr0->t0.pl - 1 << " "//skippl
				<< std::setw(2) << std::setprecision(0) << times << " "//#check
				<< std::setw(10) << std::setprecision(4) << theta << " "//diff angle //rad
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