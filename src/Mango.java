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
import java.io.*;

public class Mango 
{
    public static boolean command = false;
    
    public static void main(String[] args) 
    {
        MangoUser user = new MangoUser(new File("commands.txt"));
        MangoListener listener = new MangoListener();
        Controller controller = new Controller();
        
        controller.addListener(listener);
        
        System.out.println("Press Enter to quit...");
        
        try 
        {
            System.in.read();
        } 
        
        catch (IOException e) 
        {
            e.printStackTrace();
        }

        controller.removeListener(listener);
    }
}

