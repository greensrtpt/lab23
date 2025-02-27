#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
#include<sstream>  // ✅ เพิ่มส่วนนี้

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades) {
    ifstream file(filename);
    
    if (!file) {
        cout << "Error: Cannot open file.\n";
        return;
    }
    
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name;
        int score1, score2, score3;
        
        // อ่านชื่อที่มีช่องว่าง
        getline(ss, name, ':');
        ss >> score1 >> score2 >> score3;

        // ลบช่องว่างที่อาจมีหลังชื่อ
        while (!name.empty() && name.back() == ' ') {
            name.pop_back();
        }

        names.push_back(name);
        int totalScore = score1 + score2 + score3;
        scores.push_back(totalScore);
        grades.push_back(score2grade(totalScore));
    }

    file.close();
}


void getCommand(string &command, string &key){
    string input;
    cout << "Please input your command: "<< endl;
    getline(cin, input); // อ่านทั้งบรรทัด

    size_t spacePos = input.find(' '); // ค้นหาตำแหน่งช่องว่างแรก
    if (spacePos != string::npos) {
        command = input.substr(0, spacePos); // คำแรกเป็น command
        key = input.substr(spacePos + 1);   // ส่วนที่เหลือเป็น key
    } else {
        command = input; // ถ้าไม่มีช่องว่าง ให้ถือว่า input ทั้งหมดเป็น command
        key = "";       // key เป็นค่าว่าง
    }

    // ทำให้ command เป็นตัวพิมพ์ใหญ่ทั้งหมด
    command = toUpperStr(command);
}

void searchName(const vector<string> &names, const vector<int> &scores, const vector<char> &grades, string key) {
    bool found = false;
    string searchKey = toUpperStr(key); // แปลงให้เป็นตัวพิมพ์ใหญ่เพื่อให้เปรียบเทียบแบบไม่คำนึงถึงตัวพิมพ์เล็ก-ใหญ่

    for (size_t i = 0; i < names.size(); i++) {
        if (toUpperStr(names[i]) == searchKey) { // เทียบชื่อแบบไม่แยกพิมพ์เล็ก-ใหญ่
            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            cout << "---------------------------------\n";
            found = true;
            break; // ออกจาก loop ทันทีเมื่อพบชื่อ
        }
    }

    if (!found) {
        cout << "---------------------------------\n";
        cout << "Cannot found.\n";
        cout << "---------------------------------\n";
    }
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key) {
    bool found = false;
    char searchKey = toupper(key[0]); // แปลง key เป็นตัวพิมพ์ใหญ่เพื่อให้เปรียบเทียบได้ถูกต้อง

    cout << "---------------------------------\n";
    for (size_t i = 0; i < names.size(); i++) {
        if (grades[i] == searchKey) { // ค้นหาตามเกรด
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }

    if (!found) {
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}



int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}