/*
  This file is part of the KDAB State Machine Editor Library.

  Copyright (C) 2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com.
  All rights reserved.
  Author: Kevin Funk <kevin.funk@kdab.com>

  Licensees holding valid commercial KDAB State Machine Editor Library
  licenses may use this file in accordance with the KDAB State Machine Editor
  Library License Agreement provided with the Software.

  This file may be distributed and/or modified under the terms of the
  GNU Lesser General Public License version 2.1 as published by the
  Free Software Foundation and appearing in the file LICENSE.LGPL.txt included.

  This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
  WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

  Contact info@kdab.com if any conditions of this licensing are not
  clear to you.
*/

#ifndef KDSME_MODEL_TRANSITION_H
#define KDSME_MODEL_TRANSITION_H

#include "element.h"

namespace KDSME {

class KDSME_CORE_EXPORT Transition : public Element
{
    Q_OBJECT
    Q_PROPERTY(KDSME::State* sourceState READ sourceState WRITE setSourceState NOTIFY sourceStateChanged FINAL)
    Q_PROPERTY(KDSME::State* targetState READ targetState WRITE setTargetState NOTIFY targetStateChanged FINAL)
    Q_PROPERTY(QString guard READ guard WRITE setGuard NOTIFY guardChanged FINAL)
        /// The exact shape of this transition
    Q_PROPERTY(QPainterPath shape READ shape WRITE setShape NOTIFY shapeChanged FINAL)
    Q_PROPERTY(QRectF labelBoundingRect READ labelBoundingRect WRITE setLabelBoundingRect NOTIFY labelBoundingRectChanged FINAL)

public:
    explicit Transition(State* sourceState = 0);
    virtual ~Transition();

    virtual Type type() const;

    Q_INVOKABLE KDSME::StateMachine* machine() const;

    State* sourceState() const;
    void setSourceState(State* sourceState);

    State* targetState() const;
    void setTargetState(State* targetState);

    /**
     * The guard condition for this transition (executable content)
     *
     * @return Any boolean expression in the current language
     */
    QString guard() const;
    void setGuard(const QString& guard);

    QPainterPath shape() const;
    void setShape(const QPainterPath& path);

    QRectF labelBoundingRect() const;
    void setLabelBoundingRect(const QRectF& rect);

Q_SIGNALS:
    void sourceStateChanged(State* sourceState);
    void targetStateChanged(State* targetState);
    void guardChanged(const QString& guard);
    void shapeChanged(const QPainterPath& path);
    void labelBoundingRectChanged(const QRectF& rect);

private:
    struct Private;
    QScopedPointer<Private> d;
};

KDSME_CORE_EXPORT QDebug operator<<(QDebug dbg, const Transition* transition);

class KDSME_CORE_EXPORT SignalTransition : public Transition
{
    Q_OBJECT
    Q_PROPERTY(QString signal READ signal WRITE setSignal NOTIFY signalChanged)

public:
    explicit SignalTransition(State* sourceState);
    virtual ~SignalTransition();

    virtual Type type() const override;

    QString signal() const;
    void setSignal(const QString& signal);

Q_SIGNALS:
    void signalChanged(const QString& signal);

private:
    struct Private;
    QScopedPointer<Private> d;
};

class KDSME_CORE_EXPORT TimeoutTransition : public Transition
{
    Q_OBJECT
    Q_PROPERTY(int timeout READ timeout WRITE setTimeout NOTIFY timeoutChanged)

public:
    explicit TimeoutTransition(State* sourceState);
    virtual ~TimeoutTransition();

    virtual Type type() const override;

    int timeout() const;
    void setTimeout(int timeout);

Q_SIGNALS:
    void timeoutChanged(int timeout);

private:
    struct Private;
    QScopedPointer<Private> d;
};

}

#endif