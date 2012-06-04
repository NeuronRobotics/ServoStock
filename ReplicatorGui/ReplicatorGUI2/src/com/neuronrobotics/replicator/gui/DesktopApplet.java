package com.neuronrobotics.replicator.gui;

import java.applet.Applet;
//import java.awt.Color;
import java.awt.Button;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.File;
import java.io.IOException;
//import java.util.ArrayList;
import java.util.Hashtable;
//import java.util.Enumeration;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFileChooser;
//import javax.swing.JLabel;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JProgressBar;
import javax.swing.JTabbedPane;
import javax.swing.JToolBar;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
//import javax.swing.JTree;
//import javax.swing.tree.DefaultMutableTreeNode;
//import javax.swing.tree.MutableTreeNode;
//import javax.swing.tree.TreeNode;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.vecmath.Point3f;

import com.neuronrobotics.replicator.gui.navigator.DirectoryTree;
import com.neuronrobotics.replicator.gui.navigator.WorkspaceLeafNode;
import com.neuronrobotics.replicator.gui.navigator.WorkspaceNavigator;
import com.neuronrobotics.replicator.gui.preview.STLPreviewContainer;
import com.neuronrobotics.replicator.gui.stl.ASCIISTLWriter;
import com.neuronrobotics.replicator.gui.stl.STLObject;

//import org.j3d.loaders.InvalidFormatException;

//import com.neuronrobotics.replicator.driver.NRPrinter;
//import com.neuronrobotics.replicator.driver.PrinterStatus;

public class DesktopApplet extends Applet implements GUIFrontendInterface {

	/**
	 * 
	 */
	private static final long serialVersionUID = -7003760875384715160L;

	private File defaultWorkspaceDirectory;

	private Container menuContainer, toolbarContainer;
	private Container leftContainer, bottomContainer;// previewContainer

	private STLPreviewContainer previewContainer;

	private JTabbedPane leftTab;// , previewTab;

	private JMenuBar menuBar;
	private JToolBar mainToolbar;
	private JMenu fileMenu, editMenu, helpMenu;

	private JButton printButton;
	private JButton cancelButton;
	private JButton connectButton;

	private WorkspaceNavigator fileNavigator;
	private DirectoryTree theDirectoryTree;

	private JMenuItem openFileItem;
	private JMenuItem newProjectItem;

	private JLabel statusLabel;
	private JProgressBar printProgress;

	private GUIBackendInterface theGUIDriver;

	private Point3f workspaceDimensions;

	public DesktopApplet(GUIBackendInterface theGUIDriver) {
		super();
		this.theGUIDriver = theGUIDriver;
		this.theGUIDriver.setFrontend(this);
		workspaceDimensions = new Point3f(60, 60, 60); // TODO extract to factory
	}

	public void init() {

		//Setting a different look and feel
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
		
		
		GridBagLayout gridbag = new GridBagLayout();
		GridBagConstraints c = new GridBagConstraints();

		setFont(new Font("Helvetica", Font.PLAIN, 14));
		setLayout(gridbag);

		// TODO remove to factory
		defaultWorkspaceDirectory = new File("DefaultWorkspaceFolder");
		

		menuContainer = new Container();
		menuContainer.setLayout(new GridLayout(1, 1));

		toolbarContainer = new Container();
		toolbarContainer.setLayout(new GridLayout(1, 1));

		leftContainer = new Container();
		leftContainer.setLayout(new GridLayout(1, 1));

		leftTab = new JTabbedPane();
		leftContainer.add(leftTab);

		previewContainer = new STLPreviewContainer();

		bottomContainer = new Container();
		bottomContainer.setLayout(new GridLayout(2, 1));

		Dimension d = leftContainer.getPreferredSize();
		d.width = 225;
		leftContainer.setPreferredSize(d);
		
		d = bottomContainer.getPreferredSize();
		d.height=50;
		bottomContainer.setPreferredSize(d);

		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;

		c.gridwidth = GridBagConstraints.REMAINDER;
		gridbag.setConstraints(menuContainer, c);
		add(menuContainer);
		gridbag.setConstraints(toolbarContainer, c);
		add(toolbarContainer);

		c.weightx = 0.0;
		c.gridheight = GridBagConstraints.RELATIVE;
		c.gridwidth = GridBagConstraints.RELATIVE;
		gridbag.setConstraints(leftContainer, c);
		add(leftContainer);

		c.weightx = 1.0;
		c.gridwidth = GridBagConstraints.REMAINDER;
		c.weighty = 1.0;
		gridbag.setConstraints(previewContainer, c);
		this.add(previewContainer);

		c.weighty = 0.0;
		c.gridheight = 1;// GridBagConstraints.REMAINDER;
		gridbag.setConstraints(bottomContainer, c);
		this.add(bottomContainer);

		// //////

		menuBar = new JMenuBar();
		fileMenu = new JMenu("File");
		editMenu = new JMenu("Edit");
		helpMenu = new JMenu("Help");
		menuBar.add(fileMenu);
		menuBar.add(editMenu);
		menuBar.add(helpMenu);

		openFileItem = new JMenuItem("Open File...");
		openFileItem.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				JFileChooser fileChooser = new JFileChooser();
				int returnVal = fileChooser.showOpenDialog(new JDialog());
				if (returnVal == JFileChooser.APPROVE_OPTION) {
					System.out.println("You chose to open this file: "
							+ fileChooser.getSelectedFile().getName());
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

		this.newProjectItem = new JMenuItem("New Folder");
		newProjectItem.addActionListener(new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent arg0) {
				fileNavigator.addTestNode();//TODO testing only	
				theDirectoryTree.testNode();
			}
		});
		
		fileMenu.add(openFileItem);
		fileMenu.add(newProjectItem);

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
		cancelButton.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				cancelButtonHandler();
			}
		});

		connectButton = new JButton("CONNECT");
		connectButton.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				connectButtonHandler();
			}

		});

		mainToolbar.add(printButton);
		mainToolbar.add(cancelButton);
		mainToolbar.add(connectButton);

		toolbarContainer.add(mainToolbar);

		// DefaultMutableTreeNode root = new DefaultMutableTreeNode();
		fileNavigator = WorkspaceNavigator
				.getNavigator(defaultWorkspaceDirectory);
		
		theDirectoryTree = DirectoryTree.getDirectoryTree(defaultWorkspaceDirectory);
		//TODO
		
		//MouseListener ml = new MouseListener(){};
		
		fileNavigator.addMouseListener(new MouseListener(){

			@Override
			public void mouseClicked(MouseEvent e) {
				// TODO Auto-generated method stub
				if(e.getClickCount()==2){
					
				}
			}

			@Override
			public void mouseEntered(MouseEvent e) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void mouseExited(MouseEvent e) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void mousePressed(MouseEvent e) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void mouseReleased(MouseEvent e) {
				// TODO Auto-generated method stub
				
			}
			
		});
		
		fileNavigator.addTreeSelectionListener(new TreeSelectionListener() {

			@Override
			public void valueChanged(TreeSelectionEvent arg0) {
				// arg0.getPath();
				// System.out.println(arg0.getPath().getLastPathComponent().getClass());
			
				if (WorkspaceLeafNode.class == arg0.getPath()
						.getLastPathComponent().getClass()) {
					WorkspaceLeafNode selected = (WorkspaceLeafNode) arg0
							.getPath().getLastPathComponent();
					File stl = selected.getTheSTLFile();
					File gcode = selected.getTheGCodeFile();
					System.out.print("Selection event fired");
					try {
						addPreview(stl);
					} catch (IOException e) {
						e.printStackTrace();
						statusLabel.setText("IO Error");
						errorDialog("Couldn't load file");
					}
				}
				
				
			}
			

		});

		leftTab.add("Navigator", fileNavigator);
		//leftTab.add("New Navigator",theDirectoryTree);//TODO

		printProgress = new JProgressBar();

		statusLabel = new JLabel("Welcome (Printer Not Connected)");

		bottomContainer.add(statusLabel);
		bottomContainer.add(printProgress);

	}

	public void workspaceNavigatorPrintHandler() {
	}

	public void toolbarPrintButtonHandler() {
		// TODO prompt user
		boolean reSlice = true;
		if (previewContainer.hasNoPreviews()) {
			this.statusLabel.setText("Nothing to print");
			this.errorDialog("Nothing to print!");
			return;
		}
		
		boolean rewrite = this.userPrompt("Rewrite STL with current Transforms?");
		File currentFile = null;
		System.out.println(rewrite);
		if(rewrite){
			currentFile = new File("tempTransform.stl");
			//currentFile.delete();
			if(!currentFile.exists())
				try {
					currentFile.createNewFile();
				} catch (IOException e) {
					this.statusLabel.setText("Rewrite failed");
					this.errorDialog("Rewrite failed!");
					e.printStackTrace();
					return;
				}
			STLObject tranObj = previewContainer.getCurrentPreview().getSTLObject().getTransformedSTLObject(previewContainer.getCurrentPreview().getTransform3D());
			ASCIISTLWriter aw =new ASCIISTLWriter(tranObj);
			try {
				this.statusLabel.setText("Rewriting new STL");
				aw.writeSTLToFile(currentFile);
			} catch (IOException e) {
				this.statusLabel.setText("Rewrite failed. Aborting print.");
				this.errorDialog("Rewrite failed!");
				e.printStackTrace();
				return;
			}
			
		}
		
		if(!rewrite) currentFile = previewContainer.getCurrentSTLFile();
		File currentGCodeFile = previewContainer.getCurrentGCodeFile();
		
		boolean isPrinting;
		if (reSlice)
			isPrinting= theGUIDriver.requestPrint(currentFile, currentGCodeFile);
		else
			isPrinting = theGUIDriver.requestPrint(currentGCodeFile);
		
		
		System.out.println("Printing file " + currentFile.getAbsolutePath());
	}

	public void cancelButtonHandler() {
		theGUIDriver.requestCancel();
	}

	private void connectButtonHandler() {
		theGUIDriver.connectPrinter();
	}

	public boolean addPreview(File f) throws IOException {

		File gcode = new File(f.getAbsolutePath() + ".gcode");
		
		return this.previewContainer.addPreview(f, gcode, workspaceDimensions);

	}

	@Override
	public boolean userPrompt(String prompt) {
		return (JOptionPane.showConfirmDialog(this, prompt, "",
				JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION) ? true
				: false;
	}

	@Override
	public void errorDialog(String errorMessage) {
		JOptionPane.showMessageDialog(this, errorMessage, "Error",
				JOptionPane.ERROR_MESSAGE);
	}

	@Override
	public void alertStatusUpdated() {
		this.statusLabel.setText(theGUIDriver.getStatusString());
		if (theGUIDriver.getCurrentDriverState() == GUIBackendInterface.DriverState.SLICING)
			this.printProgress.setOrientation(theGUIDriver.getSliceProgress());
		else
			this.printProgress.setOrientation(theGUIDriver.getPrintProgress());
	}

	@Override
	public boolean errorDialogWithFix(String errorMessage, String fixPrompt) {
		int op = JOptionPane.showConfirmDialog(this,errorMessage+"\n\n"+fixPrompt,"Error",JOptionPane.YES_NO_OPTION);
		return op==JOptionPane.YES_OPTION;
	}

}
