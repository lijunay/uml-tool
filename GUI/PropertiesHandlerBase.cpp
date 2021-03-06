/*****************************************************************************
**
** Copyright (C) 2017 Fanaskov Vitaly (vt4a2h@gmail.com)
**
** Created 24.
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
#include "PropertiesHandlerBase.hpp"

#include <QLayout>
#include <QSpacerItem>
#include <QHash>

#include <Entity/Type.h>
#include <Entity/GraphicEntityData.h>

#include "Section.h"
#include "QtHelpers.h"

namespace GUI {

    /**
     * @brief PropertiesHandlerBase::PropertiesHandlerBase
     * @param sectionsLayout
     */
    PropertiesHandlerBase::PropertiesHandlerBase(QLayout &sectionsLayout)
        : m_MainLayout(sectionsLayout)
    {
    }

    /**
     * @brief PropertiesHandlerBase::layout
     * @return
     */
    QLayout &PropertiesHandlerBase::layout()
    {
        return m_MainLayout;
    }

    /**
     * @brief PropertiesHandlerBase::section
     * @return
     */
    PropertiesHandlerBase::SectionPtr PropertiesHandlerBase::currentSection()
    {
        if (auto e = entity(); e) {
            auto sectionIt = m_SectionsByType.find(e->kindOfType());
            if (sectionIt != std::end(m_SectionsByType))
                return *sectionIt;

            if (auto data = e->displayData())
                return addSection(data.value().sectionName, data.value().description, e->kindOfType());
        }

        return nullptr;
    }

    /**
     * @brief PropertiesHandlerBase::addSection
     * @param name
     * @param description
     * @param model
     * @return
     */
    PropertiesHandlerBase::SectionPtr PropertiesHandlerBase::addSection(
        const QString &name, const QString &description, Entity::KindOfType type)
    {
        if (auto it = m_SectionsByType.find(type); it != std::end(m_SectionsByType))
            return *it;

        auto newSectionIt = m_SectionsByType.insert(type, new Section(name, description));

        layout().addWidget(newSectionIt->data());

        return *newSectionIt;
    }

    /**
     * @brief PropertiesHandlerBase::entity
     * @return
     */
    Entity::SharedType PropertiesHandlerBase::entity() const
    {
        return m_Entity;
    }

    /**
     * @brief PropertiesHandlerBase::activate
     * @return
     */
    bool PropertiesHandlerBase::activate()
    {
        if (!entity() || !currentSection())
            return false;

        currentSection()->setVisible(true);
        currentSection()->updateText(m_Entity->toString());
        m_SaveConnection =
            G_CONNECT(currentSection(), &Section::saved,
                      [this](auto &&text)
                      {
                          if (!m_Entity)
                              return;

                          // FIXME: add memento command
                          bool modified = !m_Entity->fromString(text);
                          currentSection()->setModified(modified);

                          auto itemRect = m_Entity->graphicEntityData()->boundingRect();
                          emit sceneUpdateRequired(itemRect);
                      });

        return true;
    }

    /**
     * @brief PropertiesHandlerBase::deactivate
     * @return
     */
    bool PropertiesHandlerBase::deactivate()
    {
        if (currentSection())
            currentSection()->setVisible(false);

        disconnect(m_SaveConnection);

        m_Entity = nullptr;

        return true;
    }

    /**
     * @brief PropertiesHandlerBase::setEntity
     */
    void PropertiesHandlerBase::setEntity(const Entity::SharedType &entity)
    {
        deactivate();

        m_Entity = entity;

        activate();
    }

    /**
     * @brief PropertiesHandlerBase::isSaved
     * @return
     */
    bool PropertiesHandlerBase::isSaved() const
    {
        return true;
    }

    /**
     * @brief PropertiesHandlerBase::save
     */
    void PropertiesHandlerBase::save()
    {

    }

} // namespace GUI
