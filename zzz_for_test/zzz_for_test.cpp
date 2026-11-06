// count_each_event *****************************************
// 2022/02/22
// kasumi
// *** input ***
// v000.txt
// *** input format ***
// eid pl #trk x y z
// pl1 rid1 pl2 rid2 vx vy dz oa md cop arccos
// dpl upl urid cid gid nsg npl nph ax ay x y z bwdflg blkflg
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// bwdflg:bwd-->1, fwd-->0
// blkflg:blk-->1,mip-->0
// *** output ***
// the number of each event
// *** usage ***
// I:\NINJA\E71a\work\kasumi\MyStudy\mfile\DirectVertexHunting\VertexHunting\x64\Release\count_each_event.exe
// vtx.bwd.txt
// output.txt
//***********************************************************
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include<utility>//make_pair
#include <chrono>
#include<algorithm>
#include<iomanip>
#include <set>
//#include <filesystem>// treat file-name/path/...

struct Count {
	int two, multi;
	int mm2, mb2, bb2;
	int glike_mm2, glike_mb2;
	int phi_good;
	int ss_mb2;

	int allm, allb, mb;
	int g_allm, g_mb;
	int ss_mb;
	int all_fwd_mip;
};
struct Pid {
	int eve, a, pid;
	double b, c, d, e, f, g;
};
bool operator<(const Pid& lhs, const Pid& rhs) {
	return std::tie(lhs.eve, lhs.a) < std::tie(rhs.eve, rhs.a);
}

void read_file(std::string input, std::string output);

int main(int argc, char** argv) {
	if (argc != 3) {
		fprintf(stderr, "usage:prg input\n");
		exit(1);
	}
	std::string input = argv[1];// vtx.bwd.txt
	std::string output = argv[2];
	//std::string path = argv[2];
	//int mode = std::stoi(argv[3]);


	auto start = std::chrono::system_clock::now();//for measure working time

	//std::string c;
	//std::string folderpath;
	//folderpath = path;
	read_file(input,output);
	//write(output, vtx, pair, track);

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
void read_file(std::string input,std::string output) {
	std::ifstream ifs(input);
	if (!ifs) {
		std::cerr << "error" << std::endl;
		exit(1);
	}

	Pid p;
	std::set<int> k;
	std::multimap<int,Pid>pid;
	while (ifs >> p.eve >> p.a >> p.b >> p.c >> p.d >> p.e >> p.f >> p.g >> p.pid) {
		pid.insert(std::make_pair(p.eve,p));
		k.insert(p.eve);
	}

	//auto itr=pid.

	std::cout << k.size() << std::endl;
	std::ofstream ofs(output);
	//for (auto itr = pid.begin(); itr != pid.end(); itr++) {
	//	ofs << std::setw(7) << itr->first << " "
	//		<< itr->second.a << " "
	//		<< itr->second.b << " "
	//		<< itr->second.c << " "
	//		<< itr->second.d << " "
	//		<< itr->second.e << " "
	//		<< itr->second.f << " "
	//		<< itr->second.g << " "
	//		<< itr->second.pid
	//		<< std::endl;
	//}

	int count = 0;
	int id = 0;
	int pro = 0;
	int pi = 0;
	int mu = 0;
	
	for (auto itr = k.begin(); itr != k.end();itr++) {
		auto it0 = pid.equal_range(*itr);
		for (auto it1 = it0.first; it1 != it0.second; it1++) {
			if (it1->second.pid == 13) {
				mu++;
			}
			if (it1->second.pid == 211) {
				pi++;
			}
			if (it1->second.pid == 2212) {
				pro++;
			}
		
		}
		ofs << count<<" "
			<< mu<<" "
			<<pi<<" "
			<<pro<<" "
			<< std::endl;
		count++;
		mu = 0;
		pro = 0;
		pi = 0;
	}




}