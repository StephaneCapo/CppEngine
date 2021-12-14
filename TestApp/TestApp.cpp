// TestApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CppEngine.h"
#include "Factory.h"
#include "DisplayBase.h"
#include "Segment2D.h"
#include "Texture.h"

using namespace O3DCppEngine;

int main()
{
    CppEngine   engine;
    auto display=engine.getFactory().getSingleton<DisplayBase>("Display");

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
    // main loop
    do
    {
        segment->setColor(0, 0xFF, 0, 0x80);
        segment->getTransform().setRotationAngle(segment->getTransform().getRotationAngle() + 0.01f);
        //display->clear(ENCODE_COLOR(0, 0, 0, 0), 0.0f);
        display->swap();

    } while (1);

    display->close();
}
