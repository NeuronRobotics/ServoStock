package com.neuronrobotics.replicator.gui;


import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Enumeration;

import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.MutableTreeNode;
import javax.swing.tree.TreeNode;

public class WorkspaceLeafNode extends WorkspaceNode{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 883748291178354077L;
	
	private STLPreviewContainer object;
	private WorkspaceFolderNode parent;
	
	public WorkspaceLeafNode(WorkspaceFolderNode p,STLPreviewContainer obj){
		this.parent = p;
		if(this.parent!=null) parent.addChild(this); 
		this.object = obj;
	}
	
	public File getTheSTLFile() {
		return object.getSTL();
	}

	public File getTheGCodeFile() {
		return object.getGCode();
	}
	
	public Preview3D getPreview(){
		return object.getPreview();
	}

	public String toString(){
		return object.getSTL().getName();
	}

	@Override
	public Enumeration children() {
		return null;
	}

	@Override
	public boolean getAllowsChildren() {
		return false;
	}

	@Override
	public TreeNode getChildAt(int arg0) {
		return null;
	}

	@Override
	public int getChildCount() {
		return 0;
	}

	@Override
	public int getIndex(TreeNode arg0) {
		return -1;
	}

	@Override
	public TreeNode getParent() {
		return parent;
	}

	@Override
	public boolean isLeaf() {
		return true;
	}

	@Override
	public void setParent(WorkspaceFolderNode wn) {
		if(parent!=null) parent.removeChild(this);
		parent = wn;
	}
	
}
