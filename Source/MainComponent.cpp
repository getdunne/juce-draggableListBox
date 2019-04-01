#include "MainComponent.h"

MainContentComponent::MainContentComponent()
    : listBoxModel(listBox)
{
    for (int i = 0; i < 5; i++)
        listBoxModel.items.add(new MyListBoxItemData(i));

    listBox.setModel(&listBoxModel);
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
