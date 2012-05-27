package com.neuronrobotics.replicator.gui.navigator;

import javax.swing.tree.MutableTreeNode;
import javax.swing.tree.TreeNode;


public abstract class WorkspaceNode implements MutableTreeNode {
	
	public abstract void setParent(WorkspaceFolderNode wn);

}
