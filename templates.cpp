#include <QString>

namespace {

    const QString INDENT = "    ";
    const QString ENUM_TEMPLATE = "enum %class%%name%%type% {%values%};";
    const QString EXT_TYPE_TEMPLATE = "%const%%name%%pl%%template_params%";
    const QString FIELD_TEMPLATE = "%keywords%%type%%name%";
    const QString METHOD_TEMPLATE = "%lhs_k%%r_type%%name%(%parameters%)%rhs_k%%const%";
    const QString UNION_TEMPLATE = "union %name% {%variables%};";
    const QString CLASS_TEMPLATE = "%kind%%parents%{%public%%protected%%private%};";

}
