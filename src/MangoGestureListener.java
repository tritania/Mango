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


public class MangoGestureListener {
    
    private static int type;
    
    public static void recognize(Frame frame, Controller controller)
    {
        GestureList gestures = frame.gestures();
        for (int i = 0; i < gestures.count(); i++) {
            Gesture gesture = gestures.get(i);

            switch (gesture.type()) {
                case TYPE_CIRCLE:
                    CircleGesture circle = new CircleGesture(gesture);

                    // Calculate clock direction using the angle between circle normal and pointable
                    String clockwiseness;
                    if (circle.pointable().direction().angleTo(circle.normal()) <= Math.PI/4) {
                        // Clockwise if angle is less than 90 degrees
                        clockwiseness = "clockwise";
                        type = 1;
                    } else {
                        clockwiseness = "counterclockwise";
                        type = 2;
                    }

                    // Calculate angle swept since last frame
                    double sweptAngle = 0;
                    if (circle.state() != State.STATE_START) {
                        CircleGesture previousUpdate = new CircleGesture(controller.frame(1).gesture(circle.id()));
                        sweptAngle = (circle.progress() - previousUpdate.progress()) * 2 * Math.PI;
                    }


                    break;
                case TYPE_SWIPE:
                    type = 3;
                    SwipeGesture swipe = new SwipeGesture(gesture);
                   
                    break;
                case TYPE_SCREEN_TAP:
                    type = 4;
                    ScreenTapGesture screenTap = new ScreenTapGesture(gesture);
                   
                    break;
                case TYPE_KEY_TAP:
                    type = 5;
                    KeyTapGesture keyTap = new KeyTapGesture(gesture);
                
                    break;
                default:
                    break;
            }
        }

        if (!frame.hands().isEmpty() || !gestures.isEmpty()) {
        }
        
        }
}

