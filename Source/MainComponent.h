/*
 ==============================================================================
 
 This file was auto-generated!
 
 ==============================================================================
 */

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

template<typename C>
void MoveItemBefore(C& container, size_t currentIndex, size_t indexOfItemToPlaceBefore)
{
    /*
     thanks to @cbreak from ##c++-general for this
     */
    if( currentIndex == indexOfItemToPlaceBefore ) return;
    
    jassert( isPositiveAndBelow((int)currentIndex, (int)container.size() ));
    jassert( isPositiveAndBelow((int)indexOfItemToPlaceBefore, (int)container.size() ));
    
    if (currentIndex < indexOfItemToPlaceBefore)
    {
        std::rotate(container.begin() + currentIndex,
                    container.begin() + currentIndex + 1,
                    container.begin() + indexOfItemToPlaceBefore);
    }
    else
    {
        std::rotate(container.begin() + indexOfItemToPlaceBefore, //thanks to @Kyran for this fix
                    container.begin() + currentIndex,
                    container.begin() + currentIndex + 1);
    }
}

template<typename C>
void MoveItemAfter(C& container, size_t currentIndex, size_t indexOfItemToPlaceAfter)
{
    /*
     thanks to @cbreak from ##c++-general for this
     */
    if( currentIndex == indexOfItemToPlaceAfter ) return;
    
    jassert( isPositiveAndBelow((int)currentIndex, (int)container.size() ));
    jassert( isPositiveAndBelow((int)indexOfItemToPlaceAfter, (int)container.size() ));
    
    if (currentIndex < indexOfItemToPlaceAfter)
    {
        std::rotate(container.begin() + currentIndex,
                    container.begin() + currentIndex + 1,
                    container.begin() + indexOfItemToPlaceAfter + 1);
    }
    else
    {
        std::rotate(container.begin() + indexOfItemToPlaceAfter + 1, //thanks to @Kyran for this fix
                    container.begin() + currentIndex,
                    container.begin() + currentIndex + 1);
    }
}

struct Rules;
struct ListBoxItem : public Component, public DragAndDropTarget
{
    ListBoxItem(int id, Colour c_, Rules& owner_, int rowNum_) :
    idNum(id),
    c(c_),
    owner(&owner_),
    rowNum(rowNum_)
    {
    }
    
    ListBoxItem(const ListBoxItem& other)
    {
        c = other.c;
        idNum = other.idNum;
        owner = other.owner;
    }
    
    void paint(Graphics& g) override
    {
        g.fillAll(c);
        g.setColour(Colours::black);
        
        g.drawText( String::charToString( 'a' + idNum ), getLocalBounds(), Justification::centred);
        
        if( insertAfter )
        {
            g.setColour(Colours::red);
            g.fillRect(0, getHeight()-3, getWidth(), 3);
        }
        else if( insertBefore )
        {
            g.setColour(Colours::red);
            g.fillRect(0, 0, getWidth(), 3);
        }
    }
    
    void mouseDrag(const MouseEvent& e) override
    {
        /*
         thanks to @Rail Jon Rugot for this!  I would have never figured it out otherwise that I need to implement MouseDrag and find the D&D container to control dragging. 
         */
        if( DragAndDropContainer* container = DragAndDropContainer::findParentDragContainerFor(this))
        {
            container->startDragging("ListBoxItem", this);
        }
    }
    
    bool isInterestedInDragSource (const SourceDetails &dragSourceDetails) override
    {
        return true;
    }
    
    void updateInsertLines(const SourceDetails &dragSourceDetails)
    {
        if( dragSourceDetails.localPosition.y < getHeight() / 2 )
        {
            insertBefore = true;
            insertAfter = false;
        }
        else
        {
            insertAfter = true;
            insertBefore = false;
        }
        
        repaint();
    }
    
    void hideInsertLines()
    {
        insertBefore = false;
        insertAfter = false;
        
        repaint();
    }
    void itemDragEnter (const SourceDetails &dragSourceDetails) override
    {
        updateInsertLines(dragSourceDetails);
    }
    
    void itemDragMove (const SourceDetails &dragSourceDetails) override
    {
        updateInsertLines(dragSourceDetails);
    }
    
    void itemDragExit (const SourceDetails &dragSourceDetails) override
    {
        hideInsertLines();
    }
    void itemDropped (const SourceDetails &dragSourceDetails) override;
    
    bool shouldDrawDragImageWhenOver () override
    {
        return true;
    }
    
    int idNum;
    Colour c;
    bool insertAfter = false;
    bool insertBefore = false;
    Rules* owner;
    int rowNum;
};

struct ListBoxItemData
{
    int idNum;
    Colour c;
    
    ListBoxItemData(int id) : idNum(id)
    {
        Random r;
        Colour _c((uint8)r.nextInt({50,255}),
                  (uint8)r.nextInt({50,255}),
                  (uint8)r.nextInt({50,255}));
        c = _c;
    }
};

struct ListBoxContainer;
struct Rules : public ListBoxModel
{
    Rules(ListBoxContainer& owner_) : owner(owner_) { }
    
    int getNumRows() override
    {
        return items.size();
    }
    void paintListBoxItem(int rowNumber,
                          Graphics &g,
                          int width,
                          int height,
                          bool rowIsSelected) override
    {
        
    }
    var getDragSourceDescription (const SparseSet< int > &rowsToDescribe) override
    {
        return "Rules";
    }
    
    Component* refreshComponentForRow (int rowNumber,
                                       bool isRowSelected,
                                       Component *existingComponentToUpdate) override
    {
        ScopedPointer<ListBoxItem> item( dynamic_cast<ListBoxItem*>(existingComponentToUpdate) );
        
        if( isPositiveAndBelow(rowNumber, (int)items.size() ) )
        {
            item = new ListBoxItem(items[rowNumber].idNum, items[rowNumber].c, *this, rowNumber );
        }
        
        return item.release();
    }
    
    ListBoxContainer& owner;
    std::vector< ListBoxItemData > items
    {
        {0},{1},{2},{3}
    };
};

struct ListBoxContainer : public Component, public DragAndDropContainer, public AsyncUpdater
{
    ListBoxContainer() : rules(*this)
    {
        listBox.setModel(&rules);
        listBox.setRowHeight(50);
        addAndMakeVisible(listBox);
    }
    void paint(Graphics& g) override
    {
        g.fillAll(Colours::white);
        g.setColour(Colours::red);
        g.drawRect(getLocalBounds());
    }
    void resized() override
    {
        listBox.setBounds(getLocalBounds().reduced(2) );
    }
    
    void handleAsyncUpdate() override
    {
        listBox.updateContent();
    }
    
    Rules rules;
    ListBox listBox;
};

//==============================================================================
/*
 This component lives inside our window, and this is where you should put all
 your controls and content.
 */
class MainContentComponent   : public Component
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();
    
    void paint (Graphics&) override;
    void resized() override;
    
private:
    ListBoxContainer listBoxContainer;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED

