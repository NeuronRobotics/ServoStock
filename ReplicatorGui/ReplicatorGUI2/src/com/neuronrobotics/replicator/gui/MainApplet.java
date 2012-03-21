package com.neuronrobotics.replicator.gui;
import java.applet.Applet;
import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Frame;
import java.awt.GridLayout;
import java.awt.PopupMenu;
import java.awt.TextField;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.io.File;
import java.io.IOException;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;
import javax.swing.JTextField;
import javax.swing.JToolBar;

//import org.j3d.loaders.InvalidFormatException;

import com.neuronrobotics.replicator.driver.DeltaPrinter;
import com.neuronrobotics.replicator.driver.PrinterStatus;


public class MainApplet extends Applet implements PrinterStatusListener{
	
	private JMenuBar menuBar;
	private JToolBar mainToolbar;
	private JMenu file, edit, help;
	private File currentFile;
	
	private DeltaPrinter theDeltaPrinter;
	private PrinterStatus thePrinterStatus;
	
	private Preview3D preview;
	
	public MainApplet(DeltaPrinter p){
		super();
		theDeltaPrinter = p;
		thePrinterStatus = p.getPrinterStatus();
	}
	
	public void init(){
		
		thePrinterStatus.addListener(this);
		
		this.addComponentListener(new ComponentListener(){

			@Override
			public void componentHidden(ComponentEvent arg0) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void componentMoved(ComponentEvent arg0) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void componentResized(ComponentEvent arg0) {
				onResize();
			}

			@Override
			public void componentShown(ComponentEvent arg0) {
				// TODO Auto-generated method stub
				
			}
			
		});
		
		this.setLayout(null);
		
		
		
		JPopupMenu fileMenu = new JPopupMenu();
		JMenuItem openFile = new JMenuItem("Open File...");
		fileMenu.add(openFile);
		openFile.addActionListener(new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent arg0) {
				JFileChooser fileChooser = new JFileChooser();
				int returnVal = fileChooser.showOpenDialog(new JDialog());
			    if(returnVal == JFileChooser.APPROVE_OPTION) {
			       System.out.println("You chose to open this file: " +
			            fileChooser.getSelectedFile().getName());
			       currentFile = fileChooser.getSelectedFile();
			       
			       //TODO load this file
			    }
			}
			
		});
		
		mainToolbar = new JToolBar();
		
		JButton startPrint = new JButton("PRINT");
		startPrint.addActionListener(new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent arg0) {
				theDeltaPrinter.print(null);//TODO extract to listener class?				
			}
			
		});
		
		JButton cancelPrint = new JButton("Cancel");
		cancelPrint.addActionListener(new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent arg0) {
				theDeltaPrinter.cancel();//TODO	extract to listener class?			
			}
			
		});
		
		
		mainToolbar.add(startPrint);
		mainToolbar.add(cancelPrint);
		
		
		menuBar = new JMenuBar();
		file = new JMenu("File");
		edit = new JMenu("Edit");
		help = new JMenu("Help");
		
		file.add(openFile);
		
		menuBar.add(file);
		menuBar.add(edit);
		menuBar.add(help);
			
		this.add(menuBar);
		this.add(mainToolbar);
		
		try {
			String dir = "C:\\Users\\Admin\\replicator\\ReplicatorGUI2\\";
			File f = new File(dir+"bottle.stl");
			preview = new Preview3D(f);
			//preview.setModel(f);
			this.add(preview);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	
		onResize();
	
	}
	
	
	private void onResize(){
		int maxX = this.getWidth();
		int maxY = this.getHeight();
		
		
		int currX = 0,currY=0;
		menuBar.setBounds(currX, currY, maxX, menuBar.getPreferredSize().height);
		currY+=menuBar.getHeight();
		mainToolbar.setBounds(currX,currY,maxX,mainToolbar.getPreferredSize().height);
		currY+=mainToolbar.getHeight();
		preview.setBounds(currX,currY,maxX,maxY-currY);
		repaint();		
	}


	@Override
	public void statusChanged(PrinterStatus psl) {
		// TODO Auto-generated method stub		
	}
	
	
}
