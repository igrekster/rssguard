// For license of this file, see <project-root-folder>/LICENSE.md.

#ifndef MESSAGE_H
#define MESSAGE_H

#include "definitions/definitions.h"

#include <QDataStream>
#include <QDateTime>
#include <QSqlRecord>
#include <QStringList>

class QSqlDatabase;
class Label;

// Represents single enclosure.
struct RSSGUARD_DLLSPEC Enclosure {
  public:
    explicit Enclosure(QString url = QString(), QString mime = QString());

    QString m_url;
    QString m_mimeType;
};

// Represents single enclosure.
class RSSGUARD_DLLSPEC Enclosures {
  public:
    static QList<Enclosure> decodeEnclosuresFromString(const QString& enclosures_data);
    static QString encodeEnclosuresToString(const QList<Enclosure>& enclosures);
};

// Represents single message.
class RSSGUARD_DLLSPEC Message {
  public:
    explicit Message();

    void sanitize();

    // Creates Message from given record, which contains
    // row from query SELECT * FROM Messages WHERE ....;
    static Message fromSqlRecord(const QSqlRecord& record, bool* result = nullptr);
    static QString generateRawAtomContents(const Message& msg);

  public:
    QString m_title;
    QString m_url;
    QString m_author;
    QString m_contents;
    QString m_rawContents;

    // This should be preferably in UTC and should be converted
    // to localtime when needed.
    QDateTime m_created;
    QString m_feedId;
    int m_accountId;
    int m_id;
    QString m_customId;
    QString m_customHash;
    bool m_isRead;
    bool m_isImportant;
    bool m_isDeleted;
    double m_score;
    QList<Enclosure> m_enclosures;

    // List of custom IDs of labels assigned to this message.
    QList<Label*> m_assignedLabels;

    // Is true if "created" date was obtained directly
    // from the feed, otherwise is false
    bool m_createdFromFeed = false;
};

inline bool operator==(const Message& lhs, const Message& rhs) {
  return lhs.m_accountId == rhs.m_accountId &&
         ((lhs.m_id > 0 && rhs.m_id > 0 && lhs.m_id == rhs.m_id) ||
          (!lhs.m_customId.isEmpty() && !rhs.m_customId.isEmpty() && lhs.m_customId == rhs.m_customId));
}

inline bool operator!=(const Message& lhs, const Message& rhs) {
  return !(lhs == rhs);
}

// Serialize message state.
// NOTE: This is used for persistent caching of message state changes.
RSSGUARD_DLLSPEC QDataStream& operator<<(QDataStream& out, const Message& my_obj);
RSSGUARD_DLLSPEC QDataStream& operator>>(QDataStream& in, Message& my_obj);

uint qHash(const Message& key, uint seed);
uint qHash(const Message& key);

#endif // MESSAGE_H
