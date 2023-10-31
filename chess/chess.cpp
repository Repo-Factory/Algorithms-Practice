/* 
 * Question 1 (25 pts) We are given an n by n chess board. A knight can move two squares vertically and one square horizontally, 
 *  or two squares horizontally and one square vertically.
 *  Suppose the board is represented by an array A. If A[i, j] = −1 then, the square (i, j) is forbidden. 
 *  If A[i, j] = 1 then, the square (i, j) is free to move to. Design an algorithm to return all squares that 
 *  the knight can go to from the top left corner (0, 0) via a series of moves without visiting any forbidden squares. 
 *  Briefly justify the correctness and the running time in terms of n. 
 */

#include <iostream>
#include <functional>
#include <vector>

struct Point
{
    int x;
    int y;
};

// VALID MOVEMENTS
const int dx[] = { 2, 2, 1, 1, -1, -1, -2, -2 };
const int dy[] = { 1, -1, 2, -2, 2, -2, 1, -1 };

// create a 2D array and initialize it with 1 (valid squares).
int** create2DArray(int rows, int cols) {
    int** arr = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        arr[i] = new int[cols];
        for (int j = 0; j < cols; ++j) {
            arr[i][j] = 1; // Initialize all squares as valid (1).
        }
    }
    return arr;
}

// delete a dynamically allocated 2D array.
void delete2DArray(int** board, int rows)
{
    for (int i = 0; i < rows; ++i) {
        delete[] board[i];
    }
    delete[] board;
}

// print a 2D array.
void print2DArray(int** board, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (board[i][j] >= 0)
            {
                std::cout << " "; // Add space for readability.
            }
            std::cout << board[i][j] << " "; // Print the value in the square.
        }
        std::cout << std::endl;
    }
}

// check if a given point is within the boundaries of the chessboard.
bool isValidPoint(const Point& point, int n)
{
    return (point.x >= 0 && point.x < n && point.y >= 0 && point.y < n);
}

// generate an array of possible points the knight can move to from a given point.
Point** getPossiblePoints(const Point& currentPoint)
{
    Point** validPoints = new Point*[8];

    for (int i = 0; i < 8; i++)
    {
        int newX = currentPoint.x + dx[i];
        int newY = currentPoint.y + dy[i];
        validPoints[i] = new Point{newX, newY}; // Create and store valid points.
    }

    return validPoints;
}

// find and return all valid squares the knight can reach from the top-left corner.
std::vector<Point> validSquares(int** board, int n)
{
    // Define a recursive explore valid moves from a point.
    const std::function<void(const Point&)> recursiveHop = [&](const Point& point) {
        Point** possiblePoints = getPossiblePoints(point);
        board[point.x][point.y] = 0; // Mark the square as visited.
        for (int i = 0; i < 8; i++) {
            if (isValidPoint(*possiblePoints[i], n) && board[(*possiblePoints[i]).x][(*possiblePoints[i]).y] == 1)
            {
                recursiveHop(*possiblePoints[i]); // Recursively explore valid moves.
            }
        }
    };

    const Point startPoint = Point{0,0};
    recursiveHop(startPoint); // Start the exploration from the top-left corner.
    std::vector<Point> validSquares;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 0) {
                validSquares.push_back(Point{i,j}); // Collect all valid squares by looking through visited board squares (0).
            }
        }
    }
    return validSquares;
}

int main(int argc, char* argv[]) {
    // Parse the chessboard size 'n' from command line argument.
    int n = std::stoi(argv[1]); 
    int** board = create2DArray(n, n);

    // Mark certain squares as forbidden using negative values.
    board[1][1] = -1;
    board[1][2] = -1;
    board[2][0] = -1;
    board[2][2] = -1;
    board[3][3] = -1;
    
    // Find and print all valid squares the knight can reach.
    const std::vector<Point> validPoints = validSquares(board, n);
    for (const auto& point : validPoints)
    {
        std::cout << "[" << point.x << "," << point.y << "]" << " "; 
    }
    std::cout << std::endl << std::endl << std::endl;

    // Print the chessboard with marked squares.
    print2DArray(board, n, n);

    // 0: visited
    // 1: valid but not visited 
    // 2: invalid

    // Clean up memory by deleting the dynamically allocated 2D array.
    delete2DArray(board, n);

    return 0;
}
