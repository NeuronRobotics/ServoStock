package com.neuronrobotics.replicator.gui;

import javax.swing.tree.TreeNode;

public abstract class WorkspaceNode implements TreeNode {
	
	public abstract void setParent(WorkspaceFolderNode wn);

}
