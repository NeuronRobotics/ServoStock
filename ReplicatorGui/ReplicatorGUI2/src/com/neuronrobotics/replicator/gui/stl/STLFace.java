package com.neuronrobotics.replicator.gui.stl;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;

import javax.vecmath.Point3f;
import javax.vecmath.Vector3f;

public class STLFace implements Iterable<STLFacet>{
	
	private ArrayList<STLFacet> theFacets;
	private ArrayList<Point3f> theVertices;
	
	private Vector3f normal;
	private float originDistance;	
	
	
	//TODO this might work?
	public static Collection<STLFace> getSTLFace2(STLObject stlo){
		ArrayList<ArrayList<STLFace>> sameNorm = new ArrayList<ArrayList<STLFace>>();
		//int ct=0;
		for (STLFacet facet:stlo){
			Vector3f vec = facet.getNormal();
			vec.normalize();
			System.out.println(vec);
			int idx = epsilonContainsNormal(sameNorm, facet.getNormal(),.001f);
			if(idx==-1){
			//	ct++;
				ArrayList<STLFace> newL = new ArrayList<STLFace>();
				newL.add(new STLFace(facet));
				sameNorm.add(newL);
			}else{
				ArrayList<STLFace> curr = sameNorm.get(idx);//.add(facet);
				int ct2 = 0;
				STLFace currCand = new STLFace();
				ArrayList<STLFace> toRemove = new ArrayList<STLFace>();
				for(STLFace cand:curr){
					if(sharedVertices(cand,facet)>=1){
						if((ct2++)==0){
							currCand=cand;
							currCand.addFacet(facet);
							continue;
						}
						currCand.union(cand);
						toRemove.add(cand);
						//sameNorm.get(idx).remove(cand);
						if(ct2>=3) break;
					}
				}
				for(STLFace f:toRemove){
					sameNorm.get(idx).remove(f);
				}
				if(ct2==0){
					currCand = new STLFace(facet);
					sameNorm.get(idx).add(currCand);
				}
			}
		}
		ArrayList<STLFace> theFaces = new ArrayList<STLFace>();
		for(ArrayList<STLFace> faceL:sameNorm){
			theFaces.addAll(faceL);
		}
		System.out.println(theFaces.size());
		return theFaces;
	}
	
	public static Collection<STLFace> getSTLFace(STLObject stlo){
		ArrayList<STLFace> theFaces = new ArrayList<STLFace>();
		
		for (STLFacet currFacet:stlo){
			int index = indexOfMatchingFace(currFacet, theFaces);
			if(index==-1){
				theFaces.add(new STLFace(currFacet));
			} else {
				theFaces.get(index).addFacet(currFacet);
			}
		}	
		
		return theFaces;
	}

	private static int indexOfMatchingFace(STLFacet facet, Collection<STLFace> col){
		
		float epsilon = 0.0001f;
		
		int ct = 0;
		for(STLFace face:col){
			System.out.println(facet.getNormal()+" " + face.getNormal());
			if((facet.getNormal().epsilonEquals(face.getNormal(), epsilon))&&floatEpsilonEquals(face.originDistance,facet.originToPlaneDistance())){
				return ct;
			}
			ct++;
		}		
		return -1;
	}
	
	private static boolean floatEpsilonEquals(float originDistance2,float originToPlaneDistance) {
			float epsilon = 0.0001f;
			float diff = originDistance2 - originToPlaneDistance;
			return diff>=-epsilon&&diff<=epsilon;
	}

	private static int epsilonContainsNormal(ArrayList<ArrayList<STLFace>> sameNorm, Vector3f normal, float eps) {
		int idx = -1;
		int ct = 0;
		for(ArrayList<STLFace> l:sameNorm){
			Vector3f vec = l.get(0).getNormal();
			vec.normalize();
			normal.normalize();
			if(vec.epsilonEquals(normal, eps)){
				idx = ct;
				break;
			}
			ct++;
		}
		return idx;
	}
	
	private static int sharedVertices(STLFace face,STLFacet facet){
		int ct =0;
		for(Point3f vert:face.theVertices){
			if(facet.getVertex1().epsilonEquals(vert, .001f)) ct++;
			if(facet.getVertex2().epsilonEquals(vert, .001f)) ct++;
			if(facet.getVertex3().epsilonEquals(vert, .001f)) ct++;
			if(ct>=3) break;
		}
		return ct;
	}

	private void union(STLFace face) {
		this.theFacets.addAll(face.getFacets());	
	}

	protected Collection<? extends STLFacet> getFacets() {
		return theFacets;
	}

	private STLFace(){
		theFacets = new ArrayList<STLFacet>();
		normal = null;
		theVertices = new ArrayList<Point3f>();
	}
	
	private STLFace(STLFacet f){
		theFacets = new ArrayList<STLFacet>();
		theFacets.add(f);
		normal = f.getNormal();

		theVertices = new ArrayList<Point3f>();
		theVertices.add(f.getVertex1());
		theVertices.add(f.getVertex2());
		theVertices.add(f.getVertex3());
		
		originDistance = f.originToPlaneDistance();
	}
	
	public Vector3f getNormal(){
		return normal;
	}
	
	public Point3f getCenter(){
		//TODO want to make sure point is on plane
		//this seems easier to solve after rotations
		//are better figured out
		Point3f center = new Point3f(0,0,0);
		
		Point3f max = new Point3f(0,0,0), min = new Point3f(0,0,0);
		
		for(STLFacet fac:this){
			max.x = Math.max(max.x, fac.getMax().x);
			max.y = Math.max(max.y, fac.getMax().y);
			max.z = Math.max(max.z, fac.getMax().z);
			
			min.x = Math.min(min.x, fac.getMax().x);
			min.y = Math.min(min.y, fac.getMax().y);
			min.z = Math.min(min.z, fac.getMax().z);
			
		}
		center = new Point3f(((max.x-min.x)/2),((max.y-min.y)/2),((max.z-min.z)/2));
		return center;
	}

	private boolean addFacet(STLFacet fac){
		if(!normal.equals(fac.getNormal())||fac==null||theFacets.contains(fac)) return false;
		theVertices.add(fac.getVertex1());
		theVertices.add(fac.getVertex2());
		theVertices.add(fac.getVertex3());
		return theFacets.add(fac);
	}
	
	@Override
	public Iterator<STLFacet> iterator() {
		return theFacets.iterator();
	}
		
}
