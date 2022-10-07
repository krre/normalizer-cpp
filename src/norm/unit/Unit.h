#pragma once
#include "project/Node.h"

namespace Unit {

class Unit : public Node {
public:
    enum class Kind {
        Project,
        Module,
        Interface,
        Function,
        Flow,
        Parameter,
        Expression,
        Condition,
        Loop,
        Operator,
        Constant,
        Variable,
        Structure,
        Field,
        Custom
    };

    Unit(Node* parent = nullptr);

    virtual Kind kind() const = 0;

    QString comment() const;
    void setComment(const QString& comment);

private:
    QString m_comment;
};

}
