/*
    This program will read in two .txt files and create a graph that will be
    recursively searched with DFS. It will do this by guiding "Leon" throughout several
    locations within Resident Evil 4. Each location has an enemy count that uses up 1 ammo
    per enemy. Leon starts off at "Village" with 10 ammo and must reach "Church" without
    running out of ammo along the way. The function saveAshley will recurse throughout all
    possible pathways, and will backtrack by returning false when Leon does not have enough
    ammo to continue progression. Finally, Leons successful path will be printed out by
    printing out the contents of the predecessor <string, string> map.
    Output: Names of locations for the successful path (contained in predecessor map)
*/
