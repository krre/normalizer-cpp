#include "Parameter.h"

namespace Norm {

Parameter::Parameter() {

}

Type* Parameter::type() const {
    return m_type;
}

void Parameter::setType(Type* type) {
    m_type = type;
}

}
