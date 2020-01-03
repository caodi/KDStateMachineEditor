/*
  This file is part of the KDAB State Machine Editor Library.

  Copyright (C) 2014-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com.
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

#ifndef KDSME_COMMAND_REPARENTELEMENTCOMMAND_P_H
#define KDSME_COMMAND_REPARENTELEMENTCOMMAND_P_H

#include "command_p.h"

#include <QPointer>

namespace KDSME {

class Element;
class StateMachineScene;

/**
 * @brief Modifies the parent element of a @ref KDSME::Element
 *
 * This command is useful when dragging & dropping elements
 * into a different level in the state chart hierarchy.
 * On undo, the previous parent is restored.
 */
class KDSME_VIEW_EXPORT ReparentElementCommand : public Command
{
    Q_OBJECT

public:
    ReparentElementCommand(StateMachineScene* view, Element* element, QUndoCommand* parent = nullptr);

    int id() const override { return ReparentElement; }

    Q_INVOKABLE void setParentElement(KDSME::Element* parentElement);

    void redo() override;
    void undo() override;

private:
    QPointer<StateMachineScene> m_view;
    QPointer<Element> m_element;

    /// Whether this command is valid (ie. if redo/undo is doing something)
    bool m_valid;

    QPointer<Element> m_newParentElement;
    QPointer<Element> m_oldParentElement;
};

}

#endif // REPARENTELEMENTCOMMAND_P_H
