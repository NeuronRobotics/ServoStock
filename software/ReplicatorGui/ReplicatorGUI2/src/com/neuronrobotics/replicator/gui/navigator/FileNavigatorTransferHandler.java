package com.neuronrobotics.replicator.gui.navigator;
import java.awt.datatransfer.Transferable;
 
import javax.swing.*;
import javax.swing.tree.DefaultTreeModel;

import com.neuronrobotics.replicator.gui.navigator.FileNavigator;
 
/**
 * @author helloworld922
 *         <p>
 * @version 1.0
 *          <p>
 *          copyright 2010 <br>
 * 
 *          You are welcome to use/modify this code for any purposes you want so
 *          long as credit is given to me.
 */
public class FileNavigatorTransferHandler extends TransferHandler
{
	/**
	 * Using tree models allows us to add/remove nodes from a tree and pass the
	 * appropriate messages.
	 */
	protected DefaultTreeModel tree;
	protected FileNavigator fn;
	/**
	 * 
	 */
	private static final long serialVersionUID = -6851440217837011463L;
 
	/**
	 * Creates a JTreeTransferHandler to handle a certain tree. Note that this
	 * constructor does NOT set this transfer handler to be that tree's transfer
	 * handler, you must still add it manually.
	 * 
	 * @param tree
	 */
	public FileNavigatorTransferHandler(FileNavigator tree)
	{
		super();
		this.tree = (DefaultTreeModel) tree.getModel();
		fn = tree;
	}
 
	/**
	 * 
	 * @param c
	 * @return
	 */
	@Override
	public int getSourceActions(JComponent c)
	{
		return TransferHandler.COPY;
	}
 
	/**
	 * 
	 * @param c
	 * @return null if no nodes were selected, or this transfer handler was not
	 *         added to a DnDJTree. I don't think it's possible because of the
	 *         constructor layout, but one more layer of safety doesn't matter.
	 */
	@Override
	protected Transferable createTransferable(JComponent c)
	{
		if (c instanceof FileNavigator)
		{
			return new FileTransferable(((FileNavigator) c).getSelectedSTLFile());
		}
		else
		{
			return null;
		}
	}

}