#include<iostream>
#include<vector>
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

    vertex<Vertex, Distance> find_by_name(const Vertex name) 
    {
        for (int i = 0; i < graph.size(); i++) 
        {
            if (graph[i].name_v == name) return graph[i];
        }
        return NULL;
    }

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

    std::vector<Vertex> vertices() const 
    {
        std::vector<Vertex> res;
        for (int i = 0; i < graph.size(); i++) 
        {
            res.push_back(graph[i].name_v);
        }
        return res;
    }

    bool has_edge(const Vertex v, const Vertex dest) const 
    {
        vertex a = find_by_name(v);
        if (a && has_vertex(dest)) 
        {
            for (int i = 0; i < a.edges.size(); i++) 
            {
                if (a.edges[i].dest == dest) return true;
            }
        }
        return false;
    }

    bool has_edge(const Vertex v, const edge<Vertex, Distance> e) { //c учетом расстояния в edge
        vertex a = find_by_name(v);
        if (a && has_vertex(e.dest)) 
        {
            for (int i = 0; i < a.edges.size(); i++) 
            {
                if (a.edges[i] == e) return true;
            }
        }
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
        return find_by_name(name_v).edges;
    }

    size_t order() const
    {
        return graph.size();
    }

    size_t degree() const
    {
        std::vector<int> count(graph.size(), 0);
        for (int i = 0; i < graph.size(); i++) 
        {
            for (int j = 0; i < graph[i].edges.size(); j++) 
            {
                count[i]++;
                count[index_by_name(graph[i].edges.dest)]++;
            }
        }
        return std::max_element(count.begin(), count.end());
    }
    
    void print() const
    {
        for (int i = 0; i < graph.size(); i++)
        {
            std::cout << "[" << graph[i].name_v << "]";
            for (int j = 0; j < graph[i].edges.size(); j++)
            {
                std::cout << "<-[" << graph[i].edges[j].dest << "]";
            }
            std::cout << "\n";
        }
    }

    std::vector<Vertex>  walk(const Vertex& start_vertex) const
    {
        if (!has_vertex(start_vertex)) throw "Error";
        std::vector<Vertex> queue;
        std::vector<Vertex> path;
        std::vector<bool> labels(graph.size(), false);
        queue.push_back(start_vertex);
        labels[index_by_name(start_vertex)] = true;
        while (queue.size() > 0)
        {
            Vertex p = queue[0];
            vertex<Vertex, Distance> tmp = find_by_name(p);
            for (int i = 0; i < tmp.edges.size(); i++)
            {
                if (!labels[index_by_name(tmp.edges[i].dest)])
                {
                    queue.push_back(tmp.edges[i].dest);
                    labels[index_by_name(tmp.edges[i].dest)] = true;
                }
            }
            path.push_back(p);
            queue.erase(queue.begin() + index_by_name[p]);
            if (queue.size() > 0)
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

    std::vector<Vertex>  walk_2(const Vertex& p, std::vector<bool>&labels) const
    {
        std::vector<Vertex> path;
        vertex<Vertex, Distance> tmp = find_by_name(p);
        path.push_back(p);
        labels[index_by_name(p)] = true;
        for (int i = 0; i < tmp.edges.size(); i++)
        {
            if (!labels[index_by_name(tmp.edges[i].dest)])
            {
                std::vector<Vertex> path_2 = walk_2(tmp.edges[i].dest, labels);
                for (int j = 0; j < path_2.size(); j++)
                {
                    path.push_back(path_2[j]);
                }
            }
        }
        return path;
    }
    std::vector<Vertex>  walk1(const Vertex& start_vertex) const
    {
        if (!has_vertex(start_vertex)) throw "Error";
        std::vector<Vertex> path;
        std::vector<bool> labels(graph.size(), false);
        Vertex p = start_vertex;
        while (true)
        {
            std::vector<Vertex> path_2 = walk_2(p, labels);
            for (int j = 0; j < path_2.size(); j++)
            {
                path.push_back(path_2[j]);
            }
            bool f = true;
            for (int i = 0; i < graph.size(); i++)
            {
                if (labels[i] == false)
                {
                    p = graph[i].name_v;
                    f = false;
                    break;
                }
            }
            if (f) break;
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
    if (g.has_vertex(8)) std::cout << "EEEEE";
    g.print();
}