/*****************************************************************************
**
** Copyright (C) 2016 Fanaskov Vitaly (vt4a2h@gmail.com)
**
** Created 11/03/2016.
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

#include <memory>
#include <optional>

#include <QMetaType>

namespace Common {

    class BasicElement;
    // TODO: rename
    using SharedBasicEntity = std::shared_ptr<BasicElement>;

    class Memento;
    using UniqueMemento = std::unique_ptr<Memento>;

    using OptErrLst = std::optional<QStringList>;

    class IOriginator;
    using SharedOriginator = std::shared_ptr<IOriginator>;

} // common

Q_DECLARE_METATYPE(Common::SharedBasicEntity)
