package com.neuronrobotics.replicator.driver;

public class MaterialData {
	public StlSlicer getSlicerForConfig() {
		throw new RuntimeException("No slicer found for untyped MaterialData");
	}
}
