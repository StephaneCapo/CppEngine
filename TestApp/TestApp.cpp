// TestApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CppEngine.h"
#include "Factory.h"
#include "DisplayBase.h"
#include "Segment2D.h"
#include "Rectangle2D.h"
#include "Texture.h"
#include "Sprite.h"

using namespace O3DCppEngine;

int main()
{
    CppEngine   engine;
    sp<DisplayBase> display=engine.getFactory().getSingleton<DisplayBase>("Display");

    display->setDisplaySize(320, 240);
    display->init();

    auto segment= engine.getFactory().getInstance<Segment2D>("Segment2D");
    (*segment)[0] = vect2Df( -159,-119 );
    (*segment)[1] = vect2Df( 159, 119);
    segment->getTransform().setTranslation(vect2Df(160, 120));

    display->add(segment);

   

    auto rect = engine.getFactory().getInstance<Sprite>("Sprite");
    rect->setTextureName("BBYoda.bmp");
    rect->getTransform().setTranslation(vect2Df(160, 120));
    //rect->getTransform().setRotationAngle(2.2f);
    rect->getTransform().setScale(0.8f);
    rect->init();
    display->add(rect);
    // main loop
    do
    {
        segment->setColor(0, 0xFF, 0, 0x80);
        segment->getTransform().setRotationAngle(segment->getTransform().getRotationAngle() + 0.04f);
        rect->getTransform().setRotationAngle(rect->getTransform().getRotationAngle() - 0.04f);
        
        display->clear(ENCODE_COLOR(0, 0, 0, 0), 0.0f);
        display->swap();

    } while (1);

    display->close();
}
