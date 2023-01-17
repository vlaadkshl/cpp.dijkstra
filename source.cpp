#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Vertex
{
	string name;
	vector<int> edges;

	Vertex(string a, vector<int> e) : name(a), edges(e) {}
};

int main()
{
	vector<Vertex> graph =
	{
		{"A", { 0, 14, 0, 0, 0, 0, 10, 0 }},
		{"B", { 0, 0, 0, 0, 0, 0, 11, 0 }},
		{"C", { 17, 0, 0, 8, 0, 12, 0, 0 }},
		{"D", { 15, 7, 0, 0, 31, 6, 0, 24 }},
		{"E", { 0, 0, 0, 0, 0, 34, 16, 19 }},
		{"F", { 11, 0, 0, 0, 0, 0, 8, 0 }},
		{"G", { 0, 0, 0, 0, 0, 0, 0, 0 }},
		{"H", { 0, 0, 0, 0, 19, 0, 17, 0 }}
	};

	vector<bool> is_visited(8, false);
	vector<size_t> tags(8, INT_MAX);
	vector<size_t> result(8, 1);

	size_t start_index;

	cout << "VERTICES:" << endl;
	for (size_t i = 0; i < graph.size(); i++)
	{
		cout << graph[i].name;
		if (i != graph.size() - 1)
			cout << ", ";
	}
	cout << endl << endl;

	bool OK = false;
	string tmp;
	while (!OK)
	{
		tmp.clear();
		cout << "BEGIN: ";
		cin >> tmp;
		for (size_t i = 0; i < graph.size(); i++)
		{
			if (tmp == graph[i].name)
			{
				OK = true;
				start_index = i;
				tags[start_index] = 0;
				result[start_index] = 1;

				break;
			}
		}
		if (!OK) cout << "Wrong name, try again..." << endl;
	}

	if (start_index >= 0)
	{
		OK = false;
		size_t old_index;

		while (!OK)
		{
			is_visited[start_index] = true;
			old_index = start_index;

			for (size_t i = 0; i < graph.size(); i++)
			{
				if (graph[start_index].edges[i] > 0)
				{
					if (tags[start_index] + graph[start_index].edges[i] < tags[i])
					{
						tags[i] = tags[start_index] + graph[start_index].edges[i];
						result[i] = start_index;
					}
				}
			}

			size_t min = INT_MAX;
			for (size_t i = 0; i < tags.size(); i++)
			{
				if (!is_visited[i] && min > tags[i])
				{
					min = tags[i];
					start_index = i;
				}
			}

			bool isOK = true;
			for (size_t i = 0; i < is_visited.size(); i++)
				if (!is_visited[i])
					isOK = false;

			if (isOK || old_index == start_index) OK = true;
		}
	}
	else return 1;

	cout << endl << "RESULT:" << endl;
	for (size_t i = 0; i < graph.size(); i++)
	{
		cout << graph[i].name;
		for (size_t j = result[i]; j != 1; j = result[j])
		{
			cout << " -> " << graph[j].name;

			if (result[j] == 0)
				break;
		}
		cout << endl;
	}

	system("pause");
	return 0;
}
