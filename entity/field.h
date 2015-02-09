/*****************************************************************************
**
** Copyright (C) 2014 Fanaskov Vitaly (vt4a2h@gmail.com)
**
** Created 29/10/2014.
**
** This file is part of Q-UML (UML tool for Qt).
**
** Q-UML is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Q-UML is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.

** You should have received a copy of the GNU Lesser General Public License
** along with Q-UML.  If not, see <http://www.gnu.org/licenses/>.
**
*****************************************************************************/

#pragma once

#include <QString>

#include "basicentity.h"

#include "types.h"

class QJsonObject;
class QStringList;

namespace entity {

    enum Section : int;
    enum FieldKeyword : int;

    /**
     * @brief The Field class
     */
    class Field : public BasicEntity
    {
    public:
        Field();
        Field(const Field &src);
        Field(Field &&src);
        Field(const QString &name, const QString &typeId);
        Field(const QString &name, const QString &typeId, const QString &prefix, Section section);

        Field &operator =(Field &&rhs);
        Field &operator =(Field rhs);
        friend bool operator== (const Field &lhs, const Field &rhs);

        QString name() const;
        QString fullName() const;
        void setName(const QString &name);

        Section section() const;
        void setSection(Section section);

        QString prefix() const;
        void removePrefix();
        void setPrefix(const QString &prefix);

        FieldKeywordsList keywords() const;
        void addKeyword(FieldKeyword keyword);
        bool containsKeyword(FieldKeyword keyword) const;
        bool hasKeywords() const;
        void removeKeyword(FieldKeyword keyword);

        QString typeId() const;
        void setTypeId(const QString &typeId);

        QString suffix() const;
        void removeSuffix();
        void setSuffix(const QString &suffix);

        QString defaultValue() const;
        void setDefaultValue(const QString &defaultValue);

    public: // BasicEntity implementation
        QJsonObject toJson() const override;
        void fromJson(const QJsonObject &src, QStringList &errorList) override;

    private:
        void copyFrom(const Field &src);
        void moveFrom(Field &src);

        QString m_TypeId;
        Section m_Section;
        QString m_Name;
        QString m_Prefix;
        QString m_Suffix;
        QString m_DefaultValue;

        FieldKeywords m_Keywords;
    };

} // namespace entity
