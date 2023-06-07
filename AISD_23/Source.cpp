#include <cstdio>
#include <iostream>
#include <conio.h>
#include <vector>
template<typename Vertex, typename Distance = double>
class Graph {
public:
    struct edge {
        Vertex name_e;
        Distance dist;
        edge(Vertex a, Distance d) : name_e(a), dist(d) {}
    };

    struct vertex {
        std::vector<edge> edges;
        Vertex name_v;
    };

    //��������-����������-�������� ������
    bool has_vertex(const Vertex& v) const;
    void add_vertex(const Vertex& v);
    bool remove_vertex(const Vertex& v);
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
    std::vector<edge> vertex;
};
