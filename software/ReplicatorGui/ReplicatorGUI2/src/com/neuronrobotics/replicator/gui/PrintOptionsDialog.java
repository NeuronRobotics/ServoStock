package com.neuronrobotics.replicator.gui;

import java.awt.BorderLayout;
import java.awt.Dialog;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Frame;
import java.awt.Toolkit;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JDialog;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JLabel;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class PrintOptionsDialog extends JDialog {

	/**
	 * 
	 */
	private static final long serialVersionUID = 6314287431499049704L;
	
	private final JPanel contentPanel = new JPanel();
		
	private PrintOptions theOptions;
	private JCheckBox chckbxUseTransform;
	private JCheckBox chckbxForceReslice;
	
	/**
	 * Create the dialog.
	 */
	public PrintOptionsDialog(Frame owner) {
		super(owner,"Print Options",Dialog.ModalityType.APPLICATION_MODAL);
		this.setIconImage(owner.getIconImage());
						
		//center on screen
		Dimension screen = Toolkit.getDefaultToolkit().getScreenSize();
		int centX = screen.width / 2;
		int centY = screen.height / 2;
		
		theOptions = null;		
		
		//setTitle("Print Options");
		setResizable(false);
		setBounds(centX-100, centY-75, 200, 150);
		getContentPane().setLayout(new BorderLayout());
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		getContentPane().add(contentPanel, BorderLayout.CENTER);
		FlowLayout fl_contentPanel = new FlowLayout(FlowLayout.LEFT, 5, 5);
		contentPanel.setLayout(fl_contentPanel);
		{
			chckbxUseTransform = new JCheckBox("Use Current Transforms");
			contentPanel.add(chckbxUseTransform);
		}
		{
			JLabel label = new JLabel("");
			contentPanel.add(label);
		}
		{
			JLabel label = new JLabel("");
			contentPanel.add(label);
		}
		{
			chckbxForceReslice = new JCheckBox("Force Reslice");
			contentPanel.add(chckbxForceReslice);
		}
		{
			JLabel label = new JLabel("");
			contentPanel.add(label);
		}
		{
			JLabel label = new JLabel("");
			contentPanel.add(label);
		}
		{
			JLabel label = new JLabel("");
			contentPanel.add(label);
		}
		{
			JLabel label = new JLabel("");
			contentPanel.add(label);
		}
		{
			JLabel label = new JLabel("");
			contentPanel.add(label);
		}
		{
			JLabel label = new JLabel("");
			contentPanel.add(label);
		}
		{
			JLabel label = new JLabel("");
			contentPanel.add(label);
		}
		{
			JLabel label = new JLabel("");
			contentPanel.add(label);
		}
		{
			JLabel label = new JLabel("");
			contentPanel.add(label);
		}
		{
			JLabel label = new JLabel("");
			contentPanel.add(label);
		}
		{
			JLabel label = new JLabel("");
			contentPanel.add(label);
		}
		{
			JLabel label = new JLabel("");
			contentPanel.add(label);
		}
		{
			JLabel label = new JLabel("");
			contentPanel.add(label);
		}
		{
			JLabel label = new JLabel("");
			contentPanel.add(label);
		}
		{
			JPanel buttonPane = new JPanel();
			buttonPane.setLayout(new FlowLayout(FlowLayout.RIGHT));
			getContentPane().add(buttonPane, BorderLayout.SOUTH);
			{
				JButton okButton = new JButton("OK");
				okButton.addActionListener(new ActionListener() {
					public void actionPerformed(ActionEvent arg0) {
						theOptions = new PrintOptions(chckbxForceReslice.isSelected(),chckbxUseTransform.isSelected());
						dispose();
					}
				});
				okButton.setActionCommand("OK");
				buttonPane.add(okButton);
				getRootPane().setDefaultButton(okButton);
			}
			{
				JButton cancelButton = new JButton("Cancel");
				cancelButton.addActionListener(new ActionListener() {
					public void actionPerformed(ActionEvent arg0) {
						theOptions = null;
						dispose();
					}
				});
				cancelButton.setActionCommand("Cancel");
				buttonPane.add(cancelButton);
			}
		}
	}

	public PrintOptions getPrintOptions() {
		return theOptions;
	}

}
