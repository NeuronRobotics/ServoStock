package com.neuronrobotics.replicator.gui;

//import java.applet.Applet;
import java.awt.Dialog;
import java.awt.Dimension;
//import java.awt.FlowLayout;
import java.awt.Frame;
import java.awt.GridBagLayout;
import java.awt.Toolkit;
import java.awt.Window;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.io.File;
//import java.nio.file.FileSystem;
//import java.nio.file.FileSystems;

import javax.swing.ImageIcon;
import javax.swing.JButton;
//import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

import com.sun.j3d.utils.applet.MainFrame;

public class Main {
	
	private static ImageIcon imageIcon = new ImageIcon("Images\\hat.png");

	public static void main(String[] argv) {
		
		//Setting look and Feel
		String lookAndFeel = UIManager.getSystemLookAndFeelClassName();
		try {
			UIManager.setLookAndFeel(lookAndFeel);
		} catch (ClassNotFoundException e1) {
			e1.printStackTrace();
		} catch (InstantiationException e1) {
			e1.printStackTrace();
		} catch (IllegalAccessException e1) {
			e1.printStackTrace();
		} catch (UnsupportedLookAndFeelException e1) {
			e1.printStackTrace();
		}
		
		WorkspaceSelect d = new WorkspaceSelect(new Frame(),"Select Workspace");
		d.setIconImage(imageIcon.getImage());
		d.initialize();
		d.setAlwaysOnTop(true);
		
		d.addWindowListener(new WindowListener(){

			@Override
			public void windowActivated(WindowEvent arg0) {				
			}

			@Override
			public void windowClosed(WindowEvent arg0) {
				
			}

			@Override
			public void windowClosing(WindowEvent arg0) {
				arg0.getWindow().dispose();
				System.exit(0);
			}

			@Override
			public void windowDeactivated(WindowEvent arg0) {
			}

			@Override
			public void windowDeiconified(WindowEvent arg0) {
			}

			@Override
			public void windowIconified(WindowEvent arg0) {
			}

			@Override
			public void windowOpened(WindowEvent arg0) {
			}});
		
		d.setVisible(true);
		
		
	}
	
	private static void startGUI(File directory){
		DesktopApplet tapp;
		if(!directory.exists()||!directory.isDirectory()) tapp = new DesktopApplet(new GUIDriver());
		else tapp = new DesktopApplet(new GUIDriver(),directory);
		MainFrame f = new MainFrame(tapp, 1200, 700);
		f.setIconImage(imageIcon.getImage());
		f.setExtendedState(f.getExtendedState()|Frame.MAXIMIZED_BOTH);
	}
	
	private static class WorkspaceSelect extends Dialog implements ActionListener{

		/**
		 * 
		 */
		private static final long serialVersionUID = 1844314345543127648L;
		
		File theFile;
		JLabel label;
		JTextField selectedDirectory;
		JButton submit, browse;
		
		public WorkspaceSelect(Dialog owner) {
			super(owner);
		}
		
		public WorkspaceSelect(Frame frame, String string) {
			super(frame,string);
		}

		public void initialize(){
			
			theFile = new File("DefaultWorkspaceFolder");
			
			this.setLayout(new GridBagLayout());
			
			Dimension screen = Toolkit.getDefaultToolkit().getScreenSize();
			int centX = screen.width/2;
			int centY = screen.height/2;
			
			this.setBounds(centX-325,centY-50,650,100);
			this.setResizable(false);
			
			label = new JLabel("Workspace: ");
			
			selectedDirectory = new JTextField(50);
			selectedDirectory.setText(theFile.getAbsolutePath());
			
			submit = new JButton("Submit");
			browse = new JButton("Browse");
			
			submit.addActionListener(this);
			browse.addActionListener(this);
			
			this.add(label);
			this.add(selectedDirectory);
			this.add(browse);
			this.add(submit);
			
			
		}

		@Override
		public void actionPerformed(ActionEvent arg0) {
			if(arg0.getSource().equals(browse)){
				JFileChooser fileChooser = new JFileChooser();
				fileChooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
				int returnVal = fileChooser.showOpenDialog(this);
				if (returnVal == JFileChooser.APPROVE_OPTION) {
					System.out.println("You chose to open this file: "
							+ fileChooser.getSelectedFile().getName());
					theFile = fileChooser.getSelectedFile();
					selectedDirectory.setText(theFile.getAbsolutePath());
				}
			

			} else if(arg0.getSource().equals(submit)){
				startGUI(theFile);
				Window.getWindows()[0].dispose();
			}
			
			
		}
		
	}
		
	
	
	
}
