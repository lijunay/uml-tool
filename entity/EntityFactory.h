/*****************************************************************************
**
** Copyright (C) 2015 Fanaskov Vitaly (vt4a2h@gmail.com)
**
** Created 13/03/2015.
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

#include <common/ElementsFactory.h>

#include "entity_types.hpp"

#include <entity/type.h>

#include <gui/graphics/entity.h>

#include <models/models_types.hpp>


class QGraphicsScene;

namespace entity {

    /// The EntitiesFactory class
    class EntityFactory : public common::ElementsFactory
    {
    public:
        EntityFactory(const EntityFactory &) = delete;
        EntityFactory(EntityFactory &&) = delete;
        EntityFactory& operator =(const EntityFactory&) = delete;
        EntityFactory& operator =(EntityFactory&&) = delete;

        static const EntityFactory &instance();

        SharedType make(KindOfType type, const common::ID &scopeID) const;


//        template<class Type>
//        std::pair<std::shared_ptr<Type>, graphics::Entity*>
//        makeEntity(const models::SharedApplicationModel &model, const common::ID  &scopeID,
//                   QGraphicsScene &scene, const QPointF &pos) const
//        {
//            auto type = model->makeType<Type>(scopeID, Type::staticDefaultName());
//            graphics::Entity * entity = newEntity(scene, pos, type);

//            auto &&currentProject = model->currentProject();
//            connectEntity(entity, currentProject.get(), type.get());
//            currentProject->touch();

//            return {type, entity};
//        }


//        graphics::Entity *addEntity(QGraphicsScene &scene, const project::SharedProject &project,
//                                    const entity::SharedType &type, const QPointF &pos) const;

        models::WeakTreeModel treeModel() const;
        void setTreeModel(const models::WeakTreeModel &treeModel);

    private:
        explicit EntityFactory(QObject * parent = nullptr);

        models::WeakTreeModel m_TreeModel;
//        graphics::Entity *newEntity(QGraphicsScene &scene, const QPointF &pos,
//                                    const entity::SharedType &type = nullptr) const;

//        void connectEntity(graphics::Entity *entity, project::Project *currentProject,
//                           common::BasicElement *type) const;
    };

} // namespace entity
