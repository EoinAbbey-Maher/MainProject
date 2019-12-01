#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include <QUndoCommand>
#include <diagramitem.h>

class MoveCommand : public QUndoCommand
{
public:
    enum {Id = 1234};

    MoveCommand( DiagramItem *diagramItem ,const QPointF & oldPos, QUndoCommand *parent = 0);
    void undo() override;
    void redo() override;
    bool mergeWith(const QUndoCommand *other) override;
    int id() const override{return Id; }

private:
    DiagramItem *myDiagramItem;
    QPointF myOldPos;
    QPointF newPos;

};


#endif // MOVECOMMAND_H
