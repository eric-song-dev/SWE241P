/* ************************************************************************
> File Name:     tests/graph_test.cpp
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Sun Oct 26 15:53:54 2025
> Description:   
 ************************************************************************/

#include <gtest/gtest.h>
#include "../include/Graph.h"
#include <fstream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

// Helper function to create temporary test files
void createTestFile(const std::string& filename, const std::vector<std::string>& lines) {
    std::ofstream outFile(filename);
    for (const auto& line : lines) {
        outFile << line << std::endl;
    }
    outFile.close();
}

class GraphTest : public ::testing::Test {
protected:
    Graph g;
    const std::string testPopFile = "test_city_population.txt";
    const std::string testRoadFile = "test_road_network.txt";
    const std::string emptyFile = "empty_test_file.txt";

    void SetUp() override {
        createTestFile(emptyFile, {});
    }

    void TearDown() override {
        remove(testPopFile.c_str());
        remove(testRoadFile.c_str());
        remove(emptyFile.c_str());
    }
};

TEST_F(GraphTest, Task1_CityCreation) {
    City c1("Testville", 5000);
    EXPECT_EQ(c1.name, "Testville");
    EXPECT_EQ(c1.population, 5000);
    EXPECT_TRUE(c1.neighbors.empty());

    City c2("Neighborburg", 3000);
    c1.addNeighbor(&c2);
    ASSERT_EQ(c1.neighbors.size(), 1);
    EXPECT_EQ(c1.neighbors[0]->name, "Neighborburg");
    std::cout << "Test Passed: City objects created and neighbors added correctly." << std::endl << std::endl;
}

TEST_F(GraphTest, Task2_LoadData) {
    createTestFile(testPopFile, {"A: 100", "B: 200", "C: 300", "D: 400", "E: 500"});
    createTestFile(testRoadFile, {"A: B", "C: D"});

    ASSERT_TRUE(g.loadData(testPopFile, testRoadFile));

    City* cityA = g.getCity("A");
    City* cityB = g.getCity("B");
    City* cityC = g.getCity("C");
    City* cityD = g.getCity("D");
    City* cityE = g.getCity("E");

    ASSERT_NE(cityA, nullptr);
    ASSERT_NE(cityB, nullptr);
    ASSERT_NE(cityC, nullptr);
    ASSERT_NE(cityD, nullptr);
    ASSERT_NE(cityE, nullptr);

    EXPECT_EQ(cityA->population, 100);
    EXPECT_EQ(cityE->population, 500);

    // Check neighbors (bidirectional)
    ASSERT_EQ(cityA->neighbors.size(), 1);
    EXPECT_EQ(cityA->neighbors[0], cityB);
    ASSERT_EQ(cityB->neighbors.size(), 1);
    EXPECT_EQ(cityB->neighbors[0], cityA);

    ASSERT_EQ(cityC->neighbors.size(), 1);
    EXPECT_EQ(cityC->neighbors[0], cityD);
    ASSERT_EQ(cityD->neighbors.size(), 1);
    EXPECT_EQ(cityD->neighbors[0], cityC);

    EXPECT_TRUE(cityE->neighbors.empty());
    std::cout << "Test Passed: Graph constructed correctly from files." << std::endl << std::endl;
}

TEST_F(GraphTest, Task3_countIslands) {
    createTestFile(testPopFile, {"A:1", "B:1", "C:1", "D:1", "E:1", "F:1"});
    createTestFile(testRoadFile, {"A:B", "C:D", "D:E"}); // 3 islands: {A, B}, {C, D, E}, {F}

    g.loadData(testPopFile, testRoadFile);

    EXPECT_EQ(g.countIslands(), 3);
    std::cout << "Test Passed: Correct number of islands counted." << std::endl << std::endl;
}

TEST_F(GraphTest, Task3_countIslands_EmptyGraph) {
    createTestFile(testPopFile, {});
    createTestFile(testRoadFile, {});
    g.loadData(testPopFile, testRoadFile);
    EXPECT_EQ(g.countIslands(), 0);
    std::cout << "Test Passed: Correctly handles empty graph." << std::endl << std::endl;
}

TEST_F(GraphTest, Task3_countIslands_NoRoads) {
    createTestFile(testPopFile, {"A:1", "B:1", "C:1"});
    createTestFile(testRoadFile, {}); // No roads, each city is an island
    g.loadData(testPopFile, testRoadFile);
    EXPECT_EQ(g.countIslands(), 3);
    std::cout << "Test Passed: Correctly counts islands when no roads exist." << std::endl << std::endl;
}

TEST_F(GraphTest, Task4_GetIslandPopulations) {
    createTestFile(testPopFile, {"A:10", "B:20", "C:30", "D:40", "E:50", "F:60"});
    createTestFile(testRoadFile, {"A:B", "C:D", "D:E"}); // Islands: {A, B} = 30, {C, D, E} = 120, {F} = 60

    g.loadData(testPopFile, testRoadFile);

    std::vector<long long> pops = g.getIslandPopulations();
    std::sort(pops.begin(), pops.end());

    ASSERT_EQ(pops.size(), 3);
    EXPECT_EQ(pops[0], 30);
    EXPECT_EQ(pops[1], 60);
    EXPECT_EQ(pops[2], 120);

    // Verify total population
    long long totalPop = std::accumulate(pops.begin(), pops.end(), 0LL);
    EXPECT_EQ(totalPop, 10 + 20 + 30 + 40 + 50 + 60);
    std::cout << "Test Passed: Island populations calculated correctly." << std::endl << std::endl;
}

TEST_F(GraphTest, Task4_GetIslandPopulations_Empty) {
    createTestFile(testPopFile, {});
    createTestFile(testRoadFile, {});
    g.loadData(testPopFile, testRoadFile);
    std::vector<long long> pops = g.getIslandPopulations();
    EXPECT_TRUE(pops.empty());
    std::cout << "Test Passed: Handles empty graph correctly." << std::endl << std::endl;
}


TEST_F(GraphTest, Task5_FindShortestPath_Simple) {
    createTestFile(testPopFile, {"A:1", "B:1", "C:1", "D:1", "E:1", "F:1"});
    createTestFile(testRoadFile, {"A:B", "B:C", "C:D", "D:E"}); // A-B-C-D-E, F is separate

    g.loadData(testPopFile, testRoadFile);

    EXPECT_EQ(g.findShortestPath("A", "A"), 0);
    EXPECT_EQ(g.findShortestPath("A", "B"), 1);
    EXPECT_EQ(g.findShortestPath("A", "C"), 2);
    EXPECT_EQ(g.findShortestPath("A", "E"), 4);
    EXPECT_EQ(g.findShortestPath("E", "A"), 4);
    EXPECT_EQ(g.findShortestPath("B", "D"), 2);

    // Unreachable
    EXPECT_EQ(g.findShortestPath("A", "F"), -1);
    EXPECT_EQ(g.findShortestPath("F", "A"), -1);

    // Non-existent cities
    EXPECT_EQ(g.findShortestPath("A", "X"), -1);
    EXPECT_EQ(g.findShortestPath("X", "A"), -1);
    EXPECT_EQ(g.findShortestPath("X", "Y"), -1);

    std::cout << "Test Passed: Shortest paths calculated correctly." << std::endl << std::endl;
}

TEST_F(GraphTest, Task5_FindShortestPath_MultiplePaths) {
    createTestFile(testPopFile, {"A:1", "B:1", "C:1", "D:1", "E:1"});
    createTestFile(testRoadFile, {"A:B", "B:C", "A:D", "D:C", "C:E"}); // Path A-B-C-E (len 3), Path A-D-C-E (len 3), Path A-B-C (len 2), Path A-D-C (len 2)

    g.loadData(testPopFile, testRoadFile);

    EXPECT_EQ(g.findShortestPath("A", "E"), 3); // BFS should find shortest
    EXPECT_EQ(g.findShortestPath("A", "C"), 2); // via A-B-C or A-D-C
    EXPECT_EQ(g.findShortestPath("B", "D"), 2); // via B-A-D or B-C-D
    std::cout << "Test Passed: Finds shortest path among multiple options." << std::endl << std::endl;
}

TEST_F(GraphTest, Task5_FindShortestPath_EmptyGraph) {
    createTestFile(testPopFile, {});
    createTestFile(testRoadFile, {});
    g.loadData(testPopFile, testRoadFile);
    EXPECT_EQ(g.findShortestPath("A", "B"), -1);
    std::cout << "Test Passed: Handles empty graph correctly." << std::endl << std::endl;
}
