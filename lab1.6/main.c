#include <stdio.h>
#include <windows.h>


int main() {
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Pos;
    system("mode 80, 24");

    for (int i = 0; i < 12; i++) {
        if(i%2==0) {
            for (int j = 79; j >= 0; j--) {
                Pos.Y = i;
                Pos.X = j;
                SetConsoleCursorPosition(hout, Pos);
                printf("$");
                Sleep(1);
                Pos.Y = 23-i;
                SetConsoleCursorPosition(hout, Pos);
                printf("$");
                Sleep(1);
            }
        } else {
            for (int j = 0; j < 80; j++) {
                Pos.Y = i;
                Pos.X = j;
                SetConsoleCursorPosition(hout, Pos);
                printf("$");
                Sleep(1);
                Pos.Y = 23-i;
                SetConsoleCursorPosition(hout, Pos);
                printf("$");
                Sleep(1);
            }
        }

    }
    Sleep(2000);
    return 0;
}