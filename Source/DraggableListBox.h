#pragma once
#include "JuceHeader.h"

struct ListBoxItemData
{
    int idNum;

    ListBoxItemData(int id) : idNum(id) {}
};

// DraggableListBox is basically just a ListBox, that inherits from DragAndDropContainer
class DraggableListBox : public ListBox, public DragAndDropContainer
{
};

// Your Component for ListBox items should inherit from DraggableListBoxItem
// and implement paintContents()
struct DraggableListBoxModel;
struct DraggableListBoxItem : public Component, public DragAndDropTarget
{
    DraggableListBoxItem(int id, DraggableListBoxModel& m, int rn)
        : idNum(id), model(m), rowNum(rn) {}

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
    virtual void paintContents(Graphics&) {}

    int rowNum;
    DraggableListBoxModel& model;

    int idNum;
    bool insertAfter = false;
    bool insertBefore = false;
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
            item = new DraggableListBoxItem(items[rowNumber]->idNum, *this, rowNumber);
        }

        return item.release();
    }

    void MoveBefore(int indexOfItemToMove, int indexOfItemToPlaceBefore)
    {
        items.move(indexOfItemToMove, indexOfItemToPlaceBefore);
        listBox.updateContent();
        ListItemsOrder();
    }

    void MoveAfter(int indexOfItemToMove, int indexOfItemToPlaceAfter)
    {
        items.move(indexOfItemToMove, indexOfItemToPlaceAfter + 1);
        listBox.updateContent();
        ListItemsOrder();
    }

    void ListItemsOrder();

    // Draggable model has a reference to its owner ListBox, so it can tell it to update after DnD
    DraggableListBox &listBox;

    // Vector of model data
    OwnedArray<ListBoxItemData> items;
};
