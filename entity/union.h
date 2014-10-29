#pragma once

#include "type.h"
#include "types.h"

namespace entity {

    class Field;

    /**
     * @brief The Union class
     */
    class Union : public Type
    {
    public:
        Union();
        Union(Union &&src);
        Union(const Union &src);
        Union(const QString &name, const QString &scopeId);

        Union &operator= (Union rhs);
        Union &operator= (Union &&rhs);
        friend bool operator ==(const Union &lhs, const Union &rhs);

        SharedField getField(const QString &name) const;
        SharedField addField(const QString &name, const QString &typeId);
        void removeField(const QString &name);
        bool containsField(const QString &name);

        FieldsList fields() const;

        QJsonObject toJson() const override;
        void fromJson(const QJsonObject &src, QStringList &errorList) override;

        Union *clone() const;

        bool isEqual(const Union &rhs) const;

    private:
        void moveFrom(Union &src);
        void copyFrom(const Union &src);

        FieldsList m_Fields;
    };

} // namespace entity