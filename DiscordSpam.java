import java.awt.datatransfer.StringSelection;
import java.awt.Toolkit;
import java.awt.datatransfer.Clipboard;

import javax.swing.*;

public class DiscordSpam {

    public static void main(String[] args) {
        String[] boolOptions = { "Yes", "No " };
        String title = "Discord Spam";
        // Sends user dropdown list asking if they have nitro or not, ternary is used to
        // set the limit based on their answer
        int discordLimit = (String) JOptionPane.showInputDialog(null, "Do you have Nitro?", title,
                JOptionPane.QUESTION_MESSAGE, null, boolOptions, boolOptions[1]) == "Yes" ? 4000 : 2000;
        String spamText = JOptionPane.showInputDialog(null, "Input text to spam", title, JOptionPane.QUESTION_MESSAGE)+" ";
        String output = "";
        // Concatenates until the string reaches Discord's character limit
        while (output.length() < discordLimit) {
            output = output + spamText;
        }
        // Makes sure the string doesn't go above Discord's character limit
        while (output.length() >= discordLimit) {
            output = output.substring(0, output.lastIndexOf(" "));
        }
        // Sends string to the clipboard
        StringSelection stringSelection = new StringSelection(output);
        Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
        clipboard.setContents(stringSelection, null);
    }

}