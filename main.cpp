#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void clearScreen() {
    system("cls");
}

void runLCS() {
    int subChoice;
    
    while (1) {
        printf("\n");
        printf("╔════════════════════════════════════════════════════════╗\n");
        printf("║              BAI TOAN LCS - CHON PHIEN BAN             ║\n");
        printf("╠════════════════════════════════════════════════════════╣\n");
        printf("║                                                        ║\n");
        printf("║  1. LCS Co ban (Quy hoach dong thong thuong)          ║\n");
        printf("║                                                        ║\n");
        printf("║  2. LCS Mo rong (Thuat toan Hirschberg - Chia de tri) ║\n");
        printf("║     + Toi uu bo nho O(min(m,n))                       ║\n");
        printf("║     + Doc tu file hoac nhap ban phim                  ║\n");
        printf("║                                                        ║\n");
        printf("║  0. Quay lai menu chinh                                ║\n");
        printf("║                                                        ║\n");
        printf("╚════════════════════════════════════════════════════════╝\n");
        printf("\nChon phien ban (0-2): ");
        
        if (scanf("%d", &subChoice) != 1) {
            while (getchar() != '\n');
            printf("\nLua chon khong hop le!\n");
            printf("Nhan Enter de tiep tuc...");
            getchar();
            continue;
        }
        
        if (subChoice == 0) {
            break;
        }
        
        switch (subChoice) {
            case 1:
                printf("\n========================================\n");
                printf("  Dang chay: LCS Co ban\n");
                printf("========================================\n\n");
                system("LCS.exe");
                printf("\n\nNhan Enter de quay lai menu...");
                while (getchar() != '\n');
                getchar();
                break;
                
            case 2:
                printf("\n========================================\n");
                printf("  Dang chay: LCS Mo rong (Hirschberg)\n");
                printf("========================================\n\n");
                system("LCS_Extended.exe");
                printf("\n\nNhan Enter de quay lai menu...");
                while (getchar() != '\n');
                getchar();
                break;
                
            default:
                printf("\nLua chon khong hop le! Vui long chon 0-2.\n");
                printf("Nhan Enter de tiep tuc...");
                while (getchar() != '\n');
                getchar();
        }
    }
}

void runThamLamVsQHD() {
    printf("\n========================================\n");
    printf("  Dang chay: Bai toan Balo (Tham lam vs QHD)\n");
    printf("========================================\n\n");
    system("ThamlamvsQHD.exe");
    printf("\n\nNhan Enter de quay lai menu...");
    getchar();
    getchar();
}

void runChiaDeTri() {
    printf("\n========================================\n");
    printf("  Dang chay: Merge Sort (Chia de tri)\n");
    printf("========================================\n\n");
    system("Chiadetri.exe");
    printf("\n\nNhan Enter de quay lai menu...");
    getchar();
    getchar();
}

void printMenu() {
    clearScreen();
    printf("\n");
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║           CHUONG TRINH THUAT TOAN PTTKTT               ║\n");
    printf("╠════════════════════════════════════════════════════════╣\n");
    printf("║                                                        ║\n");
    printf("║  1. LCS - Day con chung dai nhat (Quy hoach dong)      ║\n");
    printf("║                                                        ║\n");
    printf("║  2. Bai toan Balo - Tham lam vs Quy hoach dong         ║\n");
    printf("║                                                        ║\n");
    printf("║  3. Merge Sort - Chia de tri (Tuan tu vs Song song)    ║\n");
    printf("║                                                        ║\n");
    printf("║  0. Thoat chuong trinh                                 ║\n");
    printf("║                                                        ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");
    printf("\nChon chuc nang (0-3): ");
}

int main() {
    // Thiet lap UTF-8 cho console Windows
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int choice;

    while (1) {
        printMenu();
        
        if (scanf("%d", &choice) != 1) {
            // Xu ly input khong hop le
            while (getchar() != '\n');
            printf("\nLua chon khong hop le! Vui long nhap so tu 0-3.\n");
            printf("Nhan Enter de tiep tuc...");
            getchar();
            continue;
        }

        switch (choice) {
            case 1:
                runLCS();
                break;
            case 2:
                runThamLamVsQHD();
                break;
            case 3:
                runChiaDeTri();
                break;
            case 0:
                clearScreen();
                printf("\n");
                printf("╔════════════════════════════════════════════════════════╗\n");
                printf("║                                                        ║\n");
                printf("║         Cam on ban da su dung chuong trinh!            ║\n");
                printf("║                   Hen gap lai!                         ║\n");
                printf("║                                                        ║\n");
                printf("╚════════════════════════════════════════════════════════╝\n\n");
                return 0;
            default:
                printf("\nLua chon khong hop le! Vui long chon tu 0-3.\n");
                printf("Nhan Enter de tiep tuc...");
                while (getchar() != '\n');
                getchar();
        }
    }

    return 0;
}
