#include "MainComponent.h"

MainContentComponent::MainContentComponent()
    : listBoxModel(listBox)
{
    listBoxModel.items.push_back({ 1 });
    listBoxModel.items.push_back({ 2 });
    listBoxModel.items.push_back({ 3 });
    listBoxModel.items.push_back({ 4 });
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
