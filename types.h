#pragma once

#include <QHash>
#include <QSet>
#include <QStringList>
#include <QMultiHash>
#include <memory>

namespace entity {
    class Field;
    using SharedField = std::shared_ptr<Field>;
    using Fields      = QHash<QString, SharedField>;
    using FieldsList  = QList<SharedField>;

    enum FieldKeyword : int;
    using FieldKeywords     = QSet<FieldKeyword>;
    using FieldKeywordsList = QList<FieldKeyword>;

    class ClassMethod;
    using SharedMethod = std::shared_ptr<ClassMethod>;
    using Methods      = QMultiHash<QString, SharedMethod>;
    using MethodsList  = QList<SharedMethod>;

    enum  LhsIdentificator : int;
    using LhsIdentificators     = QSet<LhsIdentificator>;
    using LhsIdentificatorsList = QList<LhsIdentificator>;

    class Type;
    using SharedType = std::shared_ptr<Type>;
    using Types      = QHash<QString, SharedType>;
    using TypesList  = QList<SharedType>;

    class Class;
    using SharedClass = std::shared_ptr<Class>;
    using Classes     = QHash<QString, SharedClass>;
    using ClassesList = QList<SharedClass>;

    class Union;
    using SharedUnion = std::shared_ptr<Union>;
    using Unions      = QHash<QString, SharedUnion>;
    using UnionsList  = QList<SharedUnion>;

    class Enum;
    using SharedEnum = std::shared_ptr<Enum>;
    using Enums      = QHash<QString, SharedEnum>;
    using EnumsList  = QList<SharedEnum>;

    enum Section : int;
    using Parent      = std::pair<QString, Section>;
    using Parents     = QHash<QString, Parent>; // id : {id, section}
    using ParentsList = QList<Parent>;

    class ExtendedType;
    using TemplateParameter      = std::pair<QString, QString>; // (typename, default type id)
    using TemplateParameters     = QHash<QString, TemplateParameter>;
    using TemplateParametersList = QList<TemplateParameter>;
    using SharedExtendedType     = std::shared_ptr<ExtendedType>;
    using ExtendedTypes          = QHash<QString, SharedExtendedType>;
    using ExtendedTypesList      = QList<SharedExtendedType>;
    using ExtendedTypesIdList    = QStringList;

    class Scope;
    using SharedScope = std::shared_ptr<Scope>;
    using Scopes      = QHash<QString, SharedScope>;
    using ScopesList  = QList<SharedScope>;
}
