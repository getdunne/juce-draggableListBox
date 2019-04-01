#include "DraggableListBox.h"

void DraggableListBoxItem::paint(Graphics& g)
{
    if (itemData) itemData->paintContents(g, getLocalBounds());

    if (insertAfter)
    {
        g.setColour(Colours::red);
        g.fillRect(0, getHeight() - 3, getWidth(), 3);
    }
    else if (insertBefore)
    {
        g.setColour(Colours::red);
        g.fillRect(0, 0, getWidth(), 3);
    }
}

void DraggableListBoxItem::mouseDrag(const MouseEvent&)
{
    if (DragAndDropContainer* container = DragAndDropContainer::findParentDragContainerFor(this))
    {
        container->startDragging("DraggableListBoxItem", this);
    }
}

void DraggableListBoxItem::updateInsertLines(const SourceDetails &dragSourceDetails)
{
    if (dragSourceDetails.localPosition.y < getHeight() / 2)
    {
        insertBefore = true;
        insertAfter = false;
    }
    else
    {
        insertAfter = true;
        insertBefore = false;
    }
    repaint();
}

void DraggableListBoxItem::hideInsertLines()
{
    insertBefore = false;
    insertAfter = false;
    repaint();
}

void DraggableListBoxItem::itemDragEnter(const SourceDetails& dragSourceDetails)
{
    updateInsertLines(dragSourceDetails);
}

void DraggableListBoxItem::itemDragMove(const SourceDetails& dragSourceDetails)
{
    updateInsertLines(dragSourceDetails);
}

void DraggableListBoxItem::itemDragExit(const SourceDetails& /*dragSourceDetails*/)
{
    hideInsertLines();
}

void DraggableListBoxItem::itemDropped(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails)
{
    if (DraggableListBoxItem* item = dynamic_cast<DraggableListBoxItem*>(dragSourceDetails.sourceComponent.get()))
    {
        if (dragSourceDetails.localPosition.y < getHeight() / 2)
            model.MoveBefore(item->rowNum, rowNum);
        else
            model.MoveAfter(item->rowNum, rowNum);
    }
    hideInsertLines();
}

void DraggableListBoxModel::ListItemsOrder()
{
    String msg = "\nitems: ";
    for (auto item : items) msg << item->getDescription() << " ";
    DBG(msg);
}
