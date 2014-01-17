package com.neuronrobotics.replicator.gui.preview;

import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;

import javax.swing.BorderFactory;
import javax.swing.JLayeredPane;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JPopupMenu;

import com.neuronrobotics.replicator.gui.preview.controller.DefaultSTLPreviewController;
import com.neuronrobotics.replicator.gui.preview.controller.STLPreviewMouseControlListener;
import com.neuronrobotics.replicator.gui.preview.j3d.OrientationIndicatorCanvas3D;
import com.neuronrobotics.replicator.gui.preview.model.DefaultSTLPreviewWorkspaceModel;
import com.neuronrobotics.replicator.gui.preview.model.STLWorkspaceModel;
import com.neuronrobotics.replicator.gui.preview.view.STLWorkspaceView;
import com.neuronrobotics.replicator.gui.preview.view.TestCanvas3D;
import com.neuronrobotics.replicator.gui.stl.STLLoader;
import com.neuronrobotics.replicator.gui.stl.STLObject;
import com.neuronrobotics.replicator.gui.stl.STLWorkspaceObject;

public class STLPreviewTab extends JLayeredPane implements STLPreviewMouseControlListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = -5559016123774970333L;

	private ArrayList<STLPreviewTabListener> theTabListeners;

	private boolean loaded, isDead;
	private File theSTLFile;

	private SimpleLoadingScreen theLoadingScreen;

	private STLWorkspaceModel theWorkspaceModel;
	private STLWorkspaceView theWorkspaceView;
	private DefaultSTLPreviewController theWorkspaceController;

	private LoadPreviewThread theLoadingThread;

	private JPanel indicatorPanel;

	private final JPanel canvasLayer = new JPanel(),
			loadingScreenLayer = new JPanel();

	private File theWorkspaceSTLFile;

	public STLPreviewTab(String name, File wstl) {
		loaded = false;
		isDead = false;

		theTabListeners = new ArrayList<STLPreviewTabListener>();
		theWorkspaceSTLFile = wstl;
		theSTLFile = null;
		// theSTLPreview = null;
		theLoadingScreen = new SimpleLoadingScreen(
				name + " preview loading...", true);
		// this.setLayout(new GridLayout(1,1));
		theLoadingThread = null;

		this.setName(name);

		loadingScreenLayer.setLayout(new GridLayout(1, 1));
		// overlayLayer.setLayout(new GridLayout(1,1));
		canvasLayer.setLayout(new GridLayout(1, 1));

		// this.add

		this.add(loadingScreenLayer);
		// this.add(overlayLayer,150);
		this.add(canvasLayer);
	}

	public STLPreviewTab(File stl, File wstl) {
		this(stl.getName(), wstl);
		theSTLFile = stl;
		// theSTLPreview = null;
	}

	public STLPreviewTab(STLPreviewTabListener stlc, File stl, File wstl) {
		this(stl, wstl);
		theTabListeners.add(stlc);
	}

	public void addTabListener(STLPreviewTabListener sptl) {
		this.theTabListeners.add(sptl);
	}

	public void load() {
		if (!loaded) {
			loadingScreenLayer.setSize(this.getSize());
			canvasLayer.setSize(this.getSize());
			// this.removeAll();

			// this.add(theLoadingScreen);
			loadingScreenLayer.add(theLoadingScreen);
			loadingScreenLayer.setVisible(true);

			if (theLoadingThread == null) {
				theLoadingThread = new LoadPreviewThread(theLoadingScreen,
						theSTLFile, theWorkspaceSTLFile);
			}

			theLoadingThread.start();
		}
	}

	public void reload() {
		loaded = false;
		this.removeAll();
		// this.add(theLoadingScreen);
		loadingScreenLayer.setVisible(true);
		theLoadingThread = null;
		// theSTLPreview= null;

		this.theWorkspaceModel = null;
		this.theWorkspaceController = null;
		this.theWorkspaceView = null;

		load();
	}

	private void alertPreviewLoaded(STLWorkspaceModel tempNewModel,
			STLWorkspaceView tempNewView,
			DefaultSTLPreviewController tempNewController) {
		loadingScreenLayer.setVisible(false);
		loaded = true;

		this.theWorkspaceModel = tempNewModel;
		this.theWorkspaceView = tempNewView;
		this.theWorkspaceController = tempNewController;
		
		this.theWorkspaceController.getSTLPreviewMouseController().addSTLPreviewMouseControlListener(this);
		this.theWorkspaceController.placeAllObjectsOnWorkspace();
		
		canvasLayer.add(this.theWorkspaceView.getComponent());

		final OrientationIndicatorCanvas3D theind = new OrientationIndicatorCanvas3D();
		this.theWorkspaceView.addViewListener(theind);
		

		indicatorPanel = new JPanel();
		indicatorPanel.setSize(100, 100);
		indicatorPanel.setLayout(new GridLayout(1, 1));
		indicatorPanel.setBorder(BorderFactory.createLineBorder(Color.gray));


		indicatorPanel.add(theind);
		this.add(indicatorPanel, 0);
		this.moveToFront(this.theWorkspaceView.getComponent());
		this.moveToFront(theind);

		layoutControlLayer();

		this.addComponentListener(new ComponentListener() {

			@Override
			public void componentHidden(ComponentEvent arg0) {
			}

			@Override
			public void componentMoved(ComponentEvent arg0) {
			}

			@Override
			public void componentResized(ComponentEvent arg0) {
				layoutControlLayer();
			}

			@Override
			public void componentShown(ComponentEvent arg0) {
			}
		});

		validate();

		for (STLPreviewTabListener sptl : theTabListeners)
			sptl.alertTabIsLoaded(this);

		theLoadingThread = null;
	}

	private void layoutControlLayer() {
		// int xS = getSize().width;
		int yS = getSize().height;
		indicatorPanel.setLocation(5, yS - 105);
		// testButton.setLocation(5, indicatorPanel.getY()-50);
		// testButton2.setLocation(60, indicatorPanel.getY()-50);
	}

	public STLWorkspaceView getTheMotherfuckingView() {
		return this.theWorkspaceView;
	}

	public STLWorkspaceModel getTheMotherFuckingModel() {
		return this.theWorkspaceModel;
	}

	public DefaultSTLPreviewController getTheMotherFuckingController() {
		return this.theWorkspaceController;
	}

	private void alertTabIsDead(Exception e) {
		isDead = true;
		for (STLPreviewTabListener sptl : theTabListeners)
			sptl.alertTabIsDead(this);
	}

	public boolean isDead() {
		return isDead;
	}

	public boolean isLoaded() {
		return loaded;
	}

	public void alertSTLObjectAdded(){
		theWorkspaceController.placeAllObjectsOnWorkspace();
	}
	
	public void alertRightClick(int x, int y) {

		JPopupMenu popup = new JPopupMenu();

		final STLObject currPick = this.theWorkspaceView.getPick();

		if (currPick == null) {
			popup.add(new JMenuItem("Basic"));
		} else {

			JMenuItem remove = new JMenuItem("Remove");
			remove.addActionListener(new ActionListener() {

				@Override
				public void actionPerformed(ActionEvent arg0) {
					removeCurrentModel(currPick);
				}
			});
			popup.add(remove);
			JMenuItem duplicate = new JMenuItem("Duplicate");
			duplicate.addActionListener(new ActionListener() {

				@Override
				public void actionPerformed(ActionEvent e) {
					duplicateCurrentModel(currPick);
				}

			});
			popup.add(duplicate);

			JMenuItem resetTransforms = new JMenuItem("Reset Transforms");
			resetTransforms.addActionListener(new ActionListener() {

				@Override
				public void actionPerformed(ActionEvent e) {
					resetCurrentModel(currPick);
				}
			});
			popup.add(resetTransforms);

			JMenuItem reorient = new JMenuItem("Reorient");
			reorient.addActionListener(new ActionListener() {

				@Override
				public void actionPerformed(ActionEvent e) {
					orientNextFace(currPick);
				}

			});
			popup.add(reorient);
			
			JMenuItem debug = new JMenuItem("Debug");
			debug.addActionListener(new ActionListener() {

				@Override
				public void actionPerformed(ActionEvent e) {
					printDebugDetails(currPick);
				}

			});
			popup.add(debug);
			

		}
		popup.show(this, x, y);
	}

	protected void printDebugDetails(STLObject currPick) {
		System.out.println("DEBUG STUFF");
		double[] result = new double[3];		
		this.theWorkspaceModel.getCurrMins(currPick, result);	
		System.out.println("Curr Mins: "+Arrays.toString(result));
		STLWorkspaceObject temp = this.theWorkspaceModel.getWorkspaceObject();
		if(temp!=null){
			System.out.println(temp.getSurfaceY());
		}
		System.out.println("END DEBUG DETAILS");
	}

	private void orientNextFace(STLObject currPick) {
		this.theWorkspaceController.orientNextFace(currPick);
		this.theWorkspaceController.placeAllObjectsOnWorkspace();
	}

	private void resetCurrentModel(STLObject currPick) {
		this.theWorkspaceController.resetCurrentModel(currPick);
		this.theWorkspaceController.placeAllObjectsOnWorkspace();
	}

	private void removeCurrentModel(STLObject currPick) {
		this.theWorkspaceModel.removeSTLObject(currPick);
	}

	private void duplicateCurrentModel(STLObject currPick) {
		STLObject newObj = currPick.clone();
		
		this.theWorkspaceModel.addSTLObject(newObj);
		this.theWorkspaceController.placeAllObjectsOnWorkspace();
	}

	private class LoadPreviewThread extends Thread {

		// SimpleLoadingScreen theLoadingScreen;
		File stl;
		File workspaceSTL;

		public LoadPreviewThread(SimpleLoadingScreen sls, File stl, File wstl) {
			super();
			// theLoadingScreen = sls;
			this.stl = stl;
			this.workspaceSTL = wstl;
			// currentlyLoading.add(stl);

		}

		@Override
		public void run() {

			try {
				// STLPreviewCanvas3D tempPreview;
				STLWorkspaceView tempNewView;
				STLWorkspaceModel tempNewModel = new DefaultSTLPreviewWorkspaceModel();

				if (stl != null) {
					// tempPreview = new STLPreviewCanvas3D(stl, workspaceSTL);
					tempNewModel.addSTLObject(STLLoader.loadFile(stl));
				} else {
					// tempPreview = new STLPreviewCanvas3D(workspaceSTL);
				}

				if (workspaceSTL != null) {
					tempNewModel.setWorkspace(new STLWorkspaceObject(STLLoader
							.loadFile(workspaceSTL)));
				}

				tempNewView = new TestCanvas3D(tempNewModel);
				DefaultSTLPreviewController tempNewController = new DefaultSTLPreviewController(
						tempNewView, tempNewModel);

				// tempPreview.loadFromQueue();

				alertPreviewLoaded(tempNewModel, tempNewView, tempNewController);
			} catch (Exception e) {
				e.printStackTrace();
				alertTabIsDead(e);
			}
		}

	}

}
