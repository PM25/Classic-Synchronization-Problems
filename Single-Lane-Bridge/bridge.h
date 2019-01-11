#ifndef BRIDGE_H
#define BRIDGE_H


class Bridge
{
public:
    Bridge(int len);
    ~Bridge();
    int getLength() const;
    bool move2Map(int from, int to);



private:
    int length;
    bool *map;
};

#endif // BRIDGE_H
