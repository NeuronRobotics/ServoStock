package com.neuronrobotics.replicator.gui.navigator;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;

public class FileTransferable implements Transferable {

	final private List<File> files;
	final private DataFlavor[] flavors;
	
	public FileTransferable(File f){
		ArrayList<File> fs = new ArrayList<File>();
		fs.add(f);
		this.files = Collections.unmodifiableList(fs);
		this.flavors = new DataFlavor[] { DataFlavor.javaFileListFlavor };
	}

	public FileTransferable(Collection<File> files) {
		this.files = Collections.unmodifiableList(new ArrayList<File>(files));
		this.flavors = new DataFlavor[] { DataFlavor.javaFileListFlavor };
	}

	@Override
	public Object getTransferData(DataFlavor arg0)
			throws UnsupportedFlavorException, IOException {
		if(this.isDataFlavorSupported(arg0)) return this.files;
		return null;
	}
	
	public File getFile(){
		if(files.isEmpty()) return null;
		return files.get(0);
	}

	@Override
	public DataFlavor[] getTransferDataFlavors() {
		return flavors;
	}

	@Override
	public boolean isDataFlavorSupported(DataFlavor arg0) {
		return arg0.equals(DataFlavor.javaFileListFlavor);
	}

}
