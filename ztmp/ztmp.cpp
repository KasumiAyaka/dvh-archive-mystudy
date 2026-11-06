// 
// 2022/3/15
// kasumi
// 
//PL/ISS-rawid/OSS-rawid/fixed-rawid/tracker-rawid/
//spotA*100+spotB/zone1/raw1/zone2/raw2
//unix time/t-track id/BM bunch/entry in daily file/BM nplane
//charge/BM mom/chi2_shifter[4]/eventid(í Çµî‘çÜ)/PM track type
//ECC track type
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


struct Shifter {
	int pl, zone1, raw1, zone2, raw2;
	int unixtime;
	int tracker_track_id;
	int charge;
	double momentum;
	int eventid, pm_type, ecc_type;
};
struct BaseTrack {
	int pl, rid, zone1, raw1, zone2, raw2;
};
class Key {
public:
	int pl, zone1, raw1, zone2, raw2;
};
bool operator<(const Key& lhs, const Key& rhs) {
	return std::tie(lhs.pl, lhs.zone1, lhs.raw1) < std::tie(rhs.pl, rhs.zone1, rhs.raw2);
}
struct StopTrack {
	int cid, dpl, drid, upl, urid;
};
class Label {
public:
	int pl, rid;
};
bool operator<(const Label& lhs, const Label& rhs) {
	return std::tie(lhs.pl, lhs.rid) < std::tie(rhs.pl, rhs.rid);
}
struct Shifter_Base {
	int pl, rid;
	int64_t unixtime;
	int tracker_track_id;
	int charge;
	double momentum;
	int eventid, pm_type, ecc_type;

};
struct Check {
	int unixtime, eid;
};

void Set_shifter(std::string input, std::string list, std::string output);
std::vector<std::string> StringSplit(std::string str);
std::vector<std::string> StringSplit_with_tab(std::string str);
void Set_basetrack(std::string input, std::map<Key, Shifter>& shifter, std::string output, std::map<Label, Shifter_Base>& map);
void Set_Stop(std::string filename, std::string ofilename, std::map<Label, Shifter_Base>& map);


int main(int argc, char** argv) {
	if (argc != 4) {
		fprintf(stderr, "Usage:prg input_file list output_file");
		exit(1);
	}

	std::string input = argv[1];//muon_ecc5_including_multi_w_cosmic
	std::string in_list = argv[2];//b003.sel.cor
	std::string output = argv[3];//b004.sel.cor

	auto start = std::chrono::system_clock::now();//for measure working time

	Set_shifter(input,in_list,output);//set shifter



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
void Set_shifter(std::string input, std::string list,std::string output) {
	std::ifstream ifsl(list);
	if (!ifsl) {
		std::cerr << "error" << std::endl;
		exit(1);
	}


	Check c;
	std::map<int, int> map;
	while (ifsl >> c.unixtime >> c.eid) {
		map.insert(std::make_pair(c.eid,c.unixtime));
	}


	std::ifstream ifs(input);
	if (!ifs) {
		std::cerr << "error" << std::endl;
		exit(1);
	}

	int count = 0;
	Key k;
	Shifter s;
	std::string str;					//1strein into
	std::vector<std::string> str_v;		//input 1 ward
	std::string buffer;
	std::ofstream ofs(output);
	while (std::getline(ifs, str)) {
		str_v = StringSplit_with_tab(str);
		s.eventid = std::stoi(str_v[21]);
		auto itr = map.find(s.eventid);
		if (itr != map.end()) {
			ofs << str << std::endl;
		}
		//s.pl = std::stoi(str_v[0]);//3or4
		//s.zone1 = std::stoi(str_v[6]);
		//s.raw1 = std::stoi(str_v[7]);
		//s.zone2 = std::stoi(str_v[8]);
		//s.raw2 = std::stoi(str_v[9]);
		//s.unixtime = std::stoi(str_v[10]);
		//s.tracker_track_id = std::stoi(str_v[11]);
		//s.charge = std::stod(str_v[15]);
		//s.momentum = std::stoi(str_v[16]);
		//s.eventid = std::stoi(str_v[21]);
		//s.pm_type = std::stoi(str_v[22]);
		//s.ecc_type = std::stoi(str_v[23]);
		//PL /ISS-rawid/OSS-rawid/fixed-rawid/tracker-rawid/
		//spotA*100+spotB/zone1/raw1/zone2/raw2
		//unix time/t-track id/BM bunch/entry in daily file/BM nplane
		//charge/BM mom/chi2_shifter[4]/eventid(í Çµî‘çÜ)/PM track type
		//ECC track type
		count++;
	}
	std::cout << "set shifter info" << std::endl;


}
void Set_basetrack(std::string input, std::map<Key, Shifter>& shifter, std::string output, std::map<Label, Shifter_Base>& map) {
	std::ifstream ifs(input);
	if (!ifs) {
		std::cerr << "error" << std::endl;
		exit(1);
	}
	int count = 0;
	BaseTrack b;
	Key k;
	std::string str;					//1strein into
	std::vector<std::string> str_v;		//input 1 ward
	std::string buffer;
	std::ofstream ofs(output);
	while (std::getline(ifs, str)) {
		str_v = StringSplit_with_tab(str);
		b.rid = std::stoi(str_v[0]);
		b.pl = std::stoi(str_v[1]);
		b.zone1 = std::stoi(str_v[16]);
		b.raw1 = std::stoi(str_v[18]);
		b.zone2 = std::stoi(str_v[28]);
		b.raw2 = std::stoi(str_v[30]);

		//$01 - $07->rawid, pl, isg, ax, ay, x, y
		//	$08 - $13->ph(microtrack), ax, ay(microtrack - corrected), x, y, z(basetrack - at - base - surface) ... for face - 1
		//	$14 - $19->pos, col, row, zone, isg, rawid ... for face - 1 microtrack
		//	$20 - $25->ph(microtrack), ax, ay(microtrack - corrected), x, y, z(basetrack - at - base - surface) ... for face - 2
		//	$26 - $31->pos, col, row, zone, isg, rawid ... for face - 2 microtrack
		k.pl = b.pl;
		k.raw1 = b.raw1;
		k.raw2 = b.raw2;
		k.zone1 = b.zone1;
		k.zone2 = b.zone2;


		Label l;
		Shifter_Base sb;
		auto p = shifter.find(k);
		if (p != shifter.end()) {
			ofs << b.pl << " " << b.rid << " " <<
				p->second.unixtime << " " <<
				p->second.tracker_track_id << " " <<
				p->second.charge << " " <<
				p->second.momentum << " " <<
				p->second.eventid << " " <<
				p->second.pm_type << " " <<
				p->second.ecc_type << " " <<
				std::endl;

			l.pl = b.pl;
			l.rid = b.rid;
			sb.pl = b.pl;
			sb.rid = b.rid;
			sb.unixtime = p->second.unixtime;
			sb.tracker_track_id = p->second.tracker_track_id;
			sb.charge = p->second.charge;
			sb.momentum = p->second.momentum;
			sb.eventid = p->second.eventid;
			sb.pm_type = p->second.pm_type;
			sb.ecc_type = p->second.ecc_type;
			map.insert(std::make_pair(l, sb));
			if (count < 10) {
				std::cout << b.pl << " " << b.rid << " " << b.raw1 << " " << b.zone1 << " " << b.raw2 << " " << b.zone2 << std::endl;
			}
			count++;


		}
	}
	ofs.close();
	std::cout << "set basetrack info" << std::endl;

}
void Set_Stop(std::string filename, std::string ofilename, std::map<Label, Shifter_Base>& map) {

	std::ifstream ifs(filename);		//Open File
	std::string str;					//1strein into
	std::vector<std::string> str_v;		//input 1 ward
	std::string buffer;

	std::ofstream ofs(ofilename);  //Open output file
	int count = 0;
	while (std::getline(ifs, str)) {
		str_v = StringSplit_with_tab(str);

		StopTrack s;
		Label l;

		s.cid = std::stoi(str_v[0]);
		s.dpl = std::stoi(str_v[2]);
		s.drid = std::stoi(str_v[4]);
		s.upl = std::stoi(str_v[11]);
		s.urid = std::stoi(str_v[13]);

		//ofs << std::right << std::fixed
		//0	<< std::setw(10) << std::setprecision(0) << itr->chain_id << " "
		//1	<< std::setw(4) << std::setprecision(0) << itr->nseg << " "
		//2	<< std::setw(4) << std::setprecision(0) << itr->pos0 / 10 << " "downstream
		//3	<< std::setw(10) << std::setprecision(0) << itr->basetracks.begin()->group_id << " "
		//4	<< std::setw(10) << std::setprecision(0) << itr->basetracks.begin()->rawid << " "
		//5	<< std::setw(6) << std::setprecision(0) << itr->basetracks.begin()->ph << " "
		//6	<< std::setw(7) << std::setprecision(4) << itr->basetracks.begin()->ax << " "
		//7	<< std::setw(7) << std::setprecision(4) << itr->basetracks.begin()->ay << " "
		//8	<< std::setw(8) << std::setprecision(1) << itr->basetracks.begin()->x << " "
		//9	<< std::setw(8) << std::setprecision(1) << itr->basetracks.begin()->y << " "
		//10	<< std::setw(8) << std::setprecision(1) << itr->basetracks.begin()->z << " "
		//11	<< std::setw(4) << std::setprecision(0) << itr->pos1 / 10 << " "upstream
		//12	<< std::setw(10) << std::setprecision(0) << itr->basetracks.rbegin()->group_id << " "
		//13	<< std::setw(10) << std::setprecision(0) << itr->basetracks.rbegin()->rawid << " "
		//14	<< std::endl;
		l.pl = s.dpl;
		l.rid = s.drid;

		auto p = map.find(l);
		if (p != map.end()) {
			ofs << s.cid << " " << s.dpl << " " << s.drid << " "
				<< s.upl << " " << s.urid << " " <<
				p->second.unixtime << " " <<
				p->second.tracker_track_id << " " <<
				p->second.charge << " " <<
				p->second.momentum << " " <<
				p->second.eventid << " " <<
				p->second.pm_type << " " <<
				p->second.ecc_type << " " <<
				std::endl;

			if (count < 10) {
				std::cout << s.cid << " " << s.dpl << " " << s.drid << " "
					<< s.upl << " " << s.urid << " " << p->second.eventid << std::endl;
			}
			count++;
		}
	}
	ofs.close();
	std::cout << "shifter<-->basetrack" << std::endl;


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