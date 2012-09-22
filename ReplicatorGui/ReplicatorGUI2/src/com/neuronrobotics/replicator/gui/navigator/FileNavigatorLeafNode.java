package com.neuronrobotics.replicator.gui.navigator;

import javax.swing.tree.DefaultMutableTreeNode;

public class FileNavigatorLeafNode extends DefaultMutableTreeNode{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 356979118030363688L;

	public FileNavigatorLeafNode(FileNavigatorLeafNodeObject wlno){
		super(wlno);
		this.setAllowsChildren(false);
	}
	
	/*
	public boolean isLoaded(){
		return false;
	}
	*/

}
