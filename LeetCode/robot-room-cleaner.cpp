/*
 * robot-room-cleaner.cpp
 *
 *  Created on: Apr 7, 2019
 *      Author: subha
 */

#include <bits/stdc++.h>
using namespace std;

//Problem: Design an algorithm to clean the entire room using only the 4 given APIs shown below.
//Notes:
// 1.The input is only given to initialize the room and the robot's position internally.
//	 You must solve this problem "blindfolded". In other words, you must control the robot using only
//	 the mentioned 4 APIs, without knowing the room layout and the initial robot's position.
// 2.The initial direction of the robot will be facing up.


// This is the robot's control interface.
// You should not implement it, or speculate about its implementation
class Robot {
  public:
    // Returns true if the cell in front is open and robot moves into the cell.
    // Returns false if the cell in front is blocked and robot stays in the current cell.
    bool move();
    // Robot will stay in the same cell after calling turnLeft/turnRight.
    // Each turn will be 90 degrees.
    void turnLeft();
    void turnRight();
    // Clean the current cell.
    void clean();
};



namespace std {
    template<>
    struct hash<pair<int,int>> {
        size_t operator() (const pair<int,int>& p) const {
            return hash<int>()(p.first) ^ hash<int>()(p.second);
        }
    };
}

class Solution {
    // Need to mark the places visited to avoid infinite loop
    //
    // Although we do not know the absolute positions, but we can infer relative position
    // from the starting point, remapping that as origin. So postion can be negative also.
    map<pair<int,int>, bool> visited;

    vector<vector<int>> dir = {{-1,0}, {0,-1}, {0,1}, {1,0}}; // up, left, right, down

    void cleanRoomFromParent(Robot& robot, int row, int col, int face) {
        pair<int,int> p = make_pair(row, col);
        if(visited.find(p) != visited.end()) {
            //turn back
            robot.turnLeft();
            robot.turnLeft();
            //move to original position
            robot.move();
            //turn as before the move
            robot.turnLeft();
            robot.turnLeft();
            return;
        }

        robot.clean();
        visited[p] = true;

        //make the face up
        if(face == 1) {
            robot.turnRight();
        } else if(face == 2) {
            robot.turnLeft();
        } else if(face == 3) {
            robot.turnLeft();
            robot.turnLeft();
        }

        bool moved = robot.move();
        if(moved) {
            cleanRoomFromParent(robot, row+dir[0][0], col+dir[0][1], 0);
        }

        robot.turnLeft();
        moved = robot.move();
        if(moved) {
            cleanRoomFromParent(robot, row+dir[1][0], col+dir[1][1], 1);
        }

        robot.turnRight();
        robot.turnRight();
        moved = robot.move();
        if(moved) {
            cleanRoomFromParent(robot, row+dir[2][0], col+dir[2][1], 2);
        }

        robot.turnRight();
        moved = robot.move();
        if(moved) {
            cleanRoomFromParent(robot, row+dir[3][0], col+dir[3][1], 3);
        }

        //Now it is faced down from the
        if(face == 0) {
            //Face was up. Now should be down. Nothing to do
        } else if(face == 1) {
            //Face was left. Now sould be right
            robot.turnLeft();
        } else if(face == 2) {
            //Face was right. Now should be left
            robot.turnRight();
        } else if(face == 3) {
            // Face was down. Now should be up
            robot.turnLeft();
            robot.turnLeft();
        }
        robot.move();   //Move to its previoud position
        //Turn the face 180 degree to restore how it was before
        robot.turnLeft();
        robot.turnLeft();
        return;
    }
public:
    void cleanRoom(Robot& robot) {
        cleanRoomFromParent(robot, 0, 0, 0);

        return;
    }
};


