#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
 
std::vector<std::pair<std::pair<int, int>, int>> algorithm_Kruskal(std::vector <std::pair<int, std::pair<int, int>>> graph, int n) {
    std::vector<std::pair<std::pair<int, int>, int>> result; // в данном векторе храним ребра минимального остова, где 2 числа каждое ребра - это его концевые вершины.
    std::vector<int> tree_id(n + 1); //для удобства, чтобы последняя вершина была n-ой.
    
    int sum = 0; // храним сумму остовного дерева.
    for (int i = 0; i < n + 1; i++)
        tree_id[i] = i;
 
    for (int i = 0; i < graph.size(); i++) {
        int a = graph[i].second.first;
        int b = graph[i].second.second;
        int weight = graph[i].first;
        if (tree_id[a] != tree_id[b]) {
            sum += weight;
            result.push_back({ {a, b} , sum });
            int old_id = tree_id[b]; 
            int new_id = tree_id[a];
            for (int j = 0; j < n + 1; j++) {
                if (tree_id[j] == old_id)
                    tree_id[j] = new_id;
            }
        }
    }
    return result;
}
 
int main() {
    const std::string path = "input.txt";
    const std::string outpath = "output.txt";
    std::ifstream fin;
    fin.open(path);
    int n = 0   ;
    fin >> n;
    std::string numb = " ";
    std::vector<std::pair<int, std::pair<int, int>>> graph;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> numb;
            if (i < j && numb != "~" && std::stoi(numb) > 0)
                graph.push_back({ std::stoi(numb), {i + 1, j + 1} });
        }
    }
    fin.close();
    
    std::sort(graph.begin(), graph.end());
    std::vector<std::pair<std::pair<int, int>, int>> result = algorithm_Kruskal(graph, n);
 
    std::ofstream fout;
    fout.open(outpath);
 
    fout << result[result.size() - 1].second << "\n";
    for (auto res : result)
        fout << res.first.first << " " << res.first.second << "\n";
 
    fout.close();
    return 0;
}

