#pragma once
#include "JuceHeader.h"
#include "DraggableListBox.h"

// My item-specific data (could be anything)
struct MyItemData
{
    int idNum;
    MyItemData(int id) : idNum(id) {}
};

struct MyListBoxItemData : public DraggableListBoxItemData
{
    // My model data is an OwnedArray of structs as above
    OwnedArray<MyItemData> modelData;

    int getNumItems() override
    {
        return int(modelData.size());
    }

    void paintContents(int rowNum, Graphics& g, Rectangle<int> bounds) override
    {
        g.fillAll(Colours::lightgrey);
        g.setColour(Colours::black);
        g.drawRect(bounds);
        g.drawText(String::charToString('a' + modelData[rowNum]->idNum), bounds, Justification::centred);
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

    // Not required, just something I'm adding for confirmation of correct order after DnD
    void printItemsInOrder()
    {
        String msg = "\nitems: ";
        for (auto item : modelData) msg << String::charToString('a' + item->idNum) << " ";
        DBG(msg);
    }
};

class MainContentComponent   : public Component
{
public:
    MainContentComponent();
    virtual ~MainContentComponent() = default;
    
    void paint (Graphics&) override;
    void resized() override;
    
private:
    MyListBoxItemData itemData;
    DraggableListBoxModel listBoxModel;
    DraggableListBox listBox;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
