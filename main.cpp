/*
    Name: Ramon Perez, CS 302-1004
    Description: This program will read in two .txt files and create a graph that will be
    recursively searched with DFS. It will do this by guiding "Leon" throughout several
    locations within Resident Evil 4. Each location has an enemy count that uses up 1 ammo
    per enemy. Leon starts off at "Village" with 10 ammo and must reach "Church" without
    running out of ammo along the way. The function saveAshley will recurse throughout all
    possible pathways, and will backtrack by returning false when Leon does not have enough
    ammo to continue progression. Finally, Leons successful path will be printed out by
    printing out the contents of the predecessor <string, string> map.
    Output: Names of locations for the successful path (contained in predecessor map)
*/
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <list>
#include <vector>

using namespace std;

bool saveAshley (string leon , int ammo ,
unordered_map <string , list <string >> map ,
unordered_map <string , int >           enemiesAtLocation ,
unordered_map <string , int >&          ammoAtLocation ,
unordered_map <string , string >&       predecessor )
{
    /*
    FUNCTION_IDENTIFIER: This recursive bool funciton will assist Leon with finding the
    successful path to take to get to "Church". The base case will check to see if Leon
    has made it to "Church". If so, True will be returned to all previous calls to
    establish the current path as the correct path. If base case is not met, then the
    function will go through every member at current location "leon" and travel to that
    location if the current ammo count allows it. When a new location is reached, the 
    ammoAtLocation map will be updated if the current ammo is higher than amount of ammo
    the last time leon was at the location. Finally recursively call the function and return
    True to keep the chain going.
    Return Value: True if Leon was able to reach "Church", False if Leon must backtrack
    */

    // string leon - denotes Leon’s current location

    // int ammo - the amount of ammo when Leon arrives at the current location

    // unordered_map< string, list<string> > map - adjacency list

    // unordered_map<string, int> enemiesAtLocation - a map that maps a location to the
    // amount of enemies at the location

    // &unordered_map<string, int>& ammoAtLocation - maps a location to the max amount
    // of ammo when Leon arrived at any location at any point in time

    // &unordered_map<string, string>& predecessor - predecessor array

    // Base Case
    if (leon == "Church")
    {
        bool endCredits = true;
        return endCredits;
    }
    
    // For every neighbor at location
    for (auto neighbor : map[leon])
    {
        if (ammo >= enemiesAtLocation[neighbor]) // If we have enough ammo to go to location
        {
            // Get new ammo count
            int ammoRemaining = (ammo - enemiesAtLocation[neighbor]);

            // If we have more ammo than a previous visit
            if (ammoRemaining >= ammoAtLocation[neighbor])
            {
                ammoAtLocation[neighbor] = ammoRemaining;
            }

            // Update predecessor path
            predecessor[leon] = neighbor;
            
            // If the next move returns true, return true to prev function call
            if (saveAshley(neighbor, ammoRemaining, map, enemiesAtLocation, ammoAtLocation, predecessor))
            {
                return true;
            }
        }
    }

    return false; 
}



int main()
{
    // You will need an adjacency list, since each node is labeled by a string, a hash map will be used, the structure
    // is declared below.
    unordered_map<string, list<string>> adjList;

    // This maps a location to a linked list of its neighbor locations. You will also need a map to track the amount
    // of enemies at a location
    unordered_map <string, int> enemiesAtLocation;

    // You also need a ”visited” array, this map will be used to store the amount of ammo Leon has when he arrives
    // at a location, if another path in the future is found to this location but Leon has less ammo in this time,
    // then you do not revisit the node, only revisit if the amount of ammo Leon has is more than the last time he
    // visited this node, the structure is defined below
    unordered_map<string, int> ammoAtLocation;

    // In order to output the path Leon takes, you will need a predecessor array
    unordered_map<string, string> predecessor;


// Main Program
    string mapName, enemyName;

    cout << "LEON!!!\n\nEnter map file : ";
    cin >> mapName;

    cout << "\nEnter enemies file : ";
    cin >> enemyName;


    // Read Map File
    string from, to;
    fstream mapFile;

    mapFile.open(mapName);
    while (mapFile >> from >> to)
    {
        adjList[from].push_back(to);
        // cout << "from: " << from << " to: " << to << endl; // Debug
    }
    mapFile.close();


    // Read Enemy File
    string location;
    int enemyNum;
    fstream enemyFile;

    enemyFile.open(enemyName);
    while (enemyFile >> location >> enemyNum)
    {
        enemiesAtLocation[location] = enemyNum;
        // cout << "location: " << location << " enemyNum: " << enemyNum << endl; // Debug
    }
    enemyFile.close();


    // Save Ashley
    string leon = "Village";
    int ammo = 10;
    saveAshley(leon, ammo, adjList, enemiesAtLocation, ammoAtLocation, predecessor);


    // Output
    string chapter = "Village";
    cout << "\nI'm coming Ashley!\n" << chapter;
    // predecessor array is used to output answer

    for (auto neighbor : predecessor)
    {
        if (predecessor[chapter] != "")
        {
            cout << " -> " << predecessor[chapter];
            chapter = predecessor[chapter];
        }
    }
    cout << endl;


    return 0;
}