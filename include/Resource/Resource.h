#pragma once
#include <map>
#include <string>
#include <memory>

using namespace std;


class GraphFactory {
	map<string, int> pool;

	int CreateGraph(const char*);

public:
	int GetGraph(const char*);
};
extern GraphFactory* graFac;