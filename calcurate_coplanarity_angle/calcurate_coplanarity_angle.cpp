// calcurate_coplanarity_angle *****************************
// 2022/02/17
// kasumi
// input vtx.bwd.txt
// output format
// eid pl #trk x y z
// pl1 rid1 pl2 rid2 vx vy dz oa md phi
// dpl upl urid cid gid nsg npl nph ax ay x y z bwdflg blkflg
// ***
// phi_angle (coplanarity_angle)[degree]
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
//#include <complex>//acos,sqrt
//#include <filesystem>// treat file-name/path/...

class Vertex {
public:
	int eid, pl, trk;// eid is unique
	double x, y, z;
};
class Pair {
public:
	int pl1, rid1, pl2, rid2;
	double vx, vy, vz, oa, md;
};
class Track {
public:
	//int labelt;
	int pflg, dflg;//p->mip/blk,d->fwd/bwd
	int dpl, upl, rid, cid, gid, nsg, npl, vph;
	double ax, ay, x, y, z;
};
struct Tkey {
	int id, rid;
};
bool operator<(const Tkey& lhs, const Tkey& rhs) {
	return std::tie(lhs.id, lhs.rid) < std::tie(rhs.id, rhs.rid);
}
struct OA_Cop {
	double moa, cosp,phi;
};
struct OCkey {
	int i1, i2;
};
bool operator<(const OCkey& lhs, const  OCkey& rhs) {
	return std::tie(lhs.i1, lhs.i2) < std::tie(rhs.i1, rhs.i2);
}

std::vector<std::string> StringSplit(std::string str);
std::vector<std::string> StringSplit_with_tab(std::string str);

void read_file(std::string filename, std::multimap<int, Vertex>& vtx, std::multimap<int, Pair>& pair, std::multimap<int, Track>& track);
void write(std::string filename, std::multimap<int, Vertex>& vtx, std::multimap<int, Pair>& pair, std::multimap<int, Track>& track, std::multimap<OCkey, OA_Cop>& oac);
void calc_oa_phi(std::string filename, std::multimap<int, Vertex>& vtx, std::multimap<int, Pair>& pair, std::multimap<int, Track>& track, std::multimap<OCkey, OA_Cop>& oac);

void read_file_v2(std::string filename, std::multimap<int, Vertex>& vtx, std::multimap<int, Pair>& pair, std::multimap<int, Track>& trk, std::multimap<int, OCkey>& key, std::multimap<Tkey, Track>& track);
void calc_oa_phi_v2(std::string filename, std::multimap<int, Vertex>& vtx, std::multimap<int, OCkey>& key, std::multimap<Tkey, Track>& track, std::multimap<OCkey, OA_Cop>& oac);

int main(int argc, char** argv) {
	if (argc != 3) {
		fprintf(stderr, "usage:prg input-vertex-file output\n");
		exit(1);
	}
	std::string file_in_vtx = argv[1];
	//std::string path = argv[2];
	//int mode = std::stoi(argv[3]);
	std::string output = argv[2];


	auto start = std::chrono::system_clock::now();//for measure working time

	std::multimap<int, Vertex>vtx;
	std::multimap<int, Pair>pair;
	std::multimap<int, Track> trk;
	std::multimap<OCkey, OA_Cop> oac;

	//read_file(file_in_vtx, vtx, pair, trk);
	//calc_oa_phi(output, vtx, pair, trk, oac);

	std::multimap<int, OCkey> key;
	std::multimap<Tkey, Track> track;
	read_file_v2(file_in_vtx, vtx, pair,trk, key,track);
	calc_oa_phi_v2(output, vtx, key, track, oac);

	write(output, vtx, pair, trk, oac);

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

void read_file(std::string filename, std::multimap<int, Vertex>& vtx, std::multimap<int, Pair>& pair, std::multimap<int, Track>& track) {

	//file open
	std::ifstream ifs(filename);

	std::string str;
	std::vector<std::string> str_v;
	std::string buffer;
	int cnt = 0;

	int l = 0;
	int label = 0;// event id
	int a = 0;

	std::cout << "Now Reading..." << std::endl;
	while (std::getline(ifs, str))
	{
		str_v = StringSplit_with_tab(str);

		if (str_v.size() == 6) {// 1st line
			Vertex v;
			v.eid = stoi(str_v[0]);
			v.pl = stoi(str_v[1]);
			v.trk = stoi(str_v[2]);
			v.x = stod(str_v[3]);
			v.y = stod(str_v[4]);
			v.z = stod(str_v[5]);

			l = v.pl;
			label = v.eid;
			vtx.insert(std::make_pair(label, v));

		}
		else if (str_v.size() == 9) {// 2nd line
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
		else if (str_v.size() == 15) {// 3rd line

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
			t.dflg = stoi(str_v[13]);
			t.pflg = stoi(str_v[14]);
			// set label&rid for calcuration
			Tkey k;
			k.id = label;
			k.rid = t.rid;

			track.insert(std::make_pair(label, t));

		}
		else {
			std::cout << "error?" << std::endl;
		}
	}

	std::cout << "***check***\n";
	std::cout << "vtx size = " << vtx.size() <<
		"\npair size= " << pair.size() <<
		"\ntrack size=" << track.size() << std::endl;
	std::cout << "***************" << std::endl;;
}
void calc_oa_phi(std::string filename, std::multimap<int, Vertex>& vtx, std::multimap<int, Pair>& pair, std::multimap<int, Track>& track, std::multimap<OCkey, OA_Cop>& oac) {
	OCkey key;

	// direction of nu beam
	double nx = -0.0684;
	double ny = -0.1121;

	for (auto i = vtx.begin(); i != vtx.end(); i++) {//run event
		auto v = vtx.find(i->first);

		auto p = pair.equal_range(i->first);
		for (auto itr1 = p.first; itr1 != p.second; itr1++) {// run pair

			key.i1 = itr1->second.rid1;
			key.i2 = itr1->second.rid2;

			int count = 0;

			Track tk1, tk2;
			OA_Cop oa;

			auto t = track.equal_range(i->first);
			for (auto itr2 = t.first; itr2 != t.second; itr2++) {//track
				//double ax1 = 0, ay1 = 0, ax2 = 0, ay2 = 0;

				if (itr2->second.rid == key.i1) {
					tk1 = itr2->second;
					//ax1 = itr2->second.ax;
					//ay1 = itr2->second.ay;
					count++;
					//if (tk1.ax == 0) {
					//	std::cout << "reading error? " << tk1.upl << " " << tk1.rid << std::endl;
					//}
				}
				if (itr2->second.rid == key.i2) {
					tk2 = itr2->second;
					//ax2 = itr2->second.ax;
					//ay2 = itr2->second.ay;
					count++;

				}

				if (count == v->second.trk) {
					double angle = acos((tk1.ax * tk2.ax + tk1.ay * tk2.ay + 1) / (sqrt(tk1.ax * tk1.ax + tk1.ay * tk1.ay + 1) * sqrt(tk2.ax * tk2.ax + tk2.ay * tk2.ay + 1)));
					//double angle = acos((ax1 * ax2 + ay1 * ay2 + 1) / (sqrt(ax1 * ax1 + ay1 * ay1 + 1) * sqrt(ax2 * ax2 + ay2 * ay2 + 1)));//////
					//double cop = ((tk1.ax - nx) * (tk2.ax - nx) + (tk1.ay - ny) * (tk2.ay - ny)) / (sqrt((tk1.ax - nx) * (tk1.ax - nx) + (tk1.ay - ny) * (tk1.ay - ny)) * sqrt((tk2.ax - nx) * (tk2.ax - nx) + (tk2.ay - ny) * (tk2.ay - ny)));

					//absolute of each vector
					double nu_abs = nx * nx + ny * ny + 1;//a^2
					double abs1 = tk1.ax * tk1.ax + tk1.ay * tk1.ay + 1;//b^2
					double abs2 = tk2.ax * tk2.ax + tk2.ay * tk2.ay + 1;//c^2

					// dot product
					double nu_p1 = nx * tk1.ax + ny * tk1.ay + 1; //a*b
					double nu_p2 = nx * tk2.ax + ny * tk2.ay + 1; //a*c
					double p1_p2 = tk1.ax * tk2.ax + tk1.ay * tk2.ay + 1; //b*c

					double phi_k = nu_abs * p1_p2 - nu_p1 * nu_p2;
					double phi_m = std::sqrt(nu_abs * abs1 - nu_p1 * nu_p1) * std::sqrt(nu_abs * abs2 - nu_p2 * nu_p2);

					double cos_phi = phi_k / phi_m;
					if (phi_m == 0) {///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						double cos_phi = 10;
					}
					double phi = std::acos(cos_phi) * 180 / 3.141592653589793;

					oa.moa = angle;
					oa.cosp = cos_phi;
					oa.phi = phi;
					oac.insert(std::make_pair(key, oa));
					count = 0;
					continue;
				}
			}
			if (count != 0) {
				std::cout << "reading error? " << std::endl;
			}

		}


	}


}
void write(std::string filename, std::multimap<int, Vertex>& vtx, std::multimap<int, Pair>& pair, std::multimap<int, Track>& track, std::multimap<OCkey, OA_Cop>& oac) {

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
				<< std::setw(4) << std::setprecision(1) << itr1->second.md << " ";
			OCkey k;
			k.i1 = itr1->second.rid1;
			k.i2 = itr1->second.rid2;
			auto o = oac.find(k);
			ofs << std::setw(5) << std::setprecision(4) << o->second.moa << " "//oa
				<< std::setw(5) << std::setprecision(4) << o->second.cosp << " "//cosphi
				<< std::setw(5) << std::setprecision(4) << o->second.phi << " "//a(cop)
				<< std::endl;

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
				<< std::setw(8) << std::setprecision(1) << itr2->second.dflg << " "
				<< std::setw(8) << std::setprecision(1) << itr2->second.pflg << " "
				<< std::endl;//itr->first=ip

		}

		count++;
	}
	ofs.close();
	std::cout << "event size " << count << std::endl;
}

void read_file_v2(std::string filename, std::multimap<int, Vertex>& vtx, std::multimap<int,Pair>& pair, std::multimap<int, Track>& trk,std::multimap<int, OCkey>& key, std::multimap<Tkey, Track>& track) {

	//file open
	std::ifstream ifs(filename);

	std::string str;
	std::vector<std::string> str_v;
	std::string buffer;
	int cnt = 0;

	int l = 0;
	int event_id = 0;// event id
	int a = 0;

	std::cout << "Now Reading..." << std::endl;
	while (std::getline(ifs, str))
	{
		str_v = StringSplit_with_tab(str);

		if (str_v.size() == 6) {// 1st line
			Vertex v;
			v.eid = stoi(str_v[0]);
			v.pl = stoi(str_v[1]);
			v.trk = stoi(str_v[2]);
			v.x = stod(str_v[3]);
			v.y = stod(str_v[4]);
			v.z = stod(str_v[5]);

			l = v.pl;
			event_id = v.eid;
			vtx.insert(std::make_pair(event_id, v));

		}
		else if (str_v.size() == 9) {// 2nd line
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

			pair.insert(std::make_pair(event_id, p));

			OCkey k;
			k.i1 = p.rid1;
			k.i2 = p.rid2;
			key.insert(std::make_pair(event_id, k));

		}
		else if (str_v.size() == 15) {// 3rd line

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
			t.dflg = stoi(str_v[13]);
			t.pflg = stoi(str_v[14]);
			// set label&rid for calcuration
			Tkey k;
			k.id = event_id;
			k.rid = t.rid;

			track.insert(std::make_pair(k, t));
			trk.insert(std::make_pair(event_id, t));

		}
		else {
			std::cout << "error?" << std::endl;
		}
	}

	std::cout << "***check***\n";
	std::cout << "vtx size = " << vtx.size() <<
		"\npair size= " << key.size() <<
		"\ntrack size=" << track.size() << std::endl;
}
void calc_oa_phi_v2(std::string filename, std::multimap<int, Vertex>& vtx, std::multimap<int, OCkey>& key, std::multimap<Tkey, Track>& track, std::multimap<OCkey, OA_Cop>& oac) {

	Tkey t1, t2;
	// direction of nu beam
	double nx = -0.0684;
	double ny = -0.1121;

	for (auto i = vtx.begin(); i != vtx.end(); i++) {//run event
		auto v = vtx.find(i->first);

		auto q = key.equal_range(i->first);//the set of rawid
		for (auto p = q.first; p != q.second; p++) {
			t1.id = p->first;
			t1.rid = p->second.i1;

			t2.id = p->first;
			t2.rid = p->second.i2;

			auto trk1 = track.find(t1);
			auto trk2 = track.find(t2);

			OA_Cop oa;
			Track tk1, tk2;

			tk1 = trk1->second;
			tk2 = trk2->second;

			double angle = acos((tk1.ax * tk2.ax + tk1.ay * tk2.ay + 1) / (sqrt(tk1.ax * tk1.ax + tk1.ay * tk1.ay + 1) * sqrt(tk2.ax * tk2.ax + tk2.ay * tk2.ay + 1)));

			//absolute of each vector
			double nu_abs = nx * nx + ny * ny + 1;//a^2
			double abs1 = tk1.ax * tk1.ax + tk1.ay * tk1.ay + 1;//b^2
			double abs2 = tk2.ax * tk2.ax + tk2.ay * tk2.ay + 1;//c^2

			// dot product
			double nu_p1 = nx * tk1.ax + ny * tk1.ay + 1; //a*b
			double nu_p2 = nx * tk2.ax + ny * tk2.ay + 1; //a*c
			double p1_p2 = tk1.ax * tk2.ax + tk1.ay * tk2.ay + 1; //b*c

			//double ax1 = trk1->second.ax;
			//double ay1 = trk1->second.ay;

			//double ax2 = trk2->second.ax;
			//double ay2 = trk2->second.ay;

			//double angle = acos((ax1 * ax2 + ay1 * ay2 + 1) / (sqrt(ax1 * ax1 + ay1 * ay1 + 1) * sqrt(ax2 * ax2 + ay2 * ay2 + 1)));

			////absolute of each vector
			//double nu_abs = nx * nx + ny * ny + 1;//a^2
			//double abs1 = ax1 * ax1 + ay1 * ay1 + 1;//b^2
			//double abs2 = ax2 * ax2 + ay2 * ay2 + 1;//c^2

			//// dot product
			//double nu_p1 = nx * ax1 + ny * ay1 + 1; //a*b
			//double nu_p2 = nx * ax2 + ny * ay2 + 1; //a*c
			//double p1_p2 = ax1 * ax2 + ay1 * ay2 + 1; //b*c

			double phi_k = nu_abs * p1_p2 - nu_p1 * nu_p2;
			double phi_m = std::sqrt(nu_abs * abs1 - nu_p1 * nu_p1) * std::sqrt(nu_abs * abs2 - nu_p2 * nu_p2);

			double cos_phi = phi_k / phi_m;
			if (phi_m == 0) {///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				double cos_phi = 10;
			}
			double phi = std::acos(cos_phi) * 180 / 3.141592653589793;

			oa.moa = angle;
			oa.cosp = cos_phi;
			oa.phi = phi;

			oac.insert(std::make_pair(p->second, oa));
			continue;
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

