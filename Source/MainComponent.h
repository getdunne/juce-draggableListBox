#pragma once
#include "JuceHeader.h"
#include "DraggableListBox.h"

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
