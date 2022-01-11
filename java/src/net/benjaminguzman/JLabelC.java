package net.benjaminguzman;

import javax.swing.*;
import java.awt.*;

public class JLabelC extends JLabel
{
	public JLabelC(String text)
	{
		super(text);
		init();
	}

	public JLabelC()
	{
		init();
	}

	private void init() {
		setHorizontalAlignment(SwingUtilities.CENTER);
		setAlignmentX(Component.CENTER_ALIGNMENT);
	}
}
