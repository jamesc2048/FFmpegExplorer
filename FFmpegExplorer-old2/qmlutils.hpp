#pragma once
#ifndef QQMLHELPERS_H
#define QQMLHELPERS_H

#define QML_WRITABLE_PROPERTY(type, name) \
    protected: \
        Q_PROPERTY (type name READ get_##name WRITE set_##name NOTIFY name##Changed) \
    private: \
        type m_##name; \
    public: \
        type get_##name () const { \
            return m_##name ; \
        } \
    public Q_SLOTS: \
        bool set_##name (type name) { \
            bool ret = false; \
            if ((ret = m_##name != name)) { \
                m_##name = name; \
                emit name##Changed (m_##name); \
                emit propertyChanged(#name); \
            } \
            return ret; \
        } \
    Q_SIGNALS: \
        void name##Changed (type name); \
    private:

#include <QObject>


#define QML_READONLY_PROPERTY(type, name) \
    protected: \
        Q_PROPERTY (type name READ get_##name NOTIFY name##Changed) \
    private: \
        type m_##name; \
    public: \
        type get_##name () const { \
            return m_##name ; \
        } \
        bool update_##name (type name) { \
            bool ret = false; \
            if ((ret = m_##name != name)) { \
                m_##name = name; \
                emit name##Changed (m_##name); \
            } \
            return ret; \
        } \
    Q_SIGNALS: \
        void name##Changed (type name); \
    private:

#define QML_CONSTANT_PROPERTY(type, name) \
    protected: \
        Q_PROPERTY (type name READ get_##name CONSTANT) \
    private: \
        type m_##name; \
    public: \
        type get_##name () const { \
            return m_##name ; \
        } \
    private:

#define QML_LIST_PROPERTY(CLASS, NAME, TYPE) \
    public: \
        static int NAME##_count (QQmlListProperty<TYPE> * prop) { \
            CLASS * instance = qobject_cast<CLASS *> (prop->object); \
            return (instance != NULL ? instance->m_##NAME.count () : 0); \
        } \
        static void NAME##_clear (QQmlListProperty<TYPE> * prop) { \
            CLASS * instance = qobject_cast<CLASS *> (prop->object); \
            if (instance != NULL) { \
                instance->m_##NAME.clear (); \
            } \
        } \
        static void NAME##_append (QQmlListProperty<TYPE> * prop, TYPE * obj) { \
            CLASS * instance = qobject_cast<CLASS *> (prop->object); \
            if (instance != NULL && obj != NULL) { \
                instance->m_##NAME.append (obj); \
            } \
        } \
        static TYPE * NAME##_at (QQmlListProperty<TYPE> * prop, int idx) { \
            CLASS * instance = qobject_cast<CLASS *> (prop->object); \
            return (instance != NULL ? instance->m_##NAME.at (idx) : NULL); \
        } \
        QList<TYPE *> get_##NAME##s (void) const { \
            return m_##NAME; \
        } \
    private: \
        QList<TYPE *> m_##NAME;

#define QML_ENUM_CLASS(name, ...) \
    class name : public QObject { \
        Q_GADGET \
    public: \
        enum Type { __VA_ARGS__ }; \
        Q_ENUMS (Type) \
    };

class QmlProperty : public QObject { Q_OBJECT }; // NOTE : to avoid "no suitable class found" MOC note




#include <QObject>
#include <QList>
#include <QAbstractListModel>

#define NO_PARENT QModelIndex ()
#define BASE_ROLE Qt::UserRole
#define EMPTY_STR QStringLiteral ("")
#define EMPTY_BA  QByteArrayLiteral ("")

/*!
    \defgroup QT_QML_MODELS Qt models for QML

    Brings a bunch of nice, ready-to-use, C++ models for usual use-cases in C++/QML apps :
    \li Exposing a list of QObject-derived objects to QML while supporting dynamic changes
    \li Using a simple list of QVariant / QVariantMap just as easy as the plain QML ListModel item
    \li etc...
*/

#ifndef QQMLVARIANTLISTMODEL_P_H
#define QQMLVARIANTLISTMODEL_P_H

#include <QByteArray>
#include <QChar>
#include <QDebug>
#include <QHash>
#include <QList>
#include <QString>
#include <QVariant>
#include <QVector>

class QQmlVariantListModel;

class QQmlVariantListModelPrivate : public QObject {
    Q_OBJECT

public:
    explicit QQmlVariantListModelPrivate (QQmlVariantListModel * parent);

    void updateCounter ();

    int                     m_count;
    QVariantList            m_items;
    QHash<int, QByteArray>  m_roles;
    QQmlVariantListModel  * m_publicObject;
};


#endif // QQMLVARIANTLISTMODEL_P_H


#ifndef QQMLVARIANTLISTMODEL_H
#define QQMLVARIANTLISTMODEL_H

class QQmlVariantListModelPrivate;

class QQmlVariantListModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY (int count READ count NOTIFY countChanged)

public:
    explicit QQmlVariantListModel (QObject * parent);
    virtual ~QQmlVariantListModel ();

public: // QAbstractItemModel interface reimplemented
    virtual int rowCount (const QModelIndex & parent = QModelIndex ()) const;
    virtual bool setData (const QModelIndex & index, const QVariant & value, int role);
    virtual QVariant data (const QModelIndex & index, int role) const;
    virtual QHash<int, QByteArray> roleNames () const;

public slots: // public API
    void clear ();
    int count () const;
    bool isEmpty () const;
    void append (QVariant item);
    void prepend (QVariant item);
    void insert (int idx, QVariant item);
    void appendList (QVariantList itemList);
    void prependList (QVariantList itemList);
    void replace (int pos, QVariant item);
    void insertList (int idx, QVariantList itemList);
    void move (int idx, int pos);
    void remove (int idx);
    QVariant get (int idx) const;
    QVariantList list () const;

signals: // notifiers
    void countChanged (int count);

private:
    QQmlVariantListModelPrivate * m_privateImpl;
};

#endif // QQMLVARIANTLISTMODEL_H





#ifndef QQMLOBJECTLISTMODEL_H
#define QQMLOBJECTLISTMODEL_H

#include <QAbstractListModel>
#include <QByteArray>
#include <QChar>
#include <QDebug>
#include <QHash>
#include <QList>
#include <QMetaMethod>
#include <QMetaObject>
#include <QMetaProperty>
#include <QObject>
#include <QString>
#include <QStringBuilder>
#include <QVariant>
#include <QVector>

template<typename T> QList<T> qListFromVariant (const QVariantList & list) {
    QList<T> ret;
    ret.reserve (list.size ());
    for (QVariantList::const_iterator it = list.constBegin (); it != list.constEnd (); it++) {
        const QVariant & var = (QVariant) (* it);
        ret.append (var.value<T> ());
    }
    return ret;
}

template<typename T> QVariantList qListToVariant (const QList<T> & list) {
    QVariantList ret;
    ret.reserve (list.size ());
    for (typename QList<T>::const_iterator it = list.constBegin (); it != list.constEnd (); it++) {
        const T & val = (T) (* it);
        ret.append (QVariant::fromValue (val));
    }
    return ret;
}

// custom foreach for QList, which uses no copy and check pointer non-null
#define FOREACH_PTR_IN_QLIST(_type_, _var_, _list_) \
    for (typename QList<_type_ *>::const_iterator it = _list_.begin (); it != _list_.end (); it++) \
        for (_type_ * _var_ = (_type_ *) (* it); _var_ != Q_NULLPTR; _var_ = Q_NULLPTR)

class QQmlObjectListModelBase : public QAbstractListModel { // abstract Qt base class
    Q_OBJECT
    Q_PROPERTY (int count READ count NOTIFY countChanged)

public:
    explicit QQmlObjectListModelBase (QObject * parent = Q_NULLPTR) : QAbstractListModel (parent) { }

public slots: // virtual methods API for QML
    virtual int size (void) const = 0;
    virtual int count (void) const = 0;
    virtual bool isEmpty (void) const = 0;
    virtual bool contains (QObject * item) const = 0;
    virtual int indexOf (QObject * item) const = 0;
    virtual int roleForName (const QByteArray & name) const = 0;
    virtual void clear (void) = 0;
    virtual void append (QObject * item) = 0;
    virtual void prepend (QObject * item) = 0;
    virtual void insert (int idx, QObject * item) = 0;
    virtual void move (int idx, int pos) = 0;
    virtual void remove (QObject * item) = 0;
    virtual void remove (int idx) = 0;
    virtual QObject * get (int idx) const = 0;
    virtual QObject * get (const QString & uid) const = 0;
    virtual QObject * getFirst (void) const = 0;
    virtual QObject * getLast (void) const = 0;
    virtual QVariantList toVarArray (void) const = 0;

protected slots: // internal callback
    virtual void onItemPropertyChanged (void) = 0;

signals: // notifier
    void countChanged (void);
};

template<class ItemType> class QQmlObjectListModel : public QQmlObjectListModelBase {
public:
    explicit QQmlObjectListModel (QObject *          parent      = Q_NULLPTR,
                                  const QByteArray & displayRole = QByteArray (),
                                  const QByteArray & uidRole     = QByteArray ())
        : QQmlObjectListModelBase (parent)
        , m_count (0)
        , m_uidRoleName (uidRole)
        , m_dispRoleName (displayRole)
        , m_metaObj (ItemType::staticMetaObject)
    {
        static QSet<QByteArray> roleNamesBlacklist;
        if (roleNamesBlacklist.isEmpty ()) {
            roleNamesBlacklist << QByteArrayLiteral ("id")
                               << QByteArrayLiteral ("index")
                               << QByteArrayLiteral ("class")
                               << QByteArrayLiteral ("model")
                               << QByteArrayLiteral ("modelData");
        }
        static const char * HANDLER = "onItemPropertyChanged()";
        m_handler = metaObject ()->method (metaObject ()->indexOfMethod (HANDLER));
        if (!displayRole.isEmpty ()) {
            m_roles.insert (Qt::DisplayRole, QByteArrayLiteral ("display"));
        }
        m_roles.insert (baseRole (), QByteArrayLiteral ("qtObject"));
        const int len = m_metaObj.propertyCount ();
        for (int propertyIdx = 0, role = (baseRole () +1); propertyIdx < len; propertyIdx++, role++) {
            QMetaProperty metaProp = m_metaObj.property (propertyIdx);
            const QByteArray propName = QByteArray (metaProp.name ());
            if (!roleNamesBlacklist.contains (propName)) {
                m_roles.insert (role, propName);
                if (metaProp.hasNotifySignal ()) {
                    m_signalIdxToRole.insert (metaProp.notifySignalIndex (), role);
                }
            }
            else {
                static const QByteArray CLASS_NAME = (QByteArrayLiteral ("QQmlObjectListModel<") % m_metaObj.className () % '>');
                qWarning () << "Can't have" << propName << "as a role name in" << qPrintable (CLASS_NAME);
            }
        }
    }
    bool setData (const QModelIndex & index, const QVariant & value, int role) {
        bool ret = false;
        ItemType * item = at (index.row ());
        const QByteArray rolename = (role != Qt::DisplayRole ? m_roles.value (role, emptyBA ()) : m_dispRoleName);
        if (item != Q_NULLPTR && role != baseRole () && !rolename.isEmpty ()) {
            ret = item->setProperty (rolename, value);
        }
        return ret;
    }
    QVariant data (const QModelIndex & index, int role) const {
        QVariant ret;
        ItemType * item = at (index.row ());
        const QByteArray rolename = (role != Qt::DisplayRole ? m_roles.value (role, emptyBA ()) : m_dispRoleName);
        if (item != Q_NULLPTR && !rolename.isEmpty ()) {
            ret.setValue (role != baseRole () ? item->property (rolename) : QVariant::fromValue (static_cast<QObject *> (item)));
        }
        return ret;
    }
    QHash<int, QByteArray> roleNames (void) const {
        return m_roles;
    }
    typedef typename QList<ItemType *>::iterator iterator;
    iterator begin (void) const {
        return m_items.begin ();
    }
    iterator end (void) const {
        return m_items.end ();
    }
    typedef typename QList<ItemType *>::const_iterator const_iterator;
    const_iterator constBegin (void) const {
        return m_items.constBegin ();
    }
    const_iterator constEnd (void) const {
        return m_items.constEnd ();
    }

public: // C++ API
    ItemType * at (int idx) const {
        ItemType * ret = Q_NULLPTR;
        if (idx >= 0 && idx < m_items.size ()) {
            ret = m_items.value (idx);
        }
        return ret;
    }
    ItemType * getByUid (const QString & uid) const {
        return m_indexByUid.value (uid, Q_NULLPTR);
    }
    int roleForName (const QByteArray & name) const {
        return m_roles.key (name, -1);
    }
    int count (void) const {
        return m_count;
    }
    int size (void) const {
        return m_count;
    }
    bool isEmpty (void) const {
        return m_items.isEmpty ();
    }
    bool contains (ItemType * item) const {
        return m_items.contains (item);
    }
    int indexOf (ItemType * item) const {
        return m_items.indexOf (item);
    }
    void clear (void) {
        if (!m_items.isEmpty ()) {
            beginRemoveRows (noParent (), 0, m_items.count () -1);
            FOREACH_PTR_IN_QLIST (ItemType, item, m_items) {
                dereferenceItem (item);
            }
            m_items.clear ();
            endRemoveRows ();
            updateCounter ();
        }
    }
    void append (ItemType * item) {
        if (item != Q_NULLPTR) {
            const int pos = m_items.count ();
            beginInsertRows (noParent (), pos, pos);
            m_items.append (item);
            referenceItem (item);
            endInsertRows ();
            updateCounter ();
        }
    }
    void prepend (ItemType * item) {
        if (item != Q_NULLPTR) {
            beginInsertRows (noParent (), 0, 0);
            m_items.prepend (item);
            referenceItem (item);
            endInsertRows ();
            updateCounter ();
        }
    }
    void insert (int idx, ItemType * item) {
        if (item != Q_NULLPTR) {
            beginInsertRows (noParent (), idx, idx);
            m_items.insert (idx, item);
            referenceItem (item);
            endInsertRows ();
            updateCounter ();
        }
    }
    void append (const QList<ItemType *> & itemList) {
        if (!itemList.isEmpty ()) {
            const int pos = m_items.count ();
            beginInsertRows (noParent (), pos, pos + itemList.count () -1);
            m_items.reserve (m_items.count () + itemList.count ());
            m_items.append (itemList);
            FOREACH_PTR_IN_QLIST (ItemType, item, itemList) {
                referenceItem (item);
            }
            endInsertRows ();
            updateCounter ();
        }
    }
    void prepend (const QList<ItemType *> & itemList) {
        if (!itemList.isEmpty ()) {
            beginInsertRows (noParent (), 0, itemList.count () -1);
            m_items.reserve (m_items.count () + itemList.count ());
            int offset = 0;
            FOREACH_PTR_IN_QLIST (ItemType, item, itemList) {
                m_items.insert (offset, item);
                referenceItem (item);
                offset++;
            }
            endInsertRows ();
            updateCounter ();
        }
    }
    void insert (int idx, const QList<ItemType *> & itemList) {
        if (!itemList.isEmpty ()) {
            beginInsertRows (noParent (), idx, idx + itemList.count () -1);
            m_items.reserve (m_items.count () + itemList.count ());
            int offset = 0;
            FOREACH_PTR_IN_QLIST (ItemType, item, itemList) {
                m_items.insert (idx + offset, item);
                referenceItem (item);
                offset++;
            }
            endInsertRows ();
            updateCounter ();
        }
    }
    void move (int idx, int pos) {
        if (idx != pos) {
            const int lowest  = qMin (idx, pos);
            const int highest = qMax (idx, pos);
            beginMoveRows (noParent (), highest, highest, noParent (), lowest);
            m_items.move (highest, lowest);
            endMoveRows ();
        }
    }
    void remove (ItemType * item) {
        if (item != Q_NULLPTR) {
            const int idx = m_items.indexOf (item);
            remove (idx);
        }
    }
    void remove (int idx) {
        if (idx >= 0 && idx < m_items.size ()) {
            beginRemoveRows (noParent (), idx, idx);
            ItemType * item = m_items.takeAt (idx);
            dereferenceItem (item);
            endRemoveRows ();
            updateCounter ();
        }
    }
    ItemType * first (void) const {
        return m_items.first ();
    }
    ItemType * last (void) const {
        return m_items.last ();
    }
    const QList<ItemType *> & toList (void) const {
        return m_items;
    }

public: // QML slots implementation
    void append (QObject * item) {
        append (qobject_cast<ItemType *> (item));
    }
    void prepend (QObject * item) {
        prepend (qobject_cast<ItemType *> (item));
    }
    void insert (int idx, QObject * item) {
        insert (idx, qobject_cast<ItemType *> (item));
    }
    void remove (QObject * item) {
        remove (qobject_cast<ItemType *> (item));
    }
    bool contains (QObject * item) const {
        return contains (qobject_cast<ItemType *> (item));
    }
    int indexOf (QObject * item) const {
        return indexOf (qobject_cast<ItemType *> (item));
    }
    int indexOf (const QString & uid) const {
        return indexOf (get (uid));
    }
    QObject * get (int idx) const {
        return static_cast<QObject *> (at (idx));
    }
    QObject * get (const QString & uid) const {
        return static_cast<QObject *> (getByUid (uid));
    }
    QObject * getFirst (void) const {
        return static_cast<QObject *> (first ());
    }
    QObject * getLast (void) const {
        return static_cast<QObject *> (last ());
    }
    QVariantList toVarArray (void) const {
        return qListToVariant<ItemType *> (m_items);
    }

protected: // internal stuff
    static const QString & emptyStr (void) {
        static const QString ret = QStringLiteral ("");
        return ret;
    }
    static const QByteArray & emptyBA (void) {
        static const QByteArray ret = QByteArrayLiteral ("");
        return ret;
    }
    static const QModelIndex & noParent (void) {
        static const QModelIndex ret = QModelIndex ();
        return ret;
    }
    static const int & baseRole (void) {
        static const int ret = Qt::UserRole;
        return ret;
    }
    int rowCount (const QModelIndex & parent = QModelIndex ()) const {
        Q_UNUSED (parent);
        return m_items.count ();
    }
    void referenceItem (ItemType * item) {
        if (item != Q_NULLPTR) {
            if (item->parent () == Q_NULLPTR) {
                item->setParent (this);
            }
            const QList<int> signalsIdxList = m_signalIdxToRole.keys ();
            for (QList<int>::const_iterator it = signalsIdxList.constBegin (); it != signalsIdxList.constEnd (); it++) {
                const int signalIdx = (int) (* it);
                QMetaMethod notifier = item->metaObject ()->method (signalIdx);
                connect (item, notifier, this, m_handler, Qt::UniqueConnection);
            }
            if (!m_uidRoleName.isEmpty ()) {
                const QString key = m_indexByUid.key (item, emptyStr ());
                if (!key.isEmpty ()) {
                    m_indexByUid.remove (key);
                }
                const QString value = item->property (m_uidRoleName).toString ();
                if (!value.isEmpty ()) {
                    m_indexByUid.insert (value, item);
                }
            }
        }
    }
    void dereferenceItem (ItemType * item) {
        if (item != Q_NULLPTR) {
            disconnect (this, Q_NULLPTR, item, Q_NULLPTR);
            disconnect (item, Q_NULLPTR, this, Q_NULLPTR);
            if (!m_uidRoleName.isEmpty ()) {
                const QString key = m_indexByUid.key (item, emptyStr ());
                if (!key.isEmpty ()) {
                    m_indexByUid.remove (key);
                }
            }
            if (item->parent () == this) { // FIXME : maybe that's not the best way to test ownership ?
                item->deleteLater ();
            }
        }
    }
    void onItemPropertyChanged (void) {
        ItemType * item = qobject_cast<ItemType *> (sender ());
        const int row = m_items.indexOf (item);
        const int sig = senderSignalIndex ();
        const int role = m_signalIdxToRole.value (sig, -1);
        if (row >= 0 && role >= 0) {
            QModelIndex index = QAbstractListModel::index (row, 0, noParent ());
            QVector<int> rolesList;
            rolesList.append (role);
            if (m_roles.value (role) == m_dispRoleName) {
                rolesList.append (Qt::DisplayRole);
            }
            emit dataChanged (index, index, rolesList);
        }
        if (!m_uidRoleName.isEmpty ()) {
            const QByteArray roleName = m_roles.value (role, emptyBA ());
            if (!roleName.isEmpty () && roleName == m_uidRoleName) {
                const QString key = m_indexByUid.key (item, emptyStr ());
                if (!key.isEmpty ()) {
                    m_indexByUid.remove (key);
                }
                const QString value = item->property (m_uidRoleName).toString ();
                if (!value.isEmpty ()) {
                    m_indexByUid.insert (value, item);
                }
            }
        }
    }
    inline void updateCounter (void) {
        if (m_count != m_items.count ()) {
            m_count = m_items.count ();
            emit countChanged ();
        }
    }

private: // data members
    int                        m_count;
    QByteArray                 m_uidRoleName;
    QByteArray                 m_dispRoleName;
    QMetaObject                m_metaObj;
    QMetaMethod                m_handler;
    QHash<int, QByteArray>     m_roles;
    QHash<int, int>            m_signalIdxToRole;
    QList<ItemType *>          m_items;
    QHash<QString, ItemType *> m_indexByUid;
};

#define QML_OBJMODEL_PROPERTY(type, name) \
    protected: Q_PROPERTY (QQmlObjectListModelBase * name READ get_##name CONSTANT) \
    private: QQmlObjectListModel<type> * m_##name; \
    public: QQmlObjectListModel<type> * get_##name (void) const { return m_##name; } \
    private:

#endif // QQMLOBJECTLISTMODEL_H


#endif // QQMLHELPERS_H



