/*****************************************************************************
**
** Copyright (C) 2015 Fanaskov Vitaly (vt4a2h@gmail.com)
**
** Created 09/03/2015.
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

#include <QGraphicsObject>

#include <entity/entity_types.hpp>

#include <project/project_types.hpp>

#include "common.h"

namespace gui
{
    class EditEntityDialog;
}

/// namespace graphics
namespace graphics {

    /// The Entity class
    class Entity : public QGraphicsObject
    {
        Q_OBJECT
    public:
        Entity(const entity::SharedType &type, const entity::SharedScope &scope,
               const project::SharedProject &project, QGraphicsItem *parent = nullptr);
        ~Entity();

        QRectF boundingRect() const override;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget = nullptr);

        enum { Type = UserType + int(ElementType::Entity) };
        int type() const override;

        entity::SharedType typeObject() const;
        void setTypeObject(const entity::SharedType &type);

        entity::SharedScope scope() const;
        void setScope(const entity::SharedScope &scope);

        project::SharedProject project() const;
        void setProject(const project::SharedProject &project);

        void setSelectedToConnect(bool status);
        bool selectedToConnect() const;

    signals:
        void moved(const QPointF &from, const QPointF &to);

    private:
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
        void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;

        QPolygonF resizeCorner() const;
        QRectF resizeCornerRect() const;

        void drawHeader(QPainter * painter);
        void drawFrame(QPainter * painter);
        void drawResizeCorner(QPainter * painter);
        void drawSections(QPainter * painter);
        void drawConnectFrame(QPainter * painter);

        entity::SharedType m_Type;
        QPointF m_LastPos;
        bool m_ResizeMode;
        bool m_selectedToConnect;

        qreal m_Width;
        qreal m_Height;
        qreal m_HeaderHeight;

        entity::SharedScope m_Scope;
        project::SharedProject m_Project;
    };

} // grpahics
