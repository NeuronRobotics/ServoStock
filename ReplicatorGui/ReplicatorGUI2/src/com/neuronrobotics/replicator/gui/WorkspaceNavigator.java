package com.neuronrobotics.replicator.gui;

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
import javax.swing.tree.MutableTreeNode;
import javax.swing.tree.TreeNode;
import javax.swing.tree.TreePath;

public class WorkspaceNavigator extends JTree{
	
	private WorkspaceFolderNode root;
	private File mainDirectory;
	
	private ArrayList<STLPreviewContainer> objects;
	private ArrayList<File> previewFiles;
	private ArrayList<String> previewNames;
	
	public static WorkspaceNavigator getNavigator(File mainDirectory){
		WorkspaceFolderNode root = new WorkspaceFolderNode(mainDirectory);
		
		FilenameFilter filter = new FilenameFilter(){
			@Override
			public boolean accept(File arg0, String arg1) {
				return arg1.endsWith(".stl");
			}
	
		};

		File[] allFiles = mainDirectory.listFiles();
		
		File[] theSTLFiles = mainDirectory.listFiles(filter);
		
		ArrayList<STLPreviewContainer> tempObjects = new ArrayList<STLPreviewContainer>();
		
		for(File f:theSTLFiles){
			File temp = new File(f.getName()+".sliced");
			STLPreviewContainer newObject = new STLPreviewContainer(f,temp,null);
			WorkspaceLeafNode newNode = new WorkspaceLeafNode(root,newObject);
			tempObjects.add(newObject);
		}
		
		WorkspaceNavigator theNavigator = new WorkspaceNavigator(root,mainDirectory);
		theNavigator.setRootVisible(true);
		//theNavigator.setEditable(true);		
		theNavigator.objects.addAll(tempObjects);
		 int x = 0;		
		 x=4;
		
		 theNavigator.treeDidChange();
		return theNavigator; 
	}
	/*
	private void addNode(WorkspaceLeafNode newNode) {
		if(newNode.getParent().equals(this.root)) return;
		newNode.setParent(this.root);
		root.addChild(newNode);
	}
	*/
	
	public WorkspaceNavigator(TreeNode root){
		super(root);
	}
	
	private WorkspaceNavigator(WorkspaceFolderNode root,File mainDirectory){
		super(root);
		this.root = root;
		this.mainDirectory = mainDirectory;
		objects = new ArrayList<STLPreviewContainer>();
		previewNames = new ArrayList<String>();
		previewFiles = new ArrayList<File>();
	}
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
