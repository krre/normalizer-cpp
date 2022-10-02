#include "Parameter.h"

namespace Unit {

Parameter::Parameter(Type::Type type, Node* parent) : Unit(parent), m_type(type) {

}

Unit::Kind Parameter::kind() const {
    return Kind::Parameter;
}

Type::Type Parameter::type() const {
    return m_type;
}

void Parameter::setType(const Type::Type& type) {
    m_type = type;
}

QJsonObject Parameter::toJsonUnit() const {
    QJsonObject result;
    result["name"] = name();
    result["type"] = m_type.name();

    return result;
}

QByteArray Parameter::toBinaryUnit() const {

}

void Parameter::fromBinaryUnit(const QByteArray& binary) {

}

}
