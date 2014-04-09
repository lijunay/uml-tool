#pragma once

#include "types.h"
#include <QString>

namespace relationship {

    enum RelationType : int;

    class Relation
    {
    public:
        Relation();
        Relation(const QString &tailTypeId, const QString &headTypeId);
        virtual ~Relation();

        QString description() const;
        void setDescription(const QString &description);

        virtual void make();
        virtual void clear();

        // TODO: add method for get/set global database
        // TODO: add method for get/set project database

        RelationType relationType() const;
        void setRelationType(const RelationType &relationType);

    protected:
        SharedNode m_TailNode;
        SharedNode m_HeadNode;

        entity::SharedClass m_HeadClass;
        entity::SharedClass m_TailClass;

        QString m_Description;
        RelationType m_RelationType;

        // TODO: add varibles for global and local db
    };

} // namespace relationship
