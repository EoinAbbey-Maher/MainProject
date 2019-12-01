#ifndef ADDCOMMAND_H
#define ADDCOMMAND_H

#include <QUndoCommand>
#include <QGraphicsScene>
#include <diagramitem.h>

class AddCommand : public QUndoCommand
{
public:
    AddCommand(DiagramItem::DiagramType addType, QGraphicsScene *graphicsScene, QUndoCommand *parent = 0);
    ~AddCommand();

    void undo() override;
    void redo() override;

private:
    DiagramItem *myDiagramItem;
    QGraphicsScene *myGraphicsScene;
    QPointF initialPosition;

};

#endif // ADDCOMMAND_H
