// 
// 2022/3/15
// kasumi
// 
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


class Label {
public:
	int cid, pl;
};
bool operator<(const Label& lhs, const Label& rhs) {
	return std::tie(lhs.pl, lhs.cid) < std::tie(rhs.pl, rhs.cid);
}
struct Shifter_Stop {
	int cid, dpl, drid, upl, urid;
	int64_t unixtime;
	int tracker_track_id;
	int charge;
	double momentum;
	int eventid, pm_type, ecc_type;
};
class Track {
public:
	int id,ntrk;
	int pflg, dirflg;
	int dpl,upl, urid, cid, gid, nsg, npl, vph;
	double ax, ay, x, y, z;
};
struct Output {
	int id, ntrk;
	int dpl, drid, upl,urid, rid, cid;
	int64_t unixtime;
	int tracker_track_id;
	int charge;
	double momentum;
	int eventid, pm_type, ecc_type;
};
bool operator<(const Output& lhs, const Output& rhs) {
	return std::tie(lhs.id, lhs.cid,lhs.rid) < std::tie(rhs.id, rhs.cid,rhs.rid);
}


std::vector<std::string> StringSplit(std::string str);
std::vector<std::string> StringSplit_with_tab(std::string str);
void Set_Stop(std::string filename, std::multimap<Label, Shifter_Stop>& sh);
void Match_shifter_evecand(std::multimap<Label, Shifter_Stop>& sp, std::string input, std::string output);

int main(int argc, char** argv) {
	if (argc != 4) {
		fprintf(stderr, "Usage:prg input_file list output_file");
		exit(1);
	}

	std::string in_stop = argv[1];//shifter_ecc_list.txt
	std::string in_eve = argv[2];//nu_int_cand.txt
	std::string output = argv[3];//

	auto start = std::chrono::system_clock::now();//for measure working time

	std::multimap<Label, Shifter_Stop> sp;
	Set_Stop(in_stop,sp);//matsh stop-shifter
	Match_shifter_evecand(sp,in_eve,output);

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
void Set_Stop(std::string filename, std::multimap<Label, Shifter_Stop>& sp) {

	std::ifstream ifs(filename);		//Open File
	std::string str;					//1strein into
	std::vector<std::string> str_v;		//input 1 ward
	std::string buffer;


	Shifter_Stop s;
	Label l;
	while (ifs>>s.cid >> s.dpl >> s.drid >> s.upl >> s.urid >> s.unixtime >> 
		s.tracker_track_id >> s.charge >> s.momentum >> s.eventid >> s.pm_type >> s.ecc_type) {
		l.pl=s.dpl;
		l.cid=s.cid;
		sp.insert(std::make_pair(l, s));
	}
	std::cout << "finish reading" << std::endl;

}
void Match_shifter_evecand(std::multimap<Label, Shifter_Stop>& sp, std::string input, std::string output) {
	std::ifstream ifs(input);		//Open File
	if (!ifs) {
		std::cerr << "error" << std::endl;
		exit(1);
	}

	Label count;
	std::map<int, int> cnt;
	std::set<Output> eve;
	std::map<int, int> cnt2;
	std::set<Output> eve2;

	Track t;
	Label l;
	std::stringstream ss;

	std::ofstream ofs(output);
	while (ifs>>t.id>>t.ntrk>>t.dpl>>t.upl>>t.urid >> t.cid >> t.gid >> t.nsg >> t.npl
		>> t.vph >> t.ax >> t.ay >> t.x >> t.y >> t.z >> t.dirflg >> t.pflg) {
		l.pl=t.dpl;
		l.cid=t.cid;
		auto itr0 = sp.find(l);
		if(itr0!=sp.end()){
			auto itr = sp.equal_range(l);
			for (auto p = itr.first; p != itr.second; p++) {
				if (t.ntrk == 2) {
					ofs << std::right << std::fixed
						<< std::setw(7) << std::setprecision(0) << t.id << " "
						<< std::setw(20) << std::setprecision(0) << t.cid << " "
						<< std::setw(4) << std::setprecision(0) << t.ntrk << " "
						<< std::setw(4) << std::setprecision(0) << t.dpl << " "
						<< std::setw(12) << std::setprecision(0) << p->second.drid << " "
						<< std::setw(4) << std::setprecision(0) << t.upl << " "
						<< std::setw(12) << std::setprecision(0) << t.urid << " " <<
						p->second.unixtime << " " <<
						p->second.tracker_track_id << " " <<
						p->second.charge << " " <<
						p->second.momentum << " " <<
						p->second.eventid << " " <<
						p->second.pm_type << " " <<
						p->second.ecc_type << " " <<
						std::endl;


					Output o;
					o.id = t.id;
					o.ntrk = t.ntrk;
					o.dpl = t.dpl;
					o.drid = p->second.drid;
					o.upl = t.upl;
					o.urid = p->second.urid;
					o.cid = t.cid;
					o.unixtime = p->second.unixtime;
					o.tracker_track_id = p->second.tracker_track_id;
					o.charge = p->second.charge;
					o.momentum = p->second.momentum;
					o.eventid = p->second.eventid;
					o.pm_type = p->second.pm_type;
					o.ecc_type = p->second.ecc_type;

					eve2.insert(o);
					cnt2.insert(std::make_pair(t.id, t.ntrk));
				}
				else {
					ofs << std::right << std::fixed
						<< std::setw(7) << std::setprecision(0) << t.id << " "
						<< std::setw(20) << std::setprecision(0) << t.cid << " "
						<< std::setw(4) << std::setprecision(0) << t.ntrk << " "
						<< std::setw(4) << std::setprecision(0) << t.dpl << " "
						<< std::setw(12) << std::setprecision(0) << p->second.drid << " "
						<< std::setw(4) << std::setprecision(0) << t.upl << " "
						<< std::setw(12) << std::setprecision(0) << t.urid << " " <<
						p->second.unixtime << " " <<
						p->second.tracker_track_id << " " <<
						p->second.charge << " " <<
						p->second.momentum << " " <<
						p->second.eventid << " " <<
						p->second.pm_type << " " <<
						p->second.ecc_type << " " <<
						std::endl;


					Output o;
					o.id = t.id;
					o.ntrk = t.ntrk;
					o.dpl = t.dpl;
					o.drid = p->second.drid;
					o.upl = t.upl;
					o.urid = p->second.urid;
					o.cid = t.cid;
					o.unixtime = p->second.unixtime;
					o.tracker_track_id = p->second.tracker_track_id;
					o.charge = p->second.charge;
					o.momentum = p->second.momentum;
					o.eventid = p->second.eventid;
					o.pm_type = p->second.pm_type;
					o.ecc_type = p->second.ecc_type;

					eve.insert(o);
					cnt.insert(std::make_pair(t.id, t.ntrk));
				}
			}
		}
	}
	std::cout << eve2.size()<<"\n";
	std::cout << eve.size()<<"\n";
	ofs.close();
	
	std::ofstream ofs2("output2.txt");
	std::ofstream ofs_list2("event_id_list_2.txt");

	for (auto itr = eve2.begin(); itr != eve2.end(); itr++) {
		ofs_list2 << itr->id << std::endl;

		ofs2 << std::right << std::fixed
			<< std::setw(7) << std::setprecision(0) << itr->id << " "
			<< std::setw(20) << std::setprecision(0) << itr->cid << " "
			<< std::setw(4) << std::setprecision(0) << itr->ntrk << " "
			<< std::setw(4) << std::setprecision(0) << itr->dpl << " "
			<< std::setw(12) << std::setprecision(0) << itr->drid << " "
			<< std::setw(4) << std::setprecision(0) << itr->upl << " "
			<< std::setw(12) << std::setprecision(0) << itr->urid << " " <<
			itr->unixtime << " " <<
			itr->tracker_track_id << " " <<
			itr->charge << " " <<
			itr->momentum << " " <<
			itr->eventid << " " <<
			itr->pm_type << " " <<
			itr->ecc_type << " " <<
			std::endl;
	}
	ofs2.close();
	ofs_list2.close();

	std::ofstream ofsm("outputm.txt");
	std::ofstream ofs_listm("event_id_list_m.txt");

	for (auto itr = eve.begin(); itr != eve.end(); itr++) {
		ofs_listm << itr->id << std::endl;


		ofsm << std::right << std::fixed
			<< std::setw(7) << std::setprecision(0) << itr->id << " "
			<< std::setw(20) << std::setprecision(0) << itr->cid << " "
			<< std::setw(4) << std::setprecision(0) << itr->ntrk << " "
			<< std::setw(4) << std::setprecision(0) << itr->dpl << " "
			<< std::setw(12) << std::setprecision(0) << itr->drid << " "
			<< std::setw(4) << std::setprecision(0) << itr->upl << " "
			<< std::setw(12) << std::setprecision(0) << itr->urid << " " <<
			itr->unixtime << " " <<
			itr->tracker_track_id << " " <<
			itr->charge << " " <<
			itr->momentum << " " <<
			itr->eventid << " " <<
			itr->pm_type << " " <<
			itr->ecc_type << " " <<
			std::endl;



	}
	ofsm.close();
	ofs_listm.close();

	int a = cnt.size();
	int b = 0;
	int c = 0;
	for (auto itr = cnt.begin(); itr != cnt.end(); itr++) {
		if (itr->second == 2) {
			b++;
		}
		else {
			c++;
		}
	}
	std::cout << "num of event=" << a <<std::endl;
	std::cout << "num of 2vtx =" << b << std::endl;
	std::cout << "num of multi=" << c << std::endl;
	std::ofstream out("num.txt");
	out << a << " " << b << " " << c << " " << std::endl;
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