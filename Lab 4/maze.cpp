#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

const int ROWS = 35;
const int COLS = 35;
const int CELL_SIZE = 35;

struct Cell {
    bool visited;
    bool wallTop, wallRight, wallBottom, wallLeft;

    Cell() : visited(false), wallTop(true), wallRight(true), wallBottom(true), wallLeft(true) {}
};

std::vector<Cell> maze(ROWS * COLS);
int startRow, startCol, endRow, endCol;

bool isValid(int row, int col) {
    return (row >= 0 && row < ROWS && col >= 0 && col < COLS);
}

int getRandomDirection() {
    return std::rand() % 4;
}

void carvePassage(int currentRow, int currentCol) {
    maze[currentRow * COLS + currentCol].visited = true;
    std::vector<int> directions = {0, 1, 2, 3};
    std::random_shuffle(directions.begin(), directions.end());

    for (int dir : directions) {
        int newRow = currentRow;
        int newCol = currentCol;

        switch (dir) {
            case 0: newRow--; break; // Up
            case 1: newCol++; break; // Right
            case 2: newRow++; break; // Down
            case 3: newCol--; break; // Left
        }

        if (isValid(newRow, newCol) && !maze[newRow * COLS + newCol].visited) {
            if (dir == 0) {
                maze[currentRow * COLS + currentCol].wallTop = false;
                maze[newRow * COLS + newCol].wallBottom = false;
            }
            if (dir == 1) {
                maze[currentRow * COLS + currentCol].wallRight = false;
                maze[newRow * COLS + newCol].wallLeft = false;
            }
            if (dir == 2) {
                maze[newRow * COLS + newCol].wallTop = false;
                maze[currentRow * COLS + currentCol].wallBottom = false;
            }
            if (dir == 3) {
                maze[newRow * COLS + newCol].wallRight = false;
                maze[currentRow * COLS + currentCol].wallLeft = false;
            }

            carvePassage(newRow, newCol);
        }
    }
}

void generateMaze() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            maze[row * COLS + col] = Cell();
        }
    }

    startRow = std::rand() % ROWS;
    startCol = std::rand() % COLS;

    carvePassage(startRow, startCol);

    endRow = ROWS - 1;
    endCol = COLS - 1;
}

void drawMaze() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            const Cell& cell = maze[row * COLS + col];
            int x = col * CELL_SIZE;
            int y = row * CELL_SIZE;

            glColor3f(1.0f, 1.0f, 1.0f);

            if (cell.wallTop) {
                glBegin(GL_LINES);
                glVertex2i(x, y);
                glVertex2i(x + CELL_SIZE, y);
                glEnd();
            }
            if (cell.wallRight) {
                glBegin(GL_LINES);
                glVertex2i(x + CELL_SIZE, y);
                glVertex2i(x + CELL_SIZE, y + CELL_SIZE);
                glEnd();
            }
            if (cell.wallBottom) {
                glBegin(GL_LINES);
                glVertex2i(x, y + CELL_SIZE);
                glVertex2i(x + CELL_SIZE, y + CELL_SIZE);
                glEnd();
            }
            if (cell.wallLeft) {
                glBegin(GL_LINES);
                glVertex2i(x, y);
                glVertex2i(x, y + CELL_SIZE);
                glEnd();
            }
        }
    }

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, COLS * CELL_SIZE, 0, ROWS * CELL_SIZE);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(COLS * CELL_SIZE, ROWS * CELL_SIZE);
    glutCreateWindow("Maze Generator");
    glutDisplayFunc(drawMaze);
    glutReshapeFunc(reshape);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    generateMaze();

    glutMainLoop();

    return 0;
}
