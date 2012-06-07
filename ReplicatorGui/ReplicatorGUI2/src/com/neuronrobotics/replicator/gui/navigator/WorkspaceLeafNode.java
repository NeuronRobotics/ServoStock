package com.neuronrobotics.replicator.gui.navigator;

import javax.swing.tree.DefaultMutableTreeNode;

public class WorkspaceLeafNode extends DefaultMutableTreeNode{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 356979118030363688L;

	public WorkspaceLeafNode(WorkspaceLeafNodeObject wlno){
		super(wlno);
		this.setAllowsChildren(false);
	}
	
	/*
	public boolean isLoaded(){
		return false;
	}
	*/

}
