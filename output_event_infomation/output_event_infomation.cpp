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

void read_file(std::string filename, std::multimap<int, Vertex>& vertex, std::multimap<int, Pair>& pair, std::multimap<int, Track>& track, std::string output);
void set_flg(int ph, double ax, double ay, int epl, int tpl, int& dir, int& blk);
void write(std::string filename, std::multimap<int, Vertex>& vtx, std::multimap<int, Pair>& pair, std::multimap<int, Track>& track);
void write_vtx_infomation(std::string filename, std::multimap<int, Vertex>& vtx);
void write_track(std::string filename, std::multimap<int, Vertex>& vtx, std::multimap<int, Track>& track);
void write_epair_list(std::string filename, std::multimap<int, Vertex>& vtx, std::multimap<int, Pair>& pair);

int main(int argc, char** argv) {
	if (argc != 4) {
		fprintf(stderr, "usage:prg input-vertex-file output mode(0->event,1->2vtx,2->track,3->epair like track pl id list)\n");
		exit(1);
	}
	std::string input = argv[1];// sdata.txt
	std::string output = argv[2];
	//std::string path = argv[2];
	int mode = std::stoi(argv[3]);


	auto start = std::chrono::system_clock::now();//for measure working time

	std::multimap<int, Vertex>vtx;
	std::multimap<int, Pair>pair;
	std::multimap<int, Track> track;

	//std::string c;
	//std::string folderpath;
	//folderpath = path;
	read_file(input, vtx, pair, track, output);
	if (mode == 0) {//1st line
		write_vtx_infomation(output, vtx);
	}
	if (mode == 1) {// second line
		write(output, vtx, pair, track);

	}
	if (mode == 2) {// track
		write_track(output, vtx, track);
	}
	if (mode == 3) {// epair
		//md<600-oa*60
		write_epair_list(output, vtx, pair);
	}

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
void read_file(std::string filename, std::multimap<int, Vertex>& vertex, std::multimap<int, Pair>& pair, std::multimap<int, Track>& track, std::string output) {
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
	int flg1 = 1;//md<=60-600*oa=>0
	int flg2 = 0;//phy>178.5=>1
	int flg3 = 0;//dpl<5=>1
	int flg4 = 0;//mip=>1
	int flg5 = 0;///blk=>1
	int flg6 = 0;// fwd&&mip=>1

	std::cout << "Now Reading..." << std::endl;
	while (std::getline(ifs, str)) {
		str_v = StringSplit_with_tab(str);
		//if (str_v.size() == 6) {// 1st line
		//	Vertex v;
		//	v.eid = stoi(str_v[0]);
		//	v.pl = stoi(str_v[1]);
		//	v.trk = stoi(str_v[2]);
		//	v.x = stod(str_v[3]);
		//	v.y = stod(str_v[4]);
		//	v.z = stod(str_v[5]);

		//	id = v.eid;
		//	vertex.insert(std::make_pair(id, v));
		//	tnum = v.trk;
		//	n++;

		//}

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
			//if (tnum == 2) {
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
			//}

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


}
void write_vtx_infomation(std::string filename, std::multimap<int, Vertex>& vtx) {

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
				<< std::setw(8) << std::setprecision(1) << itr0->second.z << " "
				<< std::setw(2) << std::setprecision(0) << itr0->second.nmip << " "
				<< std::setw(2) << std::setprecision(0) << itr0->second.gam << " "
				<< std::setw(2) << std::setprecision(0) << itr0->second.phi << " "
				<< std::setw(2) << std::setprecision(0) << itr0->second.rss << " "
				<< std::setw(2) << std::setprecision(0) << itr0->second.fmip
				<< std::endl;
			count++;
		}
	}
	ofs.close();
	std::cout << "event size " << count << std::endl;

}
void write(std::string filename, std::multimap<int, Vertex>& vtx, std::multimap<int, Pair>& pair, std::multimap<int, Track>& track) {

	std::ofstream ofs(filename);
	int count = 0;
	for (auto i = vtx.begin(); i != vtx.end(); i++) {
		auto v = vtx.equal_range(i->first);
			//if (v.first->second.trk == 2) {
				auto p = pair.equal_range(i->first);
				for (auto itr1 = p.first; itr1 != p.second; itr1++) {
					ofs << std::right << std::fixed
						<< std::setw(8) << std::setprecision(0) << itr1->first << " "
						<< std::setw(4) << std::setprecision(0) << itr1->second.pl1 << " "
						<< std::setw(12) << std::setprecision(0) << itr1->second.rid1 << " "
						<< std::setw(4) << std::setprecision(0) << itr1->second.pl2 << " "
						<< std::setw(12) << std::setprecision(0) << itr1->second.rid2 << " "
						<< std::setw(8) << std::setprecision(1) << itr1->second.vx << " "
						<< std::setw(8) << std::setprecision(1) << itr1->second.vy << " "
						<< std::setw(8) << std::setprecision(1) << itr1->second.vz << " "
						<< std::setw(6) << std::setprecision(4) << itr1->second.oa << " "
						<< std::setw(5) << std::setprecision(1) << itr1->second.md << " "
						<< std::setw(5) << std::setprecision(4) << itr1->second.moa << " "
						<< std::setw(5) << std::setprecision(4) << itr1->second.cosphi << " "//cop
						<< std::setw(5) << std::setprecision(4) << itr1->second.phi << " "//a(cop)

						<< std::endl;
					count++;
				}
			//}
	}
	ofs.close();
	std::cout << "event size " << count << std::endl;
}
void write_epair_list(std::string filename, std::multimap<int, Vertex>& vtx, std::multimap<int, Pair>& pair) {

	std::ofstream ofs(filename);
	int count = 0;
	for (auto i = vtx.begin(); i != vtx.end(); i++) {
		auto v = vtx.equal_range(i->first);
		//if (v.first->second.trk == 2) {
		auto p = pair.equal_range(i->first);
		for (auto itr1 = p.first; itr1 != p.second; itr1++) {
			if (itr1->second.md <= 60 - 600 * itr1->second.oa) {
				ofs << std::right << std::fixed
					<< std::setw(4) << std::setprecision(0) << itr1->second.pl1 << " "
					<< std::setw(12) << std::setprecision(0) << itr1->second.rid1 << "\n"
					<< std::setw(4) << std::setprecision(0) << itr1->second.pl2 << " "
					<< std::setw(12) << std::setprecision(0) << itr1->second.rid2
					<< std::endl;
				count++;
			}
		}
		//}
	}
	ofs.close();
	std::cout << "event size " << count << std::endl;
}

void write_track(std::string filename,std::multimap<int,Vertex>& vtx, std::multimap<int, Track>& track) {
	std::ofstream ofs(filename);
	int count = 0;
	for (auto i = vtx.begin(); i != vtx.end(); i++) {
		//ofs << std::setw(20) << std::setprecision(0) << i->first << " ";
		auto t = track.equal_range(i->first);
		for (auto itr2 = t.first; itr2 != t.second; itr2++) {
			ofs << std::right << std::fixed
				<< std::setw(8) << std::setprecision(0) << itr2->first << " "
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

