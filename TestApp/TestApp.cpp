// TestApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CppEngine.h"
#include "Factory.h"
#include "DisplayBase.h"
#include "Segment2D.h"

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

    // main loop
    do
    {
        segment->setColor(0xFF, 0, 0, 0x80);
        segment->getTransform().setRotationAngle(segment->getTransform().getRotationAngle() + 0.01f);
      //  display->clear(ENCODE_COLOR(0, 0, 0, 0), 0.0f);
        display->swap();

    } while (1);

    display->close();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
