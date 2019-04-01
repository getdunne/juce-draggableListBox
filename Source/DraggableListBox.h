#pragma once
#include "JuceHeader.h"
#include "ListBoxItemData.h"
#include "ReorderFunctions.h"

// DraggableListBox is basically just a ListBox, that inherits from DragAndDropContainer
class DraggableListBox : public ListBox, public DragAndDropContainer
{
};

struct DraggableListBoxModel;
struct DraggableListBoxItem : public Component, public DragAndDropTarget
{
    DraggableListBoxItem(int id, Colour c, DraggableListBoxModel& m, int rn)
        : idNum(id), colour(c), model(m), rowNum(rn) {}

    // Component
    void paint(Graphics& g) override;
    void mouseDrag(const MouseEvent&) override;

    // DragAndDropTarget
    bool isInterestedInDragSource(const SourceDetails&) override { return true; }
    void itemDragEnter(const SourceDetails&) override;
    void itemDragMove(const SourceDetails&) override;
    void itemDragExit(const SourceDetails&) override;
    void itemDropped(const SourceDetails&) override;
    bool shouldDrawDragImageWhenOver() override { return true; }

    // DraggableListBoxItem
    void updateInsertLines(const SourceDetails &dragSourceDetails);
    void hideInsertLines();

    int idNum;
    Colour colour;
    bool insertAfter = false;
    bool insertBefore = false;
    DraggableListBoxModel& model;
    int rowNum;
};

struct DraggableListBoxModel : public ListBoxModel
{
    DraggableListBoxModel(DraggableListBox& lb) : listBox(lb) {}

    int getNumRows() override { return int(items.size()); }
    void paintListBoxItem(int, Graphics &, int, int, bool) override {}

    Component* refreshComponentForRow(int rowNumber,
        bool /*isRowSelected*/,
        Component *existingComponentToUpdate) override
    {
        ScopedPointer<DraggableListBoxItem> item(dynamic_cast<DraggableListBoxItem*>(existingComponentToUpdate));

        if (isPositiveAndBelow(rowNumber, (int)items.size()))
        {
            item = new DraggableListBoxItem(items[rowNumber].idNum, items[rowNumber].c, *this, rowNumber);
        }

        return item.release();
    }

    void MoveBefore(int indexOfItemToMove, int indexOfItemToPlaceBefore)
    {
        MoveItemBefore(items, indexOfItemToMove, indexOfItemToPlaceBefore);
        listBox.updateContent();
    }

    void MoveAfter(int indexOfItemToMove, int indexOfItemToPlaceAfter)
    {
        MoveItemAfter(items, indexOfItemToMove, indexOfItemToPlaceAfter);
        listBox.updateContent();
    }

    // Draggable model has a reference to its owner ListBox, so it can tell it to update after DnD
    DraggableListBox &listBox;

    // Vector of model data
    std::vector<ListBoxItemData> items;
};
