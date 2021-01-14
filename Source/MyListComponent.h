#pragma once
#include "DraggableListBox.h"

// Application-specific data container
struct MyListBoxItemData : public DraggableListBoxItemData
{
    OwnedArray<String> modelData;

    int getNumItems() override
    {
        return int(modelData.size());
    }

    void deleteItem(int indexOfItemToDelete) override
    {
        modelData.remove(indexOfItemToDelete);
    }

    void addItemAtEnd() override
    {
        modelData.add(new String("Yahoo"));
    }

    void paintContents(int rowNum, Graphics& g, Rectangle<int> bounds) override
    {
        g.fillAll(Colours::lightgrey);
        g.setColour(Colours::black);
        g.drawRect(bounds);
        g.drawText(*modelData[rowNum], bounds, Justification::centred);
    }

    void moveBefore(int indexOfItemToMove, int indexOfItemToPlaceBefore) override
    {
        DBG("Move item " + String(indexOfItemToMove) + " before item " + String(indexOfItemToPlaceBefore));
        if (indexOfItemToMove <= indexOfItemToPlaceBefore)
            modelData.move(indexOfItemToMove, indexOfItemToPlaceBefore - 1);
        else
            modelData.move(indexOfItemToMove, indexOfItemToPlaceBefore);
        printItemsInOrder();
    }

    void moveAfter(int indexOfItemToMove, int indexOfItemToPlaceAfter) override
    {
        DBG("Move item " + String(indexOfItemToMove) + " after item " + String(indexOfItemToPlaceAfter));
        if (indexOfItemToMove <= indexOfItemToPlaceAfter)
            modelData.move(indexOfItemToMove, indexOfItemToPlaceAfter);
        else
            modelData.move(indexOfItemToMove, indexOfItemToPlaceAfter + 1);
        printItemsInOrder();
    }

    // Not required, just something I'm adding for confirmation of correct order after DnD.
    // This is an example of an operation on the entire list.
    void printItemsInOrder()
    {
        String msg = "\nitems: ";
        for (auto item : modelData) msg << *item << " ";
        DBG(msg);
    }

    // This is an example of an operation on a single list item.
    void doItemAction(int itemIndex)
    {
        DBG(*modelData[itemIndex]);
    }
};

// Custom list-item Component (which includes item-delete button)
class MyListComponent : public DraggableListBoxItem
{
public:
    MyListComponent(DraggableListBox& lb, MyListBoxItemData& data, int rn);
    ~MyListComponent();

    void paint(Graphics&) override;
    void resized() override;

protected:
    Rectangle<int> dataArea;
    TextButton actionBtn, deleteBtn;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MyListComponent)
};

// Customized DraggableListBoxModel overrides refreshComponentForRow() to ensure that every
// list-item Component is a MyListComponent.
class MyListBoxModel : public DraggableListBoxModel
{
public:
    MyListBoxModel(DraggableListBox& lb, DraggableListBoxItemData& md)
        : DraggableListBoxModel(lb, md) {}

    Component* refreshComponentForRow(int, bool, Component*) override;
};
