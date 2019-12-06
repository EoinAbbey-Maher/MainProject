#ifndef COMMANDS_H
#define COMMANDS_H

#include <QUndoCommand>

#include "diagramitem.h"

//! [0]
class MoveCommand : public QUndoCommand
{
public:
    enum { Id = 1234 };

    MoveCommand(DiagramItem *diagramItem, const QPointF &oldPos,
                QUndoCommand *parent = 0);

    void undo() override;
    void redo() override;
    bool mergeWith(const QUndoCommand *command) override;
    int id() const override { return Id; }

private:
    DiagramItem *myDiagramItem;
    QPointF myOldPos;
    QPointF newPos;
};
//! [0]

//! [1]
class DeleteCommand : public QUndoCommand
{
public:
    explicit DeleteCommand(QGraphicsScene *graphicsScene, QUndoCommand *parent = 0);

    void undo() override;
    void redo() override;

private:
    DiagramItem *myDiagramItem;
    QGraphicsScene *myGraphicsScene;
};
//! [1]

//! [2]
class AddCommand : public QUndoCommand
{
public:
    AddCommand(DiagramItem::DiagramType addType, QGraphicsScene *graphicsScene,
               QUndoCommand *parent = 0);
    ~AddCommand();

    void undo() override;
    void redo() override;

private:
    DiagramItem *myDiagramItem;
    QGraphicsScene *myGraphicsScene;
    QPointF initialPosition;
};
//! [2]

QString createCommandString(DiagramItem *item, const QPointF &point);

#endif
