/*****************************************************************************
**
** Copyright (C) 2017 Fanaskov Vitaly (vt4a2h@gmail.com)
**
** Created 28.
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

#include <functional>

#include <QAbstractItemModel>
#include <QDateTime>
#include <QPixmap>

#include "IMessenger.h"

namespace Models {

    /**
     * @brief The MessagesModel class
     */
    class MessagesModel : public QAbstractTableModel, public IMessenger
    {
        Q_OBJECT

    public: // Types
        using ViewStatusFunc = std::function<bool()>;

    public:
        explicit MessagesModel(QObject * parent = nullptr);
        void markAllMessagesRead();

        void setViewStatusFunction(ViewStatusFunc f);

    public: // IMessenger overrides
        Messages messages() const override;
        uint unreadMessagesCount() const override;
        void clear() override;
        void addMessage(const MessageException &e) override;

    public: // QAbstractItemModel overrides
        int rowCount(const QModelIndex &parent) const override;
        int columnCount(const QModelIndex &parent) const override;
        QVariant data(const QModelIndex &index, int role) const override;

    public slots: // IMessenger overrides
        void addMessage(MessageType type, const QString &summary,
                        const QString &description = QString()) override;

    signals:
        void newMessageAdded(); // Extend if needed

    private: // Methods
        QVariant processDisplayRole(const QModelIndex &index) const;
        QVariant processDecorationRole(const QModelIndex &index) const;
        QVariant processTextAligmentRole(const QModelIndex &index) const;
        QVariant processBackgroundRole(const QModelIndex &index) const;

    private: // Types
        enum class ColumnType : int
        {
            Text,
            Date,
            EnumSize, // Keep last
        };

    private slots:
        void resetInternalData();

    private: // Data
        Messages m_Messages;
        uint m_UnreadMessagesCount;

        // Cannot be static, because required qApp created
        QHash<MessageType, QPixmap> m_CachedIcons;

        ViewStatusFunc m_IsViewing;
    };

    inline uint qHash(MessageType t)
    {
        return ::qHash(static_cast<int>(t));
    }

} // namespace Models
