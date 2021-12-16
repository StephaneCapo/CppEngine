// TestApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CppEngine.h"
#include "Factory.h"
#include "DisplayBase.h"
#include "Segment2D.h"
#include "Rectangle2D.h"
#include "Texture.h"

using namespace O3DCppEngine;

int main()
{
    CppEngine   engine;
    sp<DisplayBase> display=engine.getFactory().getSingleton<DisplayBase>("Display");

    display->setDisplaySize(640, 480);
    display->init();

    auto segment= engine.getFactory().getInstance<Segment2D>("Segment2D");
    (*segment)[0] = vect2Df( -159,-119 );
    (*segment)[1] = vect2Df( 159, 119);
    segment->getTransform().setTranslation(vect2Df(160, 120));

    display->add(segment);

    auto texture= engine.getFactory().getInstance<Texture>("Texture");
    texture->setFileName("BBYoda.bmp");
    texture->init();

    auto rect = engine.getFactory().getInstance<Rectangle2D>("Rectangle2D");
    (*rect)[0] = vect2Df(-20, -20);
    (*rect)[1] = vect2Df(40, 40);
    rect->setColor(0, 0, 0xFF, 0, 0xFF);
    rect->setColor(1, 0, 0xFF, 0xFF, 0xFF);
    rect->setColor(2, 0xFF, 0xFF, 0, 0xFF);
    rect->setColor(3, 0xFF, 0, 0, 0xFF);
    rect->getTransform().setTranslation(vect2Df(160, 120));
    rect->getTransform().setRotationAngle(2.2f);
    display->add(rect);
    // main loop
    do
    {
        segment->setColor(0, 0xFF, 0, 0x80);
        segment->getTransform().setRotationAngle(segment->getTransform().getRotationAngle() + 0.01f);
        //rect->getTransform().setRotationAngle(rect->getTransform().getRotationAngle() - 0.01f);
        
        display->clear(ENCODE_COLOR(0, 0, 0, 0), 0.0f);
        display->swap();

    } while (1);

    display->close();
}
