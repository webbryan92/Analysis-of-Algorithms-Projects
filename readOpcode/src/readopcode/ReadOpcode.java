/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package readopcode;

import java.io.File;
import java.util.Scanner;
import java.lang.*;

/**
 *
 * @author Ryan
 */
public class ReadOpcode {

    public static void main(String[] args) {
        int line = 0;
        char firstChar;
        boolean match;
        boolean data;
        String[] output;
        String[] identify = new String[16];
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
        identify[14] = "RET";
        identify[15] = "DATA";
        String[] opCode = new String[16];
        opCode[0] = "0";
        opCode[1] = "1";
        opCode[2] = "2";
        opCode[3] = "3";
        opCode[4] = "4";
        opCode[5] = "5";
        opCode[6] = "6";
        opCode[7] = "7";
        opCode[8] = "8";
        opCode[9] = "9";
        opCode[10] = "A";
        opCode[11] = "B";
        opCode[12] = "C";
        opCode[13] = "D";
        opCode[14] = "E";
        opCode[15] = "0";
        String str = " ";
        String str2 = " ";
        try {
            File file = new File(args[0]);
            Scanner inputStream = new Scanner(file);
            File file2 = new File(args[0]);
            Scanner inputStream2 = new Scanner(file2);
            File file3 = new File(args[0]);
            Scanner inputStream3 = new Scanner(file2);

            while (inputStream.hasNextLine()) {
                line = line + 1;
                inputStream.nextLine();
            }
            inputStream.close();
            output = new String[line];
            line = 0;
            while (inputStream2.hasNextLine()) {
                //data = false;
                str = inputStream2.nextLine();
                Scanner input2 = new Scanner(str);
                String op = "";
                int junk = 0;
                while (input2.hasNext()) {
                    match = false;
                    str = input2.next();
                    //firstChar = str.charAt(0);
                    //System.out.println("+"+str+"+");
                    /*if(data == true){
                     System.out.println("Variable found: "+str);
                     }
                     if(firstChar == 58){
                     System.out.println("Found label "+str);
                     }*/
                    for (int i = 0; i < identify.length; i++) {
                        if (str.equals(identify[i])) {
                            match = true;
                            junk = i;
                        }
                    }
                    if (match == true) {
                        op = opCode[junk];
                        output[line] = op;
                    }
                    /*if(str.equals("DATA")){
                     data = true;
                     }*/
                }
                line = line + 1;
            }
            inputStream.close();
            for (int i = 0; i < output.length; i++) {
                if (output[i].equals("1") || output[i].equals("2")
                        || output[i].equals("3") || output[i].equals("4")
                        || output[i].equals("5") || output[i].equals("6")) {
                    String temp = new String();
                    temp = output[i];
                    StringBuffer sb = new StringBuffer(temp);
                    sb.append("r");
                    output[i] = sb.toString();
                }
            }
            while (inputStream3.hasNextLine()) {
                //data = false;
                str = inputStream3.nextLine();
                Scanner input3 = new Scanner(str);
                String op = "";
                int junk = 0;
                for(int i = 0; i < output.length; i++){
                        if (output[i].equals("1r") || output[i].equals("2r")
                        || output[i].equals("3r") || output[i].equals("4r")
                        || output[i].equals("5r") || output[i].equals("6r")) {
                            str = input3.next();
                        }
                    }
                while (input3.hasNext()) {
                    match = false;
                    
                    
                    //firstChar = str.charAt(0);
                    //System.out.println("+"+str+"+");
                    /*if(data == true){
                     System.out.println("Variable found: "+str);
                     }
                     if(firstChar == 58){
                     System.out.println("Found label "+str);
                     }*/
                    for (int i = 0; i < identify.length; i++) {
                        if (str.equals(identify[i])) {
                            match = true;
                            junk = i;
                        }
                    }
                    if (match == true) {
                        op = opCode[junk];
                        output[line] = op;
                    }
                    /*if(str.equals("DATA")){
                     data = true;
                     }*/
                }
                line = line + 1;
            }
            for (int i = 0; i < output.length; i++) {
                System.out.println(output[i]);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

    }
}
