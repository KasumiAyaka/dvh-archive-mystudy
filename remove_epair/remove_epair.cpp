// remove_epair
// 2022/3/11
// kasumi
// read dtop track --> remove epair track
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


class Track {
public:
	int cid, nsg, dpl, upl, gid, rid,ph;
	double ax, ay, x, y, z;
};
class Key {
public:
	int upl, rid;
};
bool operator<(const Key& lhs, const Key& rhs) {
	return std::tie(lhs.upl, lhs.rid) < std::tie(rhs.upl, rhs.rid);
}

void Set_Key(std::string list, std::multiset<Key>& key);
void read_file(std::string filename, std::string output_file, std::multiset<Key>& key);
std::vector<std::string> StringSplit(std::string str);
std::vector<std::string> StringSplit_with_tab(std::string str);



int main(int argc, char** argv) {
	if (argc != 4) {
		fprintf(stderr, "Usage:prg input_file list output_file");
		exit(1);
	}

	std::string input_file = argv[1];//stop
	std::string list = argv[2];//list
	std::string output_file = argv[3];

	std::multiset< Key> key;
	Set_Key(list, key);//set key
	read_file(input_file, output_file,key);


}
void Set_Key(std::string list, std::multiset<Key>& key) {
	std::ifstream ifs(list);
	if (!ifs) {
		std::cerr << "error" << std::endl;
		exit(1);
	}

	Key k;
	while (ifs >> k.upl >> k.rid) {
		key.insert(k);
	}
}
void read_file(std::string filename, std::string ofilename, std::multiset<Key>& key) {

	std::ifstream ifs(filename);		//Open File
	std::string str;					//1strein into
	std::vector<std::string> str_v;		//input 1 ward
	std::string buffer;

	std::ofstream ofs(ofilename);  //Open output file
	std::vector<Track>trk;
	int count = 0;
	int count0 = 0;

	Track t;
	while (ifs >> t.cid >> t.nsg >> t.dpl >> t.upl >> t.gid >> t.rid >> t.ph >> t.ax >> t.ay >> t.x >> t.y >> t.z) {
		Key k;
		k.rid = t.rid;
		k.upl = t.upl;
		//}


		//while (std::getline(ifs, str)) {
		//	str_v = StringSplit_with_tab(str);

		//	Track t;
		//	Key k;
			//k.upl = std::stoi(str_v[3]);
			//k.rid = std::stoi(str_v[5]);

			//auto itr = key.find(k);
			//count0++;
			//if (itr == key.end()) {
			//	t.cid = std::stoi(str_v[0]);
			//	t.nsg = std::stoi(str_v[1]);
			//	t.dpl = std::stoi(str_v[2]);
			//	t.upl = std::stoi(str_v[3]);
			//	t.gid = std::stoi(str_v[4]);
			//	t.rid = std::stoi(str_v[5]);
			//	t.ph = std::stoi(str_v[6]);
			//	t.ax = std::stod(str_v[7]);
			//	t.ay = std::stod(str_v[8]);
			//	t.x = std::stod(str_v[9]);
			//	t.y = std::stod(str_v[10]);
			//	t.z = std::stod(str_v[11]);

		auto itr = key.find(k);
		count0++;
		if (itr == key.end()) {

			ofs << std::setw(15) << std::setprecision(0) << t.cid << " "
				<< std::setw(4) << std::setprecision(0) << t.nsg << " "
				<< std::setw(4) << std::setprecision(0) << t.dpl << " "
				<< std::setw(4) << std::setprecision(0) << t.upl << " "
				<< std::setw(15) << std::setprecision(0) << t.gid << " "
				<< std::setw(15) << std::setprecision(0) << t.rid << " "
				<< std::setw(9) << std::setprecision(0) << t.ph << " "
				<< std::setw(10) << std::setprecision(7) << t.ax << " "
				<< std::setw(10) << std::setprecision(7) << t.ay << " "
				<< std::setw(10) << std::setprecision(7) << t.x << " "
				<< std::setw(10) << std::setprecision(7) << t.y << " "
				<< std::setw(10) << std::setprecision(7) << t.z
				<< std::endl;
			count++;
		}
	}
	ofs.close();
	std::cout << "epair =" << count0 - count << std::endl;
	std::cout << "not epair=" <<  count << std::endl;

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