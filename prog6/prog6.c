#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 80
#define HEIGHT 40

typedef struct {
    int center_x;
    int center_y;
    int radius;
} Circle;

// The 4 Core Modular Functions
void clearBuffer(char buffer[HEIGHT][WIDTH]);
void calculateCirclePoints(char buffer[HEIGHT][WIDTH], Circle c, double aspect_ratio);
void drawPairToBuffer(char buffer[HEIGHT][WIDTH], int row, int left_col, int right_col);
void renderBuffer(char buffer[HEIGHT][WIDTH]);

int main() {
    char screenBuffer[HEIGHT][WIDTH];

    Circle myCircle;
    myCircle.center_x = WIDTH / 2;   // 40
    myCircle.center_y = HEIGHT / 2;  // 20
    myCircle.radius = 12;            // Radius in vertical rows

    // Adjust this value (e.g., 2.0 to 2.4) to perfectly tune roundness for your console font
    double currentFontAspectRatio = 2.0; 

    // Execute modular execution pipeline
    clearBuffer(screenBuffer);
    calculateCirclePoints(screenBuffer, myCircle, currentFontAspectRatio);
    renderBuffer(screenBuffer);

    return 0;
}

// 1. Clears the grid buffer with blank canvas spaces
void clearBuffer(char buffer[HEIGHT][WIDTH]) {
    for (int r = 0; r < HEIGHT; r++) {
        for (int c = 0; c < WIDTH; c++) {
            buffer[r][c] = ' ';
        }
    }
}

// 2. Traverses each scanline mathematically to calculate exactly two positions per row
void calculateCirclePoints(char buffer[HEIGHT][WIDTH], Circle c, double aspect_ratio) {
    for (int y_offset = -c.radius; y_offset <= c.radius; y_offset++) {
        int target_row = c.center_y + y_offset;
        
        // Skip calculation entirely if row falls off the top or bottom of the screen
        if (target_row < 0 || target_row >= HEIGHT) {
            continue;
        }

        // Apply Pythagorean theorem: x = sqrt(R^2 - y^2)
        double x_math = sqrt((c.radius * c.radius) - (y_offset * y_offset));
        
        // Counteract font dimensional distortions
        int x_adjusted = (int)(x_math * aspect_ratio);

        int left_column = c.center_x - x_adjusted;
        int right_column = c.center_x + x_adjusted;

        // Delegate the printing pass off to the boundary supervisor function
        drawPairToBuffer(buffer, target_row, left_column, right_column);
    }
}

// 3. Validates array indices and plots a single matching pair of symbols onto the grid
void drawPairToBuffer(char buffer[HEIGHT][WIDTH], int row, int left_col, int right_col) {
    if (left_col >= 0 && left_col < WIDTH) {
        buffer[row][left_col] = '*';
    }
    if (right_col >= 0 && right_col < WIDTH) {
        buffer[row][right_col] = '*';
    }
}

// 4. Outputs the processed character array out to the stdout stream
void renderBuffer(char buffer[HEIGHT][WIDTH]) {
    for (int r = 0; r < HEIGHT; r++) {
        for (int c = 0; c < WIDTH; c++) {
            putchar(buffer[r][c]);
        }
        putchar('\n');
    }
}