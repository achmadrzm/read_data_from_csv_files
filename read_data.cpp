#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

struct Mahasiswa {
    string nim;
    string nama;
    int nilai;
};

list<Mahasiswa> read_csv_files(string path) {
    string line, tmp;
    list<Mahasiswa> data;

    fstream file(path, ios::in);
    if (file.is_open()) {
        while (getline(file, line)) {
            Mahasiswa mhs;
            stringstream str(line);
            getline(str, mhs.nim, ';');
            getline(str, mhs.nama, ';');
            getline(str, tmp, ';');
            mhs.nilai = stoi(tmp);
            data.push_back(mhs);
        }
    }
    else {
        cout << "Could not open the file...\n";
    }

    return data;
}

list<Mahasiswa> merge_data(list<Mahasiswa> data1, list<Mahasiswa> data2, list<Mahasiswa> data3, list<Mahasiswa> data4) {
    list<Mahasiswa> merged_data;
    merged_data.insert(merged_data.end(), data1.begin(), data1.end());
    merged_data.insert(merged_data.end(), data2.begin(), data2.end());
    merged_data.insert(merged_data.end(), data3.begin(), data3.end());
    merged_data.insert(merged_data.end(), data4.begin(), data4.end());
    return merged_data;
}

void print_mahasiswa(list<Mahasiswa> data) {
    for(Mahasiswa mhs: data){
        cout << mhs.nim << "\t" << mhs.nama << "\t\t" << mhs.nilai << endl;
    }
}

void print_mata_kuliah(list<Mahasiswa> data[4]) {
    string keyword, nama_mahasiswa, nim_mahasiswa;
    cout << "\nInput: ";
    getline(cin, keyword);

    for (int i = 0; i < 4; i++) {
        for (Mahasiswa mhs : data[i]) {
            if (mhs.nama == keyword || mhs.nim == keyword) {
                nama_mahasiswa = mhs.nama;
                nim_mahasiswa = mhs.nim;
            }
        }
    }

    cout << "NIM: " << nim_mahasiswa << endl;
    cout << "Nama: " << nama_mahasiswa << endl;
    cout << "Nilai:\n";

    bool found = false;
    for (int i = 0; i < 4; i++) {
        for (Mahasiswa mhs : data[i]) {
            if (mhs.nama == keyword || mhs.nim == keyword) {
                found = true;
                cout << "MK-" << char('A' + i) << " : " << mhs.nilai << endl;
            }
        }
    }

    if (!found) {
        cout << "Data not found...\n";
    }
}

void print_average_score(list<Mahasiswa> data[4]) {
    string keyword, nama_mahasiswa, nim_mahasiswa;
    cout << "\nInput: ";
    getline(cin, keyword);

    int total_nilai = 0, total_mahasiswa = 0;

    for (int i = 0; i < 4; i++) {
        for (Mahasiswa mhs : data[i]) {
            if (mhs.nama == keyword || mhs.nim == keyword) {
                total_nilai += mhs.nilai;
                total_mahasiswa++;
                nama_mahasiswa = mhs.nama;
                nim_mahasiswa = mhs.nim;
            }
        }
    }

    double rata_rata = (double) total_nilai / total_mahasiswa;

    cout << "NIM: " << nim_mahasiswa << endl;
    cout << "Nama: " << nama_mahasiswa << endl;
    cout << "Rata-rata nilai: " << rata_rata << endl;
}

void print_highest_scores(list<Mahasiswa> data) {
    int highest_score = 0;

    for (Mahasiswa mhs : data) {
        if (mhs.nilai > highest_score) {
            highest_score = mhs.nilai;
        }
    }

    cout << "NIM\t" << "NAMA\t\t\t" << "NILAI\n";
    for (Mahasiswa mhs : data) {
        if (mhs.nilai == highest_score) {
            cout << mhs.nim << "\t" << mhs.nama << "\t\t" << mhs.nilai << endl;
        }
    }
}

void print_grade_distribution(list<Mahasiswa> data) {
    int num_0_60 = 0, num_61_75 = 0, num_76_90 = 0, num_91_100 = 0;

    for (Mahasiswa mhs : data) {
        int nilai = mhs.nilai;

        if (nilai >= 0 && nilai <= 60) {
            num_0_60++;
        }
        else if (nilai >= 61 && nilai <= 75) {
            num_61_75++;
        }
        else if (nilai >= 76 && nilai <= 90) {
            num_76_90++;
        }
        else if (nilai >= 91 && nilai <= 100) {
            num_91_100++;
        }
    }

    cout << "0-60: " << num_0_60 << endl;
    cout << "61-75: " << num_61_75 << endl;
    cout << "76-90: " << num_76_90 << endl;
    cout << "91-100: " << num_91_100 << endl;
}

void print_highest_average(list<Mahasiswa> merged_data) {
    int n;
    cout << "\nInput: ";
    cin >> n;
    map<string, pair<int, int>> mahasiswa;

    for (Mahasiswa mhs : merged_data) {
        if (mahasiswa.find(mhs.nim) == mahasiswa.end()) {
            mahasiswa[mhs.nim] = make_pair(mhs.nilai, 1);
        }
        else {
            mahasiswa[mhs.nim].first += mhs.nilai;
            mahasiswa[mhs.nim].second++;
        }
    }

    map<string, double> rata_rata;
    for (auto it : mahasiswa) {
        string nim = it.first;
        int total_nilai = it.second.first;
        int total_mk = it.second.second;
        double avg = (double) total_nilai / total_mk;
        rata_rata[nim] = avg;
    }

    vector<pair<string, double>> sorted_mahasiswa;
    for (auto it : rata_rata) {
        string nim = it.first;
        double avg = it.second;
        sorted_mahasiswa.push_back(make_pair(nim, avg));
    }
    sort(sorted_mahasiswa.begin(), sorted_mahasiswa.end(), [](const pair<string, double>& a, const pair<string, double>& b) {
        return a.second > b.second;
    });

    cout << "NIM\t" << "NAMA\t\t\t" << "NILAI RATA-RATA\n";
    int counter = 0;
    for (auto it : sorted_mahasiswa) {
        string nim = it.first;
        double avg = it.second;
        for (Mahasiswa mhs : merged_data) {
            if (mhs.nim == nim) {
                cout << mhs.nim << "\t" << mhs.nama << "\t\t" << avg << endl;
                counter++;
                if (counter == n) {
                    return;
                }
                break;
            }
        }
    }
}

int main() {
    string csv_files[4] = {"MK-A.csv", "MK-B.csv", "MK-C.csv", "MK-D.csv"};
    list<Mahasiswa> data[4], merged_data;

    for (int i = 0; i < 4; i++) {
        data[i] = read_csv_files(csv_files[i]);
    }

    merged_data = merge_data(data[0], data[1], data[2], data[3]);

    while (true) {
        cout << "===========================================================\n";
        cout << "1. Tampilkan daftar mata kuliah yang diambil mahasiswa.\n";
        cout << "2. Tampilkan rata-rata nilai dari seluruh mata kuliah yang diambil mahasiswa.\n";
        cout << "3. Tampilkan mahasiswa yang mendapat nilai tertinggi pada sebuah mata kuliah.\n";
        cout << "4. Tampilkan jumlah mahasiswa yang mendapatkan nilai antara: 0-60, 61-75, 76-90, dan 91-100.\n";
        cout << "5. Tampilkan mahasiswa yang mendapat rata-rata nilai tertinggi dari seluruh mata kuliah yang diambil.\n";
        cout << "\n6. Keluar Program.\n";
        cout << "===========================================================\n";

        string input_menu;
        cout << "Input: ";
        getline(cin, input_menu);

        if (input_menu == "1") {
            print_mata_kuliah(data);
        }
        else if (input_menu == "2") {
            print_average_score(data);
        }
        else if (input_menu == "3") {
            string input_submenu;
            cout << "\nInput: ";
            getline(cin, input_submenu);

            if(input_submenu == "MK-A") {
                print_highest_scores(data[0]);
            }
            else if(input_submenu == "MK-B") {
                print_highest_scores(data[1]);
            }
            else if(input_submenu == "MK-C") {
                print_highest_scores(data[2]);
            }
            else if(input_submenu == "MK-D") {
                print_highest_scores(data[3]);
            }
        }
        else if (input_menu == "4") {
            string input_submenu;
            cout << "\nInput: ";
            getline(cin, input_submenu);

            if(input_submenu == "MK-A") {
                print_grade_distribution(data[0]);
            }
            else if(input_submenu == "MK-B") {
                print_grade_distribution(data[1]);
            }
            else if(input_submenu == "MK-C") {
                print_grade_distribution(data[2]);
            }
            else if(input_submenu == "MK-D") {
                print_grade_distribution(data[3]);
            }
        }
        else if (input_menu == "5") {
            print_highest_average(merged_data);
        }
        else if (input_menu == "6") {
            goto end;
        }
    }
    end:

    return 0;
}