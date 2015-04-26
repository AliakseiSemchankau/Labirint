#include "Labyrinth.h"
#include "Constants.h"
#include <fstream>
#include <string>
#include <map>
#include <vector>

std::vector<std::vector<std::map<std::pair<int, int>, bool> > > getGraph() {

	std::ifstream in("labirint.txt");
	std::string s;
	int n, m;
	in >> n >> m;
	std::vector<std::vector<std::map<std::pair<int, int>, bool> > > graph(n / 2 + 2, std::vector<std::map<std::pair<int, int>, bool> >(m / 2 + 2, MOVES_MAP));
	std::vector<std::vector<char> > curGraph(n + 2, std::vector<char>(m + 2, '#'));

	for (int i = 1; i <= n; ++i) {
		in >> s;
		for (int j = 1; j <= m; ++j)
			curGraph[i][j] = s[j - 1];
	}

	for (int i = 1; i <= n / 2; ++i){
		for (int j = 1; j <= m / 2; ++j) {
			for (int k = 0; k < MOVES.size(); ++k) {
				int x = MOVES[k].first;
				int y = MOVES[k].second;
				int toI = i + x;
				int toJ = j + y;
				int oldI = 2 * i;
				int oldJ = 2 * j;
				int oldToI = 2 * toI;
				int oldToJ = 2 * toJ;
				if (curGraph[(oldI + oldToI) / 2][(oldJ + oldToJ) / 2] == '#') {
					graph[i][j][MOVES[k]] = false;
				}
			}
		}
	}

	return graph;

}

std::vector< std::pair< std::pair<int,int>, std::pair<int, int> > > getEdgeGraph() {

	std::ifstream in("labirint.txt");
	std::string s;
	int n, m;
	in >> n >> m;
	
	std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > graph;
	std::vector<std::vector<char> > curGraph(m + 2, std::vector<char>(n + 2, '#'));
	for (int i = 1; i <= n; ++i) {
		in >> s;
		for (int j = 1; j <= m; ++j)
			curGraph[j][i] = s[j - 1];
	}

	for (int i = 0; i < m + 2; ++i) {

		for (int j = 0; j < n + 2; ++j)
			if (j < n + 1 - j)
				std::swap(curGraph[i][j], curGraph[i][n + 1 - j]);
	}

	for (int i = 0; i <= m / 2 ; ++i){
		for (int j = 1; j <= n / 2 + 1; ++j) {
			for (int k = 1; k <= 2; ++k) {
				int x = MOVES[k].first;
				int y = MOVES[k].second;
				int toI = i + x;
				int toJ = j + y;
				int oldI = 2 * i;
				int oldJ = 2 * j;
				int oldToI = 2 * toI;
				int oldToJ = 2 * toJ;
				if (curGraph[(oldI + oldToI) / 2][(oldJ + oldToJ) / 2] == '#') {
					if (!(i == 0 && x == 0) && !(j == n / 2 + 1 && j + y == n / 2 + 1))
					graph.push_back(std::make_pair(std::make_pair(i, j), std::make_pair(i + x, j + y)));
				}
			}
		}
	}

	std::ofstream of("output.txt");

	for (int i = 0; i < graph.size(); ++i)
		of << graph[i].first.first << " " << graph[i].first.second << " - " << graph[i].second.first << " " << graph[i].second.second << "\n";

	return graph;

}

std::vector<std::vector< char > > charGraph() {

	std::ifstream in("labirint.txt");

	int n, m;
	in >> n >> m;
	std::vector<std::vector<char> > labirint(m, std::vector<char>(n));

	std::vector<std::string> charLab(n);

	for (int i = 0; i < n; ++i)
		in >> charLab[i];

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			labirint[j][n - 1 - i] = charLab[i][j];

	return labirint;

}