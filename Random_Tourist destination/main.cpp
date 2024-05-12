#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib> 
#include <ctime>
#include <thread>
#include <sstream>
#include <shlobj.h>

using namespace std;

std::wstring s2ws(const std::string& s);

class CRan_Toursit_Spot {

protected:
	string str;
	ifstream fin;
	ofstream fout;
public:
	string result_url;
	CRan_Toursit_Spot();
	void CRan_Toursit_Spot_menu();
	void excecute();
	void end();
};


CRan_Toursit_Spot::CRan_Toursit_Spot() {}; //생성자는 아무것도 안함


void CRan_Toursit_Spot::CRan_Toursit_Spot_menu() {

	cout << "\n\n";
	cout << "---------------------------------------------------------" << endl;
	cout << "***            오늘은 어디갈래? 여긴 어때?            ***" << endl;g
	cout << "---------------------------------------------------------" << endl;
	cout << "\n\n\n";
	cout << "문화체육관광부와 한국관광공사가 추천하는 한국관광 100선" << endl;
	cout << "\n\n\n";
	cout << "---------------------------------------------------------" << endl;
	cout << "|                  1. 돌려돌려 돌림판                   |" << endl;
	cout << "|                  2. 종료                              |" << endl;
	cout << "---------------------------------------------------------" << endl;

}

void CRan_Toursit_Spot::end() {
	cout << "---------------------------------------------------------" << endl;
	cout << "|                                                       |" << endl;
	cout << "|                 좋은 시간 보내세요.                   |" << endl;
	cout << "|                                                       |" << endl;
	cout << "---------------------------------------------------------" << endl;
	exit(0);
}



class CAfter_Excecute : public CRan_Toursit_Spot {

public:
	CAfter_Excecute();
	void done_menu(int re_choose, string result_url);
	void open_select_spot_info(string result_url);

};

void CRan_Toursit_Spot::excecute() {

	string buff;
	string space = " ";
	string result;

	srand((unsigned int)time(NULL));
	int ran_value = rand() % 101;

	fin.open("tourist_spot.txt");
	if (!fin.is_open()) {
		cout << "파일을 열지 못했습니다.";
	}

	else {

		for (int i = 0; i <= ran_value; i++) {
			getline(fin, str);
		}

		istringstream ss(str);

		getline(ss, buff, ',');
		this_thread::sleep_for(chrono::seconds(2));
		cout << "\n------------------------광역권---------------------------" << endl;
		cout << "|                                                       |" << endl;
		cout << "|                       " << buff << "                          |" << endl;
		cout << "|                                                       |" << endl;
		cout << "---------------------------------------------------------" << endl;
		result.append(buff);
		result.append(space);

		getline(ss, buff, ',');
		this_thread::sleep_for(chrono::seconds(2));
		cout << "\n-------------------------시,도---------------------------" << endl;
		cout << "|                                                       |" << endl;
		cout << "|                        " << buff << "                           |" << endl;
		cout << "|                                                       |" << endl;
		cout << "---------------------------------------------------------" << endl;
		result.append(buff);
		result.append(space);

		getline(ss, buff, ',');
		this_thread::sleep_for(chrono::seconds(2));
		cout << "\n------------------------관광지---------------------------\n" << endl;
		cout << "                  " << buff << endl;
		cout << "\n---------------------------------------------------------" << endl;
		result.append(buff);
		result.append(space);

		getline(ss, buff, ',');
		result_url = buff;

		this_thread::sleep_for(chrono::seconds(2));
		cout << "\n------------------------여긴 어때?-----------------------\n" << endl;
		cout << "                " << result << "        " << endl; //전체 출력
		//cout << result << "        " << endl; //전체 출력
		cout << "\n---------------------------------------------------------" << endl;

		CAfter_Excecute b;
		int re_choose = 0;
		//cout << "번호를 선택해주세요" << endl;
		cin >> re_choose;
		b.done_menu(re_choose, result_url);
		fin.close();
	}
}

CAfter_Excecute::CAfter_Excecute() {

	cout << "---------------------------------------------------------" << endl;
	cout << "|                 1. 추첨된 여행지 정보                 | " << endl;
	cout << "|                 2. 재추첨                             | " << endl;
	cout << "|                 3. 초기화면                           | " << endl;
	cout << "|                 4. 종료                               | " << endl;
	cout << "---------------------------------------------------------" << endl;

}

void CAfter_Excecute::done_menu(int re_choose, string result_url) {

	switch (re_choose) {

	case 1: open_select_spot_info(result_url); break;
	case 2: excecute(); break;
	case 3: CRan_Toursit_Spot_menu(); break;
	case 4: end(); 
	default: break;

	}
}

void CAfter_Excecute::open_select_spot_info(string result_url) {

	// string 을 LPCWSTR로 바꿔주기
	wstring address = s2ws(result_url);
	LPCWSTR result = address.c_str();

	// 기본브라우저로 URL OPEN
	ShellExecute(NULL, L"open", result, NULL, NULL, SW_SHOW);

}





int main() {

	int choose;
	CRan_Toursit_Spot a;
	while (1) {
		a.CRan_Toursit_Spot_menu();
		cin >> choose;
		switch (choose)
		{
		case 1: a.excecute(); break;
		case 2: a.end(); 
		default: break;
		}
	}
	return 0;

}

std::wstring s2ws(const std::string& s)  //string을 LPCWSTR로 변환해주는 함수
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}
