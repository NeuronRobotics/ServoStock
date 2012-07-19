package com.neuronrobotics.replicator.gui;
import java.awt.BorderLayout;
import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import java.awt.Label;
import java.awt.TextField;
import java.awt.Button;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import java.awt.Font;
import java.awt.Toolkit;
import java.io.File;

public class WorkspaceSelectionDialog extends JDialog {

	/**
	 * 
	 */
	private static final long serialVersionUID = -9041756258923427897L;
	
	private final JPanel contentPanel = new JPanel();
	private File theFile;
	private File returnFile;
	private TextField textField;

	/**
	 * Create the dialog.
	 */
	public WorkspaceSelectionDialog(Frame owner,File defaultDir) {
						
		super(owner);
				
		this.setIconImage(owner.getIconImage());
					
		theFile = defaultDir;
		
		returnFile = null;
				
		setTitle("Select Workspace");
		
		Dimension screen = Toolkit.getDefaultToolkit().getScreenSize();
		int centX = screen.width/2;
		int centY = screen.height/2;
		
		setBounds(centX-300, centY-50, 600, 100);
		
		getContentPane().setLayout(new BorderLayout());
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		getContentPane().add(contentPanel, BorderLayout.CENTER);
		GridBagLayout gbl_contentPanel = new GridBagLayout();
		gbl_contentPanel.columnWidths = new int[]{75, 345, 33, 53, 46, 0};
		gbl_contentPanel.rowHeights = new int[]{22, 0};
		gbl_contentPanel.columnWeights = new double[]{0.0, 1.0, 0.0, 0.0, 0.0, Double.MIN_VALUE};
		gbl_contentPanel.rowWeights = new double[]{1.0, Double.MIN_VALUE};
		contentPanel.setLayout(gbl_contentPanel);
		{
			Label label = new Label("Workspace: ");
			label.setFont(new Font("Dialog", Font.PLAIN, 12));
			GridBagConstraints gbc_label = new GridBagConstraints();
			gbc_label.anchor = GridBagConstraints.EAST;
			gbc_label.insets = new Insets(0, 0, 0, 5);
			gbc_label.gridx = 0;
			gbc_label.gridy = 0;
			contentPanel.add(label, gbc_label);
		}
		Button button = new Button("Submit");
		button.setFont(new Font("Dialog", Font.PLAIN, 12));
		button.addActionListener(new ActionListener() {
			

			public void actionPerformed(ActionEvent e) {
				returnFile = theFile;
				dispose();
			}
		});
		{
			textField = new TextField();
			textField.setText(theFile.getAbsolutePath());
			GridBagConstraints gbc_textField = new GridBagConstraints();
			gbc_textField.gridwidth = 2;
			gbc_textField.fill = GridBagConstraints.HORIZONTAL;
			gbc_textField.insets = new Insets(0, 0, 0, 5);
			gbc_textField.gridx = 1;
			gbc_textField.gridy = 0;
			contentPanel.add(textField, gbc_textField);
		}
		
		{
			Button button_1 = new Button("Browse");
			button_1.setFont(new Font("Dialog", Font.PLAIN, 12));

			final JDialog tis = this;
			
			button_1.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent arg0) {
					JFileChooser fileChooser = new JFileChooser();
					fileChooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
					int returnVal = fileChooser.showOpenDialog(tis);
					if (returnVal == JFileChooser.APPROVE_OPTION) {
						System.out.println("You chose to open this file: "
								+ fileChooser.getSelectedFile().getName());
						theFile = fileChooser.getSelectedFile();
						textField.setText(theFile.getAbsolutePath());
					}
				}
			});
			GridBagConstraints gbc_button_1 = new GridBagConstraints();
			gbc_button_1.anchor = GridBagConstraints.EAST;
			gbc_button_1.insets = new Insets(0, 0, 0, 5);
			gbc_button_1.gridx = 3;
			gbc_button_1.gridy = 0;
			contentPanel.add(button_1, gbc_button_1);
		}
		GridBagConstraints gbc_button = new GridBagConstraints();
		gbc_button.anchor = GridBagConstraints.EAST;
		gbc_button.gridx = 4;
		gbc_button.gridy = 0;
		contentPanel.add(button, gbc_button);
		{
		}
	}
	
	public File getTheFile(){
		return returnFile;
	}

}
