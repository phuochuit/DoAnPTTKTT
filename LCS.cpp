#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

// Hàm tính độ dài LCS và lưu bảng DP
int computeLCS(string X, string Y, vector<vector<int>>& L) {
    int m = X.length();
    int n = Y.length();
    
    // Khởi tạo bảng L với kích thước (m+1) x (n+1)
    L.assign(m + 1, vector<int>(n + 1, 0));
    
    // Xây dựng bảng L theo công thức quy hoạch động
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i-1] == Y[j-1]) {
                // Trường hợp 1: Ký tự khớp
                L[i][j] = L[i-1][j-1] + 1;
            } else {
                // Trường hợp 2: Ký tự không khớp
                L[i][j] = max(L[i-1][j], L[i][j-1]);
            }
        }
    }
    
    return L[m][n];
}

// Hàm truy vết để tìm dãy con chung dài nhất
string traceLCS(string X, string Y, vector<vector<int>>& L) {
    string lcs = "";
    int i = X.length();
    int j = Y.length();
    
    // Truy vết ngược từ L[m][n]
    while (i > 0 && j > 0) {
        if (X[i-1] == Y[j-1]) {
            // Ký tự này thuộc LCS
            lcs = X[i-1] + lcs;
            i--;
            j--;
        } else if (L[i-1][j] > L[i][j-1]) {
            // Đi lên trên
            i--;
        } else {
            // Đi sang trái
            j--;
        }
    }
    
    return lcs;
}

// Hàm in bảng DP
void printTable(string X, string Y, vector<vector<int>>& L) {
    int m = X.length();
    int n = Y.length();
    
    cout << "\n=== BANG QUY HOACH DONG ===\n";
    cout << "      ";
    for (int j = 0; j < n; j++) {
        cout << setw(3) << Y[j];
    }
    cout << "\n";
    
    for (int i = 0; i <= m; i++) {
        if (i == 0)
            cout << "  ";
        else
            cout << X[i-1] << " ";
        
        for (int j = 0; j <= n; j++) {
            cout << setw(3) << L[i][j];
        }
        cout << "\n";
    }
}

// Hàm in công thức
void printFormula() {
    cout << "\n=== CONG THUC QUY HOACH DONG ===\n";
    cout << "Co so: L[i][0] = 0 va L[0][j] = 0\n";
    cout << "\nCong thuc truy hoi:\n";
    cout << "- Neu X[i] == Y[j]:\n";
    cout << "    L[i][j] = L[i-1][j-1] + 1\n";
    cout << "- Neu X[i] != Y[j]:\n";
    cout << "    L[i][j] = max(L[i-1][j], L[i][j-1])\n";
}

int main() {
    // Thiết lập console để hiển thị tiếng Việt (nếu cần)
    system("chcp 65001 > nul");
    
    cout << "========================================\n";
    cout << "  BAI TOAN LONGEST COMMON SUBSEQUENCE  \n";
    cout << "      (Day con chung dai nhat)         \n";
    cout << "========================================\n";
    
    string X, Y;
    
    cout << "\nNhap chuoi X: ";
    cin >> X;
    cout << "Nhap chuoi Y: ";
    cin >> Y;
    
    // In công thức
    printFormula();
    
    // Tính LCS
    vector<vector<int>> L;
    int lengthLCS = computeLCS(X, Y, L);
    
    // In bảng quy hoạch động
    printTable(X, Y, L);
    
    // Truy vết để tìm LCS
    string lcs = traceLCS(X, Y, L);
    
    // In kết quả
    cout << "\n=== KET QUA ===\n";
    cout << "Chuoi X: " << X << " (do dai: " << X.length() << ")\n";
    cout << "Chuoi Y: " << Y << " (do dai: " << Y.length() << ")\n";
    cout << "Do dai LCS: " << lengthLCS << "\n";
    cout << "Day con chung dai nhat: " << lcs << "\n";
    
    cout << "\n========================================\n";
    
    return 0;
}
