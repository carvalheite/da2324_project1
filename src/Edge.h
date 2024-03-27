#ifndef DA2324_PROJECT1_EDGE_H
#define DA2324_PROJECT1_EDGE_H


class Vertex;

class Pipe {
public:
    Pipe(Vertex *orig, Vertex *dest, double c, int type): dest(dest),capacity(c),type(type) {}

    Vertex * getDest() const;
    double getcapacity() const;
    bool isSelected() const;
    Vertex* getOrig() const;
    Pipe *getReverse() const;
    double getFlow() const;

    void setSelected(bool selected);
    void setReverse(Pipe *reverse);
    void setFlow(double flow);
protected:
    Vertex * dest; // destination vertex
    double capacity; // edge capacity, can also be used for capacity
    int type;

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex *orig;
    Pipe *reverse = nullptr;

    double flow; // for flow-related problems
};

#endif //DA2324_PROJECT1_EDGE_H
