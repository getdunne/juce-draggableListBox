#include "MainComponent.h"

MainContentComponent::MainContentComponent()
    : listBoxModel(listBox, itemData)
{
    itemData.modelData.add(new String("Item 1"));
    itemData.modelData.add(new String("Item 2"));
    itemData.modelData.add(new String("Item 3"));

    addBtn.setButtonText("Add Item...");
    addBtn.onClick = [this]()
    {
        itemData.modelData.add(new String("Item " + String(1 + itemData.getNumItems())));
        listBox.updateContent();
    };
    addAndMakeVisible(addBtn);

    listBox.setModel(&listBoxModel);
    listBox.setRowHeight(40);
    addAndMakeVisible(listBox);
    setSize (600, 400);
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void MainContentComponent::resized()
{
    auto area = getLocalBounds().reduced(20);
    auto row = area.removeFromTop(24);
    addBtn.setBounds(row.removeFromRight(100));

    area.removeFromTop(6);
    listBox.setBounds(area);
}
