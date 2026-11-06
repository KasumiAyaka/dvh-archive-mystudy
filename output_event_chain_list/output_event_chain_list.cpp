// count_each_event *****************************************
// 2022/03/15
// kasumi
// *** input ***
// 
// *** input format ***
//
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//// *** usage ***
//
//***********************************************************
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include<utility>//make_pair
#include <chrono>
#include<algorithm>
#include<iomanip>
//#include <filesystem>// treat file-name/path/...


class Vertex {
public:
	//int labelv;
	int eid, pl, trk;
	double x, y, z;

	int nmip;//all mip 0, mip+blk=1, all blk=2
	int gam;//not gamma like=1,epair like=0
	int rss;//at least 1 mip reaches ss=1
	int fmip;//doesnt have fwd mip=1
	int phi;//phi>170
};
class Pair {
public:
	int pl1, rid1, pl2, rid2;
	double vx, vy, vz, oa, md;
	double cosphi, phi;
	double moa;
};
class Track {
public:
	//int labelt;
	int pflg, dirflg;
	int dpl, upl, rid, cid, gid, nsg, npl, vph;
	double ax, ay, x, y, z;
};
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



std::vector<std::string> StringSplit(std::string str);
std::vector<std::string> StringSplit_with_tab(std::string str);

void set_event_id(std::string input, std::set<int>& list);
void read_file(std::string filename, std::multimap<int, Vertex>& vertex, std::multimap<int, Pair>& pair, std::multimap<int, Track>& track);
void output_event_list(std::multimap<int, Track>& trk, std::set<int>& list);
	
int main(int argc, char** argv) {
	if (argc != 3) {
		fprintf(stderr, "usage:prg input-vertex-file list\n");
		exit(1);
	}
	std::string input = argv[1];// fdata
	std::string input_list = argv[2];// event_list

	auto start = std::chrono::system_clock::now();//for measure working time

	std::set<int> list;


	std::multimap<int, Vertex>vtx;
	std::multimap<int, Pair>pair;
	std::multimap<int, Track> track;

	//std::string c;
	//std::string folderpath;
	//folderpath = path;
	read_file(input, vtx, pair, track);
	//set_event_id(input_list, list);
	output_event_list(track, list);



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
void set_event_id(std::string input, std::set<int>& list) {
	std::ifstream ifs(input);
	if (!ifs) {
		std::cerr << "error" << std::endl;
		exit(1);
	}

	int a;
	while (ifs >> a) {
		list.insert(a);
	}

}
void read_file(std::string filename, std::multimap<int, Vertex>& vertex, std::multimap<int, Pair>& pair, std::multimap<int, Track>& track) {
	//file open
	std::ifstream ifs(filename);
	if (!ifs) {
		std::cerr << "cannot open " << filename << std::endl;
		exit(1);
	}

	std::string str;
	std::vector<std::string> str_v;
	std::string buffer;
	int cnt = 0;

	Count c{ 0 };

	int n = 0;
	int id = 0;
	int tnum = 0;//2->1

	std::cout << "Now Reading..." << std::endl;
	while (std::getline(ifs, str)) {
		str_v = StringSplit_with_tab(str);

		if (str_v.size() == 11) {// 1st line
			Vertex v;
			v.eid = stoi(str_v[0]);
			v.pl = stoi(str_v[1]);
			v.trk = stoi(str_v[2]);
			v.x = stod(str_v[3]);
			v.y = stod(str_v[4]);
			v.z = stod(str_v[5]);
			v.nmip = stoi(str_v[6]);
			v.gam = stoi(str_v[7]);
			v.phi = stoi(str_v[8]);
			v.rss = stoi(str_v[9]);
			v.fmip = stoi(str_v[10]);
			id = v.eid;
			vertex.insert(std::make_pair(id, v));
			tnum = v.trk;
			n++;
		}
		else if (str_v.size() == 12) {// 2nd line
			Pair p;
			p.pl1 = stoi(str_v[0]);
			p.rid1 = stoi(str_v[1]);
			p.pl2 = stoi(str_v[2]);
			p.rid2 = stoi(str_v[3]);
			p.vx = stod(str_v[4]);
			p.vy = stod(str_v[5]);
			p.vz = stod(str_v[6]);
			p.oa = stod(str_v[7]);
			p.md = stod(str_v[8]);
			p.moa = stod(str_v[9]);
			p.cosphi = stod(str_v[10]);
			p.phi = stod(str_v[11]);
			pair.insert(std::make_pair(id, p));

		}
		else if (str_v.size() == 15) {// 3rd

			Track t;
			t.dpl = stoi(str_v[0]);
			t.upl = stoi(str_v[1]);
			t.rid = stoi(str_v[2]);
			t.cid = stoi(str_v[3]);
			t.gid = stoi(str_v[4]);
			t.nsg = stoi(str_v[5]);
			t.npl = stoi(str_v[6]);
			t.vph = stoi(str_v[7]);
			t.ax = stod(str_v[8]);
			t.ay = stod(str_v[9]);
			t.x = stod(str_v[10]);
			t.y = stod(str_v[11]);
			t.z = stod(str_v[12]);
			t.dirflg = stoi(str_v[13]);
			t.pflg = stoi(str_v[14]);

			track.insert(std::make_pair(id, t));


		}
		else {
			std::cout << "error?" << std::endl;
		}

	}
	std::cout << "Finish reading!" << std::endl;

}
void output_event_list(std::multimap<int,Track>& trk, std::set<int>& list) {
	std::cout << "trk size " << trk.size() << "\n";
	std::cout << "list_num " << list.size() << "\n";

	for (int i = 0; i < 60834; i++) {
		//for (auto itr = list.begin(); itr != list.end(); itr++) {
		std::string filename;
		std::stringstream name;

		//name << "list\\e" << std::setfill('0') << std::setw(5) << std::right << std::to_string(*itr) << ".txt";
		name << "list\\e" << std::setfill('0') << std::setw(5) << std::right << std::to_string(i) << ".txt";
		std::string file_name = name.str();
		std::ofstream ofs(file_name);

		auto q = trk.find(i);
		//std::cout << "eve_id " << q->first<<"\n";

		if (q != trk.end()) {
			auto p = trk.equal_range(i);
			for (auto itr0 = p.first; itr0 != p.second; itr0++) {
				ofs << itr0->second.cid << " " << itr0->first << std::endl;
				//std::cout << itr0->second.cid << " " << itr0->first << std::endl;

			}
		}
		ofs.close();
		//}
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
	std::stringstream ss{ str };
	std::vector<std::string> v;
	std::string buf;
	while (std::getline(ss, buf, ' ')) {
		if (buf != "") {
			v.push_back(buf);
		}
	}
	return v;
}

