#include "bridge.h"
#include <QDebug>

Bridge::Bridge(int len)
{
    length = len + 1;
    map = new bool[len];
    for(int pos(0); pos < length; ++pos) {
        map[pos] = false;
    }
}

Bridge::~Bridge()
{
    delete map;
}

int
Bridge::getLength() const
{
    return length;
}

bool
Bridge::move2Map(int from, int to)
{
    if(from < 0 || from >= length || to < 0 || from >= length) {
        return false;
    } else if(to == -1) {
        map[from] = false;
        return true;
    } else if(map[to] == true) {
        return false;
    } else {
        if(from != -1) map[from] = false;
        map[to] == true;
        return true;
    }
}
