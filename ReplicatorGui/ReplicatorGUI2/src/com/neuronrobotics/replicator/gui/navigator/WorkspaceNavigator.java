package com.neuronrobotics.replicator.gui.navigator;

//import java.awt.Component;
import java.io.File;
import java.io.FilenameFilter;
import java.io.IOException;
import java.nio.file.FileSystem;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;
//import java.nio.file.FileSystems;
//import java.nio.file.Path;
import java.util.LinkedList;


//import java.util.ArrayList;
//import java.util.Enumeration;

import javax.swing.JTree;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.DefaultMutableTreeNode;
//import javax.swing.tree.DefaultTreeCellRenderer;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreePath;
//import javax.swing.tree.MutableTreeNode;
//import javax.swing.tree.TreeNode;
//import javax.swing.tree.TreeCellRenderer;

public class WorkspaceNavigator extends JTree implements TreeSelectionListener {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 5148061626146938126L;
	
	//private File mainDirectory;
	private WorkspaceFolderNode theRoot;
	private DefaultMutableTreeNode currentNode;
	
	private LinkedList<WorkspaceNavigatorListener> theDirectoryTreeListeners;

	public static WorkspaceNavigator getDirectoryTree(File mainDirectory){
		
		if(!mainDirectory.isDirectory()) throw new IllegalArgumentException(); 
		//TODO handle this better
		
		WorkspaceFolderNodeObject rootObject = new WorkspaceFolderNodeObject(mainDirectory);
		WorkspaceFolderNode root = new WorkspaceFolderNode(rootObject);
		
		FilenameFilter dirFilter = new FilenameFilter(){

			@Override
			public boolean accept(File arg0, String arg1) {
				File testF = new File(arg0.getAbsolutePath()+"\\"+arg1);
				return testF.isDirectory();
			}
			
		};
		
		FilenameFilter filter = new FilenameFilter(){
			@Override
			public boolean accept(File arg0, String arg1) {
				return arg1.endsWith(".stl");
			}
	
		};	
		
		DefaultTreeModel dtm = new DefaultTreeModel(root);
		WorkspaceNavigator theDirectoryTree = new WorkspaceNavigator(dtm);
		
		
		theDirectoryTree.theRoot = root;
		
		//theDirectoryTree.mainDirectory = mainDirectory;
				
		//File mainDirectory = mainDir;
		
		File[] directoryFiles = mainDirectory.listFiles(dirFilter);
		
		File[] theSTLFiles = mainDirectory.listFiles(filter);
		
		int ct=0;
		for(File f:theSTLFiles){
			File temp = new File(f.getName()+".gcode");
			WorkspaceLeafNodeObject tempObj = new WorkspaceLeafNodeObject(f,temp);
			WorkspaceLeafNode newNode = new WorkspaceLeafNode(tempObj);
			//newNode.setUserObject(tempObj);
			dtm.insertNodeInto(newNode, root, ct++);
		}
		
		//TODO doesn't add contents of subdirectories yet
		ct=0;
		for(File d:directoryFiles){
			if(d.getName().contains(".svn")) continue; //Ignore .svn folder when testing
			WorkspaceFolderNodeObject tempObj = new WorkspaceFolderNodeObject(d);
			WorkspaceFolderNode newNode = new WorkspaceFolderNode(tempObj);
			dtm.insertNodeInto(newNode, root, ct++);
		}
	
		//theDirectoryTree.setExpandedState(, true);
		
		//DefaultTreeCellRenderer dtcr = (DefaultTreeCellRenderer)theDirectoryTree.getCellRenderer();
		
		
		TreePath tp = new TreePath(root.getPath());
		theDirectoryTree.setExpandedState(tp, true);
		
		theDirectoryTree.setRootVisible(false);
		
		theDirectoryTree.treeDidChange();
		return theDirectoryTree; 
		
	}
		
	
	private WorkspaceNavigator(DefaultTreeModel tm){
		super(tm);
		addTreeSelectionListener(this);
		currentNode = null;
		theDirectoryTreeListeners = new LinkedList<WorkspaceNavigatorListener>();
	}
	
	/*
	public void linkNewFolder(String newFullFileName){
		linkNewFolder(theRoot,newFullFileName);
	}
	
	public void linkNewFolder(DefaultMutableTreeNode parent,String newFullFileName){
		//TODO
		
	}
	 */
	
	public void addNewFolder(String folderName) throws FileNotDirectoryException, IOException{
		addNewFolder(theRoot,folderName);		
	}
	
	public void addNewFolder(WorkspaceFolderNode parent, String folderName) throws FileNotDirectoryException, IOException{
		//TODO not very robust
		String newName = ((WorkspaceFolderNodeObject)(parent.getUserObject())).getTheDirectory().getAbsolutePath()+"\\"+folderName;
		File newFolder = new File(newName);
		if(newFolder.exists()&&!newFolder.isDirectory()) throw new FileNotDirectoryException();
		else if(!newFolder.exists()) {
			//newFolder.createNewFile();
			newFolder.mkdir();
		}
		
		WorkspaceFolderNodeObject newObject = new WorkspaceFolderNodeObject(newFolder);
		WorkspaceFolderNode newNode = new WorkspaceFolderNode(newObject);
		
				
		((DefaultTreeModel)treeModel).insertNodeInto(newNode, parent, parent.getChildCount());
	
		/*
		WorkspaceFolderNodeObject newObject2 = new WorkspaceFolderNodeObject(newFolder);
		DefaultMutableTreeNode newNode2 = new DefaultMutableTreeNode(newObject);
		((DefaultTreeModel)treeModel).insertNodeInto(newNode2, newNode, newNode.getChildCount());
		*/
	}
	
	public void copyInSTLFile(String name) throws IOException{
		File stl = new File(name);
		copyInSTLFile(theRoot,stl);
	}
	
	public void copyInSTLFile(File stl) throws IOException{
		copyInSTLFile(theRoot,stl);
	}
	
	public void copyInSTLFile(WorkspaceFolderNode parent, File stl) throws IOException{
		
		//TODO missing packages necessary to copy files\
		String pathName = ((WorkspaceFolderNodeObject)parent.getUserObject()).getTheDirectory().getAbsolutePath()+"\\"+stl.getName();
		
		Path outPath = FileSystems.getDefault().getPath(pathName);
		
		Path inPath = stl.toPath();
		
		Files.copy(inPath, outPath);	
		
		File newSTL = outPath.toFile();
		
		//((WorkspaceFolderNodeObject)parent.getUserObject()).getTheDirectory();
		
		File gcode = new File(stl.getAbsolutePath()+".gcode");
						
		WorkspaceLeafNodeObject newObject = new WorkspaceLeafNodeObject(newSTL,gcode);
		
		WorkspaceLeafNode newChild = new WorkspaceLeafNode(newObject);
		
		((DefaultTreeModel)this.treeModel).insertNodeInto(newChild, parent, parent.getChildCount());
	}
	
	
	
	/*
	public void testNode(){
		DefaultMutableTreeNode newChild = new DefaultMutableTreeNode("test worked");
		((DefaultTreeModel)treeModel).insertNodeInto(newChild , theRoot, 0);
	}*/
	
	public File getSelectedSTLFile(){
		if(currentNode==null) return null; //TODO throw exception?
		Object obj = currentNode.getUserObject();		
		if(!obj.getClass().equals(WorkspaceLeafNodeObject.class)) return null;
		
		return ((WorkspaceLeafNodeObject)obj).getTheSTLFile();
	}
	
	public File getSelectedGCodeFile(){
		if(currentNode==null) return null; //TODO throw exception?
		Object obj = currentNode.getUserObject();		
		if(!obj.getClass().equals(WorkspaceLeafNodeObject.class)) return null;
		
		return ((WorkspaceLeafNodeObject)obj).getTheGCodeFile();
	}

	@Override
	public void valueChanged(TreeSelectionEvent arg0) {
		currentNode = (DefaultMutableTreeNode)arg0.getPath().getLastPathComponent();
		if(currentNode.getUserObject().getClass().equals(WorkspaceLeafNodeObject.class)){
			notifyListenersLeafSelected();
		} else if(currentNode.getUserObject().getClass().equals(WorkspaceFolderNodeObject.class)){
			notifyListenersFolderSelected();
		} 
	}
	
	private void notifyListenersLeafSelected() {
		for(WorkspaceNavigatorListener dtl:this.theDirectoryTreeListeners) dtl.alertDirectoryLeafSelected();	
	}
	
	private void notifyListenersFolderSelected() {
		for(WorkspaceNavigatorListener dtl:this.theDirectoryTreeListeners) dtl.alertDirectoryFolderSelected();	
	}

	public void addDirectoryTreeListener(WorkspaceNavigatorListener dtl){
		if(!this.theDirectoryTreeListeners.contains(dtl)) theDirectoryTreeListeners.add(dtl);
	}

}
