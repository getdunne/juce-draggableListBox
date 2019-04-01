#include "MainComponent.h"

MainContentComponent::MainContentComponent()
    : listBoxModel(listBox, itemData)
{
    for (int i = 0; i < 5; i++)
        itemData.modelData.add(new MyItemData(i));

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
    listBox.setBounds(getLocalBounds().reduced(20));
}
