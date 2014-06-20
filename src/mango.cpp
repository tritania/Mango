/*
 * Copyright 2014 Erik Wilson <erikwilson@magnorum.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <QApplication>
#include "Leap.h"
#include "files.h"
#include "shapedclock.h"
using namespace Leap;

class MangoListener : public Listener {
  public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);

  private:
    bool onPreGesture = false;
    int preGestureCounter;
};

void MangoListener::onInit(const Controller& controller) {
  std::cout << "Initialized" << std::endl;
}

void MangoListener::onConnect(const Controller& controller) {
  std::cout << "Connected" << std::endl;
  controller.enableGesture(Gesture::TYPE_CIRCLE);
  controller.enableGesture(Gesture::TYPE_KEY_TAP);
  controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
  controller.enableGesture(Gesture::TYPE_SWIPE); //need to add new beta gestures
}

void MangoListener::onDisconnect(const Controller& controller) {
  std::cout << "Disconnected" << std::endl;
}

void MangoListener::onExit(const Controller& controller) {
  std::cout << "Exited" << std::endl;
}

void MangoListener::onFrame(const Controller& controller) {
  const Frame frame = controller.frame();

    HandList hands = frame.hands();
    for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
        const Hand hand = *hl;

        int extendedFingers = 0;
        for (int i = 0; i < hand.fingers().count(); i++)
        {
            Finger finger = hand.fingers()[i];
            if(finger.isExtended()) extendedFingers++;
        }

        if (!frame.hands().isEmpty() && frame.hands().count() == 1 && extendedFingers == 0)
        {
            std::cout << "Gesture Counter begins." << std::endl;
            preGestureCounter++;
            if (preGestureCounter > 60)
            {
                if (onPreGesture == false)
                {
                    ShapedClock clock;
                    clock.show();
                    while(1)
                    {

                    }
                }
                onPreGesture = true;

                preGestureCounter = 0;
                const GestureList gestures = frame.gestures();
                for (int g = 0; g < gestures.count(); ++g) {
                    Gesture gesture = gestures[g];
                    switch (gesture.type()) {
                        case Gesture::TYPE_CIRCLE:
                        {
                            CircleGesture circle = gesture;
                            std::string clockwiseness; //probably simplfy to a bool

                            if (circle.pointable().direction().angleTo(circle.normal()) <= PI/4) {
                              clockwiseness = "clockwise";
                            } else {
                              clockwiseness = "counterclockwise";
                            }
                            break;
                        }
                        case Gesture::TYPE_SWIPE:
                        {
                            SwipeGesture swipe = gesture;
                            break;
                        }
                        case Gesture::TYPE_KEY_TAP:
                        {
                            KeyTapGesture tap = gesture;
                            break;
                        }
                        case Gesture::TYPE_SCREEN_TAP:
                        {
                            ScreenTapGesture screentap = gesture;
                            break;
                        }
                        default:
                        {
                        std::cout << std::string(2, ' ')  << "Unknown gesture type." << std::endl;
                        break;
                        }
                    }
                }
            }
        }
        else
        {
            if (preGestureCounter > 0)
                preGestureCounter--;
        }
        std::cout << preGestureCounter << std::endl;
    }
}

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  MangoListener listener;
  MangoCommands commands;

  Controller controller;
  controller.addListener(listener);

  std::cout << "Mango started, press enter to quit..." << std::endl;
  std::cin.get();

  controller.removeListener(listener);
  return app.exec();
}
