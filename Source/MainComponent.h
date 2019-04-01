#pragma once
#include "JuceHeader.h"
#include "DraggableListBox.h"

struct MyListBoxItem : public DraggableListBoxItem
{
    MyListBoxItem(int id, Colour c, DraggableListBoxModel& m, int rn)
        : DraggableListBoxItem(id, m, rn), colour(c) {}

    void paintContents(Graphics& g) override
    {
        g.fillAll(colour);
        g.setColour(Colours::black);
        g.drawText(String::charToString('a' + idNum), getLocalBounds(), Justification::centred);
    }

    Colour colour;
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
