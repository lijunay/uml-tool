#include "enum.h"
#include "constants.cpp"
#include "helpfunctions.h"
#include "enums.h"

#include <algorithm>
#include <utility>

#include <QJsonObject>
#include <QStringList>
#include <QJsonArray>

namespace entity {

    Enum::Enum()
        : Enum(DEFAULT_NAME, GLOBAL_SCOPE_ID)
    {
    }

    Enum::Enum(Enum &&src)
    {
       moveFrom(src);
    }

    Enum::Enum(const Enum &src)
        : Type(src)
        , m_EnumTypeId(src.m_EnumTypeId)
        , m_StrongStatus(src.m_StrongStatus)
        , m_Variables(src.m_Variables)
    {
    }

    Enum::Enum(const QString &name, const QString &scopeId)
        : Type(name, scopeId)
        , m_EnumTypeId(STUB_ID)
        , m_StrongStatus(false)
    {
       m_KindOfType = EnumType;
    }

    Enum &Enum::operator =(Enum &&rhs)
    {
       moveFrom(rhs);
       return *this;
    }

    Enum &Enum::operator =(Enum rhs)
    {
       moveFrom(rhs);
       return *this;
    }

    bool Enum::isStrong() const
    {
        return m_StrongStatus;
    }

    void Enum::setStrongStatus(bool status)
    {
        m_StrongStatus = status;
    }

    Enum::Variable &Enum::addVariable(const QString &name)
    {
        m_Variables.append(std::make_pair(name, m_Variables.size()));
        return m_Variables.last();
    }

    Enum::Variable Enum::getVariable(const QString &name) const
    {
        auto it = std::find_if(m_Variables.cbegin(), m_Variables.cend(),
                               [&name](const Variable &v){ return v.first == name; });
        return (it != m_Variables.end() ? *it : std::make_pair(DEFAULT_NAME, -1));
    }

    void Enum::removeVariable(const QString &name)
    {
        auto it = std::find_if(m_Variables.begin(), m_Variables.end(),
                               [&name](Variable &v){ return v.first == name; });
        if (it != m_Variables.end()) m_Variables.erase(it);
    }

    bool Enum::containsVariable(const QString &name)
    {
        return (std::find_if(m_Variables.begin(), m_Variables.end(),
                            [&name](Variable &v){ return v.first == name; }) !=
                m_Variables.end());
    }

    Enum::VariablesList Enum::variables() const
    {
        return m_Variables;
    }

    QString Enum::enumTypeId() const
    {
        return m_EnumTypeId;
    }

    void Enum::setEnumTypeId(const QString &enumTypeId)
    {
        m_EnumTypeId = enumTypeId;
    }

    QJsonObject Enum::toJson() const
    {
        QJsonObject result(Type::toJson());

        result.insert("Enum type id", m_EnumTypeId);
        result.insert("Strong status", m_StrongStatus);

        QJsonArray variables;
        QJsonObject variable;
        for (auto &&v : m_Variables) {
            variable.insert("Name", v.first);
            variable.insert("Number", v.second);
            variables.append(variable);
        }
        result.insert("Variables", variables);

        return result;
    }

    void Enum::fromJson(const QJsonObject &src, QStringList &errorList)
    {
        Type::fromJson(src, errorList);

        utility::checkAndSet(src, "Enum type id",  errorList, [&src, this](){ m_EnumTypeId   = src["Enum type id"].toString(); });
        utility::checkAndSet(src, "Strong status", errorList, [&src, this](){ m_StrongStatus = src["Strong status"].toBool();  });

        m_Variables.clear();
        utility::checkAndSet(src, "Variables", errorList, [&src, &errorList, this](){
            if (src["Variables"].isArray()) {
                QJsonObject obj;
                Variable var;
                for (auto &&value : src["Variables"].toArray()) {
                    obj = value.toObject();
                    utility::checkAndSet(obj, "Name",   errorList, [&obj, &var, this](){ var.first  = obj["Name"].toString(); });
                    utility::checkAndSet(obj, "Number", errorList, [&obj, &var, this](){ var.second = obj["Number"].toInt();  });
                    m_Variables.append(var);
                  }
            } else {
                errorList << "Error: \"Varibles\" is not array";
            }
        });
    }

    void Enum::moveFrom(Enum &src)
    {
        Type::moveFrom(src);

        m_EnumTypeId = std::move(src.m_EnumTypeId);
        m_StrongStatus = std::move(src.m_StrongStatus);
        m_Variables = std::move(src.m_Variables);
    }

} // namespace entity
