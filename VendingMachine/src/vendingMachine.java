/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Ryan
 */
import java.util.*;
import java.lang.*;

public class vendingMachine {
    public static void main(String args[]){
        String str = "";
        System.out.println("Enter change, Q=quarter, D=dime, N=nickel.");
        Scanner input = new Scanner(System.in);
        str = input.nextLine();
        String[] array = str.split("");
        int sum = 0;
        boolean test = true;
        for(int i = 1; i < array.length; i++){
            if(array[i].equals("Q") == false && array[i].equals("D") == false && array[i].equals("N") == false){
                System.out.println("invalid input");
                test = false;
            }
        }
        if(test == true){
            for(int i = 1; i < array.length; i++){
                if(array[i].equals("Q")){
                    sum = sum + 25;
                }
                if(array[i].equals("D")){
                    sum = sum + 10;
                }
                if(array[i].equals("N")){
                    sum = sum + 5;
                }
            }
            if(sum >= 35){
                System.out.println("Enjoy your soda");
                if(sum > 10000){
                    System.out.println("Not enough change to return");
                }
                else{
                    sum = sum - 35;
                    System.out.println("Here is your change");
                    while(sum != 0){
                        sum = sum - 5;
                        System.out.print("N");                        
                    }
                    System.out.println("");
                }
            }
            else{
                System.out.println("Not enough money");
            }
        } 
    }   
}
