package com.neuronrobotics.replicator.gui.navigator;

import java.io.File;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Enumeration;

import javax.swing.tree.MutableTreeNode;
import javax.swing.tree.TreeNode;


public class WorkspaceFolderNode implements MutableTreeNode{
	
	private File directory;
	
	private WorkspaceFolderNode parent;
	private ArrayList<MutableTreeNode> children;
	
	public WorkspaceFolderNode(File d){
		this.directory = d;
		children = new ArrayList<MutableTreeNode>();
		this.parent = null;
	}
	
	public WorkspaceFolderNode(WorkspaceFolderNode p,File d){
		this.directory=d;
		this.parent=p;
		children = new ArrayList<MutableTreeNode>();
	}
	
	public Iterable<MutableTreeNode> getChildren(){
		return children;
	}

	@Override
	public Enumeration children() {
		return Collections.enumeration(children);
	}

	@Override
	public boolean getAllowsChildren() {
		return true;
	}

	@Override
	public TreeNode getChildAt(int childIndex) {
		return (TreeNode)children.get(childIndex);
	}

	@Override
	public int getChildCount() {
		return children.size();
	}

	@Override
	public int getIndex(TreeNode node) {
		return children.indexOf(node);
	}

	@Override
	public TreeNode getParent() {
		return parent;
	}

	@Override
	public boolean isLeaf() {
		return false;
	}
	
	public String toString(){
		return this.directory.getName();
	}

	@Override
	public void insert(MutableTreeNode child, int index) {
		children.add(index,child);		
	}
	
	public void insert(MutableTreeNode wn){
		children.add(wn);
	}

	@Override
	public void remove(int index) {
		this.children.remove(index);		
	}

	@Override
	public void remove(MutableTreeNode node) {
		this.children.remove(node);		
	}
	
	public boolean remove(WorkspaceFolderNode child){
		return children.remove(child);
	}
	
	public boolean remove(WorkspaceLeafNode child){
		return children.remove(child);
	}	

	@Override
	public void removeFromParent() {
		//this.parent.remove(this);
		this.parent=null;
		
	}

	@Override
	public void setParent(MutableTreeNode newParent) {
		this.parent = (WorkspaceFolderNode)newParent;
	}
	
	public void setParent(WorkspaceFolderNode fn){
		parent.remove(this);
		//TODO maybe want to actually move files around
		parent=fn;
	}

	@Override
	public void setUserObject(Object object) {
		//TODO		
	}

}
