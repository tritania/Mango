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

public class MangoUser 
{
    
    public boolean gestureGo; //boolean value to determine whether or not a user wants to execute a command
    private int tOne, tTwo; //time keepers to register whether or not to change the boolean value
    
    public MangoUser()
    {
        gestureGo = false;
        tOne = 0;
        tTwo = 0;
    }
    
    public boolean execute() 
    {
        if ((tOne+100) >= tTwo)
        {
            gestureGo = true;
        }
        return true; //needs to be built out.
    }
    
    public void setGestureRequestTime(int a) 
    {
        tTwo = a;
    }
    
    public void setFrameTime(int a)
    {
        tOne = a;
    }
    
}
