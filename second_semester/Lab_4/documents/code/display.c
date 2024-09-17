#include <windows.h>
#include <math.h>
#include "../header/matrix.h"
#include <stdio.h>

void drawArrow(HDC, float, int, int);                                // стрілки
void drawLoops(HDC, double**, int**, int);                           // петлі
void drawMultipleArc(HDC, int, int, int, int);                       // кратні дуги
void drawDoubleArc (HDC, int, int, int, int, int);                   // верхні і нижні дуги
void drawLeftArc(HDC, int, int, int, int, int);                      // ліві дуги
void drawRightArc(HDC, int, int, int, int, int);                     // праві дуги
void drawStraightEdge(HDC, int, int, int, int, int);                 // прямі ребра
void drawEdges(HDC, int**, int);
int **getVerticesCoords(int);

void drawGraph(HWND hWnd, HDC hdc, PAINTSTRUCT ps, int start, int isDirected) {
    int **coords = getVerticesCoords(start);
    int radius = RADIUS, dtx = 5;

    HPEN bluePen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
    HPEN blackPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

    SelectObject(hdc, blackPen);
    drawEdges(hdc, coords, isDirected);

    SelectObject(hdc, bluePen);
    for (int j = 0; j < NUM_VERTICES; j++) {
        char num[2];
        itoa(j + 1, num, 10);
        int x = coords[0][j];
        int y = coords[1][j];
        Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
        TextOut(hdc, x - dtx, y - radius / 2, num, 2);
    }

    freeCoords(coords);
}

void drawEdges(HDC hdc, int **coords, int isDirected) {
    double **matrix = isDirected ? directedMatrix() : undirectedMatrix();
    int n = NUM_VERTICES;
    int vertInSide = (int)(n / 3.0 + 0.5);

    int k = n;
    int distance = abs(coords[0][0] - coords[0][1]);
    drawLoops(hdc, matrix, coords, isDirected);

    for (int i = 0; i < n; i++) {
        if (!isDirected) k = i;
        for (int j = 0; j < k; j++) {
            if (matrix[i][j] && i != j) {
                int isFirstInCorner;
                int isSecondInCorner;
                int inWhichRowFirst;
                int inWhichRowSecond;
                isFirstInCorner = i==0 || i==vertInSide || i==vertInSide + vertInSide;
                isSecondInCorner = j==0 || j==vertInSide || j==vertInSide + vertInSide;
                inWhichRowFirst = i / vertInSide;
                inWhichRowSecond = j / vertInSide;

                int isInside = isFirstInCorner ? !(inWhichRowFirst == inWhichRowSecond || ((inWhichRowFirst+2) % 3) == inWhichRowSecond) : isSecondInCorner ? !(inWhichRowSecond == inWhichRowFirst || ((inWhichRowSecond+2) % 3) == inWhichRowFirst) : inWhichRowFirst != inWhichRowSecond;
                isInside = isInside || (i+1 == j || i-1 == j || i+10 == j);
                int x1 = coords[0][i];
                int y1 = coords[1][i];
                int x2 = coords[0][j];
                int y2 = coords[1][j];

                if (isInside) {
                    if (matrix[j][i] && isDirected) {
                        drawMultipleArc(hdc, x1, y1, x2, y2);
                    } else {
                        drawStraightEdge(hdc, x1, y1, x2, y2, isDirected);
                    }
                } else {
                    if (matrix[j][i] && isDirected) {
                        if (i > j) {
                            drawDoubleArc(hdc, x1, y1, x2, y2, isDirected);
                        }
                    } else {
                        if (y1 == y2) {
                            if (x1 < x2) {
                                drawLeftArc(hdc, x1, y1, x2, y2, isDirected);
                            } else {
                                drawRightArc(hdc, x1, y1, x2, y2, isDirected);
                            }
                        } else {
                            if (y1 < y2) {
                                if (x1 < x2) {
                                    drawLeftArc(hdc, x1, y1, x2, y2, isDirected);
                                } else {
                                    drawRightArc(hdc, x1, y1, x2, y2, isDirected);
                                }
                            } else {
                                if (x1 > x2) {
                                    drawLeftArc(hdc, x1, y1, x2, y2, isDirected);
                                } else {
                                    drawRightArc(hdc, x1, y1, x2, y2, isDirected);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    freeMatrix(matrix);
}


void drawArrow(HDC hdc, float fi, int px, int py) {
    // Convert angle from degrees to radians
    fi = 3.1416 * (180.0 - fi) / 180.0;

    // Calculate coordinates for left and right points of the arrowhead
    int lx, ly, rx, ry;
    lx = px + 15 * cos(fi + 0.3);
    rx = px + 15 * cos(fi - 0.3);
    ly = py + 15 * sin(fi + 0.3);
    ry = py + 15 * sin(fi - 0.3);

    // Move to the left point of the arrowhead
    MoveToEx(hdc, lx, ly, NULL);
    // Draw line from left point to the starting point of the arrow
    LineTo(hdc, px, py);
    // Draw line from starting point of the arrow to the right point of the arrowhead
    LineTo(hdc, rx, ry);
}

void drawLoops(HDC hdc, double **matrix, int **coords, int isDirected) {
    int n = NUM_VERTICES;
    int radius = RADIUS;
    double indent = radius * 2.5;
    for (int i = 0; i < n; i++) {
        if (matrix[i][i]) {
            int x1 = coords[0][i];
            int y1 = coords[1][i];
            Ellipse(hdc, x1 - indent, y1 - indent, x1, y1);
            if (isDirected) drawArrow(hdc, -10, x1 - radius, y1);
        }
    }
}

void drawMultipleArc(HDC hdc, int x1, int y1, int x2, int y2) {
    int radius = RADIUS;
    double cx, cy;
    double dx, dy;
    double fi, tanFi;
    int ax, ay;
    if (y1 == y2) {
        cx = (x1 + x2) * 0.5;
        cy = (y1 + y2) * 0.5;
        cy = x2 > x1 ? cy + radius : cy - radius;
        dx = fabs(cx - x2);
        dy = fabs(cy - y2);

        tanFi = dy / dx;
        fi = atan(tanFi) * 180 / 3.1416;
        ax = radius / sqrt(1 + tanFi * tanFi);
        ay = ax * tanFi;

        ax = x2 > x1 ? -ax : ax;
        ay = x2 > x1 ? ay : -ay;
        fi = x2 > x1 ? fi : 180 + fi;

        MoveToEx(hdc, x1, y1, NULL);
        LineTo(hdc, cx, cy);
        MoveToEx(hdc, cx, cy, NULL);
        LineTo(hdc, x2, y2);
        drawArrow(hdc, fi, x2 + ax, y2 + ay);

    } else if (x1 == x2) {
        cx = (x1 + x2) * 0.5;
        cx = y2 > y1 ? cx - radius : cx + radius;
        cy = (y1 + y2) * 0.5;
        dx = fabs(cx - x2);
        dy = fabs(cy - y2);

        tanFi = dx / dy;
        fi = atan(tanFi) * 180 / 3.1416;
        ay = radius / sqrt(1 + tanFi * tanFi);
        ax = ay * tanFi;

        ax = y2 > y1 ? -ax : ax;
        ay = y2 > y1 ? -ay : ay;
        fi = y2 > y1 ? -90 + fi : 90 + fi;

        MoveToEx(hdc, x1, y1, NULL);
        LineTo(hdc, cx, cy);
        MoveToEx(hdc, cx, cy, NULL);
        LineTo(hdc, x2, y2);
        drawArrow(hdc, fi, x2 + ax, y2 + ay);

    } else if (x2 > x1) {
        cx = (x1 + x2) * 0.5 - radius;
        cy = (y1 + y2) * 0.5 - radius;
        dx = fabs(cx - x2);
        dy = fabs(cy - y2);

        if (dx > dy) {
            tanFi = dx / dy;
            fi = 90 - atan(tanFi) * 180 / 3.1416;
            ay = radius / sqrt(1 + tanFi * tanFi);
            ax = ay * tanFi;
        } else {
            tanFi = dy / dx;
            fi = atan(tanFi) * 180 / 3.1416;
            ax = radius / sqrt(1 + tanFi * tanFi);
            ay = ax * tanFi;
        }

        fi = y2 > y1 ? -fi : fi;
        ay = y2 > y1 ? -ay : ay;

        MoveToEx(hdc, x1, y1, NULL);
        LineTo(hdc, cx, cy);
        MoveToEx(hdc, cx, cy, NULL);
        LineTo(hdc, x2, y2);
        drawArrow(hdc, fi, x2 - ax, y2 + ay);

    } else {
        cx = (x1 + x2) * 0.5 + radius;
        cy = (y1 + y2) * 0.5 + radius;
        dx = abs(cx - x2);
        dy = abs(cy - y2);

        if (dx > dy) {
            tanFi = dx / dy;
            fi = 90 - atan(tanFi) * 180 / 3.1416;
            ay = radius / sqrt(1 + tanFi * tanFi);
            ax = ay * tanFi;
        } else {
            tanFi = dy / dx;
            fi = atan(tanFi) * 180 / 3.1416;
            ax = radius / sqrt(1 + tanFi * tanFi);
            ay = ax * tanFi;
        }

        fi = y1 > y2 ? -fi : fi;
        ay = y2 > y1 ? -ay : ay;

        MoveToEx(hdc, x1, y1, NULL);
        LineTo(hdc, cx, cy);
        MoveToEx(hdc, cx, cy, NULL);
        LineTo(hdc, x2, y2);
        drawArrow(hdc, fi + 180, x2 + ax, y2 + ay);
    }
}

void drawDoubleArc(HDC hdc,int x1, int y1, int x2, int y2, int isDirected) {

    int radius = RADIUS;
    double cx1 = (x1 + x2) * 0.60;
    double cy1 = (y1 + y2) * 0.53;
    if (y1 == y2) cy1 = (y1 + y2 - 100) * 0.5;
    double dx1 = fabs(cx1 - x2);
    double dy1 = fabs(cy1 - y2);
    double tanFi1 = dx1 / dy1;

    double fi1 = atan2(dy1, dx1) * 180 / 3.1416;
    int ay1 = radius / sqrt(1 + tanFi1 * tanFi1);
    int ax1 = ay1 * tanFi1;

    double cx2 = (x1 + x2) * 0.52;
    double cy2 = (y1 + y2) * 0.64;
    if (y1 == y2) cy2 = (y1 + y2 - 100) * 0.5;
    double dx2 = fabs(cx2 - x2);
    double dy2 = fabs(cy2 - y2);
    double tanFi2 = dx2 / dy2;

    double fi2 = atan2(dy2, dx2) * 180 / 3.1426;
    int ay2 = radius / sqrt(1 + tanFi2 * tanFi2);
    int ax2 = ay2 * tanFi2;

    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, cx1, cy1);
    MoveToEx(hdc, cx1, cy1, NULL);
    LineTo(hdc, x2, y2);
    if (isDirected) drawArrow(hdc, fi1, x2 + ax1, y2 + ay1);

    MoveToEx(hdc, x2, y2, NULL);
    LineTo(hdc, cx2, cy2);
    MoveToEx(hdc, cx2, cy2, NULL);
    LineTo(hdc, x1, y1);
    if (isDirected) drawArrow(hdc, fi2, x1 + ax2, y1 + ay2);
}
void drawLeftArc(HDC hdc, int x1, int y1, int x2, int y2, int isDirected ) {
    int radius = RADIUS;
    double cx = (x1 + x2) * 0.5 - radius * 2;
    double cy = (y1 + y2) * 0.55;
    if (y1 == y2) cy = (y1 + y2 - 100) * 0.5;
    double dx = fabs(cx - x2);
    double dy = fabs(cy - y2);
    double tanFi = dx / dy;

    double fi = atan2(dy, dx) * 180 / 3.1416;
    int ay = radius / sqrt(1 + tanFi * tanFi);
    int ax = ay * tanFi;

    if (y1 == y2) {
        ax = -ax;
        ay = -ay;
        fi = -fi;
    } else {
        if (y1 < y2) {
            ax = -ax;
            ay = -ay;
            fi = -fi;
        } else {
            fi = 180 -fi;
        }
    }

    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, cx, cy);
    MoveToEx(hdc, cx, cy, NULL);
    LineTo(hdc, x2, y2);
    if (isDirected) drawArrow(hdc, fi, x2 + ax, y2 + ay);
}

void drawRightArc(HDC hdc, int x1, int y1, int x2, int y2, int isDirected) {
    int radius = RADIUS;
    double cx = (x1 + x2) * 0.5 + radius * 2;
    double cy = (y1 + y2) * 0.55;
    if (y1 == y2) cy = (y1 + y2 - 100) * 0.5;
    double dx = abs(cx - x2);
    double dy = abs(cy - y2);

    double tanFi = dy / dx;
    double fi = atan(tanFi) * 180 / 3.1416;
    int ax = radius / sqrt(1 + tanFi * tanFi);
    int ay = ax * tanFi;

    if (y1 == y2) {
        ay = -ay;
        fi = 180 + fi;
    } else {
        if (y1 < y2) {
            ay = -ay;
            fi = 180 + fi;
        } else {
            ax = -ax;
        }
    }

    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, cx, cy);
    MoveToEx(hdc, cx, cy, NULL);
    LineTo(hdc, x2, y2);
    if (isDirected) drawArrow(hdc, fi, x2 + ax, y2 + ay);
}
void drawStraightEdge(HDC hdc, int x1, int y1, int x2, int y2, int isDirected) {
    int radius = RADIUS;
    int absx = abs(x1 - x2);
    int absy = abs(y1 - y2);
    double cx, cy;
    double fi, tanFi;
    int ax, ay;

    if (y1 == y2) {
        fi = x2 > x1 ? 0 : 180;
        ax = x2 > x1 ? -radius : radius;

        MoveToEx(hdc, x1, y1, NULL);
        LineTo(hdc, x2, y2);
        if (isDirected) drawArrow(hdc, fi, x2 + ax, y2);

    } else if (x1 == x2) {
        fi = y2 > y1 ? -90 : 90;
        ay = y2 > y1 ? -radius : radius;

        MoveToEx(hdc, x1, y1, NULL);
        LineTo(hdc, x2, y2);
        if (isDirected) drawArrow(hdc, fi, x2, y2 + ay);

    } else if (x2 > x1) {
        if (absx > absy) {
            tanFi = absx / absy;
            fi = 90 - atan(tanFi) * 180 / 3.1416;
            ay = radius / sqrt(1 + tanFi * tanFi);
            ax = ay * tanFi;
        } else {
            tanFi = absy / absx;
            fi = atan(tanFi) * 180 / 3.1416;
            ax = radius / sqrt(1 + tanFi * tanFi);
            ay = ax * tanFi;
        }

        fi = y2 > y1 ? -fi : fi;
        ay = y2 > y1 ? -ay : ay;

        MoveToEx(hdc, x1, y1, NULL);
        LineTo(hdc, x2, y2);
        if (isDirected) drawArrow(hdc, fi, x2 - ax, y2 + ay);

    } else if (x1 > x2) {
        if (absx > absy) {
            tanFi = absx / absy;
            fi = 90 - atan(tanFi) * 180 / 3.1416;
            ay = radius / sqrt(1 + tanFi * tanFi);
            ax = ay * tanFi;
        } else {
            tanFi = absy / absx;
            fi = atan(tanFi) * 180 / 3.1416;
            ax = radius / sqrt(1 + tanFi * tanFi);
            ay = ax * tanFi;
        }

        fi = y1 > y2 ? -fi : fi;
        ay = y2 > y1 ? -ay : ay;

        MoveToEx(hdc, x1, y1, NULL);
        LineTo(hdc, x2, y2);
        if (isDirected) drawArrow(hdc, fi + 180, x2 + ax, y2 + ay);
    }
}
