#pragma once
#include "Node.h"

class Root : public Node {
public:
    Root();
    QJsonValue serializeToJson() const;
};
