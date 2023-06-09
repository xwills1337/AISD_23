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
    edge(Vertex a = 0, Distance d = 0) : dest(a), dist(d) {}
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
    vertex(Vertex n = 0) : name_v(n) {}
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

    Graph() {}

    Graph(std::vector < vertex<Vertex, Distance>>& Ver)
    {
        for (int i = 0; i < Ver.size(); i++)
        {
            if (!has_vertex(Ver[i].name_v))
            {
                for (int j = 0; j < Ver[i].edges.size(); j++)
                {
                    if (has_vertex(Ver[i].name_v, Ver[i].edges[j].dest)) throw "Error";
                }
                graph.push_back(Ver[i].name_v);
            }
            else throw "Error";
        }
    }

    Graph& operator = (const Graph& p)
    {
        graph.clear();
        for (int i = 0; i < p.graph.size(); i++)
        {
            graph.push_back(p.graph[i]);
        }
        return *this;
    }

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

    void add_edge(const Vertex v, const Vertex dest, const Distance& dist)
    {
        if (v == dest) throw "Error! Can't create a loop";
        if (dist == 0) throw "Error! Distance can't be 0";
        if (!has_edge(v, dest))
        {
            graph[index_by_name(v)].edges.push_back(edge<Vertex, Distance>(dest, dist));
        }
        else throw "Error! An edge with such vertices already exists";
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
            if (graph[i].edges.size() == 0) std::cout << "[" << graph[i].name_v << "]";
            else
            {
                for (int j = 0; j < graph[i].edges.size(); j++)
                {
                    std::cout << "[" << graph[i].name_v << "]";
                    std::cout << "-(" << graph[i].edges[j].dist << ")->[" << graph[i].edges[j].dest << "]  ";
                }
            }
            std::cout << "\n\n";
        }
    }

    Vertex vertex_name(const int i)
    {
        if (i >= 0 && i < graph.size()) return graph[i].name_v;
        else throw "Error";
    }

    std::vector<Vertex> shortest_path(const Vertex& from, const Vertex& to)
    {
        std::vector<Distance> paths(graph.size(), INT_MAX);
        std::vector<bool> labels(graph.size(), false);

        paths[index_by_name(from)] = 0;
        labels[index_by_name(from)] = true;
        Vertex p = from;
        for (int i = 0; i < graph.size() - 1; i++)
        {
            for (int j = 0; j < graph[index_by_name(p)].edges.size(); j++)
            {
                if (!labels[graph[index_by_name(p)].edges[j].dest])
                {
                    if (paths[index_by_name(p)] + graph[index_by_name(p)].edges[j].dist < paths[index_by_name(graph[index_by_name(p)].edges[j].dest)])
                        paths[index_by_name(graph[index_by_name(p)].edges[j].dest)] = paths[index_by_name(p)] + graph[index_by_name(p)].edges[j].dist;
                }
            }
            Distance min = INT_MIN;
            for (int d = 0; d < graph.size(); d++)
            {
                if ((labels[index_by_name(graph[d].name_v)] == false) && (min > paths[d]))
                {
                    min = paths[d];
                    p = graph[d].name_v;
                }
            }
            labels[index_by_name(p)] = true;

            std::vector<Vertex> short_path;
            short_path.push_back(to);
            int q = index_by_name(to);
            for (int x = 0; x < paths.size(); x++)
            {
                for (int i = 0; i < paths.size(); i++)
                {
                    if (i != q)
                    {
                        for (int j = 0; j < graph[i].edges.size(); j++)
                        {
                            if (index_by_name(graph[i].edges[j].dest) == q)
                            {
                                if (paths[i] + graph[i].edges[j].dist == paths[q])
                                {
                                    short_path.push_back(graph[i].name_v);
                                    q = i;
                                }
                                break;
                            }
                        }
                    }
                    if (q == index_by_name(from))
                    {
                        for (int z = 0; z < short_path.size() / 2; z++)
                        {
                            Vertex k = short_path[z];
                            short_path[z] = short_path[short_path.size() - 1 - z];
                            short_path[short_path.size() - 1 - z] = k;
                        }
                        return short_path;
                    }
                }
            }
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

bool test_int(char* b)
{
    if (*b == '-') b++;
    if (*b == 0) return false;
    if (*b == '0' && *(b + 1) != 0) return false;
    while (*b)
    {
        if (*b < '0' || *b>'9') return false;
        b++;
    }
    return true;
}
bool test_unsigned_int(char* b)
{
    if (*b == 0 || *b == '0') return false;
    while (*b)
    {
        if (*b < '0' || *b>'9') return false;
        b++;
    }
    return true;
}
bool test_double(char* b)
{
    if (*b == '-') b++;
    if (*b == 0 || *b == '.') return false;
    if (*b == '0' && (*(b + 1) != 0 && *(b + 1) != '.')) return false;
    while (*b != 0 && *b != '.')
    {
        if (*b < '0' || *b > '9') return false;
        b++;
    }
    if (*b == '.')
    {
        b++;
        if (*b == 0) return false;
        while (*b)
        {
            if (*b < '0' || *b > '9') return false;
            b++;
        }
    }
    return true;
}

bool test_char(char* b)
{
    if (*b == 0) return false;
    if (*(b + 1) != 0) return false;
    return true;

}

template <class Type>
Type scan()
{
    bool i = false;
    while (true)
    {
        char* str = new char[256];
        std::cin.getline(str, 256);
        if (typeid(Type) == typeid(int)) i = test_int(str);
        if (typeid(Type) == typeid(unsigned int)) i = test_unsigned_int(str);
        if (typeid(Type) == typeid(double) || typeid(Type) == typeid(float)) i = test_double(str);
        if (typeid(Type) == typeid(char)) i = test_char(str);
        if (i)
        {
            Type x = 0;
            if (typeid(Type) == typeid(int) || typeid(Type) == typeid(unsigned int)) x = atoi(str);
            if (typeid(Type) == typeid(double) || typeid(Type) == typeid(float)) x = atof(str);
            if (typeid(Type) == typeid(char)) x = str[0];
            delete[] str;
            return x;
        }
        else puts("Wrong data");
        delete[]str;
    }
}





template<typename Vertex, typename Distance = double>
Vertex task(const Graph<Vertex, Distance>& g)
{
    int z = INT_MAX;
    Vertex min = -1;
    for (int i = 0; i < g.size(); i++)
    {
        Distance count = 0;
        for (int j = 0; j < g.size(); j++)
        {
            count += g.shortest_path(i, j);
        }
        count = count / (g.size() - 1);
        if (count < z)
        {
            z = count;
            min = g.vertex_name(i);
        }
    }
    return min;
}

template<typename V, typename D = double>
void menu()
{
    Graph<V, D> g;
    while (true)
    {
        system("cls");
        g.print();
        std::cout << "1 - create graph\n";
        std::cout << "2 - add vertex\n";
        std::cout << "3 - remove vertex\n";
        std::cout << "4 - add edge\n";
        std::cout << "5 - remove edge\n";
        std::cout << "6 - get order and degree\n";
        std::cout << "7 - walk\n";
        std::cout << "8 - shortest_path\n";
        std::cout << "9 - task\n";
        std::cout << "esc - exit\n";
        int z = getch();
        system("cls");
        if (z == '1')
        {
            Graph<V, D> y;
            std::cout << "Enter number of vertices: ";
            int count = scan<unsigned int>();
            std::cout << "Enter vertex names\n";
            for (int i = 0; i < count; i++)
            {
                std::cout << "V[" << i << "] = ";
                while (true)
                {
                    V a = scan<V>();
                    if (!y.has_vertex(a))
                    {
                        y.add_vertex(a);
                        break;
                    }
                    else std::cout << "Such vertex already exists. Enter a different vertex name\n";
                }
            }

            std::cout << "Enter number of edges (no more than the square of the number of vertices): ";
            int count_2 = scan<unsigned int>();
            while (true)
            {
                if (count_2 <= count * count) break;
                else
                {
                    std::cout << "Error! Wrong data\n";
                    count_2 = scan<unsigned int>();
                }
            }
            std::cout << "Enter edges\n";
            for (int i = 0; i < count_2; i++)
            {
                V start, end;
                D Dis;
                std::cout << "E[" << i << "]\n";
                while (true)
                {
                    std::cout << "V start = ";
                    V start = scan<V>();
                    std::cout << "V end = ";
                    V end = scan<V>();
                    std::cout << "Distance = ";
                    D Dis = scan<D>();
                    if (y.has_vertex(start) && y.has_vertex(end) && (start != end) && !y.has_edge(start, end))
                    {
                        y.add_edge(start, end, Dis);
                        break;
                    }
                    else std::cout << "Error! Wrong data\n";
                }
            }
            g = y;
        }

        if (z == '2')
        {
            std::cout << "Enter vertex name\n";
            V a = scan<V>();
            if (!g.has_vertex(a)) g.add_vertex(a);
            else
            {
                std::cout << "Error! This vertex is already in the graph\n";
                if (getch()) z = '0';
            }
        }
        if (z == '3')
        {
            std::cout << "Enter vertex name\n";
            V a = scan<V>();
            if (g.has_vertex(a)) g.remove_vertex(a);
            else
            {
                std::cout << "Error! This vertex is not in the graph\n";
                if (getch()) z = '0';
            }
        }
        if (z == '4')
        {
            std::cout << "Enter vertex start\n";
            V start = scan<V>();
            std::cout << "Enter vertex end\n";
            V end = scan<V>();
            std::cout << "Enter distance\n";
            D dis = scan<D>();

            try
            {
                g.add_edge(start, end, dis);
            }
            catch (const char* msg)
            {
                std::cout << msg << std::endl;
                if (getch()) z = '0';
            }
        }
        if (z == '5')
        {
            std::cout << "Enter vertex start\n";
            V start = scan<V>();
            std::cout << "Enter vertex end\n";
            V end = scan<V>();
            if (g.has_edge(start, end)) g.remove_edge(start, end);
            else
            {
                std::cout << "Error! This edge is not in the graph\n";
                if (getch()) z = '0';
            }
        }
        if (z == '6')
        {
            std::cout << "Order: " << g.order()<<"\n";
            std::cout << "Degree: " << g.degree()<<"\n";
            if (getch()) z = '0';
        }
        if (z == '7')
        {
            std::cout << "Enter vertex start name\n";
            V start = scan<V>();
            if (g.has_vertex(start))
            {
                std::cout << "Bypass in width\n";
                std::vector<V> a = g.walk(start);
                for (int i = 0; i < a.size(); i++) std::cout << a[i] << " ";
                std::cout << "\n";
            }
            else std::cout << "Error! This vertex is not in the graph\n";
            if (getch()) z = '0';
        }
        if (z == '8')
        {
            std::cout << "Enter vertex start\n";
            V start = scan<V>();
            std::cout << "Enter vertex end\n";
            V end = scan<V>();
            if (g.has_vertex(start) && g.has_vertex(end))
            {
                std::cout << "Shortest path\n";
                std::vector<V> a = g.shortest_path(start, end);
                for (int i = 0; i < a.size(); i++) std::cout << a[i] << " ";
                std::cout << "\n";
            }
            else std::cout << "Error! This vertex(s) is not in the graph\n";
            if (getch()) z = '0';
        }
        if (z == 27) break;
    }
}

int main() 
{
    std::cout << "Select the data type for the vertices\n1 - int\n2 - double\n3 - char\n";
    int l = '0';
    while (l != '1' && l != '2' && l != '3')
    {
        l = getch();
    }
    system("cls");
    std::cout << "Select the data type for the distance\n1 - int\n2 - double\n";
    int n = '0';
    while (n != '1' && n != '2')
    {
        n = getch();
    }
    if (l == '1' && n == '1') menu<int, int>();
    if (l == '2' && n == '1') menu<double, int>();
    if (l == '3' && n == '1') menu<char, int>();
    if (l == '1' && n == '2') menu<int, double>();
    if (l == '2' && n == '2') menu<double, double>();
    if (l == '3' && n == '2') menu<char, double>();
}