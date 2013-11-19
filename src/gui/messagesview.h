#ifndef MESSAGESVIEW_H
#define MESSAGESVIEW_H

#include <QTreeView>

#include "core/messagesmodel.h"


class MessagesProxyModel;

class MessagesView : public QTreeView {
    Q_OBJECT

  public:
    // Constructors and destructors.
    explicit MessagesView(QWidget *parent = 0);
    virtual ~MessagesView();

    void setSortingEnabled(bool enable);

    // Model accessors.
    MessagesProxyModel *model();
    MessagesModel *sourceModel();

  protected:
    void setupAppearance();

    void keyPressEvent(QKeyEvent *event);

    void currentChanged(const QModelIndex &current,
                        const QModelIndex &previous);

    void selectionChanged(const QItemSelection &selected,
                          const QItemSelection &deselected);

  signals:
    // TODO: dodělat signál.
    void currentMessageChanged(const Message &message);
    void currentMessageRemoved();

  private:
    MessagesProxyModel *m_proxyModel;
    MessagesModel *m_sourceModel;
};

#endif // MESSAGESVIEW_H
