#include<iostream>
#include<vector>

template<typename Vertex, typename Distance = double>
struct edge 
{
    Vertex dest;
    Distance dist;
    edge(Vertex a, Distance d) : dest(a), dist(d) {}
};

template<typename Vertex, typename Distance = double>
struct vertex 
{
    std::vector<edge<Vertex, Distance>> edges;
    Vertex name_e;
    vertex(Vertex n) : name_e(n) {}
};

template<typename Vertex, typename Distance = double>
class Graph 
{
private:
    std::vector<vertex<Vertex, Distance>> graph;

    vertex<Vertex, Distance> find_by_name(const Vertex name) 
    {
        for (int i = 0; i < graph.size(); i++) 
        {
            if (graph[i].src == name) return graph[i];
        }
        return NULL;
    }

public:
    bool has_vertex(const Vertex& v) const 
    {
        for (int i = 0; i < graph.size(); i++) 
        {
            if (graph[i].src == v) return true;
        }
        return false;
    }

    bool add_vertex(const Vertex& v) 
    {
        if (!has_vertex(v)) 
        {
            graph.push_back(vertex(v));
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
                if (graph[i].src == v) graph.erase(i);
                else 
                {
                    for (int j = 0; j < graph[i].edges.size(); j++) 
                    {
                        if (graph[i].edges[j].dest == v) graph[i].edges.erase(j);
                    }
                }
            }
            return true;
        }
        return false;
    }

    std::vector<Vertex> vertices() const 
    {
        std::vector<Vertex> res;
        for (int i = 0; i < graph.size(); i++) 
        {
            res.push_back(graph[i].src);
        }
        return res;
    }

    bool has_edge(const Vertex src, const Vertex dest) const 
    {
        vertex a = find_by_name(src);
        if (a && has_vertex(dest)) 
        {
            for (int i = 0; i < a.edges.size(); i++) 
            {
                if (a.edges[i].dest == dest) return true;
            }
        }
        return false;
    }

    bool has_edge(const Vertex src, const edge<Vertex, Distance> e) { //c учетом расстояния в edge
        vertex a = find_by_name(src);
        if (a && has_vertex(e.dest)) 
        {
            for (int i = 0; i < a.edges.size(); i++) 
            {
                if ((a.edges[i].dest == e.dest) && a.edges[i].dist == e.dist) return true;
            }
        }
        return false;
    }

    void add_edge(const Vertex src, const Vertex dest, const Distance& d) 
    {

    }
    bool remove_edge(const Vertex from, const Vertex to);
    bool remove_edge(const edge<Vertex, Distance> e); //c учетом расстояния


};

int main() 
{
    vertex<char> k('a');
    k.edges.push_back(edge<char, double>('b', 15));
    return 0;
}