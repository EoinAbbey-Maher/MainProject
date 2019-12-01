#ifndef DELETECOMMAND_H
#define DELETECOMMAND_H

#include <QUndoCommand>
#include <QGraphicsScene>
#include <diagramitem.h>

class DeleteCommand : public QUndoCommand
{
public:
    explicit DeleteCommand(QGraphicsScene * scene, QUndoCommand *parent = 0);

    void undo() override;
    void redo() override;

private:
    DiagramItem *myDiagramItem;
    QGraphicsScene *myGraphicsScene;

};

#endif // DELETECOMMAND_H
