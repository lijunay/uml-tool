/*****************************************************************************
**
** Copyright (C) 2014 Fanaskov Vitaly (vt4a2h@gmail.com)
**
** Created 03/11/2014.
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

#include <QMetaType>

namespace entity {

    /// The Section enum
    enum Section  : int {
        Public,   ///< Public
        Private,  ///< Private
        Protected ///< Protected
    };

    /// The Kind enum
    enum Kind     : int {
        ClassType, ///< ClassType
        StructType ///< StructType
    };

    /// The UserType enum
    enum UserType : int {
        BasicType,          ///< BasicType
        UserClassType,      ///< UserClassType
        TemplateClassType,  ///< TemplateClassType
        UnionType,          ///< UnionType
        EnumType,           ///< EnumType
        ExtendedTypeType,    ///< ExtendedTypeType
        Count
    };

    /// The RhsIdentificator enum
    enum RhsIdentificator : int {
        None,       ///< None
        Override,   ///< Override
        Final,      ///< Final
        Delete,     ///< Delete
        Default,    ///< Default
        PureVirtual ///< PureVirtual
    };

    /// The LhsIdentificator enum
    enum LhsIdentificator : int {
        Explicit,     ///< Explicit
        Inline,       ///< Inline
        MethodStatic, ///< MethodStatic
        Virtual,      ///< Virtual
        Friend        ///< Friend
    };

    /// The FieldKeyword enum
    enum FieldKeyword     : int {
        Volatile,   ///< Volatile
        Mutable,    ///< Mutable
        FieldStatic ///< FieldStatic
    };

    /// The ClassMethodType enum
    enum ClassMethodType  : int {
        SimpleMethod,   ///< SimpleMethod
        TemplateMethod  ///< TemplateMethod
    };
}

namespace relationship {

    /// The Multiplicity enum
    enum Multiplicity : int {
        NotSpecified, ///< NotSpecified
        ZeroOrOne,    ///< ZeroOrOne
        One,          ///< One
        ZeroOrInf,    ///< ZeroOrInf
        OneOrInf,     ///< OneOrInf
        Inf           ///< Inf
    };

    /// The RelationType enum
    enum RelationType : int {
        SimpleRelation,         ///< SimpleRelation
        AssociationRelation,    ///< AssociationRelation
        DependencyRelation,     ///< DependencyRelation
        GeneralizationRelation, ///< GeneralizationRelation
        RealizationRelation,    ///< RealizationRelation
        CompositionRelation,    ///< CompositionRelation
        AggregationRelation,    ///< AggregationRelation
        MultiRelation           ///< MultiRelation
    };
}

Q_DECLARE_METATYPE(entity::UserType)
