/*****************************************************************************
**
** Copyright (C) 2015 Fanaskov Vitaly (vt4a2h@gmail.com)
**
** Created 07/02/2015.
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

#include "entity_types.hpp"

namespace entity {

    /// The IComponents class
    class IComponents
    {
    public:
        virtual ~IComponents();

        void addExists(const SharedMethod &method, int pos);
        int remove(const SharedMethod &method);
        MethodsList components() const;

        virtual SharedMethod addNewMethod();
        virtual void addExistsMethod(const SharedMethod &method, int pos);
        virtual int removeMethod(const SharedMethod &method);
        virtual MethodsList methods() const;

        virtual SharedField addNewFiled();
        virtual void addExistsFiled(const SharedField &field, int pos);
        virtual int removeField(const SharedField &field);
        virtual FieldsList fields() const;

        virtual SharedElement addNewElement();
        virtual void addExistsElement(const SharedElement &element, int pos);
        virtual int removeElement(const SharedElement &element);
        virtual ElementsList elements() const;

        virtual SharedProperty addNewProperty();
        virtual void addExistsProperty(const SharedProperty &property, int pos);
        virtual int removeProperty(const SharedProperty &property);
        virtual PropertiesList properties() const;
    };

} // end of namespace entity
