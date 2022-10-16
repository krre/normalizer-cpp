#pragma once
#include "norm/Token.h"
#include "norm/helper/FunctionId.h"
#include "norm/helper/ExpressionId.h"

namespace Norm {

class Expression : public Token, public Helper::FunctionId, public Helper::ExpressionId {
public:
    Expression();

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;

    void setIndex(quint16 index);
    quint16 index() const;

private:
    quint16 m_index = 0;
};

}
