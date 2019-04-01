#pragma once
#include "JuceHeader.h"

struct ListBoxItemData
{
    int idNum;
    Colour c;

    ListBoxItemData(int id) : idNum(id)
    {
        Random r;
        c = Colour((uint8)r.nextInt({ 50,255 }), (uint8)r.nextInt({ 50,255 }), (uint8)r.nextInt({ 50,255 }));
    }
};
