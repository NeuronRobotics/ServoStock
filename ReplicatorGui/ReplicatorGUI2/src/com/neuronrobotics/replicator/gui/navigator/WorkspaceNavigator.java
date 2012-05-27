package com.neuronrobotics.replicator.gui.navigator;

import java.io.File;
import java.io.FilenameFilter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Enumeration;
import java.util.Hashtable;

import javax.swing.JTree;
import javax.swing.filechooser.FileFilter;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.MutableTreeNode;
import javax.swing.tree.TreeNode;
import javax.swing.tree.TreePath;


public class WorkspaceNavigator extends JTree{
	
	private WorkspaceFolderNode root;
	private File mainDirectory;
	
	
	public static WorkspaceNavigator getNavigator(File mainDirectory){
		WorkspaceFolderNode root = new WorkspaceFolderNode(mainDirectory);
		
		FilenameFilter filter = new FilenameFilter(){
			@Override
			public boolean accept(File arg0, String arg1) {
				return arg1.endsWith(".stl");
			}
	
		};
		
		DefaultTreeModel dtm = new DefaultTreeModel(root);

		File[] allFiles = mainDirectory.listFiles();
		
		File[] theSTLFiles = mainDirectory.listFiles(filter);
		
		
		for(File f:theSTLFiles){
			File temp = new File(f.getName()+".gcode");
			
			WorkspaceLeafNode newNode = new WorkspaceLeafNode(root,f,temp);
			//tempObjects.add(newObject);
		}
		
		WorkspaceNavigator theNavigator = new WorkspaceNavigator(dtm,mainDirectory);
		theNavigator.setRootVisible(true);
		//theNavigator.setEditable(true);
		
		theNavigator.setSize(theNavigator.getMaximumSize());
		
		 theNavigator.treeDidChange();
		return theNavigator; 
	}
		
	public WorkspaceNavigator(TreeNode root){
		super(root);
	}
	
	private WorkspaceNavigator(WorkspaceFolderNode root,File mainDirectory){
		super(root);
		this.root = root;
		this.mainDirectory = mainDirectory;
		treeModel = new DefaultTreeModel(root);
		((DefaultTreeModel)treeModel).reload();
	}
	
	private WorkspaceNavigator(DefaultTreeModel dtm,File mainDirectory){
		super(dtm);
		this.root = (WorkspaceFolderNode) dtm.getRoot();
		this.mainDirectory = mainDirectory;
		treeModel = new DefaultTreeModel(root);
		((DefaultTreeModel)treeModel).reload();
	}
	
	public void addTestNode(){
		((DefaultTreeModel)treeModel).insertNodeInto(new DefaultMutableTreeNode("Blah"), root, 0);
		//((DefaultTreeModel)treeModel).reload();
	}
	
	/*
	private void addNode(WorkspaceLeafNode newNode) {
		if(newNode.getParent().equals(this.root)) return;
		newNode.setParent(this.root);
		root.addChild(newNode);
	}
	*/
	
	/*
	public boolean addFolder(String name){
		return false; //TODO
	}
	
	public boolean addFile(TreePath path, String fileName){
		return false;
	}
	
	public boolean addFile(String name){
		if (previewNames.contains(name)){ 
			System.out.println("Name is already taken");
			return false;
		}
		
		STLPreviewContainer tempCont;
		
		File tempFile = new File(mainDirectory.getAbsolutePath()+"\\"+name);
		if (!tempFile.exists())
			try {
				tempFile.createNewFile();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				return false;
			}		
			previewNames.add(name);
			previewFiles.add(tempFile);
			tempCont = new STLPreviewContainer(tempFile,null,null);
			WorkspaceLeafNode newPreview = new WorkspaceLeafNode(root,tempCont);
			return true;
	}
	

	public WorkspaceFolderNode getTreeRoot() {
		return root;
	}
	
	*/
	
	
}
