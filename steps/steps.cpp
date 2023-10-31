/* 
 * Question 4 (20 pts) Suppose we start with x = 1. At each step, we can either a) multiply x by 2 or b) increment x by 5, c) 
 * increment x by 7, or d) decrement x by 1 The goal is to reach a target T. Design an algorithm that returns the minimum number
 * of steps to reach T. Briefly justify the correctness and the running time in terms of T. 
 */


/*
    We can think of this problem as a sort of tree because each node gives us 4 other nodes to jump to

                                      1
                    2          6            8           0
                4 7 9 1    12 11 13 5   16 13 15 7   0 5 7 -1


    When we reach the target, we'll return the level we're on
*/

#include <iostream>
#include <functional>
#include <vector>
#include <queue>
#include <cmath>

// Use queue for BFS. Every time we see a node, we add its children to queue. We iterate through children. If we find target, we
// return the level we're on. When we're done with that round of children, we increment the level.
int returnMinimumSteps(int target, int current)
{
    int level = 0;
    std::queue<int> q;
    q.push(current);
    while (!q.empty())
    {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; i++)
        {
            int front = q.front(); q.pop();
            if (front == target)
            {
                return level;
            }
            q.push(front * 2);
            q.push(front + 5);
            q.push(front + 7);
            q.push(front - 1);
        }
        level++;
    }
    return -1;
}

// Pass a target as command line arg.
int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <target>" << std::endl;
        return 1;
    }
    int target = std::stoi(argv[1]);
    int minimumSteps = returnMinimumSteps(target, 1);   // Start at 1
    std::cout << "Minimum steps to reach target " << target << ": " << minimumSteps << std::endl;
    // Note since we can subtract by 1 it is possible to reach any target
    return 0;
}
