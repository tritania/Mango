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
import java.util.Date;



public class MangoListener extends Listener {
    
    private boolean command = false;
    private boolean alert = false;
    private int commandcheck= 0;
    private long datetime;
    private long splashtime;
    
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

        if(datetime < new Date().getTime() && alert == true)
        {
            alert = false;
            try 
            {
            MangoSplash.hideSplashScreen();
            }
            catch (Exception ex) {}
        }

        if(command == true && datetime > new Date().getTime())
        {
            MangoGestureListener.recognize(frame, controller);
        }
        
        if(datetime < new Date().getTime())
        {
            command = false;
            commandcheck =0; 
        }

        if (!frame.hands().isEmpty() && (frame.hands().count() == 1) && (frame.fingers().count() == 0) && command == false) 
        {
           System.out.println("Ready!");
           commandcheck++;
           if (commandcheck == 60)
           {
                command = true;
                alert = true;
                MangoSplash.showSplashScreen();
                datetime = new Date().getTime() + 3000;
           } 
           datetime = new Date().getTime() + 10000;
        }   
        else if(command == false)
        {
            commandcheck = 0;
        }
        
    }
}
