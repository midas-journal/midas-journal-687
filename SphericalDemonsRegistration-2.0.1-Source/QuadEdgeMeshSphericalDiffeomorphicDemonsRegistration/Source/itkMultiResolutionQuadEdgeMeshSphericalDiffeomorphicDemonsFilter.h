/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: ITKHeader.h,v $
  Language:  C++
  Date:      $Date: 2006-04-25 23:20:16 $
  Version:   $Revision: 1.1 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef __itkMultiResolutionQuadEdgeMeshSphericalDiffeomorphicDemonsFilter_h
#define __itkMultiResolutionQuadEdgeMeshSphericalDiffeomorphicDemonsFilter_h

#include "itkQuadEdgeMeshSphericalDiffeomorphicDemonsFilter.h"

#include "itkVersorTransformOptimizer.h"
#include "itkVersorTransform.h"

#ifdef USE_VTK
#include "MultiResolutionDeformableAndAffineRegistrationMonitor.h"
#endif


namespace itk
{
template< class TMesh >
class MultiResolutionQuadEdgeMeshSphericalDiffeomorphicDemonsFilter : 
    public QuadEdgeMeshToQuadEdgeMeshFilter< TMesh, TMesh >
{
public:
  typedef MultiResolutionQuadEdgeMeshSphericalDiffeomorphicDemonsFilter Self;
  typedef SmartPointer< Self >                                          Pointer;
  typedef SmartPointer< const Self >                                    ConstPointer;
  typedef QuadEdgeMeshToQuadEdgeMeshFilter< TMesh, TMesh >              Superclass;
  
  /** Method that instantiates a new object */
  itkNewMacro( Self );

  /** Method that provides the name of the class as a string as well as the
   * name of the parent class. */
  itkTypeMacro( 
    MultiResolutionQuadEdgeMeshSphericalDiffeomorphicDemonsFilter, QuadEdgeMeshToQuadEdgeMeshFilter );
  
  /** Using a unique mesh type. */
  typedef  TMesh                                  MeshType;
  typedef typename  MeshType::PointType           PointType;

  /** Set the Fixed mesh. */
  void SetFixedMesh( const MeshType * fixedMesh );

  /** Set the Moving mesh. */
  void SetMovingMesh( const MeshType * movingMesh );

  /** Set the Fixed mesh for a given resolution level. */
  void SetFixedMesh( unsigned int level, const MeshType * fixedMesh );

  /** Set the Moving mesh for a given resolution level. */
  void SetMovingMesh( unsigned int level, const MeshType * movingMesh );


  /** Set Sphere Center.  The implementation of this filter assumes that the
   * Mesh surface has a spherical geometry (not only spherical topology). With
   * this method you can specify the coordinates of the center of the sphere
   * represented by the Mesh. This will be used in the computation of parallel
   * transport for vector values associated with nodes.
   */
  itkSetMacro( SphereCenter, PointType );
  itkGetConstMacro( SphereCenter, PointType );

  /** Set Sphere Radius.  The implementation of this filter assumes that the
   * Mesh surface has a spherical geometry (not only spherical topology). With
   * this method you can specify the radius of the sphere. This will be used in
   * the computation of parallel transport for vector values associated
   * with nodes.
   */
  itkSetMacro( SphereRadius, double );
  itkGetConstMacro( SphereRadius, double );

  /** Set the number of resolution levels for the combination of rigid and
   * demons registration */
  itkSetMacro( NumberOfResolutionLevels, unsigned int );
  itkGetMacro( NumberOfResolutionLevels, unsigned int );

  /**  Create the Output of the proper type for that output number */
  DataObject::Pointer MakeOutput(unsigned int idx);

  typedef VersorTransform< double >  TransformType;

  itkGetConstObjectMacro( RigidTransform, TransformType );

  typedef VersorTransformOptimizer     RigidOptimizerType;

  itkGetObjectMacro( RigidOptimizer, RigidOptimizerType );

  typedef QuadEdgeMeshSphericalDiffeomorphicDemonsFilter< 
    MeshType, MeshType, MeshType >  DemonsRegistrationFilterType;

  typedef DemonsRegistrationFilterType    DeformationFilterType;

  typedef typename DemonsRegistrationFilterType::DestinationPointSetType    DestinationPointSetType;

  itkGetObjectMacro( DemonsRegistrationFilter, DemonsRegistrationFilterType );

  itkGetConstObjectMacro( FinalDestinationPoints, DestinationPointSetType );

  typedef typename MeshType::PointsContainer          PointsContainer;
  typedef typename PointsContainer::Pointer           PointsContainerPointer;
  typedef typename MeshType::PointsContainerIterator  PointsContainerIterator;

  typedef Array< unsigned int >                       IntegerArrayType;
  typedef Array< double >                             DoubleArrayType;

  /** Schedule of smoothing iterations to be used at every resolution level. */
  itkSetMacro( SmoothingIterations, IntegerArrayType );
  itkGetConstReferenceMacro( SmoothingIterations, IntegerArrayType );

  /** Schedule of demons iterations to be used at every resolution level. */
  itkSetMacro( DemonsIterations, IntegerArrayType );
  itkGetConstReferenceMacro( DemonsIterations, IntegerArrayType );

  /** Schedule of rigid registration iterations to be used at every resolution level. */
  itkSetMacro( RigidRegistrationIterations, IntegerArrayType );
  itkGetConstReferenceMacro( RigidRegistrationIterations, IntegerArrayType );

  /** Schedule of rigid registration initial step length to be used at every resolution level. */
  itkSetMacro( RigidRegistrationStepLength, DoubleArrayType );
  itkGetConstReferenceMacro( RigidRegistrationStepLength, DoubleArrayType );

  /** Schedule of Epsilon values to be used at every resolution level. */
  itkSetMacro( EpsilonValues, DoubleArrayType );
  itkGetConstReferenceMacro( EpsilonValues, DoubleArrayType );

  /** Schedule of SigmaX values to be used at every resolution level. */
  itkSetMacro( SigmaXValues, DoubleArrayType );
  itkGetConstReferenceMacro( SigmaXValues, DoubleArrayType );

  /** Variable that defines whether the filter will self-adjust the values of
   * SigmaX and Epsilon in order to get closer to the ratio of
   * largestVelocityMagnitude being similar to the value of the shortest edge
   * length. */
  itkSetMacro( SelfRegulatedMode, bool );
  itkGetConstMacro( SelfRegulatedMode, bool );
  itkBooleanMacro( SelfRegulatedMode );

  /** Return the fixed mesh that is being used in the current resolution level.
   * This fixed mesh may have incorporated deformations resulting from previous
   * resolutions levels. */
  itkGetConstObjectMacro( CurrentLevelFixedMesh, MeshType );

  /** Return the fixed mesh that is being used in the current resolution level.
   * This mesh is the truly original mesh and has not been deformed at all. */
  itkGetConstObjectMacro( CurrentLevelInitialFixedMesh, MeshType );

#ifdef USE_VTK
  typedef MultiResolutionDeformableAndAffineRegistrationMonitor< 
    Self, DestinationPointSetType >  RegistrationMonitorType;

  void SetRegistrationMonitor( RegistrationMonitorType * monitor )
    {
    this->m_RegistrationMonitor = monitor;
    }
#endif

  typedef enum
    {
    RIGID,
    DEFORMABLE
    }  RegistrationModeType;
  
  RegistrationModeType GetRegistrationMode() const;

  /** Get the destination points from the demons filter. */
  const DestinationPointSetType * GetCurrentDestinationPoints() const;

protected:
  MultiResolutionQuadEdgeMeshSphericalDiffeomorphicDemonsFilter();
  ~MultiResolutionQuadEdgeMeshSphericalDiffeomorphicDemonsFilter();
  void PrintSelf(std::ostream& os, Indent indent) const;
  
  virtual void GenerateData( );
  
private:
  MultiResolutionQuadEdgeMeshSphericalDiffeomorphicDemonsFilter( const Self& );
  void operator = ( const Self& );

  /** Perform rigid registration between two meshes at the current resolution level. */
  void ComputeRigidRegistration();

  /** Map the points of the fixed mesh using the rigid transform. */
  void RigidlyTransformPointsOfFixedMesh();

  /** Perform demons registration between two meshes at the current resolution level. */
  void ComputeDemonsRegistration();

  /** Configure the meshs to be used for the coarsest resolution */
  void PrepareCoarsestResolutionMeshes();

  /** Setup initial parameters of internal classes */
  void InitializeRigidRegistrationParameters();
  void InitializeDemonsRegistrationParameters();

  /** Deforme the next resolution level fixed mesh by using the destination
   * points from the current resolution level demons registration. */
  void DeformNextResolutionLevelFixedMesh();

  /** Prepare the input meshes for the next resolution level. */
  void PrepareNextResolutionLevelMeshes();

  /** Set the rigid transform to Identity. */
  void SetRigidTransformToIdentity();

  /** Center of spherical mesh. We assume that both the Fixed and
   * Moving meshes have spherical geometry and that they share the same
   * center and radius. */
  PointType       m_SphereCenter;

  /** Radius of spherical mesh. We assume that both the Fixed and
   * Moving meshes have spherical geometry and that they share the same
   * center and radius. */
  double          m_SphereRadius;

  unsigned int    m_CurrentResolutionLevel;

  unsigned int    m_NumberOfResolutionLevels;

  typename TransformType::Pointer  m_RigidTransform;

  typename RigidOptimizerType::Pointer  m_RigidOptimizer;

  typename MeshType::ConstPointer   m_CurrentLevelInitialFixedMesh;

  typename MeshType::ConstPointer   m_CurrentLevelFixedMesh;
  typename MeshType::ConstPointer   m_CurrentLevelMovingMesh;

  typename MeshType::Pointer        m_CurrentLevelRigidlyMappedFixedMesh;
  typename MeshType::Pointer        m_CurrentLevelDemonsMappedFixedMesh;

  typename MeshType::ConstPointer   m_NextLevelFixedMesh;
  typename MeshType::ConstPointer   m_NextLevelMovingMesh;

  typename DemonsRegistrationFilterType::Pointer   m_DemonsRegistrationFilter;

  typename DestinationPointSetType::ConstPointer    m_FinalDestinationPoints;

  IntegerArrayType             m_SmoothingIterations;
  IntegerArrayType             m_DemonsIterations;
  IntegerArrayType             m_RigidRegistrationIterations;

  DoubleArrayType              m_EpsilonValues;
  DoubleArrayType              m_SigmaXValues;
  DoubleArrayType              m_RigidRegistrationStepLength;

  RegistrationModeType         m_RegistrationMode;

  /** Variable that defines whether the filter will self-adjust the values of
   * SigmaX and Epsilon in order to get closer to the ratio of
   * largestVelocityMagnitude being similar to the value of the shortest edge
   * length. */
  bool          m_SelfRegulatedMode;


#ifdef USE_VTK
  RegistrationMonitorType  *   m_RegistrationMonitor;
#endif

};

}

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkMultiResolutionQuadEdgeMeshSphericalDiffeomorphicDemonsFilter.txx"
#endif

#endif
