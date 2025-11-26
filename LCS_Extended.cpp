#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <windows.h>
using namespace std;

// ===========================
// THUAT TOAN HIRSCHBERG - CHIA DE TRI (TOI UU BO NHO)
// ===========================

// Tinh mot hang cua bang LCS
vector<int> computeLCSRow(string X, string Y) {
    int m = X.length();
    int n = Y.length();
    
    vector<int> prev(n + 1, 0);
    vector<int> curr(n + 1, 0);
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i-1] == Y[j-1]) {
                curr[j] = prev[j-1] + 1;
            } else {
                curr[j] = max(prev[j], curr[j-1]);
            }
        }
        prev = curr;
    }
    
    return curr;
}

// Thuat toan Hirschberg - Chia de tri
string hirschbergLCS(string X, string Y) {
    int m = X.length();
    int n = Y.length();
    
    // Base cases
    if (m == 0) return "";
    if (n == 0) return "";
    if (m == 1) {
        for (int j = 0; j < n; j++) {
            if (X[0] == Y[j]) return string(1, X[0]);
        }
        return "";
    }
    
    // Chia X thanh 2 phan
    int mid = m / 2;
    string X1 = X.substr(0, mid);
    string X2 = X.substr(mid);
    
    // Tinh LCS tu trai sang phai
    vector<int> L1 = computeLCSRow(X1, Y);
    
    // Tinh LCS tu phai sang trai (dao nguoc)
    string X2_rev(X2.rbegin(), X2.rend());
    string Y_rev(Y.rbegin(), Y.rend());
    vector<int> L2 = computeLCSRow(X2_rev, Y_rev);
    reverse(L2.begin(), L2.end());
    
    // Tim diem chia tot nhat
    int split = 0;
    int maxLen = L1[0] + L2[0];
    for (int j = 1; j <= n; j++) {
        if (L1[j] + L2[j] > maxLen) {
            maxLen = L1[j] + L2[j];
            split = j;
        }
    }
    
    // De quy
    string Y1 = Y.substr(0, split);
    string Y2 = Y.substr(split);
    
    return hirschbergLCS(X1, Y1) + hirschbergLCS(X2, Y2);
}

// ===========================
// HAM DOC FILE
// ===========================

vector<string> readStringsFromFile(string filename) {
    vector<string> strings;
    ifstream file(filename);
    
    if (!file.is_open()) {
        cout << "Loi: Khong the mo file " << filename << endl;
        return strings;
    }
    
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            strings.push_back(line);
        }
    }
    
    file.close();
    return strings;
}

// ===========================
// HAM HIEN THI MENU
// ===========================

void printMenu() {
    cout << "\n";
    cout << "+=========================================================+\n";
    cout << "|    LCS - THUAT TOAN HIRSCHBERG (CHIA DE TRI)           |\n";
    cout << "+=========================================================+\n";
    cout << "| 1. Nhap 2 chuoi tu ban phim                            |\n";
    cout << "| 2. Doc 2 chuoi tu file trong thu muc 'Chuoi'           |\n";
    cout << "| 0. Quay lai                                             |\n";
    cout << "+=========================================================+\n";
    cout << "Chon chuc nang: ";
}

void displayResults(string X, string Y, string lcs, double time_ms) {
    cout << "\n+=========================================================+\n";
    cout << "|                      KET QUA                            |\n";
    cout << "+=========================================================+\n";
    cout << "Chuoi X: " << X << "\n";
    cout << "Do dai X: " << X.length() << "\n";
    cout << "\nChuoi Y: " << Y << "\n";
    cout << "Do dai Y: " << Y.length() << "\n";
    cout << "\n--- THUAT TOAN HIRSCHBERG ---\n";
    cout << "LCS: " << lcs << "\n";
    cout << "Do dai LCS: " << lcs.length() << "\n";
    cout << "Bo nho: O(min(m, n)) = O(" << min(X.length(), Y.length()) << ") cells\n";
    cout << "Do phuc tap thoi gian: O(m x n)\n";
    cout << "Thoi gian thuc thi: " << fixed << setprecision(4) << time_ms << " ms\n";
    cout << "\nTiet kiem bo nho: " << fixed << setprecision(2)
         << (1.0 - (double)min(X.length(), Y.length()) / (X.length() * Y.length())) * 100
         << "% so voi phuong phap co ban\n";
    cout << "+=========================================================+\n";
}

// ===========================
// MAIN
// ===========================

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    int choice;
    
    while (true) {
        printMenu();
        cin >> choice;
        cin.ignore();
        
        if (choice == 0) {
            cout << "\n+=========================================================+\n";
            cout << "|              Thoat chuong trinh LCS mo rong             |\n";
            cout << "+=========================================================+\n";
            break;
        }
        
        switch (choice) {
            case 1: {
                // Nhap tu ban phim
                string X, Y;
                cout << "\nNhap chuoi X: ";
                getline(cin, X);
                cout << "Nhap chuoi Y: ";
                getline(cin, Y);
                
                clock_t start = clock();
                string lcs = hirschbergLCS(X, Y);
                clock_t end = clock();
                double time_ms = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
                
                displayResults(X, Y, lcs, time_ms);
                break;
            }
            
            case 2: {
                // Doc tu file
                cout << "\n=== DOC CHUOI TU FILE ===\n";
                cout << "Danh sach file trong thu muc 'Chuoi':\n";
                cout << "  - test1.txt\n";
                cout << "  - test2.txt\n";
                cout << "  - test3.txt\n";
                cout << "  - test_large.txt\n";
                
                string filename;
                cout << "\nNhap ten file: ";
                getline(cin, filename);
                
                vector<string> strings = readStringsFromFile("Chuoi/" + filename);
                
                if (strings.empty()) {
                    cout << "Khong doc duoc file hoac file rong!\n";
                    break;
                }
                
                if (strings.size() < 2) {
                    cout << "File phai chua it nhat 2 chuoi!\n";
                    break;
                }
                
                cout << "\nDa doc duoc " << strings.size() << " chuoi:\n";
                cout << "Chuoi X: " << strings[0] << " (do dai: " << strings[0].length() << ")\n";
                cout << "Chuoi Y: " << strings[1] << " (do dai: " << strings[1].length() << ")\n";
                
                clock_t start = clock();
                string lcs = hirschbergLCS(strings[0], strings[1]);
                clock_t end = clock();
                double time_ms = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
                
                displayResults(strings[0], strings[1], lcs, time_ms);
                break;
            }
            
            default:
                cout << "\nLua chon khong hop le!\n";
        }
        
        cout << "\nNhan Enter de tiep tuc...";
        cin.get();
    }
    
    return 0;
}
