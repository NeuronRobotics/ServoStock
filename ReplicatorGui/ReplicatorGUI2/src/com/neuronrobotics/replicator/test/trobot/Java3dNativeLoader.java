package com.neuronrobotics.replicator.test.trobot;

import java.io.File;
import java.io.FileOutputStream;
import java.io.FilePermission;
import java.io.IOException;
import java.io.InputStream;
import java.security.AccessController;
import java.util.ArrayList;

import com.neuronrobotics.sdk.common.Log;

public class Java3dNativeLoader {
	private static boolean loaded = false;
	
	public static void load(){
		if(loaded)
			return;
//		String path = System.getProperty("java.library.path");
//		System.out.println("Path is: "+path);	
//		String [] paths = path.split("\\:");
//		ArrayList<String> accessiable = new ArrayList<String>();
//		for(int i=0;i<paths.length;i++){
//			try
//			{
//			     /*
//			      * Create and delete a dummy file in order to check file permissions. Maybe 
//			      * there is a safer way for this check.
//			      */
//				File sample = new File(paths[i],"empty.txt"); 
//				sample.createNewFile();
//				sample.delete();
//				accessiable.add(paths[i]);
//			}
//			catch(IOException e)
//			{
//			      //Error message shown to user. Operation is aborted
//			}
//		}
//		if(accessiable.size()==0){
//			System.err.println("No path accessiable");
//		}
		
		
		
//		if(OSUtil.isOSX()) {
//			Log.warning("OSX has no native lib defined");
//		}else{
//			if(OSUtil.isWindows()) {
//				if(OSUtil.is64Bit()){
//					new Java3dNativeLoader().loadLib("j3dcore-ogl");
//				}else {
//					new Java3dNativeLoader().loadLib("j3dcore-ogl");
//					//new Java3dNativeLoader().loadLib("j3dcore-d3d");
//					//new Java3dNativeLoader().loadLib("j3dcore-ogl-cg");
//					//new Java3dNativeLoader().loadLib("j3dcore-ogl-chk");
//				}
//			}else if(OSUtil.isLinux()) {
//
//				if(OSUtil.is64Bit()) {
//					new Java3dNativeLoader().loadLib("libj3dcore-ogl");
//				}else {
//					new Java3dNativeLoader().loadLib("libj3dcore-ogl");
//					//new Java3dNativeLoader().loadLib("libj3dcore-ogl-cg");
//				}
//			}
//		}
		loaded = true;
	}
	private void inJarLoad(String name)throws UnsatisfiedLinkError{
		//start by assuming the library can be loaded from the jar
		InputStream resourceSource = locateResource(name);
		File resourceLocation = prepResourceLocation(name);
		try {
			copyResource(resourceSource, resourceLocation);
		} catch (IOException e) {
			throw new UnsatisfiedLinkError();
		}
		loadResource(resourceLocation);
	}

	private void loadLib(String name)  {

		//String libName = name.substring(name.indexOf("lib")+3);
		try {
			inJarLoad(name);
			return;
		} catch (UnsatisfiedLinkError ex) {
//			if(OSUtil.isOSX() || OSUtil.isLinux()){
//				try{
//					inJarLoad("libNRJavaSerial_legacy");
//					//ex.printStackTrace();
//					System.err.println("Normal lib failed, using legacy..OK!");
//					return;
//				}catch(UnsatisfiedLinkError errr){
//					ex.printStackTrace();
//					errr.printStackTrace();
//					System.err.println("Both normal lib and legacy failed");
//				}
//			}else{
//				ex.printStackTrace();
//			}
//			try{
//				//check to see if the library is availible in standard locations
//				System.loadLibrary(libName);
//				testNativeCode();
//				return;
//			}catch(UnsatisfiedLinkError e){
//				try{
//					name = "rxtxSerial";
//					//last ditch effort to load
//					System.loadLibrary( name);	
//					testNativeCode();
//					return;
//				}catch(UnsatisfiedLinkError err){
//					System.err.println("Failed to load all possible JNI local and from: \n"+System.getProperty("java.library.path"));
//					ex.printStackTrace();
//					throw new NativeResourceException("Unable to load deployed native resource");
//				}
//			}
			throw ex;
		}
	}

	private InputStream locateResource(String name) {
		name += OSUtil.getExtension();
		String file="";
		if(OSUtil.isWindows()) {
			if(OSUtil.is64Bit()){
				file="/native/windows/amd64/" + name;
			}else {
				file="/native/windows/i586/" + name;
			}
		}else if(OSUtil.isLinux()) {

			if(OSUtil.is64Bit()) {
				file="/native/linux/amd64/" + name;
			}else {
				file="/native/linux/i586/" + name;
			}
			
		}else{
			System.err.println("Can't load native file: "+name+" for os arch: "+OSUtil.getOsArch());
			return null;
		}
		//System.out.println("Loading "+file);
		return getClass().getResourceAsStream(file);
	}
	
	private void loadResource(File resource) {
		if(!resource.canRead())
			throw new RuntimeException("Cant open JNI file: "+resource.getAbsolutePath());
		//System.out.println("Loading: "+resource.getAbsolutePath());
		System.load(resource.getAbsolutePath());
	}

	private void copyResource(InputStream io, File file) throws IOException {
		FileOutputStream fos = new FileOutputStream(file);
		
		
		byte[] buf = new byte[256];
		int read = 0;
		while ((read = io.read(buf)) > 0) {
			fos.write(buf, 0, read);
		}
		fos.close();
		io.close();
	}

	private File prepResourceLocation(String fileName) {		
		String tmpDir = System.getProperty("java.io.tmpdir");
		//String tmpDir = "M:\\";
		if ((tmpDir == null) || (tmpDir.length() == 0)) {
			tmpDir = "tmp";
		}
		
		String displayName = new File(fileName).getName().split("\\.")[0];
		
		String user = System.getProperty("user.name");
		
		File fd = null;
		File dir = null;
		
		for(int i = 0; i < 10; i++) {
			dir = new File(tmpDir, displayName + "_" + user + "_" + (i));
			if (dir.exists()) {
				if (!dir.isDirectory()) {
					continue;
				}
				
				try {
					File[] files = dir.listFiles();
					for (int j = 0; j < files.length; j++) {
						if (!files[j].delete()) {
							continue;
						}
					}
				} catch (Throwable e) {
					
				}
			}
			
			if ((!dir.exists()) && (!dir.mkdirs())) {
				continue;
			}
			
			try {
				dir.deleteOnExit();
			} catch (Throwable e) {
				// Java 1.1 or J9
			}
			
			fd = new File(dir, fileName + OSUtil.getExtension());
			if ((fd.exists()) && (!fd.delete())) {
				continue;
			}
			
			try {
				if (!fd.createNewFile()) {
					continue;
				}
			} catch (IOException e) {
				continue;
			} catch (Throwable e) {
				// Java 1.1 or J9
			}
			
			break;
		}
		
		if(fd == null || !fd.canRead()) {
			throw new RuntimeException("Unable to deploy native resource");
		}
		//System.out.println("Local file: "+fd.getAbsolutePath());
		return fd;
	}
	
	private static class OSUtil {
		public static boolean is64Bit() {
			//System.out.println("Arch: "+getOsArch());
			return getOsArch().startsWith("x86_64") || getOsArch().startsWith("amd64");
		}
		public static boolean isARM() {
			return getOsArch().startsWith("arm");
		}
		public static boolean isCortexA8(){
			if(isARM()){
				//TODO check for cortex a8 vs arm9 generic
				return true;
			}
			return false;
		}
		public static boolean isWindows() {
			//System.out.println("OS name: "+getOsName());
			return getOsName().toLowerCase().startsWith("windows") ||getOsName().toLowerCase().startsWith("microsoft") || getOsName().toLowerCase().startsWith("ms");
		}
		
		public static boolean isLinux() {
			return getOsName().toLowerCase().startsWith("linux");
		}
		
		public static boolean isOSX() {
			return getOsName().toLowerCase().startsWith("mac");
		}
		
		public static String getExtension() {
			if(isWindows()) {
				return ".dll";
			}
			
			if(isLinux()) {
				return ".so";
			}
			
			if(isOSX()) {
				return ".jnilib";
			}
			
			return "";
		}
		
		public static String getOsName() {	
			return System.getProperty("os.name");
		}
		
		public static String getOsArch() {
			return System.getProperty("os.arch");
		}
		
		@SuppressWarnings("unused")
		public static String getIdentifier() {
			return getOsName() + " : " + getOsArch();
		}
	}
}
