package com.neuronrobotics.replicator.gui;

import java.io.File;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Enumeration;

import javax.swing.tree.TreeNode;

public class WorkspaceFolderNode extends WorkspaceNode{
	
	private File directory;
	
	private WorkspaceFolderNode parent;
	private ArrayList<WorkspaceNode> children;
	
	public WorkspaceFolderNode(File d){
		this.directory = d;
		children = new ArrayList<WorkspaceNode>();
		this.parent = null;
	}
	
	public WorkspaceFolderNode(WorkspaceFolderNode p,File d){
		this.directory=d;
		this.parent=p;
		children = new ArrayList<WorkspaceNode>();
	}
	
	public void setParent(WorkspaceFolderNode fn){
		parent.removeChild(this);
		//TODO maybe want to actually move files around
		parent=fn;
	}
	
	public boolean removeChild(WorkspaceNode child){
		//TODO maybe want to actually move files around?
		return children.remove(child);
	}
	
	public boolean addChild(WorkspaceNode wn){
		return children.add(wn);
	}
	
	public Iterable<WorkspaceNode> getChildren(){
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

}
