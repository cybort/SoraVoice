﻿#include <iostream>
#include <fstream>
#include <iomanip>

#include "Common.h"

#define ATTR_SNT "._SN.txt"
#define ATTR_OUT ".txt"
#define REP_NAME "snt_report.txt"

#define MAXCH_ONELINE 2048

#define FLAG_CLEAR 0
#define FLAG_SAY 1
#define FLAG_TEXT 2
#define FLAG_TALK 4
#define FLAG_MENU 8


#define STR_SAY "say"
#define STR_TEXT "text"
#define STR_TALK "talk"
#define STR_4TBL "\t\t\t\t"
#define CH_TBL '\t'
#define CH_SQ '\''

constexpr char Seperator[] = "#-------------------------------------------------------------------#";

using namespace std;

int main(int argc, char* argv[])
{
	if (argc <= 1) {
		cout << "Usage:\n"
			"\t" "Exporter_SNT dir_snt [dir_out]\n"
			"\n"
			"Default: dir_out = dir_snt.out"
			<< endl;
		return 0;
	}

	string dir_snt = argv[1];  while (dir_snt.back() == '/' || dir_snt.back() == '\\') dir_snt.pop_back();
	string dir_out = argc > 2 ? argv[2] : dir_snt + ".out";

	Sora::MakeDirectory(dir_out);
	if (dir_out.length() > 0 && dir_out.back() != '\\') dir_out.push_back('\\');

	dir_snt.push_back('\\');
	vector<string> fn_snts;
	Sora::SearchFiles(dir_snt + "*" ATTR_SNT, fn_snts);

	ofstream ofs_rp(REP_NAME);
	for (const auto &fn_snt : fn_snts) {
		const string name = fn_snt.substr(0, fn_snt.rfind(ATTR_SNT));
		cout << "处理" << fn_snt << "..." << endl;

		ifstream ifs(dir_snt + fn_snt);
		ofstream ofs;
		int out_cnt = 0;
		
		char buff_snt[MAXCH_ONELINE + 1];
		int line_cnt = 0;

		int flag = FLAG_CLEAR;
		int line_no = 0;
		string text;

		while (ifs.getline(buff_snt, sizeof(buff_snt)).good())
		{
			line_cnt++;


		}

		ifs.close();
		if(out_cnt > 0) ofs.close();

		ofs_rp << name << '\t' <<  out_cnt << endl;
	}
	ofs_rp.close();

	return 0;
}
