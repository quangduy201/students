#include <iostream>
#include <iomanip>
#include <string.h>
#define maxn 100
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
using namespace std;
struct Student {
    char id[16] = {0};
    char name[40] = {0};
    double score;
};
void inputStudents(Student s) {
    FILE *f = fopen("students.dat", "wb");
    int n;
    cout << "Input number of students: "; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "\tStudent " << i+1 << ":\n";
        cout << "ID   : "; fflush(stdin); gets(s.id);
        cout << "Name : "; fflush(stdin); gets(s.name);
        cout << "Score: "; cin >> s.score;
        fwrite(&s, sizeof(s), 1, f);
    }
    fclose(f);
}
void appendStudents(Student s) {
    FILE *f = fopen("students.dat", "ab");
    int n;
    cout << "Input number of students: "; cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "\tStudent " << i+1 << ":\n";
        cout << "ID   : "; fflush(stdin); gets(s.id);
        cout << "Name : "; fflush(stdin); gets(s.name);
        cout << "Score: "; cin >> s.score;
        fwrite(&s, sizeof(s), 1, f);
    }
    fclose(f);
}
void outputStudents(Student s) {
    FILE *f = fopen("students.dat", "rb");
    fread(&s, sizeof(s), 1, f);
    while (!feof(f)) {
        cout << YELLOW << setfill(' ') << setw(50) << s.score << "\r" << setw(15) << " " << s.name << "\r" << s.id << endl << RESET;
        fread(&s, sizeof(s), 1, f);
    }
    fclose(f);
}
void findStudentsByID(Student s) {
    FILE *f = fopen("students.dat", "rb");
    char id[16] = {0};
    cout << "Input ID: "; fflush(stdin); gets(id);
    int found = 0;
    while (!feof(f)) {
        fread(&s, sizeof(s), 1, f);
        if (!strcmp(s.id, id)) {    
            cout << YELLOW << setfill(' ') << setw(50) << s.score << "\r" << setw(15) << " " << s.name << "\r" << s.id << endl << RESET;
            found = 1;
        }
    }
    if (!found)
        cout << "Not found!";
    fclose(f);
}
void findStudentsByName(Student s) {
    FILE *f = fopen("students.dat", "rb");
    char name[40] = {0};
    cout << "Input name: "; fflush(stdin); gets(name);
    int found = 0;
    while (!feof(f)) {
        fread(&s, sizeof(s), 1, f);
        if (!strcmp(strrchr(s.name, ' ')+1, name)) {    
            cout << YELLOW << setfill(' ') << setw(50) << s.score << "\r" << setw(15) << " " << s.name << "\r" << s.id << endl << RESET;
            found = 1;
        }
    }
    if (!found)
        cout << "Not found!";
    fclose(f);
}
void findStudentsByScore(Student s) {
    FILE *f = fopen("students.dat", "rb");
    double score;
    cout << "Input score: "; cin >> score;
    int found = 0;
    while (!feof(f)) {
        fread(&s, sizeof(s), 1, f);
        if (s.score == score) {    
            cout << YELLOW << setfill(' ') << setw(50) << s.score << "\r" << setw(15) << " " << s.name << "\r" << s.id << endl << RESET;
            found = 1;
        }
    }
    if (!found)
        cout << "Not found!";
    fclose(f);
}
void highestScore(Student s) {
    FILE *f = fopen("students.dat", "rb");
    double max = 0;
    fread(&s, sizeof(s), 1, f);
    while (!feof(f)) {
        fread(&s, sizeof(s), 1, f);
        if (s.score > max)
        max = s.score;
    }
    fseek(f, 0, SEEK_SET);
    fread(&s, sizeof(s), 1, f);
    while (!feof(f)) {
        if (s.score == max)
            cout << YELLOW << setfill(' ') << setw(50) << s.score << "\r" << setw(15) << " " << s.name << "\r" << s.id << endl << RESET;
        fread(&s, sizeof(s), 1, f);
    }
    fclose(f);
}
void swap(Student &s1, Student &s2) {
    Student temp = s1;
    s1 = s2;
    s2 = temp;
}
void sortStudentsByID(Student *&s) {
    FILE *f = fopen("students.dat", "rb");
    s = new Student[maxn];
    int i = 0;
    fread(&s[i], sizeof(s[i]), 1, f);
    while (!feof(f))
        fread(&s[++i], sizeof(s[i]), 1, f);
    fclose(f);
    int n = i;
    int id[n];
    for (int i = 0; i < n; i++)
        id[i] = atoi(s[i].id);
    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
            if (id[i] > id[j]) {
                swap(id[i], id[j]);
                swap(s[i], s[j]);
            }
    cout << "Sorted by ID:\n";
    for (int i = 0; i < n; i++)
        cout << YELLOW << setfill(' ') << setw(50) << s[i].score << "\r" << setw(15) << " " << s[i].name << "\r" << s[i].id << endl << RESET;
}
void sortStudentsByName(Student *&s) {
    FILE *f = fopen("students.dat", "rb");
    s = new Student[maxn];
    int i = 0;
    fread(&s[i], sizeof(s[i]), 1, f);
    while (!feof(f))
        fread(&s[++i], sizeof(s[i]), 1, f);
    fclose(f);
    int n = i;
    char name[n][40];
    for (int i = 0; i < n; i++)
        strcpy(name[i], strrchr(s[i].name, ' ')+1);
    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
            if (strcmp(name[i], name[j]) > 0) {
                swap(name[i], name[j]);
                swap(s[i], s[j]);
            }
    cout << "Sorted by name:\n";
    for (int i = 0; i < n; i++)
        cout << YELLOW << setfill(' ') << setw(50) << s[i].score << "\r" << setw(15) << " " << s[i].name << "\r" << s[i].id << endl << RESET;
}
void sortStudentsByScore(Student *&s) {
    FILE *f = fopen("students.dat", "rb");
    s = new Student[maxn];
    int i = 0;
    fread(&s[i], sizeof(s[i]), 1, f);
    while (!feof(f))
        fread(&s[++i], sizeof(s[i]), 1, f);
    fclose(f);
    int n = i;
    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
            if (s[i].score < s[j].score)
                swap(s[i], s[j]);
    cout << "Sorted by score:\n";
    for (int i = 0; i < n; i++)
        cout << YELLOW << setfill(' ') << setw(50) << s[i].score << "\r" << setw(15) << " " << s[i].name << "\r" << s[i].id << endl << RESET;
}
void removeStudents(Student s) {
    FILE *f = fopen("students.dat", "wb");
    fclose(f);
    cout << "Removed!\n";
}
int main() {
    Student s;
    Student *pS;
    int a;
    while (1) {
        system("cls");
        cout << CYAN << setfill('-') << setw(50) << "-" << endl;
        cout << setfill(' ') << setw(50) << "|" << "\r|1. Input students\n";
        cout << setfill(' ') << setw(50) << "|" << "\r|2. Append students\n";
        cout << setfill(' ') << setw(50) << "|" << "\r|3. Output students\n";
        cout << setfill(' ') << setw(50) << "|" << "\r|4. Find students by ID\n";
        cout << setfill(' ') << setw(50) << "|" << "\r|5. Find students by name\n";
        cout << setfill(' ') << setw(50) << "|" << "\r|6. Find students by score\n";
        cout << setfill(' ') << setw(50) << "|" << "\r|7. Highest score\n";
        cout << setfill(' ') << setw(50) << "|" << "\r|8. Sort students by ID\n";
        cout << setfill(' ') << setw(50) << "|" << "\r|9. Sort students by name\n";
        cout << setfill(' ') << setw(50) << "|" << "\r|10. Sort students by score\n";
        cout << setfill(' ') << setw(50) << "|" << "\r|11. Remove all students\n";
        cout << setfill(' ') << setw(50) << "|" << "\r|12. Exit\n";
        cout << setfill(' ') << setw(50) << "made by: Quang Duy|" << "\r|" << endl;
        cout << setfill('-') << setw(50) << "-" << endl;
        cout << GREEN << "Your choice: " << RESET; cin >> a;
        cout << endl;
        switch (a) {
            case 1:
                inputStudents(s);
                break;
            case 2:
                appendStudents(s);
                break;
            case 3:
                outputStudents(s);
                break;
            case 4:
                findStudentsByID(s);
                break;
            case 5:
                findStudentsByName(s);
                break;
            case 6:
                findStudentsByScore(s);
                break;
            case 7:
                highestScore(s);
                break;
            case 8:
                sortStudentsByID(pS);
                break;
            case 9:
                sortStudentsByName(pS);
                break;
            case 10:
                sortStudentsByScore(pS);
                break;
            case 11:
                removeStudents(s);
                break;
            case 12:
                cout << RED;
                return 0;
            default:
                cout << "Choose again!\n";
        }
        cout << endl;
        system("pause");
    }
    return 0;
}
/*
3121410048
Nguyen Ho Khanh An
63
3121410057
Nguyen Tuan Anh
0
3121410067
Chau Gia Bao
0
3121410076
Nguyen Tri Bao
55
3121410085
Van Pham Tuan Cat
58
3121410095
Ho Quoc Cuong
58
3121410106
Nguyen Tien Duan
60
3121410116
Dinh Quang Duy
80
3121410125
Tran Nhat Duy
43
3121410134
Lam Quoc Dai
0
3121410144
Ngo Tan Dat
67
3121410005
Nguyen Quang Dat
72
3121410154
Nguyen Phuong Dien
67
3121410165
Tran Trung Duc
0
3121410174
Ho Thi Hai
63
3121410184
Nguyen Huu Hau
38
3121410195
Nguyen Huynh Minh Hieu
58
3121410205
Vi Thi Hoa
80
3121410215
Vo Dinh Xuan Hoang
59
3121410227
Kieu Duc Huy
66
3121410237
Cao Huy Hung
70
3121410247
Hy Phu Kam
63
3121410258
Le Duy Khanh
65
3121410268
Do Dang Khoa
64
3121410278
Hoang Trong Khoi
0
3121410287
Lam Tuan Kiet
62
3121410296
Nguyen Hoang Long
74
3121410306
Nguyen Phuoc Luan
53
3121410316
Dang Sy Manh
63
3121410325
Vo Chi Minh
0
3121410335
Than Trong Hoai Nam
68
3121410345
Phan Trung Nghia
65
3121410356
Lai Thanh Nhan
69
3121410367
Hua Tuyet Nhi
65
3121410377
Nguyen Hoang Phat
69
3121410386
Ta Duc Phu
63
3121410395
Nguyen Van Minh Phuc
60
3121410405
Do Phan Uyen Quan
64
3121410415
Huynh Le San
72
3121410424
Nguyen Hoang Thai Son
70
3121410433
Nguyen Chi Tai
72
3121410444
Nguyen Van Tan
67
3121410038
Nguyen Duc Tay
67
3121410456
Truong Gia Thanh
45
3121410466
Nguyen Chi Thien
0
3121410014
Nguyen Khanh Thien
63
3121410475
Vo Duc Thinh
60
3121410484
Phan Nguyen Trung Thuan
68
3121410495
Doan Minh Tien
0
3121410505
Dang Duc Tin
67
3121410514
Pham Quoc Toan
40
3121410534
Nguyen Xuan Truc
69
3121410543
Pham Hoang Dan Truong
68
3121410552
Vu Ngoc Tu
62
3121410561
Pham Quoc Tuan
43
3121410570
Nguyen Thanh Thien Tu
79
3121410580
Nguyen The Vu
69
3121410023
Tien Minh Vy
67
3121410588
Tang Nghia Xuong
0
*/