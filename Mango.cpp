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
#include "Leap.h"
using namespace Leap;

class MangoListener : public Listener {
  public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
    virtual void onFocusGained(const Controller&);
    virtual void onFocusLost(const Controller&);
    virtual void onDeviceChange(const Controller&);
    virtual void onServiceConnect(const Controller&);
    virtual void onServiceDisconnect(const Controller&);

  private:
    bool onPreGesture;
    int preGestureCounter;
};

const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
const std::string boneNames[] = {"Metacarpal", "Proximal", "Middle", "Distal"};
const std::string stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};

void MangoListener::onInit(const Controller& controller) {
  std::cout << "Initialized" << std::endl;
}

void MangoListener::onConnect(const Controller& controller) {
  std::cout << "Connected" << std::endl;
  controller.enableGesture(Gesture::TYPE_CIRCLE);
  controller.enableGesture(Gesture::TYPE_KEY_TAP);
  controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
  controller.enableGesture(Gesture::TYPE_SWIPE);
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
                preGestureCounter = 0;
                const GestureList gestures = frame.gestures();
                for (int g = 0; g < gestures.count(); ++g) {
                    Gesture gesture = gestures[g];
                    switch (gesture.type()) {
                        case Gesture::TYPE_CIRCLE:
                        {
                            CircleGesture circle = gesture;
                            std::string clockwiseness;

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

void MangoListener::onFocusGained(const Controller& controller) {
    std::cout << "Focus Gained" << std::endl;
}

void MangoListener::onFocusLost(const Controller& controller) {
    std::cout << "Focus Lost" << std::endl;
}

void MangoListener::onDeviceChange(const Controller& controller) {
  std::cout << "Device Changed" << std::endl;
  const DeviceList devices = controller.devices();

  for (int i = 0; i < devices.count(); ++i) {
    std::cout << "id: " << devices[i].toString() << std::endl;
    std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
  }
}

void MangoListener::onServiceConnect(const Controller& controller) {
  std::cout << "Service Connected" << std::endl;
}

void MangoListener::onServiceDisconnect(const Controller& controller) {
  std::cout << "Service Disconnected" << std::endl;
}

int main()
{
  MangoListener listener;
  Controller controller;
  controller.addListener(listener);

  std::cout << "Mango started, press enter to quit..." << std::endl;
  std::cin.get();

  controller.removeListener(listener);

  return 0;
}
