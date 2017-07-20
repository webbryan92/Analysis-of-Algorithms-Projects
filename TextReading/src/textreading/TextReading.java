/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package textreading;

import java.io.*;
import java.util.Scanner;
import java.lang.Character;

/**
 *
 * @author Ryan
 */
public class TextReading {

    /**
     * @param args the command line arguments
     */    
    public static void main(String[] args) {
        int line = 1;
        char firstChar;
        boolean match;
        boolean data;
        String[] identify= new String[15];
        identify[0] = "HALT";
        identify[1] = "JNEG";
        identify[2] = "JPOS";
        identify[3] = "JZER";
        identify[4] = "JMP";
        identify[5] = "LOAD";
        identify[6] = "STOR";
        identify[7] = "ADD";
        identify[8] = "SUB";
        identify[9] = "RSH";
        identify[10] = "LSH";
        identify[11] = "AND";
        identify[12] = "OR";
        identify[13] = "NOT";
        identify[14] = "DATA";
        String str = " ";
        try{
            File file = new File(args[0]);
            Scanner inputStream = new Scanner(file);
            while(inputStream.hasNextLine()){   
                data = false;
                str = inputStream.nextLine();
                Scanner input2 = new Scanner(str);                
                while(input2.hasNext()){
                    match = false;
                    str = input2.next();
                    firstChar = str.charAt(0);
                    //System.out.println("+"+str+"+");
                    if(data == true){
                        System.out.println("Variable found: "+str);
                    }
                    if(firstChar == 58){
                        System.out.println("Found label "+str);
                    }
                    for(int i = 0; i < identify.length; i++){
                        if(str.equals(identify[i])){
                            match = true;
                        }
                    }
                    if(match == true){
                        System.out.println("Found "+str+" on line "+line);
                    }
                    if(str.equals("DATA")){
                        data = true;
                    }
                }                
                line = line + 1;
            }
        }
        catch(Exception e){
            e.printStackTrace();
        }        
    }    
}
