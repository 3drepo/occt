// Created on: 1999-03-03
// Created by: Fabrice SERVANT
// Copyright (c) 1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _IntPolyh_MaillageAffinage_HeaderFile
#define _IntPolyh_MaillageAffinage_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Handle.hxx>

#include <Bnd_Box.hxx>
#include <Standard_Integer.hxx>
#include <Standard_Real.hxx>
#include <IntPolyh_ArrayOfPoints.hxx>
#include <IntPolyh_ArrayOfEdges.hxx>
#include <IntPolyh_ArrayOfTriangles.hxx>
#include <IntPolyh_ArrayOfCouples.hxx>
#include <IntPolyh_ArrayOfStartPoints.hxx>
#include <Standard_Boolean.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <IntPolyh_ArrayOfSectionLines.hxx>
#include <IntPolyh_ArrayOfTangentZones.hxx>
class Adaptor3d_HSurface;
class Bnd_Box;
class IntPolyh_Point;
class IntPolyh_StartPoint;
class IntPolyh_Triangle;
class IntPolyh_SectionLine;


//! Provide the algorythms used in the package
class IntPolyh_MaillageAffinage 
{
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT IntPolyh_MaillageAffinage(const Handle(Adaptor3d_HSurface)& S1, const Standard_Integer NbSU1, const Standard_Integer NbSV1, const Handle(Adaptor3d_HSurface)& S2, const Standard_Integer NbSU2, const Standard_Integer NbSV2, const Standard_Integer PRINT);
  
  Standard_EXPORT IntPolyh_MaillageAffinage(const Handle(Adaptor3d_HSurface)& S1, const Handle(Adaptor3d_HSurface)& S2, const Standard_Integer PRINT);
  
  //! Compute points on one surface and fill an array of points;
  //! standard (default) method
  Standard_EXPORT void FillArrayOfPnt (const Standard_Integer SurfID);
  
  //! isShiftFwd flag is added. The purpose is to define shift
  //! of points along normal to the surface in this point. The
  //! shift length represents maximal deflection of triangulation.
  //! The direction (forward or reversed regarding to normal
  //! direction) is defined by isShiftFwd flag.
  //! Compute points on one surface and fill an array of points;
  //! advanced method
  Standard_EXPORT void FillArrayOfPnt (const Standard_Integer SurfID, const Standard_Boolean isShiftFwd);
  
  //! Compute points on one surface and fill an array of points;
  //! standard (default) method
  Standard_EXPORT void FillArrayOfPnt (const Standard_Integer SurfID, const TColStd_Array1OfReal& Upars, const TColStd_Array1OfReal& Vpars);
  
  //! isShiftFwd flag is added. The purpose is to define shift
  //! of points along normal to the surface in this point. The
  //! shift length represents maximal deflection of triangulation.
  //! The direction (forward or reversed regarding to normal
  //! direction) is defined by isShiftFwd flag.
  //! Compute points on one surface and fill an array of points;
  //! advanced method
  Standard_EXPORT void FillArrayOfPnt (const Standard_Integer SurfID, const Standard_Boolean isShiftFwd, const TColStd_Array1OfReal& Upars, const TColStd_Array1OfReal& Vpars);
  
  //! Compute the common box  witch is the intersection
  //! of the two bounding boxes,  and mark the points of
  //! the two surfaces that are inside.
  Standard_EXPORT void CommonBox (const Bnd_Box& B1, const Bnd_Box& B2, Standard_Real& xMin, Standard_Real& yMin, Standard_Real& zMin, Standard_Real& xMax, Standard_Real& yMax, Standard_Real& zMax);
  
  //! Compute edges from the array of points
  Standard_EXPORT void FillArrayOfEdges (const Standard_Integer SurfID);
  
  //! Compute triangles from the array of points, and --
  //! mark the triangles  that use marked points by the
  //! CommonBox function.
  Standard_EXPORT void FillArrayOfTriangles (const Standard_Integer SurfID);
  
  //! fill the  edge fields in  Triangle object  for the
  //! two array of triangles.
  Standard_EXPORT void LinkEdges2Triangles();
  
  //! Refine systematicaly all marked triangles of both surfaces
  Standard_EXPORT void CommonPartRefinement();
  
  //! Refine systematicaly all marked triangles of ONE surface
  Standard_EXPORT void LocalSurfaceRefinement (const Standard_Integer SurfId);
  
  //! Compute deflection  for   all  triangles  of  one
  //! surface,and sort min and max of deflections
  Standard_EXPORT void ComputeDeflections (const Standard_Integer SurfID);
  
  //! Refine  both  surfaces using  BoundSortBox  as --
  //! rejection.  The  criterions  used to refine a  --
  //! triangle are:  The deflection The  size of the --
  //! bounding boxes   (one surface may be   very small
  //! compared to the other)
  Standard_EXPORT void TrianglesDeflectionsRefinementBSB();
  
  //! This fonction     Check if two triangles   are  in
  //! contact or no,  return 1 if yes, return 0
  //! if no.
  Standard_EXPORT Standard_Integer TriContact (const IntPolyh_Point& P1, const IntPolyh_Point& P2, const IntPolyh_Point& P3, const IntPolyh_Point& Q1, const IntPolyh_Point& Q2, const IntPolyh_Point& Q3, Standard_Real& Angle) const;
  
  Standard_EXPORT Standard_Integer TriangleEdgeContact (const Standard_Integer TriSurfID, const Standard_Integer EdgeIndice, const IntPolyh_Point& P1, const IntPolyh_Point& P2, const IntPolyh_Point& P3, const IntPolyh_Point& C1, const IntPolyh_Point& C2, const IntPolyh_Point& C3, const IntPolyh_Point& Pe1, const IntPolyh_Point& Pe2, const IntPolyh_Point& E, const IntPolyh_Point& N, IntPolyh_StartPoint& SP1, IntPolyh_StartPoint& SP2) const;
  
  Standard_EXPORT Standard_Integer TriangleEdgeContact2 (const Standard_Integer TriSurfID, const Standard_Integer EdgeIndice, const IntPolyh_Triangle& Tri1, const IntPolyh_Triangle& Tri2, const IntPolyh_Point& P1, const IntPolyh_Point& P2, const IntPolyh_Point& P3, const IntPolyh_Point& C1, const IntPolyh_Point& C2, const IntPolyh_Point& C3, const IntPolyh_Point& Pe1, const IntPolyh_Point& Pe2, const IntPolyh_Point& E, const IntPolyh_Point& N, IntPolyh_StartPoint& SP1, IntPolyh_StartPoint& SP2) const;
  
  Standard_EXPORT Standard_Integer StartingPointsResearch (const Standard_Integer T1, const Standard_Integer T2, IntPolyh_StartPoint& SP1, IntPolyh_StartPoint& SP2) const;
  
  //! From  two  triangles compute intersection  points.
  //! If I found   more  than two intersection  points
  //! that's mean that those triangle are coplanar
  Standard_EXPORT Standard_Integer StartingPointsResearch2 (const Standard_Integer T1, const Standard_Integer T2, IntPolyh_StartPoint& SP1, IntPolyh_StartPoint& SP2) const;
  
  Standard_EXPORT Standard_Integer NextStartingPointsResearch (const Standard_Integer T1, const Standard_Integer T2, const IntPolyh_StartPoint& SPInit, IntPolyh_StartPoint& SPNext) const;
  
  //! from  two triangles  and an intersection   point I
  //! seach the other point (if it exist).
  //! This function is used by StartPointChain
  Standard_EXPORT Standard_Integer NextStartingPointsResearch2 (const Standard_Integer T1, const Standard_Integer T2, const IntPolyh_StartPoint& SPInit, IntPolyh_StartPoint& SPNext) const;
  
  //! Analyse  each couple of  triangles from the two --
  //! array  of triangles,  to   see  if they are  in
  //! contact,  and  compute the  incidence.  Then  put
  //! couples  in contact  in  the  array  of  couples
  Standard_EXPORT Standard_Integer TriangleCompare();
  
  //! The   same as   TriangleCompare, plus compute the
  //! StartPoints without chaining them.
  Standard_EXPORT Standard_Integer TriangleComparePSP();
  
  //! From the array  of couples compute  all the start
  //! points and display them on the screen
  Standard_EXPORT void StartPointsCalcul() const;
  
  //! Loop on the array of couples. Compute StartPoints.
  //! Try to chain  the StartPoints into SectionLines or
  //! put  the  point  in  the    ArrayOfTangentZones if
  //! chaining it, is not possible.
  Standard_EXPORT Standard_Integer StartPointsChain (IntPolyh_ArrayOfSectionLines& TSectionLines, IntPolyh_ArrayOfTangentZones& TTangentZones);
  
  //! Mainly  used  by StartPointsChain(), this function
  //! try to compute the next StartPoint.
  Standard_EXPORT Standard_Integer GetNextChainStartPoint (const IntPolyh_StartPoint& SPInit, IntPolyh_StartPoint& SPNext, IntPolyh_SectionLine& MySectionLine, IntPolyh_ArrayOfTangentZones& TTangentZones, const Standard_Boolean Prepend = Standard_False);
  
  Standard_EXPORT const IntPolyh_ArrayOfPoints& GetArrayOfPoints (const Standard_Integer SurfID) const;
  
  Standard_EXPORT const IntPolyh_ArrayOfEdges& GetArrayOfEdges (const Standard_Integer SurfID) const;
  
  Standard_EXPORT const IntPolyh_ArrayOfTriangles& GetArrayOfTriangles (const Standard_Integer SurfID) const;
  
  Standard_EXPORT Standard_Integer GetFinTE (const Standard_Integer SurfID) const;
  
  Standard_EXPORT Standard_Integer GetFinTT (const Standard_Integer SurfID) const;
  
  Standard_EXPORT Bnd_Box GetBox (const Standard_Integer SurfID) const;
  
  Standard_EXPORT void GetBoxDraw (const Standard_Integer SurfID) const;
  
  Standard_EXPORT const IntPolyh_ArrayOfStartPoints& GetArrayOfSP() const;
  
  //! This method returns array of couples of contact triangles.
  Standard_EXPORT IntPolyh_ArrayOfCouples& GetArrayOfCouples();
  
  Standard_EXPORT void SetEnlargeZone (Standard_Boolean& EnlargeZone);
  
  Standard_EXPORT Standard_Boolean GetEnlargeZone() const;
  
  //! returns FlecheMin
  Standard_EXPORT Standard_Real GetMinDeflection (const Standard_Integer SurfID) const;
  
  //! returns FlecheMax
  Standard_EXPORT Standard_Real GetMaxDeflection (const Standard_Integer SurfID) const;




protected:





private:



  Handle(Adaptor3d_HSurface) MaSurface1;
  Handle(Adaptor3d_HSurface) MaSurface2;
  Bnd_Box MyBox1;
  Bnd_Box MyBox2;
  Standard_Integer NbSamplesU1;
  Standard_Integer NbSamplesU2;
  Standard_Integer NbSamplesV1;
  Standard_Integer NbSamplesV2;
  Standard_Real FlecheMax1;
  Standard_Real FlecheMax2;
  Standard_Real FlecheMin1;
  Standard_Real FlecheMin2;
  Standard_Real FlecheMoy1;
  Standard_Real FlecheMoy2;
  IntPolyh_ArrayOfPoints TPoints1;
  IntPolyh_ArrayOfPoints TPoints2;
  IntPolyh_ArrayOfEdges TEdges1;
  IntPolyh_ArrayOfEdges TEdges2;
  IntPolyh_ArrayOfTriangles TTriangles1;
  IntPolyh_ArrayOfTriangles TTriangles2;
  IntPolyh_ArrayOfCouples TTrianglesContacts;
  IntPolyh_ArrayOfStartPoints TStartPoints;
  Standard_Boolean myEnlargeZone;


};







#endif // _IntPolyh_MaillageAffinage_HeaderFile
