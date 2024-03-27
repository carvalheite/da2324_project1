#ifndef DA2324_PROJECT1_EDGE_H
#define DA2324_PROJECT1_EDGE_H


class Vertex;

class Pipe {
public:
    Pipe(Vertex *orig, Vertex *dest, double c, int type);

    Vertex * getDest() const;
    double getcapacity() const;
    bool isSelected() const;
    Vertex* getOrig() const;
    Pipe *getReverse() const;
    double getFlow() const;

    void setSelected(bool selected);
    void setReverse(Pipe *reverse);
    void setFlow(double flow);
    Pipe* getReverse();

protected:
    Vertex* orig;
    Vertex * dest; // destination vertex
    double capacity; // edge capacity, can also be used for capacity

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Pipe *reverse = nullptr;

    double flow{}; // for flow-related problems
};

#endif //DA2324_PROJECT1_EDGE_H
