#include <cstdio>
#include <iostream>
#include <conio.h>
#include <vector>
#include<algorithm>
template<typename Vertex, typename Distance = double>
struct edge 
{
    Vertex dest;
    Distance dist;
    edge(Vertex a, Distance d) : dest(a), dist(d) {}
    bool operator==(edge e) 
    {
        if ((this->dest == e.dest) && (this->dist == e.dist)) 
        {
            return true;
        }
        return false;
    }
};

template<typename Vertex, typename Distance = double>
struct vertex 
{
    std::vector<edge<Vertex, Distance>> edges;
    Vertex name_v;
    vertex(Vertex n) : name_v(n) {}
};

template<typename Vertex, typename Distance = double>
class Graph 
{
private:
    std::vector<vertex<Vertex, Distance>> graph;

    int index_by_name(const Vertex name) 
    {
        for (int i = 0; i < graph.size(); i++) 
        {
            if (graph[i].name_v == name) return i;
        }
        return -1;
    }

public:
    bool has_vertex(const Vertex& v) const 
    {
        for (int i = 0; i < graph.size(); i++) 
        {
            if (graph[i].name_v == v) return true;
        }
        return false;
    }

    bool add_vertex(const Vertex& v) 
    {
        if (!has_vertex(v)) 
        {
            graph.push_back(vertex<Vertex, Distance>(v));
            return true;
        }
        return false;
    }

    bool remove_vertex(const Vertex& v) 
    {
        if (has_vertex(v)) 
        {
            for (int i = 0; i < graph.size(); i++) 
            {
                if (graph[i].name_v == v) graph.erase(graph.begin() + i);
                else 
                {
                    for (int j = 0; j < graph[i].edges.size(); j++) 
                    {
                        if (graph[i].edges[j].dest == v) graph[i].edges.erase(graph[i].edges.begin() + j);
                    }
                }
            }
            return true;
        }
        return false;
    }

    std::vector<Vertex> vertices() 
    {
        std::vector<Vertex> res;
        for (int i = 0; i < graph.size(); i++) 
        {
            res.push_back(graph[i].name_v);
        }
        return res;
    }

    bool has_edge(const Vertex v, const Vertex dest) 
    {
        if (!has_vertex(v) || !has_vertex(dest)) return false;
        for (int i = 0; i < graph[index_by_name(v)].edges.size(); i++)
        {
            if (graph[index_by_name(v)].edges[i].dest == dest) return true;
        }
        return false;
    }

    bool has_edge(const Vertex v, const edge<Vertex, Distance> e) //c учетом расстояния в edge
    {
        if (!has_vertex(v) || !has_vertex(e.dest)) return false;
        for (int i = 0; i < graph[index_by_name(v)].edges.size(); i++)
        {
            if (graph[index_by_name(v)].edges[i] == e) return true;
        }
        return false;
        return false;
    }

    bool add_edge(const Vertex v, const Vertex dest, const Distance& dist)
    {
        if (!has_edge(v, dest)) 
        {
            graph[index_by_name(v)].edges.push_back(edge<Vertex, Distance>(dest, dist));
            return true;
        }
        return false;
    }

    bool remove_edge(const Vertex name_v, const Vertex dest)
    {
        if (has_edge(name_v, dest)) {
            for (int i = 0; i < graph[index_by_name(name_v)].edges.size(); i++) 
            {
                if (graph[index_by_name(name_v)].edges[i].dest == dest) graph[index_by_name(name_v)].edges.erase(graph[index_by_name(name_v)].edges.begin() + i);
                return true;
            }
        }
        return false;
    }

    bool remove_edge(const Vertex name_v, const edge<Vertex, Distance> e) //c учетом расстояния
    {
        if (has_edge(name_v, e))
        {
            for (int i = 0; i < graph[index_by_name(name_v)].edges.size(); i++)
            {
                if (graph[index_by_name(name_v)].edges[i] == e) graph[index_by_name(name_v)].edges.erase(graph[index_by_name(name_v)].edges.begin() + i);
                return true;
            }
        }
        return false;
    }

    std::vector<edge<Vertex, Distance>> edges(const Vertex name_v)
    {
        std::vector<edge<Vertex, Distance>> res;
        if (has_vertex(name_v)) {
            for (int i = 0; i < graph[index_by_name(name_v)].edges.size(); i++) {
                res.push_back(graph[index_by_name(name_v)].edges[i]);
            }
        }
        return res;
    }

    size_t order() const
    {
        return graph.size();
    }

    size_t degree()
    {
        std::vector<int> count(graph.size(), 0);
        for (int i = 0; i < graph.size(); i++) 
        {
            for (int j = 0; j < graph[i].edges.size(); j++) 
            {
                count[i]++;
                count[index_by_name(graph[i].edges[j].dest)]++;
            }
        }

        int max = 0;
        if (count.size() > 0) max = count[0];
        else return 0;
        for (int i = 1; i < count.size(); i++) {
            if (max < count[i]) max = count[i];
        }

        return max;
    }
    
    void print() const
    {
        for (int i = 0; i < graph.size(); i++)
        {
            std::cout << "[" << graph[i].name_v << "]";
            for (int j = 0; j < graph[i].edges.size(); j++)
            {
                std::cout << "-("<< graph[i].edges[j].dist <<")->[" << graph[i].edges[j].dest << "]";
            }
            std::cout << "\n";
        }
    }

    std::vector<Vertex>  walk(const Vertex& start_vertex)
    {
        if (!has_vertex(start_vertex)) throw "Error";
        std::vector<Vertex> queue;
        std::vector<Vertex> path;
        std::vector<bool> labels(graph.size(), false);
        queue.push_back(start_vertex);
        while (queue.size() > 0)
        {
            Vertex p = queue[0];
            labels[index_by_name(p)] = true;
            for (int i = 0; i < graph[index_by_name(p)].edges.size(); i++)
            {
                if (!labels[index_by_name(graph[index_by_name(p)].edges[i].dest)])
                {
                    queue.push_back(graph[index_by_name(p)].edges[i].dest);
                    labels[index_by_name(graph[index_by_name(p)].edges[i].dest)] = true;
                }
            }
            path.push_back(p);
            queue.erase(queue.begin() + 0);
            if (queue.size() == 0)
            {
                for (int i = 0; i < graph.size(); i++)
                {
                    if (labels[i] == false)
                    {
                        queue.push_back(graph[i].name_v);
                        labels[i] == true;
                        break;
                    }
                }
            }
        }
        return path;
    }

};


int main() 
{
    Graph<int, int> g;
    for (int i = 1; i < 9; i++)
    {
        g.add_vertex(i);
    }
    g.add_edge(1, 2, 10);
    g.add_edge(1, 4, 10);
    g.add_edge(1, 6, 10);
    g.add_edge(1, 8, 10);
    g.add_edge(2, 1, 10);
    g.add_edge(2, 4, 10);
    g.add_edge(3, 5, 10);
    g.add_edge(3, 6, 10);
    g.add_edge(4, 7, 10);
    g.add_edge(5, 1, 10);
    g.add_edge(5, 3, 10);
    g.add_edge(5, 8, 10);
    g.add_edge(6, 5, 10);
    g.add_edge(7, 2, 10);
    g.add_edge(7, 8, 10);
    g.add_edge(8, 1, 10);
    g.print();
    std::vector<int> a = g.walk(1);

    for (int i = 0; i < a.size(); i++)
    {
        std::cout << a[i] << " ";
    }
}