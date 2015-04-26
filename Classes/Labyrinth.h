#pragma once
#include <vector>
#include <list>
#include <map>

std::vector<std::vector<std::map<std::pair<int, int>, bool> > > getGraph();

std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > getEdgeGraph();

std::vector< std::vector< char > > charGraph();

