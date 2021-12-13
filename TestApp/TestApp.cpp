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
    auto display=std::static_pointer_cast<DisplayBase>(engine.getFactory().getSingleton("Display"));

    display->setDisplaySize(320, 240);
    display->init();

    auto segment= std::static_pointer_cast<Segment2D>(engine.getFactory().getInstance("Segment2D"));
    (*segment)[0] = vect2Df( -159,-119 );
    (*segment)[1] = vect2Df( 159, 119);
    segment->getTransform().setTranslation(vect2Df(160, 120));

    display->add(segment);

    auto texture= std::static_pointer_cast<Texture>(engine.getFactory().getInstance("Texture"));
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
