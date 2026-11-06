// shuffle_stop_track_position*******************************
// 2022/02/17
// kasumi
// invariant:angle,vph...(except for the position of treack, all of param is kept)
// the position of track is shuffled
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// usage:I:\NINJA\E71a\work\kasumi\MyStudy\mfile\DirectVertexHunting\VertexHunting\x64\Release\shuffle_stop_track_position.exe input output
//***********************************************************

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

#include <numeric>
#include <iterator>
#include <random>

struct Position {
	double x, y;
};
struct Track {
	int cid, nseg, dpl, upl, urid, gid, ph;
	double ax, ay, z;
};
struct Stoptrack {
	std::vector<Track> trk;
	std::vector<Position> pos;
	
};



std::vector<std::string> StringSplit(std::string str);
std::vector<std::string> StringSplit_with_tab(std::string str);

void set_stoptrack(std::string input, std::multimap<int, Track>& trk, std::multimap<int, Position>& pos);
void shuffle_position_of_track(std::multimap<int, Stoptrack>& stop, std::multimap<int, Track>& trk, std::multimap<int, Position>& pos);
void write_output_file(std::string path, std::string output, std::multimap<int, Stoptrack>& stop);


int main(int argc, char** argv) {
	if (argc != 4) {
		fprintf(stderr, "Usage:exe input.txt output.txt output_folder_path\n");
		exit(1);
	}
	std::string input = argv[1];
	std::string output = argv[2];
	std::string path = argv[3];


	std::multimap<int, Track> trk;
	std::multimap<int, Position> pos;
	std::multimap<int, Stoptrack> stop;
	set_stoptrack(input, trk, pos);
	shuffle_position_of_track(stop, trk, pos);
	write_output_file(path, output, stop);

}
void set_stoptrack(std::string input, std::multimap<int, Track>& trk, std::multimap<int, Position>& pos) {

	std::ifstream ifs(input);
	if (!ifs) {
		std::cerr << "cannot open " << input << std::endl;
		std::cin.get();
		exit(1);
	}

	Position p;
	Track s;
	while (ifs >> s.cid >> s.nseg >> s.dpl >> s.upl >> s.gid >> s.urid >> s.ph >> s.ax >> s.ay >> p.x >> p.y >> s.z) {
		trk.insert(std::make_pair(s.upl, s));
		pos.insert(std::make_pair(s.upl, p));
	}

}
void shuffle_position_of_track(std::multimap<int,Stoptrack>&stop,std::multimap<int, Track>& trk, std::multimap<int, Position>& pos) {
	//std::vector<int>v(z.size());
	//std::iota(v.begin(), v.end(), 0);

	for (int i = 3; i < 134; i++) {
		auto p = pos.find(i);
		if (p == pos.end()) continue;

		auto q = pos.equal_range(i);
		auto r = trk.equal_range(i);
		std::vector<Track> t;
		std::vector<Position> po;
		Stoptrack strack;
		for (auto itr = q.first; itr != q.second; itr++) {
			po.push_back(itr->second);
		}

		for (auto itr = r.first; itr != r.second; itr++) {
			t.push_back(itr->second);
		}

		std::random_device seed_gen;
		std::mt19937 engine(seed_gen());
		std::shuffle(po.begin(), po.end(), engine);//shuffle xy
		std::shuffle(t.begin(), t.end(), engine);//shuffle track
		
		strack.pos = po;
		strack.trk = t;

		stop.insert(std::make_pair(i, strack));
	}



}
void write_output_file(std::string path,std::string output, std::multimap<int, Stoptrack>& stop) {
	
	std::stringstream fpath;
	fpath << path << "\\" << output;
	std::string out = fpath.str();

	std::stringstream name;
	name << path << "\\num_of_trk.txt";
	std::string ss = name.str();

	std::ofstream ofs(out);
	std::ofstream memo(ss);

	for (int i = 3; i < 134; i++) {
		auto p = stop.find(i);
		if (p == stop.end()) continue;

		for (int j = 0; j < p->second.pos.size(); j++) {
			ofs << std::setw(12) << p->second.trk[j].cid << " "
				<< std::setw(3) << p->second.trk[j].nseg << " "
				<< std::setw(3) << p->second.trk[j].dpl << " "
				<< std::setw(3) << p->second.trk[j].upl << " "
				<< std::setw(12) << p->second.trk[j].gid << " "
				<< std::setw(12) << p->second.trk[j].urid << " "
				<< std::setw(7) << p->second.trk[j].ph << " "
				<< std::setw(7) << std::fixed << std::setprecision(4) << p->second.trk[j].ax << " "
				<< std::setw(7) << std::fixed << std::setprecision(4) << p->second.trk[j].ay << " "
				<< std::setw(7) << std::fixed << std::setprecision(1) << p->second.pos[j].x << " "
				<< std::setw(7) << std::fixed << std::setprecision(1) << p->second.pos[j].y << " "
				<< std::setw(7) << std::fixed << std::setprecision(1) << p->second.trk[j].z
				<< std::endl;

		}
		std::cout<< "PL" << i << "\t" << p->second.pos.size() << std::endl;
		memo << "PL" << i << "\t" << p->second.pos.size() << std::endl;

	}
	ofs.close();
	memo.close();
}

//void make_vtx(std::string name0, std::string name1) {
//	std::ifstream ifs(name0);
//	if (!ifs) {
//		std::cout << "cannot open " << name0 << " ." << std::endl;
//		std::cin.get();
//	}
//
//	std::string str;					//1strein into
//	std::vector<std::string> str_v;		//input 1 ward
//	std::string buffer;
//
//	//std::vector<Position> p;
//	std::vector<int>id;
//	std::vector<int>pl;
//	std::vector<int>raw;
//	std::vector<int>ph;
//	std::vector<double>ax;
//	std::vector<double>ay;
//	std::vector<double>x;
//	std::vector<double>y;
//	std::vector<double>z;
//	std::cout << "Now reading..." << std::endl;
//
//	while (std::getline(ifs, str)) {
//		str_v = StringSplit_with_tab(str);
//
//		//	p.push_back(Position(stoi(str_v[0]), stoi(str_v[1]), stoi(str_v[2]), stoi(str_v[3]), stod(str_v[4]),
//		//		stod(str_v[5]), stod(str_v[6]), stod(str_v[7]), stod(str_v[8])));
//
//		id.push_back(stoi(str_v[0]));
//		pl.push_back(stoi(str_v[1]));
//		raw.push_back(stoi(str_v[2]));
//		ph.push_back(stoi(str_v[3]));
//		ax.push_back(stod(str_v[4]));
//		ay.push_back(stod(str_v[5]));
//		x.push_back(stod(str_v[6]));
//		y.push_back(stod(str_v[7]));
//		z.push_back(stod(str_v[8]));
//	}
//	std::cout << pl.size() << std::endl;
//	std::cout << "Finished!" << std::endl;
//
//
//	double ac, bc, cx, cy, cz;
//	double aa, bb, ab, c, ab0, md, oa, Dz, bun;
//	double s, t, dd;
//
//	int count = 0;
//
//	std::cout << "Make vtx....." << std::endl;
//
//	std::ofstream output(name1);
//	for (int i = 0; i < pl.size(); ++i) {
//		//std::cout << pl[i] << std::endl;
//
//		for (int j = 0; j < pl.size(); ++j) {
//			if (raw[j] == raw[i]) {
//				//std::cout << pl[i] << std::endl;
//			}
//			else {
//
//				//std::cout << pl[i] << std::endl;
//				//exit(1);
//				// ‚Æ‚è‚ ‚¦‚¸‚×‚½‘‚«
//				aa = (ax[i]) * (ax[i]) + (ay[i]) * (ay[i]) + 1;
//				bb = (ax[j]) * (ax[j]) + (ay[j]) * (ay[j]) + 1;
//				ab = sqrt(aa * bb);
//				ab0 = (ax[i]) * (ax[j]) + (ay[i]) * (ay[j]) + 1;
//				bun = ab0 * ab0 - ab * ab;
//				cx = (x[i]) - (x[j]);
//				cy = (y[i]) - (y[j]);
//				cz = (z[i]) - (z[j]);
//
//				ac = cx * (ax[i]) + cy * (ay[i]) + cz;
//				bc = cx * (ax[j]) + cy * (ay[j]) + cz;
//
//				s = (((ax[i]) * (x[i] - x[j]) + (ay[i]) * (y[i] - y[j]) + (z[i] - z[j])) * ab0 - ((ax[j]) * (x[i] - x[j]) + (ay[j]) * (y[i] - y[j]) + (z[i] - z[j])) * aa) / bun;
//				t = (((ax[i]) * (x[i] - x[j]) + (ay[i]) * (y[i] - y[j]) + (z[i] - z[j])) * bb - ((ax[j]) * (x[i] - x[j]) + (ay[j]) * (y[i] - y[j]) + (z[i] - z[j])) * ab0) / bun;
//				dd = ((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]) + (z[i] - z[j]) * (z[i] - z[j]))
//					+ 2 * ((x[i] - x[j]) * (t * ax[i] - s * ax[j]) + (y[i] - y[j]) * (t * ay[i] - s * ay[j]) + (z[i] - z[j]) * (t - s))
//					+ ((t * ax[i] - s * ax[j]) * (t * ax[i] - s * ax[j]) + (t * ay[i] - s * ay[j]) * (t * ay[i] - s * ay[j]) + (t - s) * (t - s));
//				oa = acos(ab0 / ab);
//				//md = sqrt(dd);
//				Dz = 0.5 * (t + s);
//				//std::cout << "dd=" << dd << std::endl;
//
//				if (abs(pl[j] - pl[i]) < 4) {
//					if ((pl[j] % 2 == 1) | (pl[i] % 2 == 1)) {
//						if (abs(Dz) < 3500) {
//							if (dd < 30) {
//								output << count << " " << pl[i] << " " << raw[i] << " " << ph[i] << " " << ax[i] << " " << ay[i] << " " << x[i] << " " << y[i] << " " << z[i] << " " << oa << " " << dd << " " << Dz << std::endl;
//								output << count << " " << pl[j] << " " << raw[j] << " " << ph[j] << " " << ax[j] << " " << ay[j] << " " << x[j] << " " << y[j] << " " << z[j] << " " << oa << " " << dd << " " << Dz << std::endl;
//								//p.erase(itr);
//								count++;
//							}
//						}
//					}
//					if ((pl[j] % 2 == 0) & (pl[i] % 2 == 0)) {
//						if (abs(Dz) < 800) {
//							if (dd < 15) {
//								output << count << " " << pl[i] << " " << raw[i] << " " << ph[i] << " " << ax[i] << " " << ay[i] << " " << x[i] << " " << y[i] << " " << z[i] << " " << oa << " " << dd << " " << Dz << std::endl;
//								output << count << " " << pl[j] << " " << raw[j] << " " << ph[j] << " " << ax[j] << " " << ay[j] << " " << x[j] << " " << y[j] << " " << z[j] << " " << oa << " " << dd << " " << Dz << std::endl;
//								//p.erase(itr);
//								count++;
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//
//
//	std::cout << "Finished!" << std::endl;
//
//
//
//}

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