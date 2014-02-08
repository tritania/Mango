import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Frame;
import java.net.URL;
import java.util.List;
import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import java.util.Date;

public class MangoSplash {

    private static JDialog dialog;
    private static JFrame frame;

    public static void hideSplashScreen() {
        dialog.dispose();
    }

    public static void showSplashScreen() {
        dialog = new JDialog((Frame) null);
        dialog.setModal(false);
        dialog.setUndecorated(true);
        dialog.getRootPane ().setOpaque (false);
        dialog.getContentPane ().setBackground (new Color (0, 0, 0, 0));
        dialog.setBackground (new Color (0, 0, 0, 0));
        JLabel background = new JLabel(new ImageIcon("Gesture.png"));
        background.setLayout(new BorderLayout());
        dialog.add(background);
        JLabel text = new JLabel("Gesture system ready!");
        text.setForeground(Color.WHITE);
        text.setBorder(BorderFactory.createEmptyBorder(100, 50, 100, 50));
        background.add(text);
        dialog.pack();
        dialog.setLocationRelativeTo(null);
        dialog.setVisible(true);
    }
}
