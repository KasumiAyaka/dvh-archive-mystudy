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
struct Key {
	int pl, place;
};
bool operator<(const Key& lhs, const Key& rhs) {
	return std::tie(lhs.pl, lhs.place) < std::tie(rhs.pl, rhs.place);
}
struct Area {
	int pl;
	double xmin, xmax, ymin, ymax;
	double z;
};
struct Mesh {
	int pl;
	double x, y;
};
bool operator<(const Mesh& lhs, const Mesh& rhs) {
	return std::tie(lhs.pl, lhs.x,lhs.y) < std::tie(rhs.pl, rhs.x,rhs.y);
}
struct Mtrack {
	Track t;
	Position p;
};
struct Tag {
	int tx, ty;
	int pl;
};
bool operator<(const Tag& lhs, const Tag& rhs) {
	return std::tie(lhs.pl, lhs.tx, lhs.ty) < std::tie(rhs.pl, rhs.tx, rhs.ty);
}
int f = 10;
int w = 8;



std::vector<std::string> StringSplit(std::string str);
std::vector<std::string> StringSplit_with_tab(std::string str);

void set_film_area(std::string film_area, std::map<int, Area>& area) ;
void set_stoptrack(std::string input, std::map<int, Area>& area, std::multimap<Key, Track>& trk, std::multimap<Key, Position>& pos);
void shuffle_position_of_track(std::multimap<int, Stoptrack>& stop, std::multimap<Key, Track>& trk, std::multimap<Key, Position>& pos);
void write_output_file(std::string path, int times, std::multimap<int, Stoptrack>& stop);

void set_stoptrack_for_mesh(std::string input, std::map<int, Area>& area, std::multimap<Tag, Mtrack>& trk);
void set_stoptrack_for_mesh_start(std::string input, std::map<int, Area>& area, std::multimap<Tag, Mtrack>& trk);
void shuffle_mesh(std::multimap<int, Stoptrack>& stop, std::multimap<Tag, Mtrack>& trk);

int main(int argc, char** argv) {
	if (argc != 7) {
		fprintf(stderr, "Usage:exe input.txt input_filmsize.txt output_folder_path times_of_shuffle mode mode1(stop:0/start:1)\n");
		std::cout << "mode=0:shuffle in 1place(divide into 5 place), node=1:shuffle in meshed area\n" << std::endl;
		exit(1);
	}
	std::string input = argv[1];
	std::string film_area = argv[2];
	//std::string output = argv[3];
	std::string path = argv[3];
	int n = std::stoi(argv[4]);
	int mode = std::stoi(argv[5]);
	int mode1 = std::stoi(argv[6]);

	std::map<int, Area> area;
	set_film_area(film_area, area);//get the size of each film


	if (mode == 0) {// shuffle per each place
		std::multimap<Key, Track> trk;
		std::multimap<Key, Position> pos;
		set_stoptrack(input, area, trk, pos);// get most upstream track infomation
		int count = 0;
		do {
			std::multimap<int, Stoptrack> stop;
			std::cout << count + 1 << "th" << std::endl;
			shuffle_position_of_track(stop, trk, pos);// shuffle by each area
			write_output_file(path, count, stop);// write output file
			count++;
		} while (count < n);
	}
	if (mode == 1) {// shuffle in 1 mesh
		std::multimap<Tag, Mtrack> trk;
		if (mode1 == 0) {
			set_stoptrack_for_mesh(input, area, trk);
		}
		else if (mode1 == 1) {
			set_stoptrack_for_mesh_start(input, area, trk);
		}
		else {
			std::cout << "error" << std::endl;
		}
		std::cout << "ntrk " << trk.size() << std::endl;
		int count = 0;
		do {
			std::multimap<int, Stoptrack> stop;
			std::cout << count + 1 << "th" << std::endl;
			shuffle_mesh(stop, trk);
			write_output_file(path, count, stop);// write output file
			count++;
		} while (count < n);
	}

}
void set_film_area(std::string film_area, std::map<int, Area>& area) {
	std::ifstream ifs(film_area);
	if (!ifs) {
		std::cerr << "file open error : " << film_area << std::endl;
		exit(1);
	}

	Area a;
	while (ifs >> a.pl >> a.xmin >> a.xmax >> a.ymin >> a.ymax >> a.z) {
		area.insert(std::make_pair(a.pl, a));
	}
}
void set_stoptrack(std::string input, std::map<int, Area>& area, std::multimap<Key, Track>& trk, std::multimap<Key, Position>& pos) {

	std::ifstream ifs(input);
	if (!ifs) {
		std::cerr << "cannot open " << input << std::endl;
		std::cin.get();
		exit(1);
	}

	Position p;
	Track s;
	Key k;
	double xin0, xin1, yin0, yin1, xy0, xy1;
	while (ifs >> s.cid >> s.nseg >> s.dpl >> s.upl >> s.gid >> s.urid >> s.ph >> s.ax >> s.ay >> p.x >> p.y >> s.z) {
		k.pl = s.upl;
		auto q = area.find(s.upl);
		
		xin0 = q->second.xmin + 20000;//left
		xin1 = q->second.xmax - 20000;//right
		yin0 = q->second.ymin + 20000;//bottom
		yin1 = q->second.ymax - 20000;//top
		
		//+ -
		xy0 = p.x * (q->second.ymax - q->second.ymin) / (q->second.xmax - q->second.xmin) + (q->second.ymin * q->second.xmax - q->second.ymax * q->second.xmin) / (q->second.xmax - q->second.xmin);
		xy1 = p.x * (q->second.ymin - q->second.ymax) / (q->second.xmax - q->second.xmin) + (q->second.ymax * q->second.xmax - q->second.ymin * q->second.xmin) / (q->second.xmax - q->second.xmin);

		if (p.x<xin0 && p.y>xy0 && p.y < xy1) {
			k.place = 1;
		}
		else if (p.x > xin1 && p.y < xy0 && p.y > xy1) {
			k.place = 3;
		}
		else if (p.y > yin1) {
			k.place = 2;
		}
		else if (p.y < yin0) {
			k.place = 4;
		}
		else {
			k.place = 0;
		}

		trk.insert(std::make_pair(k, s));
		pos.insert(std::make_pair(k, p));
	}

}
void shuffle_position_of_track(std::multimap<int, Stoptrack>& stop, std::multimap<Key, Track>& trk, std::multimap<Key, Position>& pos) {
	//std::vector<int>v(z.size());
	//std::iota(v.begin(), v.end(), 0);

	for (int i = 3; i < 134; i++) {

		for (int j = 0; j < 5; j++) {//shuffle by each place
			
			Key k;
			k.pl = i;
			k.place = j;
			
			auto p = pos.find(k);
			if (p == pos.end()) continue;

			auto q = pos.equal_range(k);
			auto r = trk.equal_range(k);

			std::vector<Track> t;
			std::vector<Position> po;
			Stoptrack strack;
			
			for (auto itr = q.first; itr != q.second; itr++) {//set x,y
				po.push_back(itr->second);
			}

			for (auto itr = r.first; itr != r.second; itr++) {//set track info
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



}
void write_output_file(std::string path, int times, std::multimap<int, Stoptrack>& stop) {

	std::stringstream fpath;
	fpath << path << "\\s00" << times<<".txt";
	std::string out = fpath.str();

	std::stringstream name;
	name << path << "\\num_of_trk.txt";
	std::string ss = name.str();

	std::ofstream ofs(out);
	std::ofstream memo(ss);

	int fe = 0;
	int wa = 0;
	int fen = 0;
	int wan = 0;
	for (int i = 3; i < 134; i++) {
		auto p = stop.find(i);
		if (p == stop.end()) continue;

		auto q = stop.equal_range(i);
		int a = 0;
		for (auto itr = q.first; itr != q.second; itr++) {//place 0~5
			for (int j = 0; j < itr->second.pos.size(); j++) {
				ofs << std::setw(20) << itr->second.trk[j].cid << " "
					<< std::setw(3) << itr->second.trk[j].nseg << " "
					<< std::setw(3) << itr->second.trk[j].dpl << " "
					<< std::setw(3) << itr->second.trk[j].upl << " "
					<< std::setw(12) << itr->second.trk[j].gid << " "
					<< std::setw(12) << itr->second.trk[j].urid << " "
					<< std::setw(7) << itr->second.trk[j].ph << " "
					<< std::setw(7) << std::fixed << std::setprecision(4) << itr->second.trk[j].ax << " "
					<< std::setw(7) << std::fixed << std::setprecision(4) << itr->second.trk[j].ay << " "
					<< std::setw(7) << std::fixed << std::setprecision(1) << itr->second.pos[j].x << " "
					<< std::setw(7) << std::fixed << std::setprecision(1) << itr->second.pos[j].y << " "
					<< std::setw(7) << std::fixed << std::setprecision(1) << itr->second.trk[j].z
					<< std::endl;
				a++;
			}

		}
		//std::cout << "PL" << i << "\t" << a << std::endl;
		memo << "PL" << i << "\t" << a << std::endl;
		if (i % 2 == 0) {
			fe = fe + a;
			fen++;
		}
		if (i % 2 == 1) {
			wa = wa + a;
			wan++;
		}

	}

	memo << "Fe    sum: " << fe <<
		"\nWater sum: " << wa << std::endl;
	memo << "Fe    ave: " << fe/fen <<
		"\nWater ave: " << wa/wan << std::endl;
	memo << "Fe     pl: " <<  fen <<
		"\nWater  pl: " << wan << std::endl;
	ofs.close();
	memo.close();
}

void set_stoptrack_for_mesh(std::string input, std::map<int, Area>& area, std::multimap<Tag, Mtrack>& trk) {

	std::ifstream ifs(input);
	if (!ifs) {
		std::cerr << "cannot open " << input << std::endl;
		std::cin.get();
		exit(1);
	}


	Position p;
	Track s;
	Mtrack mt;
	Tag t;
	double dx, dy;
	while (ifs >> s.cid >> s.nseg >> s.dpl >> s.upl >> s.gid >> s.urid >> s.ph >> s.ax >> s.ay >> p.x >> p.y >> s.z) {

		auto itr = area.find(s.upl);
		if (itr != area.end()) {
			if (s.upl < 16 || s.upl % 2 == 0) {
				dx = 0.5 + (itr->second.xmax - itr->second.xmin) / 10.;
				dy = 0.5 + (itr->second.ymax - itr->second.ymin) / 10.;
			}
			else if (s.upl % 2 == 1) {
				dx = 0.5 + (itr->second.xmax - itr->second.xmin) / 8.;
				dy = 0.5 + (itr->second.ymax - itr->second.ymin) / 8.;
			}
			else {
				std::cout << "unexpected error...?" << std::endl;
			}

			dx = (p.x - itr->second.xmin) / dx;
			dy = (p.y - itr->second.ymin) / dy;

			t.tx = (int)dx;
			t.ty = (int)dy;
			t.pl = s.upl;

			// *** error ***************************************
			if (s.upl < 16 || s.upl % 2 == 0) {
				if (t.tx > 9) {
					std::cout << "*** Fe ***" << std::endl;
					std::cout << "x " << t.tx << " y " << t.ty << std::endl;
				}
				if (t.ty > 9) {
					std::cout << "*** Fe ***" << std::endl;
					std::cout << "x " << t.tx << " y " << t.ty << std::endl;
				}

			}
			else if (s.upl % 2 == 1) {
				if (t.tx > 7) {
					std::cout << "*** Wa ***" << std::endl;
					std::cout << "x " << t.tx << " y " << t.ty << std::endl;
				}
				if (t.ty > 7) {
					std::cout << "*** Wa ***" << std::endl;
					std::cout << "x " << t.tx << " y " << t.ty << std::endl;
				}
			}
			// *************************************************

			mt.p = p;
			mt.t = s;
			trk.insert(std::make_pair(t, mt));
		}
	}
}
void set_stoptrack_for_mesh_start(std::string input, std::map<int, Area>& area, std::multimap<Tag, Mtrack>& trk) {

	std::ifstream ifs(input);
	if (!ifs) {
		std::cerr << "cannot open " << input << std::endl;
		std::cin.get();
		exit(1);
	}

	Position p;
	Track s;
	Mtrack mt;
	Tag t;
	double dx, dy;
	while (ifs >> s.cid >> s.nseg >> s.dpl >> s.upl >> s.gid >> s.urid >> s.ph >> s.ax >> s.ay >> p.x >> p.y >> s.z) {

		auto itr = area.find(s.dpl);
		if (itr != area.end()) {
			if (s.dpl < 16 || s.dpl % 2 == 0) {
				dx = 0.5 + (itr->second.xmax - itr->second.xmin) / f;
				dy = 0.5 + (itr->second.ymax - itr->second.ymin) / f;
			}
			else if (s.dpl % 2 == 1) {
				dx = 0.5 + (itr->second.xmax - itr->second.xmin) / w;
				dy = 0.5 + (itr->second.ymax - itr->second.ymin) / w;
			}
			else {
				std::cout << "unexpected error...?" << std::endl;
			}

			dx = (p.x - itr->second.xmin) / dx;
			dy = (p.y - itr->second.ymin) / dy;

			t.tx = (int)dx;
			t.ty = (int)dy;
			t.pl = s.dpl;

			// *** error ***************************************
			if (s.dpl < 16 || s.dpl % 2 == 0) {
				if (t.tx > f) {
					std::cout << "*** Fe ***" << std::endl;
					std::cout << "x " << t.tx << " y " << t.ty << std::endl;
				}
				if (t.ty >f) {
					std::cout << "*** Fe ***" << std::endl;
					std::cout << "x " << t.tx << " y " << t.ty << std::endl;
				}

			}
			else if (s.dpl % 2 == 1) {
				if (t.tx > w) {
					std::cout << "*** Wa ***" << std::endl;
					std::cout << "x " << t.tx << " y " << t.ty << std::endl;
				}
				if (t.ty > w) {
					std::cout << "*** Wa ***" << std::endl;
					std::cout << "x " << t.tx << " y " << t.ty << std::endl;
				}
			}
			// *************************************************

			mt.p = p;
			mt.t = s;
			trk.insert(std::make_pair(t, mt));
		}
	}
}

void shuffle_mesh(std::multimap<int, Stoptrack>& stop, std::multimap<Tag, Mtrack>& trk) {

	Tag t;
	for (int i = 3; i < 134; i++) {//pl
	//	std::cout << "PL " << i << std::endl;
		if (i < 16 || i % 2 == 0) {//Fe--->divide by 10
			for (int k = 0; k < f; k++) {//x
				//std::cout << "x  " << k << std::endl;
				for (int j = 0; j < f; j++) {//y
				//	std::cout << "y  " << j << std::endl;
					t.pl = i;
					t.tx = k;
					t.ty = j;

					auto p = trk.find(t);
					if (p == trk.end()) continue;
					//std::cout << "ntrk " << trk.count(t) << std::endl;
					auto q = trk.equal_range(t);

					std::vector<Track> t;
					std::vector<Position> po;
					Stoptrack strack;

					for (auto itr = q.first; itr != q.second; itr++) {//set x,y
							po.push_back(itr->second.p);
							t.push_back(itr->second.t);
					}
					std::random_device seed_gen;
					std::mt19937 engine(seed_gen());
					std::shuffle(po.begin(), po.end(), engine);//shuffle xy
					std::shuffle(t.begin(), t.end(), engine);//shuffle track

					strack.pos = po;
					strack.trk = t;

					stop.insert(std::make_pair(i, strack));
				}
				auto p = trk.find(t);
				if (p == trk.end()) continue;
			}
			
		}
		else if (i % 2 == 1) {//wa--->divide by 8
			//std::cout << "PL " << i << std::endl;
			for (int k = 0; k < w; k++) {//x
				for (int j = 0; j < w; j++) {//y
					t.pl = i;
					t.tx = k;
					t.ty = j;

					auto p = trk.find(t);
					if (p == trk.end()) continue;
					auto q = trk.equal_range(t);

					std::vector<Track> t;
					std::vector<Position> po;
					Stoptrack strack;

					for (auto itr = q.first; itr != q.second; itr++) {//set x,y
						po.push_back(itr->second.p);
						t.push_back(itr->second.t);
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
		}
		else {
			std::cout << "Unexpected error...??" << std::endl;
		}
	}
}
/*
void shuffle_mesh(std::multimap<int, Stoptrack>& stop, std::multimap<Mesh, Track>& trk, std::multimap<Mesh, Position>& pos, std::map<int, Area>& area) {

	Mesh m0, m1;
	for (int i = 3; i < 134; i++) {

		if (i < 16 || i % 2 == 0) {//Fe--->divide by 10
			for (int k = 0; k < 10; k++) {//x
				for (int j = 0; i < 10; j++) {//y
					double dx = (area[i].xmax - area[i].xmin) / 10.;
					double dy = (area[i].ymax - area[i].ymin) / 10.;
					m0.pl = i;
					m0.x = area[i].xmin + dx * j;
					m0.y = area[i].ymin + dy * k;

					m1.pl = i;
					m1.x = area[i].xmin + dx * (j + 1);
					m1.y = area[i].ymin + dy * (k + 1);

					if (area[i].xmin + dx * j <= m0.x && m0.x < area[i].xmin + dx * (j + 1) && area[i].ymin + dy * k <= m0.y && m0.y < area[i].ymin + dy * (k + 1)) {

						std::vector<Track> t;
						std::vector<Position> po;
						Stoptrack strack;

						auto p0 = pos.lower_bound(m0);//m0<=
						auto p1 = pos.upper_bound(m1);// <=m1

						auto q0 = trk.lower_bound(m0);//m0<=
						auto q1 = trk.upper_bound(m1);// <=m1

						for (auto itr = p0; itr != p1; itr++) {//set x,y
							po.push_back(itr->second);
						}
						for (auto itr = q0; itr != q1; itr++) {//set trk
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
			}
		}
		else if (i % 2 == 1) {//wa--->divide by 8
			for (int k = 0; k < 8; k++) {//x
				for (int j = 0; i < 8; j++) {//y
					int dx = (area[i].xmax - area[i].xmin) / 8;
					int dy = (area[i].ymax - area[i].ymin) / 8;

					m0.pl = i;
					m0.x = area[i].xmin + dx * j;
					m0.y = area[i].ymin + dy * k;

					m1.pl = i;
					m1.x = area[i].xmin + dx * (j + 1);
					m1.y = area[i].ymin + dy * (k + 1);

					std::vector<Track> t;
					std::vector<Position> po;
					Stoptrack strack;

					auto p0 = pos.lower_bound(m0);//m0<=
					auto p1 = pos.upper_bound(m1);// <=m1

					auto q0 = trk.lower_bound(m0);//m0<=
					auto q1 = trk.upper_bound(m1);// <=m1

					for (auto itr = p0; itr != p1; itr++) {//set x,y
						po.push_back(itr->second);
					}
					for (auto itr = q0; itr != q1; itr++) {//set trk
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
		}
		else {
			std::cout << "Unexpected error...??" << std::endl;
		}
	}
}
*/


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