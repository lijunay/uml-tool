#include "scope.h"
#include "type.h"
#include "class.h"
#include "templateclass.h"
#include "union.h"
#include "enum.h"
#include "enums.h"
#include "extendedtype.h"
#include "constants.cpp"

#include <utility>

#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>

#include <utility/helpfunctions.h>

namespace entity {

    Scope::Scope(Scope &&src)
    {
        moveFrom(src);
    }

    Scope::Scope(const Scope &src)
    {
        copyFrom(src);
    }

    Scope::Scope(const QString &scopeName, const QString &scopeId)
        : m_Name(!scopeName.isEmpty() ? scopeName : DEFAULT_NAME)
        , m_Id(utility::genId())
        , m_ParentScopeId(!scopeId.isEmpty() ? scopeId : GLOBAL_SCOPE_ID)
    {
    }

    Scope &Scope::operator =(Scope rhs)
    {
        moveFrom(rhs);
        return *this;
    }

    Scope &Scope::operator =(Scope &&rhs)
    {
        if (this != &rhs)
            moveFrom(rhs);

        return *this;
    }

    bool operator ==(const Scope &lhs, const Scope &rhs)
    {
        return lhs.m_Name          == rhs.m_Name                       &&
               lhs.m_Id            == rhs.m_Id                         &&
               lhs.m_ParentScopeId == rhs.m_ParentScopeId              &&
               utility::seqSharedPointerEq(lhs.m_Scopes, rhs.m_Scopes) &&
               utility::seqSharedPointerEq(lhs.m_Types, rhs.m_Types);
    }

    QString Scope::name() const
    {
        return m_Name;
    }

    void Scope::setName(const QString &name)
    {
        m_Name = name;
    }

    SharedType Scope::getType(const QString &typeId) const
    {
        return (m_Types.contains(typeId) ? m_Types[typeId] : nullptr);
    }

    SharedType Scope::takeType(const QString &typeId)
    {
        SharedType result(nullptr);

        if (m_Types.contains(typeId)) {
            result = m_Types[typeId];
            m_Types.remove(typeId);
        }

        return result;
    }

    void Scope::addClonedType(const SharedType &type)
    {
        SharedType newType(std::make_shared<Type>(*type));
        newType->setScopeId(m_Id);
        newType->setId(utility::genId());
        m_Types.insert(newType->id(), newType);
    }

    bool Scope::containsType(const QString &typeId) const
    {
        return m_Types.contains(typeId);
    }

    void Scope::removeType(const QString &typeId)
    {
        m_Types.remove(typeId);
    }

    TypesList Scope::types() const
    {
        return m_Types.values();
    }

    SharedScope Scope::getChildScope(const QString &typeId)
    {
        return (m_Scopes.contains(typeId) ? m_Scopes[typeId] : nullptr);
    }

    SharedScope Scope::takeChildScope(const QString &typeId)
    {
        SharedScope result(nullptr);

        if (m_Scopes.contains(typeId)) {
            result = m_Scopes[typeId];
            m_Scopes.remove(typeId);
        }

        return result;
    }

    SharedScope Scope::addChildScope(const QString &name)
    {
        SharedScope scope = std::make_shared<Scope>(name, m_Id);
        m_Scopes.insert(scope->id(), scope);
        return scope;
    }

    bool Scope::containsChildScope(const QString &typeId)
    {
        return m_Scopes.contains(typeId);
    }

    bool Scope::hasChildScopes() const
    {
        return !m_Scopes.isEmpty();
    }

    void Scope::removeChildScope(const QString &typeId)
    {
        m_Scopes.remove(typeId);
    }

    ScopesList Scope::scopes() const
    {
        return m_Scopes.values();
    }

    QString Scope::id() const
    {
        return m_Id;
    }

    void Scope::setId(const QString &id)
    {
        m_Id = id;
    }

    QString Scope::parentScopeId() const
    {
        return m_ParentScopeId;
    }

    void Scope::setParentScopeId(const QString &parentScopeId)
    {
        m_ParentScopeId = parentScopeId;
    }

    QJsonObject Scope::toJson() const
    {
        QJsonObject result;

        result.insert("Name", m_Name);
        result.insert("ID", m_Id);
        result.insert("Parent ID", m_ParentScopeId);

        QJsonArray scopes;
        for (auto &&scope : m_Scopes.values()) scopes.append(scope->toJson());
        result.insert("Scopes", scopes);

        QJsonArray types;
        for (auto &&type : m_Types.values()) types.append(type->toJson());
        result.insert("Types", types);

        return result;
    }

    void Scope::fromJson(const QJsonObject &src, QStringList &errorList)
    {
        utility::checkAndSet(src, "Name", errorList, [&src, this](){ m_Name = src["Name"].toString(); });
        utility::checkAndSet(src, "ID", errorList, [&src, this](){ m_Id = src["ID"].toString(); });
        utility::checkAndSet(src, "Parent ID", errorList, [&src, this](){ m_ParentScopeId = src["Parent ID"].toString(); });

        m_Scopes.clear();
        utility::checkAndSet(src, "Scopes", errorList, [&src, &errorList, this](){
            if (src["Scopes"].isArray()) {
                SharedScope scope;
                for (auto &&val : src["Scopes"].toArray()) {
                    scope = std::make_shared<Scope>();
                    scope->fromJson(val.toObject(), errorList);
                    m_Scopes.insert(scope->id(), scope);
                }
            } else {
                errorList << "Error: \"Scopes\" is not array";
            }
        });

        m_Types.clear();
        utility::checkAndSet(src, "Types", errorList, [&src, &errorList, this](){
            if (src["Types"].isArray()) {
                SharedType type;
                QJsonObject obj;
                for (auto &&val : src["Types"].toArray()) {
                    obj = val.toObject();
                    utility::checkAndSet(obj, "Kind of type", errorList,
                                         [&obj, &type, &errorList, this](){
                        type = utility::makeType(static_cast<UserType>(obj["Kind of type"].toInt()));
                        type->fromJson(obj, errorList);
                        m_Types.insert(type->id(), type);
                    });
                }
            } else {
                errorList << "Error: \"Types\" is not array";
            }
        });
    }

    void Scope::writeToFile(const QString &fileName) const
    {
         utility::writeToFile(*this, fileName);
    }

    bool Scope::readFromFile(const QString &fileName)
    {
        return utility::readFromFile(*this, fileName);
    }

    void Scope::copyFrom(const Scope &src)
    {
        m_Name = src.m_Name;
        m_Id   = src.m_Id;
        m_ParentScopeId = src.m_ParentScopeId;

        utility::deepCopySharedPointerHash(src.m_Scopes, m_Scopes, &Scope::id);
        utility::deepCopySharedPointerHash(src.m_Types,  m_Types, &Type::id);
    }

    void Scope::moveFrom(Scope &src)
    {
        m_Name = std::move(src.m_Name);
        m_Id   = std::move(src.m_Id);
        m_ParentScopeId = std::move(src.m_ParentScopeId);

        m_Scopes = std::move(src.m_Scopes);
        m_Types  = std::move(src.m_Types );
    }

} // namespace entity
