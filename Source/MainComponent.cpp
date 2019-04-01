/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


void ListBoxItem::itemDropped(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails)
{
    if( ListBoxItem* item = dynamic_cast<ListBoxItem*>(dragSourceDetails.sourceComponent.get()))
    {
        DBG( "\n\nitem " << String(item->idNum) << " dropped onto " << String(idNum) );
        
        if( dragSourceDetails.localPosition.y < getHeight() / 2 )
        {
            MoveItemBefore(owner->items,
                           item->rowNum,
                           rowNum);
        }
        else
        {
            MoveItemAfter(owner->items,
                          item->rowNum,   //the current position
                          rowNum);    //drop it AFTER the item it was dropped on
        }
        
        owner->owner.triggerAsyncUpdate();
    }
    hideInsertLines();
}
//==============================================================================
MainContentComponent::MainContentComponent()
{
    addAndMakeVisible(listBoxContainer);
    setSize (600, 400);
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xff001F36));

    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
    
    
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    listBoxContainer.setBounds(20, 20, 200, 250);
}


