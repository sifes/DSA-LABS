#include <stdio.h>
#include <windows.h>

int main() {
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    int columns = 80, rows = 24;
    COORD Pos;
    system("mode 80, 24");

    for (int i = 0; i < rows/2; i++) {
        if(i%2==0) {
            for (int j = columns-1; j >= 0; j--) {
                Pos.Y = i;
                Pos.X = j;
                SetConsoleCursorPosition(hout, Pos);
                printf("$");
                Sleep(1);
                Pos.Y = (rows-1)-i;
                SetConsoleCursorPosition(hout, Pos);
                printf("$");
                Sleep(1);
            }
        } else {
            for (int j = 0; j < columns; j++) {
                Pos.Y = i;
                Pos.X = j;
                SetConsoleCursorPosition(hout, Pos);
                printf("$");
                Sleep(1);
                Pos.Y = (rows-1)-i;
                SetConsoleCursorPosition(hout, Pos);
                printf("$");
                Sleep(1);
            }
        }
    }
    Sleep(2000); // can see the result for additional 2 sec
    return 0;
}