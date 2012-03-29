package com.neuronrobotics.replicator.driver;


public class SliceStatusData {
	
	
	/**
	 * This enum should be used to report on state of the slicer
	 * SLICING indicates the slicer is working and there is no problem
	 * ERROR indicates the slicer has had a problem and should terminate the slice
	 * WARNING_SLICING indicates a possible problem detected but the slice has not been terminated
	 * WARNING_DONE indicates the slice has terminated with a warning
	 * SUCCESS indicates slice has terminated with no warnings or errors
	 * NOTE: option to set messages for the state. Recommended for ERROR and WARNING
	 * or might be better to define more specific types?
	 */
	public enum SlicerState {
		SLICING, ERROR, WARNING_DONE,WARNING_SLICING, SUCCESS;
		private String message;
		
		private void setMessage(String m) {
			message = m;
		}

		public String getMessage() {
			return message;
		}

		public boolean hasMessage() {
			return message != null;
		}
	};

	private int layers;
	
	private int sliceProgress;
	
	private SlicerState currentSlicerState;
	
	/**
	 * Constructor that leaves state message blank
	 * @param layers
	 * @param sliceProgress
	 * @param currentSlicerState
	 */
	public SliceStatusData(int layers, int sliceProgress, SlicerState currentSlicerState){
		this.layers = layers;
		this.sliceProgress = sliceProgress;
		this.currentSlicerState = currentSlicerState;
	}
	/**
	 * Constructor with ability to set state message
	 * @param layers
	 * @param sliceProgress
	 * @param currentSlicerState
	 * @param stateMessage
	 */
	public SliceStatusData(int layers, int sliceProgress, SlicerState currentSlicerState, String stateMessage){
		this.layers = layers;
		this.sliceProgress = sliceProgress;
		this.currentSlicerState = currentSlicerState;
		this.currentSlicerState.setMessage(stateMessage);
	}
	
	/**
	 * This should return the amount of layers needed to print the current object
	 * May or may not be useful/accurate depending on whether slice has completed 
	 * @return current calculated amount of layers
	 */
	public int getLayers(){
		return layers;
	}
	
	/**
	 * sliceProgress should be an integer between 0 and 100 specifiying how far
	 * along in the slice we are
	 * @return sliceProgress
	 */
	public int getSliceProgress(){
		return sliceProgress;
	}
	
	public SlicerState getCurrentSlicerState(){
		return currentSlicerState;
	}

}
