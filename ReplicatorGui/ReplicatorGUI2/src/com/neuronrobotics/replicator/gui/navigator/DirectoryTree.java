package com.neuronrobotics.replicator.gui.navigator;

import java.io.File;
import java.io.FilenameFilter;
import java.util.ArrayList;
import java.util.Enumeration;

import javax.swing.JTree;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.MutableTreeNode;
import javax.swing.tree.TreeNode;

public class DirectoryTree extends JTree {
	
	private File mainDirectory;
	private MutableTreeNode theRoot;

	public static DirectoryTree getDirectoryTree(File mainDir){
		
		DefaultMutableTreeNode root = new DefaultMutableTreeNode(mainDir);
		
		
		FilenameFilter filter = new FilenameFilter(){
			@Override
			public boolean accept(File arg0, String arg1) {
				return arg1.endsWith(".stl");
			}
	
		};
		
		
		
		DefaultTreeModel dtm = new DefaultTreeModel(root);
		DirectoryTree theDirectoryTree = new DirectoryTree(dtm);
		
		theDirectoryTree.theRoot = root;
		
		
		File mainDirectory = mainDir;
		
		File[] allFiles = mainDirectory.listFiles();
		
		File[] theSTLFiles = mainDirectory.listFiles(filter);
		
		
		for(File f:theSTLFiles){
			File temp = new File(f.getName()+".gcode");
			DefaultMutableTreeNode newNode = new DefaultMutableTreeNode(temp);
			dtm.insertNodeInto(newNode, root, 0);
			//WorkspaceLeafNode newNode = new WorkspaceLeafNode(root,f,temp);
			//tempObjects.add(newObject);
		}
		
		//WorkspaceNavigator theNavigator = new WorkspaceNavigator(dtm,mainDirectory);
		//theNavigator.setRootVisible(true);
		//theNavigator.setEditable(true);
		
		//theNavigator.setSize(theNavigator.getMaximumSize());
		
		theDirectoryTree.treeDidChange();
		return theDirectoryTree; 
		
	}
	
	private DirectoryTree(DefaultTreeModel tm){
		super(tm);
	}
	
	public void testNode(){
		DefaultMutableTreeNode newChild = new DefaultMutableTreeNode("test worked");
		((DefaultTreeModel)treeModel).insertNodeInto(newChild , theRoot, 0);
	}
	

}
