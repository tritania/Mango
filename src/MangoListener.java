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

import java.io.IOException;
import java.lang.Math;
import java.lang.Runtime;
import com.leapmotion.leap.*;
import com.leapmotion.leap.Gesture.State;


public class MangoListener extends Listener {
    
    private int listener, recorder; // makes sure that gestures arent repeated too quickly
    private String command1 = "ls"; //at the moment only for debbuging
    
    public void swipeCommand(int time) {
        if (recorder == 0) {
            recorder = listener;
            try {
                Process proc = Runtime.getRuntime().exec(command1);
                } 
            catch (IOException e) {
                e.printStackTrace();
                                  }
                              }
        else if ((recorder + 35) >= listener)
        {}
        else {
            recorder = listener;
            try {
                Process proc = Runtime.getRuntime().exec(command1);
            } 
            catch (IOException e) {
                e.printStackTrace();
            }
            }
    }
    
    public void onInit(Controller controller) {
        System.out.println("Initialized");
    }

    public void onConnect(Controller controller) {
        System.out.println("Connected");
        controller.enableGesture(Gesture.Type.TYPE_SWIPE);
        controller.enableGesture(Gesture.Type.TYPE_CIRCLE);
        controller.enableGesture(Gesture.Type.TYPE_SCREEN_TAP);
        controller.enableGesture(Gesture.Type.TYPE_KEY_TAP);
    }

    public void onDisconnect(Controller controller) {
        System.out.println("Disconnected");
    }

    public void onExit(Controller controller) {
        System.out.println("Exited");
    }

    public void onFrame(Controller controller) {
        Frame frame = controller.frame();

        if (!frame.hands().isEmpty()) {
            Hand hand = frame.hands().get(0);

            FingerList fingers = hand.fingers();
            if (!fingers.isEmpty()) {
                Vector avgPos = Vector.zero();
                for (Finger finger : fingers) {
                    avgPos = avgPos.plus(finger.tipPosition());
                }
                avgPos = avgPos.divide(fingers.count());
                
            }

           

            Vector normal = hand.palmNormal();
            Vector direction = hand.direction();

            
        }

        GestureList gestures = frame.gestures();
        for (int i = 0; i < gestures.count(); i++) {
            listener++;
            Gesture gesture = gestures.get(i);

            switch (gesture.type()) {
                case TYPE_CIRCLE:
                    CircleGesture circle = new CircleGesture(gesture);

                    String clockwiseness;
                    if (circle.pointable().direction().angleTo(circle.normal()) <= Math.PI/4) {
                        clockwiseness = "clockwise";
                    } else {
                        clockwiseness = "counterclockwise";
                    }

                    double sweptAngle = 0;
                    if (circle.state() != State.STATE_START) {
                        CircleGesture previousUpdate = new CircleGesture(controller.frame(1).gesture(circle.id()));
                        sweptAngle = (circle.progress() - previousUpdate.progress()) * 2 * Math.PI;
                    }

                    
                    break;
                    
                case TYPE_SWIPE:
                    SwipeGesture swipe = new SwipeGesture(gesture);
                    swipeCommand(listener);
                    break;
                    
                case TYPE_SCREEN_TAP:
                    ScreenTapGesture screenTap = new ScreenTapGesture(gesture);
                   
                    break;
                    
                case TYPE_KEY_TAP:
                    KeyTapGesture keyTap = new KeyTapGesture(gesture);
                   
                    break;
                    
                default:
                    System.out.println("Unknown gesture type.");
                    break;
            }
        }

        if (!frame.hands().isEmpty() || !gestures.isEmpty()) {
        }
    }
}
