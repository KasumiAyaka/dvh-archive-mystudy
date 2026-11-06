// 
// 2023/9/4
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
	int IssId, OssId, FixedId;
	int spot;
};
struct SharingFile {
	Shifter s;
	int trackerId;//rawid

	int unixtime;
	int tracker_track_id;
	int charge;
	double momentum;
	int eventid, pm_type, ecc_type;
};
struct OssBasetrack {
	int RawId, pl;
	double ax, ay, x, y;
};
struct OssIssLinklet {
	int pos0, pos1, id0, id1;//pos1==110
	double ax0, ay0, x0, y0, ax1, ay1, x1, y1;
};
struct Key {
	int ido, idi;
};
bool operator<(const Key& lhs, const Key& rhs) {
	return std::tie(lhs.ido, lhs.idi) < std::tie(rhs.ido, rhs.idi);
}


std::vector<std::string> StringSplit(std::string str);
std::vector<std::string> StringSplit_with_tab(std::string str);

void ReadSharingFile(std::string input, std::multimap<int, SharingFile>& sf);
void Set_basetrack(std::string input, std::multimap<int, SharingFile>& sf, std::string output);

void SetLinklet(std::string input, std::multimap<Key, OssIssLinklet>& oil);
void OutputIssOssLinklet(std::string input, std::multimap<Key, OssIssLinklet>& oil3, std::multimap<Key, OssIssLinklet>& oil4, std::string output);


int main(int argc, char** argv) {
	if (argc != 5) {
		fprintf(stderr, "Usage:prg in_sharingfile in_oss output_file mode\n");
		fprintf(stderr, "mode 1 : add oss info to sf\n");
		fprintf(stderr, "mode 2 : add oss info to sf->linklet");

		exit(1);
	}

	std::string in_sf = argv[1];//muon_ecc5_including_multi_w_cosmic
	std::string in_basetrack = argv[2];//OSS basetrack
	std::string output_file = argv[3];//output
	int mode = std::stoi(argv[4]);
	auto start = std::chrono::system_clock::now();//for measure working time

	if (mode == 1) {
		std::multimap<int, SharingFile>sf;
		ReadSharingFile(in_sf, sf);
		Set_basetrack(in_basetrack, sf, output_file);
	}
	else if (mode == 2) {
		std::string in3, in4, sf,output;
		std::cout << "input in3,in4,sf,output" << std::endl;
		std::cin >> in3 >> in4 >> sf>>output;
		std::multimap<Key, OssIssLinklet> oil3;
		std::multimap<Key, OssIssLinklet> oil4;
		SetLinklet(in3, oil3);
		SetLinklet(in4, oil4);
		OutputIssOssLinklet(sf, oil3, oil4, output);
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
void ReadSharingFile(std::string input, std::multimap<int, SharingFile>& sf) {
	std::ifstream ifs(input);
	if (!ifs) {
		std::cerr << "error" << std::endl;
		exit(1);
	}

	int count = 0;
	SharingFile s;
	std::string str;					//1strein into
	std::vector<std::string> str_v;		//input 1 ward
	std::string buffer;

	while (std::getline(ifs, str)) {
		str_v = StringSplit_with_tab(str);
		s.s.pl = std::stoi(str_v[0]);//3or4
		s.s.IssId = std::stoi(str_v[1]);
		s.s.OssId = std::stoi(str_v[2]);
		s.s.FixedId = std::stoi(str_v[3]);
		s.trackerId = std::stoi(str_v[4]);
		s.s.spot = std::stoi(str_v[5]);

		s.s.zone1 = std::stoi(str_v[6]);
		s.s.raw1 = std::stoi(str_v[7]);
		s.s.zone2 = std::stoi(str_v[8]);
		s.s.raw2 = std::stoi(str_v[9]);
		s.unixtime = std::stoi(str_v[10]);
		s.tracker_track_id = std::stoi(str_v[11]);
		s.charge = std::stod(str_v[15]);
		s.momentum = std::stoi(str_v[16]);
		s.eventid = std::stoi(str_v[21]);
		s.pm_type = std::stoi(str_v[22]);
		s.ecc_type = std::stoi(str_v[23]);
		//PL /ISS-rawid/OSS-rawid/fixed-rawid/tracker-rawid/
		//spotA*100+spotB/zone1/raw1/zone2/raw2
		//unix time/t-track id/BM bunch/entry in daily file/BM nplane
		//charge/BM mom/chi2_shifter[4]/eventid(í Çµî‘çÜ)/PM track type
		//ECC track type
		sf.insert(std::make_pair(s.s.OssId, s));
		if (count < 10) {
			std::cout << s.s.pl << " " << s.s.IssId << " " << s.s.OssId << std::endl;
		}
		count++;
	}
	std::cout << "set shifter info" << std::endl;


}

void Set_basetrack(std::string input, std::multimap<int, SharingFile>& sf, std::string output) {
	std::ifstream ifs(input);
	if (!ifs) {
		std::cerr << "error" << std::endl;
		exit(1);
	}
	int count = 0;
	OssBasetrack ob;
	std::string str;					//1strein into
	std::vector<std::string> str_v;		//input 1 ward
	std::string buffer;
	std::ofstream ofs(output);
	while (std::getline(ifs, str)) {
		str_v = StringSplit_with_tab(str);
		ob.RawId = std::stoi(str_v[0]);
		ob.pl = std::stoi(str_v[1]);
		ob.ax = std::stod(str_v[2]);
		ob.ay = std::stod(str_v[3]);
		ob.x = std::stod(str_v[4]);
		ob.y = std::stod(str_v[5]);

		//$01 - $07->rawid, pl, isg, ax, ay, x, y
		//	$08 - $13->ph(microtrack), ax, ay(microtrack - corrected), x, y, z(basetrack - at - base - surface) ... for face - 1
		//	$14 - $19->pos, col, row, zone, isg, rawid ... for face - 1 microtrack
		//	$20 - $25->ph(microtrack), ax, ay(microtrack - corrected), x, y, z(basetrack - at - base - surface) ... for face - 2
		//	$26 - $31->pos, col, row, zone, isg, rawid ... for face - 2 microtrack

		if (sf.find(ob.RawId) != sf.end()) {
			auto itr0 = sf.equal_range(ob.RawId);
			int cnt = 0;
			for (auto itr = itr0.first; itr != itr0.second; itr++) {

				ofs << std::right << std::fixed
					<< std::setw(3) << std::setprecision(0) << cnt << " "
					<< std::setw(12) << std::setprecision(0) << ob.RawId << " "
					<< std::setw(4) << std::setprecision(0) << ob.pl << " "
					<< std::setw(10) << std::setprecision(4) << ob.ax << " "
					<< std::setw(10) << std::setprecision(4) << ob.ay << " "
					<< std::setw(10) << std::setprecision(1) << ob.x << " "
					<< std::setw(10) << std::setprecision(1) << ob.y << " "
					<< std::setw(4) << std::setprecision(0) << itr->second.s.pl << " "
					<< std::setw(12) << std::setprecision(0) << itr->second.s.IssId << " "
					<< std::setw(12) << std::setprecision(0) << itr->second.s.FixedId << " "
					<< std::setw(4) << std::setprecision(0) << itr->second.s.spot << " "
					<< std::setw(4) << std::setprecision(0) << itr->second.eventid << " "
					<< std::setw(20) << std::setprecision(0) << itr->second.unixtime
					<< std::endl;
				cnt++;
			}
		}
		else {

		}
	}

}


void SetLinklet(std::string input, std::multimap<Key, OssIssLinklet>& oil) {
	std::ifstream ifs(input);
	if (!ifs) {
		std::cerr << "error" << std::endl;
		exit(1);
	}

	int count = 0;
	OssIssLinklet s;
	std::string str;					//1strein into
	std::vector<std::string> str_v;		//input 1 ward
	std::string buffer;
	Key k;

	while (std::getline(ifs, str)) {
		str_v = StringSplit_with_tab(str);
		s.pos0 = std::stoi(str_v[0])/10;//3or4
		s.id0 = std::stoi(str_v[1]);
		s.pos1 = std::stoi(str_v[2])/10;
		s.id1 = std::stoi(str_v[3]);//oss
		s.ax0 = std::stod(str_v[4]);
		s.ay0 = std::stod(str_v[5]);
		s.x0 = std::stod(str_v[6]);
		s.y0 = std::stod(str_v[7]);
		s.ax1 = std::stod(str_v[8]);
		s.ay1 = std::stod(str_v[9]);
		s.x1 = std::stod(str_v[10]);
		s.y1 = std::stod(str_v[11]);

		k.idi = s.id0;
		k.ido = s.id1;
		oil.insert(std::make_pair(k, s));
		if (count < 10) {
			std::cout << s.pos0 << " " << s.pos1 << std::endl;
		}
		count++;
	}
	std::cout << "set shifter info" << std::endl;
}
void OutputIssOssLinklet(std::string input, std::multimap<Key, OssIssLinklet>& oil3, std::multimap<Key, OssIssLinklet>& oil4, std::string output) {
	std::ifstream ifs(input);
	if (!ifs) {
		std::cerr << "error" << std::endl;
		exit(1);
	}
	int count = 0;
	SharingFile s;
	OssBasetrack ob;
	int cnt = 0;
	std::string str;					//1strein into
	std::vector<std::string> str_v;		//input 1 ward
	std::string buffer;
	std::ofstream ofs(output);
	Key k;
	while (std::getline(ifs, str)) {
		str_v = StringSplit_with_tab(str);

		cnt = std::stoi(str_v[0]);
		s.s.OssId = std::stoi(str_v[1]);
		ob.pl = std::stoi(str_v[2]);
		ob.ax = std::stod(str_v[3]);
		ob.ay = std::stod(str_v[4]);
		ob.x = std::stod(str_v[5]);
		ob.y = std::stod(str_v[6]);
		s.s.pl = std::stoi(str_v[7]);//3or4
		s.s.IssId = std::stoi(str_v[8]);
		s.s.FixedId = std::stoi(str_v[9]);
		s.s.spot = std::stoi(str_v[10]);
		s.eventid = std::stoi(str_v[11]);
		s.unixtime = std::stoi(str_v[12]);
		k.idi = s.s.IssId;
		k.ido = s.s.OssId;

		if (s.s.pl == 3){
			
			if (oil3.find(k) != oil3.end()) {
				auto itr0 = oil3.equal_range(k);
				int cnt = 0;
				for (auto itr = itr0.first; itr != itr0.second; itr++) {

					ofs << std::right << std::fixed
						<< std::setw(3) << std::setprecision(0) << cnt << " "
						<< std::setw(12) << std::setprecision(0) << s.s.OssId << " "
						<< std::setw(4) << std::setprecision(0) << ob.pl << " "
						<< std::setw(10) << std::setprecision(4) << ob.ax << " "
						<< std::setw(10) << std::setprecision(4) << ob.ay << " "
						<< std::setw(10) << std::setprecision(1) << ob.x << " "
						<< std::setw(10) << std::setprecision(1) << ob.y << " "
						<< std::setw(4) << std::setprecision(0) << s.s.pl << " "
						<< std::setw(12) << std::setprecision(0) << s.s.IssId << " "
						<< std::setw(12) << std::setprecision(0) << s.s.FixedId << " "
						<< std::setw(4) << std::setprecision(0) << s.s.spot << " "
						<< std::setw(4) << std::setprecision(0) << s.eventid << " "
						<< std::setw(20) << std::setprecision(0) << s.unixtime
						<< std::setw(10) << std::setprecision(4) << itr->second.ax1 - itr->second.ax0 << " "
						<< std::setw(10) << std::setprecision(4) << itr->second.ay1 - itr->second.ay0 << " "
						<< std::setw(10) << std::setprecision(1) << itr->second.x1 - itr->second.x0 << " "
						<< std::setw(10) << std::setprecision(1) << itr->second.y1 - itr->second.y0
						<< std::endl;
				}
			}
			else {
				std::cout << "?"<<std::endl;
			}
		}
		else if (s.s.pl == 4) {
			if (oil4.find(k) != oil4.end()) {
				auto itr0 = oil4.equal_range(k);
				int cnt = 0;
				for (auto itr = itr0.first; itr != itr0.second; itr++) {

					ofs << std::right << std::fixed
						<< std::setw(3) << std::setprecision(0) << cnt << " "
						<< std::setw(12) << std::setprecision(0) << s.s.OssId << " "
						<< std::setw(4) << std::setprecision(0) << ob.pl << " "
						<< std::setw(10) << std::setprecision(4) << ob.ax << " "
						<< std::setw(10) << std::setprecision(4) << ob.ay << " "
						<< std::setw(10) << std::setprecision(1) << ob.x << " "
						<< std::setw(10) << std::setprecision(1) << ob.y << " "
						<< std::setw(4) << std::setprecision(0) << s.s.pl << " "
						<< std::setw(12) << std::setprecision(0) << s.s.IssId << " "
						<< std::setw(12) << std::setprecision(0) << s.s.FixedId << " "
						<< std::setw(4) << std::setprecision(0) << s.s.spot << " "
						<< std::setw(4) << std::setprecision(0) << s.eventid << " "
						<< std::setw(20) << std::setprecision(0) << s.unixtime
						<< std::setw(10) << std::setprecision(4) << itr->second.ax1 - itr->second.ax0 << " "
						<< std::setw(10) << std::setprecision(4) << itr->second.ay1 - itr->second.ay0 << " "
						<< std::setw(10) << std::setprecision(1) << itr->second.x1 - itr->second.x0 << " "
						<< std::setw(10) << std::setprecision(1) << itr->second.y1 - itr->second.y0
						<< std::endl;
				}
			}
			else {
				std::cout << "?" << std::endl;
			}

		}
		else {
			std::cout << "not found" << std::endl;
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