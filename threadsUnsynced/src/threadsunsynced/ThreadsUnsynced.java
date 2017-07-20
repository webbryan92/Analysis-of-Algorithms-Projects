/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package threadsunsynced;

import java.io.*;
import java.util.*;

class globals {

    public static int incr;
}

class MyThread extends Thread {

    public void run() {
        while (globals.incr != 1000000) {
            globals.incr = globals.incr + 1;
        }
    }
}

class MyThread2 extends Thread {

    public void run() {
        while (globals.incr != 1000000) {
            if (globals.incr % 1000 == 0) {
                System.out.println(globals.incr);
            }
        }
    }
}

public class ThreadsUnsynced {
    public static void main(String args[]) {
        MyThread thread = new MyThread();
        MyThread2 read = new MyThread2();

        read.start();
        thread.start();
    }
}
