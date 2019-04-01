#pragma once
#include "JuceHeader.h"
#include "MyListComponent.h"

class MainContentComponent   : public Component
{
public:
    MainContentComponent();
    virtual ~MainContentComponent() = default;
    
    void paint (Graphics&) override;
    void resized() override;
    
private:
    TextButton addBtn;

    MyListBoxItemData itemData;
    MyListBoxModel listBoxModel;
    DraggableListBox listBox;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
