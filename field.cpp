#include "field.h"
#include "extendedtype.h"
#include "enums.h"
#include "constants.cpp"
#include "helpfunctions.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>

namespace entity {

    Field::Field()
        : Field(DEFAULT_NAME, STUB_ID)
    {
    }

    Field::Field(const QString &name, const QString &typeId)
        : m_TypeId(typeId)
        , m_Section(Public)
        , m_Name(name)
        , m_Prefix("m_")
    {
    }

    QString Field::name() const
    {
        return m_Name;
    }

    void Field::setName(const QString &name)
    {
        m_Name = name;
    }

    Section Field::section() const
    {
        return m_Section;
    }

    void Field::setSection(Section section)
    {
        m_Section = section;
    }

    QString Field::prefix() const
    {
        return m_Prefix;
    }
    
    void Field::setPrefix(const QString &prefix)
    {
        m_Prefix = prefix;
    }

    FieldKeywordsList Field::keywords() const
    {
        return m_Keywords.values();
    }

    void Field::addKeyword(FieldKeyword keyword)
    {
        m_Keywords << keyword;
    }

    bool Field::containsKeyword(FieldKeyword keyword) const
    {
        return m_Keywords.contains(keyword);
    }

    bool Field::hasKeywords() const
    {
        return m_Keywords.isEmpty();
    }

    void Field::removeKeyword(FieldKeyword keyword)
    {
        m_Keywords.remove(keyword);
    }

    QString Field::typeId() const
    {
        return m_TypeId;
    }

    void Field::setTypeId(const QString &typeId)
    {
        m_TypeId = typeId;
    }

    QJsonObject Field::toJson() const
    {
        QJsonObject result;

        result.insert("Type ID", m_TypeId);
        result.insert("Section", m_Section);
        result.insert("Name", m_Name);
        result.insert("Prefix", m_Prefix);

        QJsonArray keywords;
        for (auto keyword : m_Keywords) keywords.append(keyword);
        result.insert("Keywords", keywords);

        return result;
    }

    void Field::fromJson(const QJsonObject &src, QStringList &errorList)
    {
        utility::checkAndSet(src, "Type ID", errorList, [&src, this](){ m_TypeId = src["Type ID"].toString(); });
        utility::checkAndSet(src, "Section", errorList, [&src, this](){ m_Section = static_cast<Section>(src["Section"].toInt()); });
        utility::checkAndSet(src, "Name", errorList, [&src, this](){ m_Name = src["Name"].toString(); });
        utility::checkAndSet(src, "Prefix", errorList, [&src, this](){ m_Prefix = src["Prefix"].toString(); });

        m_Keywords.clear();
        utility::checkAndSet(src, "Keywords", errorList, [&src, &errorList, this](){
            if (src["Keywords"].isArray()) {
                for (auto value : src["Keywords"].toArray()) m_Keywords.insert(static_cast<FieldKeyword>(value.toInt()));
            } else {
                errorList << "Error: \"Keywords\" is not array";
            }
        });
    }

} // namespace entity
