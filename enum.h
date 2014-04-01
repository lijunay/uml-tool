#pragma once

#include "type.h"
#include <utility>
#include <QHash>

namespace entity {

    class Enum : public Type
    {
    public:
        using Variable  = std::pair<QString, unsigned int>;
        using Variables = QHash<QString, Variable>;
        using VariablesList = QList<Variable>;

        Enum();
        Enum(const QString &name, const QString &scopeId);

        bool isStrong() const;
        void setStrongStatus(bool status);

        Variable &addVariable(const QString &name);
        Variable getVariable(const QString &name) const;
        void removeVariable(const QString &name);
        bool containsVariable(const QString &name);
        VariablesList variables() const;

        QString enumTypeId() const;
        void setEnumTypeId(const QString &enumTypeId);

    private:
        QString m_EnumTypeId;
        bool m_StrongStatus;
        Variables m_Variables;
    };

} // namespace entity
