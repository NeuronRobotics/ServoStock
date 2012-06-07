package com.neuronrobotics.replicator.gui.navigator;

import javax.swing.tree.DefaultMutableTreeNode;

public class WorkspaceFolderNode extends DefaultMutableTreeNode{

	/**
	 * 
	 */
	private static final long serialVersionUID = 2723295072493525605L;

	public WorkspaceFolderNode(WorkspaceFolderNodeObject newObject) {
		super(newObject);
	}

	@Override
	public boolean isLeaf(){
		return false;
	}

}
