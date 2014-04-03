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

import java.io.*;
import java.util.ArrayList;
import java.util.*;

public class MangoUser 
{
    private File file;
    Writer tofile = null;
    ArrayList<String> commands = new ArrayList<String>();
    
    public MangoUser(File file)
    {
        BufferedWriter tofile = null;
        BufferedReader br = null;
        this.file = file;
        if (!file.exists())
        {
            try 
            {
                tofile = new BufferedWriter(new OutputStreamWriter(
                new FileOutputStream(file), "utf-8"));
                tofile.write("HAND-1:FINGERS-1:GESTURE-1:'ls';" + "\n" +"GESTURE-3:'pwd';"); //currently only one gesture 
            } 
            catch (IOException ex) 
            {
                 ex.printStackTrace();
            } 
            finally 
            {
                try {tofile.close();} catch (Exception ex) {}
            }
        }
        else 
        {
            try 
            {
                br = new BufferedReader(new FileReader(file));
                String line;
                while ((line = br.readLine()) != null)
                {
                    commands.add(line);
                }
            }
            catch (IOException e) 
            {
                e.printStackTrace();
            }
            finally 
            {
                try 
                {
                    if (br != null)
                        br.close();
                }
                catch (IOException ex)
                {
                     ex.printStackTrace();
                }
            }
        }
    }
}
