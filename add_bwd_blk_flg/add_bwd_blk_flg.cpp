// add_bwd_blk_flg *****************************************
// 2022/02/17
// kasumi
// *** input ***
// vtx.bwd.txt
// *** output format ***
// eid pl #trk x y z
// pl1 rid1 pl2 rid2 vx vy dz oa md
// dpl upl urid cid gid nsg npl nph ax ay x y z bwdflg blkflg
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// bwdflg:bwd-->1, fwd-->0
// blkflg:blk-->1,mip-->0
// event id -> reset to be unique
// *** usage ***
// I:\NINJA\E71a\work\kasumi\MyStudy\mfile\DirectVertexHunting\VertexHunting\x64\Release\add_bwd_blk_flg.exe
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
//#include <filesystem>// treat file-name/path/...



class Vertex {
public:
	//int labelv;
	int eid, pl, trk;
	double x, y, z;
	//id is not uniqe
};
class Pair {
public:
	int pl1, rid1, pl2, rid2;
	double vx, vy, vz, oa, md;
};
class Track {
public:
	//int labelt;
	int pflg, dirflg;
	int dpl, upl, rid, cid, gid, nsg, npl, vph;
	double ax, ay, x, y, z;
};
struct Flg {
	int mbflg, fbflg;
};
std::vector<std::string> StringSplit(std::string str);
std::vector<std::string> StringSplit_with_tab(std::string str);

void read_file(std::string filename, std::multimap<int, Vertex>& vertex, std::multimap<int, Pair>& pair, std::multimap<int, Track>& track);
void set_flg(int ph, double ax, double ay, int epl, int tpl, int& dir, int& blk);
void write(std::string filename, std::multimap<int, Vertex>& vtx, std::multimap<int, Pair>& pair, std::multimap<int, Track>& track);


int main(int argc, char** argv) {
	if (argc != 3) {
		fprintf(stderr, "usage:prg input-vertex-file output\n");
		exit(1);
	}
	std::string input = argv[1];// vtx.bwd.txt
	std::string output = argv[2];
	//std::string path = argv[2];
	//int mode = std::stoi(argv[3]);


	auto start = std::chrono::system_clock::now();//for measure working time

	std::multimap<int, Vertex>vtx;
	std::multimap<int, Pair>pair;
	std::multimap<int, Track> track;

	//std::string c;
	//std::string folderpath;
	//folderpath = path;
	read_file(input, vtx, pair, track);
	write(output, vtx, pair, track);

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

void read_file(std::string filename, std::multimap<int, Vertex>& vertex, std::multimap<int, Pair>& pair, std::multimap<int, Track>& track) {

	//file open
	std::ifstream ifs(filename);

	std::string str;
	std::vector<std::string> str_v;
	std::string buffer;
	int cnt = 0;

	int l = 0;
	int label = -1;// event id
	int a = 0;

	std::cout << "Now Reading..." << std::endl;
	while (std::getline(ifs, str))
	{
		str_v = StringSplit_with_tab(str);

		if (str_v.size() == 6) {// 1st line
				//vertex.push_back(Vertex(label, stoi(str_v[0]), stoi(str_v[1]), stoi(str_v[2]), stoi(str_v[3]), stoi(str_v[4]), stoi(str_v[5])));
			Vertex v;
			v.eid = stoi(str_v[0]);
			v.pl = stoi(str_v[1]);
			v.trk = stoi(str_v[2]);
			v.x = stod(str_v[3]);
			v.y = stod(str_v[4]);
			v.z = stod(str_v[5]);

			l = v.pl;
			label++;// event-id
			vertex.insert(std::make_pair(label, v));

		}
		else if (str_v.size() == 9) {// 2nd line
				//pair.push_back(Pair(label, stod(str_v[4]), stod(str_v[5]), stod(str_v[6]), stod(str_v[7]), stod(str_v[8])));//me
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

			pair.insert(std::make_pair(label, p));

		}
		else if (str_v.size() == 13) {// 3rd

			Track t;
			//fprintf(stderr, "check3");
			//	track01.push_back(Track(label, stoi(str_v[0]), stoi(str_v[1]), stoi(str_v[2]), stoi(str_v[3]), stoi(str_v[4]), stoi(str_v[5]), stoi(str_v[6]), stoi(str_v[7]), stod(str_v[8]), stod(str_v[9]), stod(str_v[10]), stod(str_v[11]), stod(str_v[12])));
			//track1.insert(std::make_pair(label, Track(label, stoi(str_v[0]), stoi(str_v[1]), stoi(str_v[2]), stoi(str_v[3]), stoi(str_v[4]), stoi(str_v[5]), stoi(str_v[6]), stoi(str_v[7]), stod(str_v[8]), stod(str_v[9]), stod(str_v[10]), stod(str_v[11]), stod(str_v[12]))));
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
			int blk = 0; int dir = 0;
			set_flg(t.vph, t.ax, t.ay, l, t.dpl, dir, blk);
			t.dirflg = dir;
			t.pflg = blk;

			track.insert(std::make_pair(label, t));


		}
		else {
			std::cout << "error?" << std::endl;
		}
	}

	std::cout << "**** check ****\n";
	std::cout << "vtx size = " << vertex.size() <<
		"\npair size= " << pair.size() <<
		"\ntrack size=" << track.size() << std::endl;
	std::cout << "eventid : " << 0 << "to" << label << std::endl;
	std::cout << "**** ***** ****" << std::endl;
	//ok!
	// *** check ***
	//for (auto itr = track01.begin(); itr != track01.end(); itr++) {
	//	track1.insert(std::make_pair(label, *itr));
	//}
	//for (auto itr2 = track02.begin(); itr2 != track02.end(); itr2++) {
	//	track2.insert(std::make_pair(label, *itr2));
	//}
	//std::cout << "map\n\n";
	//auto itr0 = vertex.find(10);
	//if (itr0 != vertex.end()) std::cout << "find!" << itr0->first << std::endl;
	//auto itr = track1.find(10);
	//if (itr != track1.end()) {
	//	std::cout << itr->first << "ok\n"; 
	//}
	// ***       ***


}
void set_flg(int ph, double ax, double ay, int epl, int tpl, int& dir, int& blk) {//track_information
//	std::string input;
	//std::stringstream name;
	//name << path << "\\" << input << "_t.txt";
	//std::string filename = name.str();

	//std::cout << "Now Reading" << filename << std::endl;
	////file open
	//std::ifstream ifs(filename);
	//if (!ifs) {
	//	std::cerr << "Cannot open " << filename << std::endl;
	//}

	// cut condition  -a*angle + b
	double angle;
	double a, b, a1, b1, a2, b2, a3, b3;
	// cut condition  -a*angle + b
	a = 102.5; b = 177.5;// 0  -1.0
	a1 = 16.5; b1 = 91.5;//1.0-2.0
	a2 = 12.; b2 = 82.5;//2.0-3.0
	a3 = -3.; b3 = 37.5;// 3.0-
	//***************************
	int vph;
	//std::cout << "Now classifing..." << std::endl;

	//label:mip->0,blk->1
	// id,vph,count,eid,epl,ntrk,ex,ey,ez,pl0,pl1,rid,cid,gid,nsg,npl,ph,ax,ay,x,y,z
	vph = ph % 10000;
	angle = std::sqrt(ax * ax + ay * ay);
	if (tpl > epl) {//bwd
		if ((angle <= 1.0) && (vph <= b - a * angle)) {//mip
			blk = 0;
			dir = 1;

		}
		else if ((angle > 1.0 && angle <= 2.0) & (vph % 10000 <= b1 - a1 * angle)) {
			blk = 0;
			dir = 1;

		}
		else if ((angle > 2.0 && angle <= 3.0) & (vph % 10000 <= b2 - a2 * angle)) {
			blk = 0;
			dir = 1;

		}
		else if ((angle > 3.0) & (vph % 10000 <= b3 - a3 * angle)) {
			blk = 0;
			dir = 1;

		}
		else {//blk
			blk = 1;
			dir = 1;

		}
	}
	else {//fwd
		if ((angle <= 1.0) && (vph <= b - a * angle)) {//mip
			blk = 0;
			dir = 0;

		}
		else if ((angle > 1.0 && angle <= 2.0) & (vph % 10000 <= b1 - a1 * angle)) {
			blk = 0;
			dir = 0;

		}
		else if ((angle > 2.0 && angle <= 3.0) & (vph % 10000 <= b2 - a2 * angle)) {
			blk = 0;
			dir = 0;

		}
		else if ((angle > 3.0) & (vph % 10000 <= b3 - a3 * angle)) {
			blk = 0;
			dir = 0;

		}
		else {//blk
			blk = 1;
			dir = 0;

		}

	}
}
void write(std::string filename, std::multimap<int, Vertex>& vtx, std::multimap<int, Pair>& pair, std::multimap<int, Track>& track) {

	std::ofstream ofs(filename);
	int count = 0;
	for (auto i = vtx.begin(); i != vtx.end(); i++) {
		auto v = vtx.equal_range(i->first);
		for (auto itr0 = v.first; itr0 != v.second; itr0++) {
			ofs << std::right << std::fixed
				<< std::setw(12) << std::setprecision(0) << itr0->first << " "
				<< std::setw(4) << std::setprecision(0) << itr0->second.pl << " "
				<< std::setw(4) << std::setprecision(0) << itr0->second.trk << " "
				<< std::setw(8) << std::setprecision(1) << itr0->second.x << " "
				<< std::setw(8) << std::setprecision(1) << itr0->second.y << " "
				<< std::setw(8) << std::setprecision(1) << itr0->second.z << std::endl;
		}
		auto p = pair.equal_range(i->first);
		for (auto itr1 = p.first; itr1 != p.second; itr1++) {
			ofs << std::right << std::fixed
				<< std::setw(4) << std::setprecision(0) << itr1->second.pl1 << " "
				<< std::setw(12) << std::setprecision(0) << itr1->second.rid1 << " "
				<< std::setw(4) << std::setprecision(0) << itr1->second.pl2 << " "
				<< std::setw(12) << std::setprecision(0) << itr1->second.rid2 << " "
				<< std::setw(8) << std::setprecision(1) << itr1->second.vx << " "
				<< std::setw(8) << std::setprecision(1) << itr1->second.vy << " "
				<< std::setw(8) << std::setprecision(1) << itr1->second.vz << " "
				<< std::setw(6) << std::setprecision(4) << itr1->second.oa << " "
				<< std::setw(4) << std::setprecision(1) << itr1->second.md << std::endl;
		}

		auto t = track.equal_range(i->first);
		for (auto itr2 = t.first; itr2 != t.second; itr2++) {
			ofs << std::right << std::fixed
				<< std::setw(4) << std::setprecision(0) << itr2->second.dpl << " "
				<< std::setw(4) << std::setprecision(0) << itr2->second.upl << " "
				<< std::setw(12) << std::setprecision(0) << itr2->second.rid << " "
				<< std::setw(20) << std::setprecision(0) << itr2->second.cid << " "
				<< std::setw(20) << std::setprecision(0) << itr2->second.gid << " "
				<< std::setw(4) << std::setprecision(0) << itr2->second.nsg << " "
				<< std::setw(4) << std::setprecision(0) << itr2->second.npl << " "
				<< std::setw(6) << std::setprecision(0) << itr2->second.vph << " "
				<< std::setw(7) << std::setprecision(4) << itr2->second.ax << " "
				<< std::setw(7) << std::setprecision(4) << itr2->second.ay << " "
				<< std::setw(8) << std::setprecision(1) << itr2->second.x << " "
				<< std::setw(8) << std::setprecision(1) << itr2->second.y << " "
				<< std::setw(4) << std::setprecision(1) << itr2->second.z << ""
				<< std::setw(8) << std::setprecision(1) << itr2->second.dirflg << " "
				<< std::setw(8) << std::setprecision(1) << itr2->second.pflg << " "
				<< std::endl;//itr->first=ip


		}
		count++;
	}
	ofs.close();
	std::cout << "event size " << count << std::endl;
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

