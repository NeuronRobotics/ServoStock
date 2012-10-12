package com.neuronrobotics.replicator.gui.preview;

import javax.media.j3d.Appearance;
import javax.media.j3d.Background;
import javax.media.j3d.BoundingSphere;
import javax.media.j3d.Bounds;
import javax.media.j3d.BranchGroup;
import javax.media.j3d.Canvas3D;
import javax.media.j3d.ColoringAttributes;
import javax.media.j3d.DirectionalLight;
import javax.media.j3d.IndexedTriangleArray;
import javax.media.j3d.LineArray;
import javax.media.j3d.Shape3D;
import javax.media.j3d.Transform3D;
import javax.media.j3d.TransformGroup;
import javax.vecmath.Color3f;
import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;
import javax.vecmath.Vector3f;

import com.sun.j3d.utils.universe.SimpleUniverse;

public class OrientationIndicatorCanvas3D extends Canvas3D{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 8787828185414596224L;
	private SimpleUniverse simpleU;
	private DirectionalLight theLight;

	public OrientationIndicatorCanvas3D() {
		super(SimpleUniverse.getPreferredConfiguration());
		
		simpleU = new SimpleUniverse(this);
		
		BranchGroup mainBranch = new BranchGroup();
		
		mainBranch.addChild(this.getIndicatorArrow(ArrowDirection.POSITIVE_X));
		mainBranch.addChild(this.getIndicatorArrow(ArrowDirection.POSITIVE_Y));
		mainBranch.addChild(this.getIndicatorArrow(ArrowDirection.POSITIVE_Z));
		//mainBranch.addChild(this.getIndicatorArrow(ArrowDirection.NEGATIVE_X));
		//mainBranch.addChild(this.getIndicatorArrow(ArrowDirection.NEGATIVE_Y));
		//mainBranch.addChild(this.getIndicatorArrow(ArrowDirection.NEGATIVE_Z));
		
		theLight = new DirectionalLight();
		theLight.setInfluencingBounds(new BoundingSphere(new Point3d(0, 0, 0),
				900));
		theLight.setCapability(DirectionalLight.ALLOW_DIRECTION_READ);
		theLight.setCapability(DirectionalLight.ALLOW_DIRECTION_WRITE);
	
		Background b = createBackground();
		mainBranch.addChild(b);
		
		mainBranch.compile();
		
		simpleU.addBranchGraph(mainBranch);		
		
		setCamera(new Point3d(2,2,2),new Point3d(0,0,0),new Vector3d(0,1,0));
		
	}
	
	protected Background createBackground()
	 {
	  //We create a color by specifying the Red, Green, and Blue
	  //components, in this case a light gray.
	  Background back = new Background(
	   new Color3f( 0.7f, 0.7f, 0.7f ) );
	  	  
	  //Color3f col = new Color3f(1f,1f,1f);
	  
	  //We need to set the volume within the scene within which the
	  //Background is active
	  back.setApplicationBounds( createApplicationBounds() );
	  return back;
	 }
	
	protected Bounds createApplicationBounds()
	 {
	  return new BoundingSphere(new Point3d(0.0,0.0,0.0), 100.0);
	 }
	
	public void setCamera(Point3d position, Point3d direction,Vector3d cameraOrientation){
			
		Point3d newPosition,newDirection;		
		
		Vector3d temp = new Vector3d(position);
		temp.sub(direction);
		temp.normalize();		
		newPosition = new Point3d(temp); 
		newPosition.scale(3);
		
		newDirection = new Point3d(0,0,0);
		
		TransformGroup viewTransform = simpleU.getViewingPlatform()
				.getViewPlatformTransform();

		Transform3D t3d = new Transform3D();
		t3d.lookAt(newPosition, newDirection, new Vector3d(0,1,0));
		t3d.invert();
		viewTransform.setTransform(t3d);
		
		temp.scale(-1);
		
		theLight.setDirection(new Vector3f(temp));
	}
		
	private enum ArrowDirection {
		POSITIVE_X {
			@Override
			Point3d getDirection() {
				return new Point3d(1,0,0);
			}

			@Override
			Color3f getDefaultColor() {
				return new Color3f(1.0f,0,0);
			}

			@Override
			boolean isNegative() {
				return false;
			}
		}, POSITIVE_Y {
			@Override
			Point3d getDirection() {
				return new Point3d(0,1,0);
			}

			@Override
			Color3f getDefaultColor() {
				return new Color3f(0,1.0f,0);
			}

			@Override
			boolean isNegative() {
				return false;
			}
		}, POSITIVE_Z {
			@Override
			Point3d getDirection() {
				return new Point3d(0,0,1);
			}

			@Override
			Color3f getDefaultColor() {
				return new Color3f(0,0,1.0f);
			}

			@Override
			boolean isNegative() {
				return false;
			}
		}, NEGATIVE_X {
			@Override
			Point3d getDirection() {
				return new Point3d(-1,0,0);
			}

			@Override
			Color3f getDefaultColor() {
				return new Color3f(0.5f,0,0);
			}

			@Override
			boolean isNegative() {
				return true;
			}
		}, NEGATIVE_Y {
			@Override
			Point3d getDirection() {
				return new Point3d(0,-1,0);
			}

			@Override
			Color3f getDefaultColor() {
				return new Color3f(0,0.5f,0);
			}

			@Override
			boolean isNegative() {
				return true;
			}
		}, NEGATIVE_Z {
			@Override
			Point3d getDirection() {
				return new Point3d(0,0,-1);
			}

			@Override
			Color3f getDefaultColor() {
				return new Color3f(0,0,0.5f);
			}

			@Override
			boolean isNegative() {
				return true;
			}
		};
		
		abstract Point3d getDirection();
		abstract Color3f getDefaultColor();
		abstract boolean isNegative();
	}
		
	private BranchGroup getIndicatorArrow(ArrowDirection ad){
		
		BranchGroup result = new BranchGroup();
		result.addChild(getIndicatorLine(ad));		
		if(!ad.isNegative()) result.addChild(getIndicatorArrowHead(ad));
						
		return result;
		
	}
	
	private Shape3D getIndicatorArrowHead(ArrowDirection ad){
		
		Appearance theAppearance = new Appearance();
		ColoringAttributes ca = new ColoringAttributes();
		ca.setColor(ad.getDefaultColor());
		theAppearance.setColoringAttributes(ca);
		
		IndexedTriangleArray theTriArray = new IndexedTriangleArray(5, IndexedTriangleArray.COORDINATES, 18);
		
		theTriArray.setCoordinate(0, ad.getDirection());
		
		int ct =1;
		
		Point3d temp = new Point3d(ad.getDirection());
		Point3d temp2 = new Point3d(ad.getDirection());
		temp2.scale(0.09);
		temp.sub(temp2);
		
		double off = 0.07;
		
		Point3d xL = new Point3d(temp.x-off,temp.y,temp.z);
		Point3d xR = new Point3d(temp.x+off,temp.y,temp.z);
		
		Point3d yL = new Point3d(temp.x,temp.y-off,temp.z);
		Point3d yR = new Point3d(temp.x,temp.y+off,temp.z);
		
		Point3d zL = new Point3d(temp.x,temp.y,temp.z-off);
		Point3d zR = new Point3d(temp.x,temp.y,temp.z+off);
		
		
		if (ad.getDirection().x == 0) {
			theTriArray.setCoordinate(ct++, xL);
			theTriArray.setCoordinate(ct++, xR);
		}
		
		if (ad.getDirection().y == 0) {
			theTriArray.setCoordinate(ct++, yL);
			theTriArray.setCoordinate(ct++, yR);
		}

		if (ad.getDirection().z == 0) {
			theTriArray.setCoordinate(ct++, zL);
			theTriArray.setCoordinate(ct++, zR);
		}
				
		theTriArray.setCoordinateIndex(0, 0);
		theTriArray.setCoordinateIndex(1, 1);
		theTriArray.setCoordinateIndex(2, 2);
		
		theTriArray.setCoordinateIndex(3, 0);
		theTriArray.setCoordinateIndex(4, 4);
		theTriArray.setCoordinateIndex(5, 1);
		
		theTriArray.setCoordinateIndex(6, 0);
		theTriArray.setCoordinateIndex(7, 3);
		theTriArray.setCoordinateIndex(8, 4);
		
		theTriArray.setCoordinateIndex(9, 0);
		theTriArray.setCoordinateIndex(10, 2);
		theTriArray.setCoordinateIndex(11, 3);

		theTriArray.setCoordinateIndex(12, 1);
		theTriArray.setCoordinateIndex(13, 4);
		theTriArray.setCoordinateIndex(14, 2);

		theTriArray.setCoordinateIndex(15, 2);
		theTriArray.setCoordinateIndex(16, 4);
		theTriArray.setCoordinateIndex(17, 3);
		
		Shape3D result = new Shape3D(theTriArray);
		result.setAppearance(theAppearance);
		
		return result;
	}
		
	private Shape3D getIndicatorLine(ArrowDirection ad){
		Appearance theAppearance = new Appearance();
		ColoringAttributes ca = new ColoringAttributes();
		ca.setColor(ad.getDefaultColor());
		theAppearance.setColoringAttributes(ca);
		
		LineArray theLineArray = new LineArray(2,LineArray.COORDINATES);
		theLineArray.setCoordinate(0, new Point3d(0,0,0));
		theLineArray.setCoordinate(1, ad.getDirection());
		
		Shape3D theShape = new Shape3D(theLineArray);	
		theShape.setAppearance(theAppearance);
		
		return theShape;	
		
	}

}
