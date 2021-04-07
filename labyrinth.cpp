/*  
*   
*   GSoC-2021 JdeRobot- Universidad Rey Juan Carlos
*
*   IdeaSource: https://www.geeksforgeeks.org/rat-in-a-maze-backtracking-2
* 
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

int dirNum = 4;
int dirX[] = { -1, 0, 1,  0 };
int dirY[] = { 0, 1, 0, -1 };

void DFS(int x, int y, vector<vector<char>>& labyMap, vector<vector<bool>>& visited, int& curLen, bool outputMap)
{
    if (outputMap) {
        labyMap[x][y] = curLen + '0'; //ASCII
    }

    for (int i = 0; i < dirNum; i++) {
        //4directions -> [up, right, down, left]
        int newX = x + dirX[i];
        int newY = y + dirY[i];
        if (newX >= 0 && newX < labyMap.size() &&
            newY >= 0 && newY < labyMap[0].size() &&
            labyMap[newX][newY] == '.' &&
            visited[newX][newY] == false) {

            visited[newX][newY] = true;
            curLen++;
            DFS(newX, newY, labyMap, visited, curLen, outputMap);
        }
    }
}

int main(int argc, char* argv[]) {

    string inputFileName = "labyrinth.txt";

    if (argc == 2) inputFileName = argv[1];
    ifstream mapFile(inputFileName.c_str());

    if (!mapFile.is_open())
    {
        cout << "Error opening the map file: " << argv[1] << endl;
        exit(1);
    }

    int labyRow, labyCol;
    vector<vector<char>> labyMap;
    char tmpChar;
    mapFile >> labyRow >> labyCol;
    for (int i = 0; i < labyRow; i++) {
        vector<char> row;
        labyMap.push_back(row);

        for (int j = 0; j < labyCol; j++) {
            mapFile >> tmpChar;
            labyMap[i].push_back(tmpChar);
        }
    }
    mapFile.close();

    // Input BackUp
    vector<vector<char>> outputMap = labyMap;

    cout << "The Labyrinth input is like follows:\n" << endl;
    cout << labyRow << " " << labyCol << endl;
    for (int i = 0; i < labyRow; i++) {
        for (int j = 0; j < labyCol; j++) {
            cout << labyMap[i][j];
        }
        cout << endl;
    }

    // Solve the labyrinth problem using DFS, it's like finding connected components
    vector<vector<bool>> visited;
    for (int i = 0; i < labyRow; i++) {
        vector<bool> row;
        visited.push_back(row);

        for (int j = 0; j < labyCol; j++) {
            visited[i].push_back(false);
        }
    }

    // Output BackUp
    vector<vector<bool>> outputVisited = visited;

    int maxLen = 0, curLen, startX, startY;
    for (int i = 0; i < labyRow; i++) {
        for (int j = 0; j < labyCol; j++) {
            if (labyMap[i][j] == '#' || visited[i][j] == true) continue;

            //'.'not visited -> DFS from here and track the pathway
            curLen = 0;
            visited[i][j] = true;
            DFS(i, j, labyMap, visited, curLen, false);

            if (curLen > maxLen) {
                maxLen = curLen;
                startX = i;
                startY = j;
            }
        }
    }

    // Restore the map and do a final DFS to get the result
    curLen = 0;
    outputVisited[startX][startY] = true;
    DFS(startX, startY, outputMap, outputVisited, curLen, true);

    cout << "\nThe output is as follows:\n" << endl;
    for (int i = 0; i < labyRow; i++) {
        for (int j = 0; j < labyCol; j++) {
            cout << outputMap[i][j];
        }
        cout << endl;
    }
    return 0;
}