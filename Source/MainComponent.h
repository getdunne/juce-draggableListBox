#pragma once
#include "JuceHeader.h"
#include "DraggableListBox.h"

struct MyListBoxItemData : public DraggableListBoxItemData
{
    int idNum;
    MyListBoxItemData(int id) : idNum(id) {}

    String getDescription() override
    {
        return String::charToString('a' + idNum);
    }

    void paintContents(Graphics& g, Rectangle<int> bounds) override
    {
        g.fillAll(Colours::lightgrey);
        g.setColour(Colours::black);
        g.drawRect(bounds);
        g.drawText(String::charToString('a' + idNum), bounds, Justification::centred);
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
    DraggableListBoxModel listBoxModel;
    DraggableListBox listBox;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
