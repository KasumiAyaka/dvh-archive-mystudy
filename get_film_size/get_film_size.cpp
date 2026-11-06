// get_film_size
// 2022/02/16
// kasumi
// input stoptrack->output film-area
// output format
// pl xmin xmax ymax ymin z
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

struct StopTrack {
	int cid, nsg, pl0, pl1, gid, rid, ph;
	double ax, ay, x, y, z;
};
struct Area {
	double xmin, xmax, ymin, ymax, z;
};
bool operator<(const StopTrack& lhs, const  StopTrack& rhs) {
	return std::tie(lhs.pl1, lhs.x,lhs.y) < std::tie(rhs.pl1, rhs.z,rhs.y);
}


void read_stoptrack(std::string input,int mode, std::multimap<int, StopTrack>& stop);
void write_file_area(std::string output, std::multimap<int, StopTrack>& stop, std::map<int, Area>& area);

int main(int argc, char** argv) {
	if (argc != 4) {
		fprintf(stderr, "usage:prg input(stop.txt) output(pl,xmin,xmax,ymin,ymax,z) mode(0:stop,1:start)\n");
		exit(1);
	}

	std::string input = argv[1];
	std::string output = argv[2];
	int mode = std::stoi(argv[3]);//0:stop . 1:start

	auto start = std::chrono::system_clock::now();//for measure working time


	std::multimap<int, StopTrack> stop;
	read_stoptrack(input,mode, stop);
	std::map<int, Area> area;
	write_file_area(output, stop,area);


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
void read_stoptrack(std::string input, int mode,std::multimap<int, StopTrack>& stop) {
	std::ifstream ifs(input);
	if (!ifs) {
		std::cout << "cannot open " << input << " ." << std::endl;
		std::cin.get();
		//	return;
	}

	StopTrack s;
	while (ifs >> s.cid >> s.nsg >> s.pl0 >> s.pl1 >> s.gid >> s.rid >> s.ph >> s.ax >> s.ay >> s.x >> s.y >> s.z) {
		if (mode == 0) {
			stop.insert(std::make_pair(s.pl1, s));
		}
		if (mode == 1) {
			stop.insert(std::make_pair(s.pl0, s));
		}
		//*******************************
		// for check
		//if (s.pl1 == 16&&s.x<9000) {
		//	std::cout << s.x << std::endl;
		//}
		//if (s.pl1 == 16 && s.x > 245000) {
		//	std::cout <<"\t"<< s.x << std::endl;
		//}
		//*******************************
	}


}
void write_file_area(std::string output, std::multimap<int, StopTrack>& stop,std::map<int,Area>& area) {

	for (int i = 3; i < 134; i++) {
		auto q = stop.find(i);
		if (q == stop.end()) {
			continue;
		}
		auto p = stop.equal_range(i);
		double xmin = p.first->second.x;
		double xmax = p.first->second.x;
		double ymin = p.first->second.y;
		double ymax = p.first->second.y;

		Area a;
		for (auto itr = p.first; itr != p.second; itr++) {
			if (itr->second.x < xmin) {
				xmin = itr->second.x;
			}
			if (itr->second.x > xmax) {
				xmax = itr->second.x;
			}
			if (itr->second.y < ymin) {
				ymin = itr->second.y;
			}
			if (itr->second.y > ymax) {
				ymax = itr->second.y;
			}
		}
		a.xmax = xmax;
		a.ymax = ymax;
		a.xmin = xmin;
		a.ymin = ymin;
		a.z = p.first->second.z;
		area.insert(std::make_pair(p.first->first, a));
	}

	std::ofstream ofs(output);
	for (auto itr = area.begin(); itr != area.end(); itr++) {
		ofs << std::setw(3) << std::setprecision(0) << itr->first << " "
			<< std::setw(8) << std::fixed << std::setprecision(1) << itr->second.xmin << " "
			<< std::setw(8) << std::fixed << std::setprecision(1) << itr->second.xmax << " "
			<< std::setw(8) << std::fixed << std::setprecision(1) << itr->second.ymin << " "
			<< std::setw(8) << std::fixed << std::setprecision(1) << itr->second.ymax << " "
			<< std::setw(8) << std::fixed << std::setprecision(1) << itr->second.z << " "
			<< std::endl;
	}
}