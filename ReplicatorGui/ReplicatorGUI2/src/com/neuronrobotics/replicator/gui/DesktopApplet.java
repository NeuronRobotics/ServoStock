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
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.MutableTreeNode;
import javax.swing.tree.TreeNode;

//import org.j3d.loaders.InvalidFormatException;

import com.neuronrobotics.replicator.driver.NRPrinter;
import com.neuronrobotics.replicator.driver.PrinterStatus;


public class DesktopApplet extends Applet{
	
	private File defaultWorkspaceDirectory;
	
	private Container menuContainer,toolbarContainer;
	private Container leftContainer,previewContainer,bottomContainer;
	
	private JTabbedPane leftTab, previewTab;
	
	private JMenuBar menuBar;
	private JToolBar mainToolbar;
	private JMenu fileMenu, editMenu, helpMenu;
	
	private JButton printButton;
	private JButton cancelButton;
	private JButton connectButton;
	
	private WorkspaceNavigator fileNavigator;
	private DefaultMutableTreeNode treeRoot;
		
	private JMenuItem openFileItem;
	private JMenuItem newProjectItem;
	
	private JProgressBar printProgress;


	private ArrayList<File> stlFiles;
	private ArrayList<File> gcodeFiles;
	private ArrayList<Preview3D> previews;
		
	private GUIDriver theGUIDriver;
	
	public DesktopApplet(GUIDriver theGUIDriver){
		super();
		this.theGUIDriver = theGUIDriver;
	}
	
	public void init(){
		
		//TODO un-hard code this
		defaultWorkspaceDirectory = new File("DefaultWorkspaceFolder");
		
		stlFiles = new ArrayList<File>();
		gcodeFiles = new ArrayList<File>();
		previews = new ArrayList<Preview3D>();
		
		this.setLayout(null); 
				
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
			       File newFile = fileChooser.getSelectedFile();
			       try {
					addPreview(newFile);
					
				} catch (IOException e) {
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
		printButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				toolbarPrintButtonHandler();
			}
		});
		cancelButton = new JButton("CANCEL");
		cancelButton.addActionListener(new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent arg0) {
				cancelButtonHandler();
			}});
		
		connectButton = new JButton("CONNECT");
		connectButton.addActionListener(new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent arg0) {
				connectButtonHandler();
			}

			
		});
		
		mainToolbar.add(printButton);
		mainToolbar.add(cancelButton);
		mainToolbar.add(connectButton);
		
		toolbarContainer.add(mainToolbar);	
		
		//DefaultMutableTreeNode root = new DefaultMutableTreeNode();
		fileNavigator = WorkspaceNavigator.getNavigator(defaultWorkspaceDirectory);
		
		
		
		leftTab.add("Navigator",fileNavigator);
						
		printProgress = new JProgressBar();
				
		bottomContainer.add(printProgress);
						
		this.addComponentListener(new ComponentListener(){

			@Override
			public void componentHidden(ComponentEvent arg0) {
				
			}

			@Override
			public void componentMoved(ComponentEvent arg0) {
			}

			@Override
			public void componentResized(ComponentEvent arg0) {
				onResize();
			}

			@Override
			public void componentShown(ComponentEvent arg0) {				
			}
			
		});
		onResize();
	}
	
	public void workspaceNavigatorPrintHandler(){
		//TODO
	}
	
	public void toolbarPrintButtonHandler(){
		//TODO prompt user
		if(stlFiles.size()==0){
			//TODO change status to nothing to print
			return;
		}
		File currentFile = stlFiles.get(previewTab.getSelectedIndex());
		File currentGCodeFile = gcodeFiles.get(previewTab.getSelectedIndex());
		if (currentGCodeFile==null) theGUIDriver.requestPrint(currentFile,currentGCodeFile);
		else {
			//TODO prompt user
			theGUIDriver.requestPrint(currentGCodeFile);
		}
		System.out.println("Printing file "+currentFile.getAbsolutePath());
	}
	
	public void cancelButtonHandler(){
		theGUIDriver.requestCancel();		
	}
	
	private void connectButtonHandler() {
		theGUIDriver.connectPrinter();		
	}
	
	public boolean addPreview(File f) throws IOException{
		
		if(!stlFiles.contains(f)){
			Preview3D tempPreview = new Preview3D(f);
			stlFiles.add(f);
			gcodeFiles.add(new File(f.getName()+".sliced"));
			previews.add(tempPreview);
			String name=tempPreview.getSTLObject().getName();
			if (name==null||name.equals("Default")){
				name = f.getName();
			}
			previewTab.add(name,tempPreview);
		
			previewTab.setSelectedIndex(previews.size()-1);
			
			repaint();
			return true;
		}
		previewTab.setSelectedIndex(stlFiles.indexOf(f));
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
