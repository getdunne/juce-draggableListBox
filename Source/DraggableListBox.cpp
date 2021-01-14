#include "DraggableListBox.h"

DraggableListBoxItemData::~DraggableListBoxItemData() {};

void DraggableListBoxItem::paint(Graphics& g)
{
    modelData.paintContents(rowNum, g, getLocalBounds());

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

void DraggableListBoxItem::mouseEnter(const MouseEvent&)
{
    savedCursor = getMouseCursor();
    setMouseCursor(MouseCursor::DraggingHandCursor);
}

void DraggableListBoxItem::mouseExit(const MouseEvent&)
{
    setMouseCursor(savedCursor);
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
            modelData.moveBefore(item->rowNum, rowNum);
        else
            modelData.moveAfter(item->rowNum, rowNum);
        listBox.updateContent();
    }
    hideInsertLines();
}

Component* DraggableListBoxModel::refreshComponentForRow(int rowNumber,
                                                         bool /*isRowSelected*/,
                                                         Component *existingComponentToUpdate)
{
    std::unique_ptr<DraggableListBoxItem> item(dynamic_cast<DraggableListBoxItem*>(existingComponentToUpdate));
    if (isPositiveAndBelow(rowNumber, modelData.getNumItems()))
    {
        item = std::make_unique<DraggableListBoxItem>(listBox, modelData, rowNumber);
    }
    return item.release();
}
