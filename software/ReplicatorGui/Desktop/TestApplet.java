package com.neuronrobotics.replicator.gui;

import java.applet.Applet;
import java.awt.Color;
import java.awt.Container;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Enumeration;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JProgressBar;
import javax.swing.JTabbedPane;
import javax.swing.JToolBar;
import javax.swing.JTree;
import javax.swing.tree.TreeNode;

import org.j3d.loaders.InvalidFormatException;

import com.neuronrobotics.replicator.driver.DeltaPrinter;
import com.neuronrobotics.replicator.driver.PrinterStatus;


public class TestApplet extends Applet{
	
	private Container menuContainer,toolbarContainer;
	private Container leftContainer,previewContainer,bottomContainer;
	
	private JTabbedPane leftTab, previewTab;
	
	private JMenuBar menuBar;
	private JToolBar mainToolbar;
	private JMenu fileMenu, editMenu, helpMenu;
	private File currentFile;
	
	private JButton printButton;
	private JButton cancelButton;
	
	private JTree fileNavigator;
	
	private DeltaPrinter theDeltaPrinter;
	private PrinterStatus thePrinterStatus;
	
	private JMenuItem openFileItem;
	
	private JProgressBar printProgress;
	
	private ArrayList<File> previewFiles;
	private ArrayList<Preview3D> previews;
	
	public void init(){
				
		previewFiles = new ArrayList<File>();
		previews = new ArrayList<Preview3D>();
		
		this.setLayout(null); 
		
		int ct= 0;
		
		menuContainer = new Container();
		menuContainer.setLayout(new GridLayout(1,1));
		
		toolbarContainer= new Container();
		toolbarContainer.setLayout(new GridLayout(1,1));
		
		leftContainer = new Container();
		leftContainer.setLayout(new GridLayout(1,1));
		
		leftTab = new JTabbedPane();
		leftContainer.add(leftTab);
		
		
		previewContainer = new Container();
		previewContainer.setLayout(new GridLayout(1,1));
		
		previewTab = new JTabbedPane();
		//previewTab.add(new JButton("TestButton"+(ct++)));
		//previewTab.add(new JButton("TestButton"+(ct++)));
		//previewTab.add(new JButton("TestButton"+(ct++)));
		
		previewContainer.add(previewTab);
		
		bottomContainer = new Container();
		bottomContainer.setLayout(new GridLayout(1,1));
		
		this.add(menuContainer);
		this.add(toolbarContainer);
		this.add(leftContainer);
		this.add(previewContainer);
		this.add(bottomContainer);
		
		menuBar = new JMenuBar();
		fileMenu = new JMenu("File");
		editMenu = new JMenu("Edit");
		helpMenu = new JMenu("Help");
		menuBar.add(fileMenu);
		menuBar.add(editMenu);
		menuBar.add(helpMenu);
		
		openFileItem = new JMenuItem("Open File...");
		openFileItem.addActionListener(new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent arg0) {
				JFileChooser fileChooser = new JFileChooser();
				int returnVal = fileChooser.showOpenDialog(new JDialog());
			    if(returnVal == JFileChooser.APPROVE_OPTION) {
			       System.out.println("You chose to open this file: " +
			            fileChooser.getSelectedFile().getName());
			       currentFile = fileChooser.getSelectedFile();
			       try {
					addPreview(currentFile);
				} catch (InvalidFormatException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
					System.out.println("Incorrectly formatted file");
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
					System.out.println("IO Exception dun happen'd");
				}
			    }
			}
			
		});
		
		fileMenu.add(openFileItem);
		
		menuContainer.add(menuBar);
		
		mainToolbar = new JToolBar();
		printButton = new JButton("PRINT");
		cancelButton = new JButton("CANCEL");
		
		mainToolbar.add(printButton);
		mainToolbar.add(cancelButton);
		
		toolbarContainer.add(mainToolbar);	
		
		fileNavigator = new JTree();
		fileNavigator.removeAll();
		
		leftTab.add("Navigator",fileNavigator);
		
		printProgress = new JProgressBar();
		printProgress.setValue(0); //TODO just to see how it looks
		printProgress.setName("SDFSD");
		
		
		bottomContainer.add(printProgress);
		
		
		
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
		
		
		onResize();
	}
	
	public boolean addPreview(File f) throws InvalidFormatException, IOException{
		if(!previewFiles.contains(f)){
			Preview3D tempPreview = new Preview3D(f);
			previewFiles.add(f);
			previews.add(tempPreview);
			String name=tempPreview.getSTLObject().getName();// = tempPreview.;
			if (name==null||name.equals("Default")){
				name = f.getName();
			}
			previewTab.add(name,tempPreview);
		
			
			
			repaint();
			return true;
		}
		return false;
	}
	
	private void onResize(){
		
		int maxX = this.getWidth();
		int maxY = this.getHeight();
		
		int currY = 0;
		
		menuContainer.setBounds(0,currY,maxX,menuBar.getPreferredSize().height);
		currY+=menuContainer.getHeight();
		toolbarContainer.setBounds(0,currY,maxX,mainToolbar.getPreferredSize().height);
		currY += toolbarContainer.getHeight();
		
		leftContainer.setBounds(0,currY,150,maxY-100);
		previewContainer.setBounds(150, currY, maxX-150, maxY-100);
		
		currY+=leftContainer.getHeight();
		
		bottomContainer.setBounds(0, currY, maxX, maxY-currY);		
		
		
		repaint();
	}

}
