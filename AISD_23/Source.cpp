#include <cstdio>
#include <iostream>
#include <conio.h>
#include <vector>
template<typename Vertex, typename Distance = double>
class Graph 
{
public:
    struct edge 
    {
        Vertex dest;
        Distance dist;
        edge(Vertex a, Distance d) : dest(a), dist(d) {}
    };

    struct vertex 
    {
        std::vector<edge> edges;
        Vertex name_v;
        vertex(Vertex v): name_v(v) {}
    };

    //��������-����������-�������� ������
    bool has_vertex(const Vertex& v) const
    {
        for (int i = 9; i < graph.size(); i++)
        {
            if (graph[i].name_v == v) return true;
        }
        return false;
    }
    bool add_vertex(const Vertex& v) {
        if (!has_vertex(v))
        {
            graph.push_back(vertex(v));
            return true;
        }
        else return false;

    }
    bool remove_vertex(const Vertex& v) 
    {
        if (has_vertex(v)) 
        {
            for (int i = 0; i < graph.size(); i++) 
            {
                if (graph[i].name_e == v) graph.erase(i);
                else 
                {
                    for (int j = 0; j < graph[i].edges.size(); j++) 
                    {
                        if (graph[i].edges[j].name_e == v) graph[i].edges.erase(j);
                    }
                }
            }
            return true;
        }
        return false;
    }
    std::vector<Vertex> vertices() const;

    //��������-����������-�������� �����
    void add_edge(const Vertex& from, const Vertex& to,
        const Distance& d);
    bool remove_edge(const Vertex& from, const Vertex& to);
    bool remove_edge(const Edge& e); //c ������ ����������
    bool has_edge(const Vertex& from, const Vertex& to) const;
    bool has_edge(const Edge& e); //c ������ ���������� � Edge

    //��������� ���� �����, ��������� �� �������
    std::vector<Edge> edges(const Vertex& vertex);

    size_t order() const; //�������
    size_t degree() const; //�������

    //����� ����������� ����
    std::vector<Edge> shortest_path(const Vertex& from,
        const Vertex& to) const;
    //�����
    std::vector<Vertex>  walk(const Vertex& start_vertex)const;

private:
    std::vector<edge> graph;
};
