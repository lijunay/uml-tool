#pragma once

namespace entity {
    enum Section  : int {Public, Private, Protected};
    enum Kind     : int {ClassType, StructType};
    enum UserType : int {BasicType, UserClassType, TemplateClassType, UnionType, EnumType};
    enum Identificator : int {None, Override, Final, Delete, PureVirtual};
}