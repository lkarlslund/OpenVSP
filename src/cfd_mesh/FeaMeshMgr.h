//
// This file is released under the terms of the NASA Open Source Agreement (NOSA)
// version 1.3 as detailed in the LICENSE file which accompanies this software.
//

//////////////////////////////////////////////////////////////////////
// FeaMeshMgr.h
// J.R. Gloudemans
//////////////////////////////////////////////////////////////////////

#if !defined(FeaMeshMgr_FeaMeshMgr__INCLUDED_)
#define FeaMeshMgr_FeaMeshMgr__INCLUDED_

#include "CfdMeshMgr.h"
#include "FeaStructure.h"
#include "FeaElement.h"
#include "AnalysisMgr.h"
#include "FeaMesh.h"

#include "StructureMgr.h"

#include <unordered_map>

using namespace std;

enum
{
    SURFACE_FIX_POINT, BORDER_FIX_POINT, INTERSECT_FIX_POINT
};

typedef unordered_map < string, FeaMesh* > meshmaptype;

class FeaCount
{
public:
    FeaCount();
    unsigned int m_NumNodes;
    unsigned int m_NumEls;
    unsigned int m_NumTris;
    unsigned int m_NumQuads;
    unsigned int m_NumBeams;
};

//////////////////////////////////////////////////////////////////////
class FeaMeshMgrSingleton : public CfdMeshMgrSingleton
{
protected:
    FeaMeshMgrSingleton();
    //FeaMeshMgrSingleton( FeaMeshMgrSingleton const& copy );          // Not Implemented
    //FeaMeshMgrSingleton& operator=( FeaMeshMgrSingleton const& copy ); // Not Implemented

public:

    static FeaMeshMgrSingleton& getInstance()
    {
        static FeaMeshMgrSingleton instance;
        return instance;
    }

    virtual ~FeaMeshMgrSingleton();
    virtual void CleanUp();
    virtual void CleanMeshMap();

    virtual SimpleGridDensity* GetGridDensityPtr()
    {
        if ( m_ActiveMesh )
        {
            return m_ActiveMesh->GetGridDensityPtr();
        }
        return NULL;
    }

    virtual SimpleMeshCommonSettings* GetSettingsPtr()
    {
        if ( m_ActiveMesh )
        {
            return (SimpleMeshCommonSettings* ) m_ActiveMesh->GetStructSettingsPtr();
        }
        return NULL;
    }

    virtual void SetActiveMesh( string struct_id );

    virtual FeaMesh* GetMeshPtr()
    {
        return m_ActiveMesh;
    }

    virtual FeaMesh* GetMeshPtr( string struct_id );

    virtual bool LoadSurfaces();
    virtual void LoadSkins();
    virtual void GenerateFeaMesh();
    virtual void ExportFeaMesh();
    virtual void ExportCADFiles();
    virtual void TransferMeshSettings();
    virtual void IdentifyCompIDNames();
    virtual void TransferFeaData();
    virtual void TransferPropMatData();
    virtual void TransferSubSurfData();
    virtual void TransferBCData();
    virtual void MergeCoplanarParts();
    virtual void AddStructureSurfParts();
    virtual void AddStructureFixPoints();
    virtual void ForceSurfaceFixPoints( int surf_indx, vector < vec2d > &adduw );
    virtual void AddStructureTrimPlanes();
    virtual void BuildMeshOrientationLookup();
    virtual bool CullPtByTrimGroup( const vec3d &pt, const vector < vec3d > & pplane, const vector < vec3d > & nplane );
    virtual void RemoveTrimTris();
    virtual void SetFixPointSurfaceNodes();
    virtual void SetFixPointBorderNodes();
    virtual void CheckFixPointIntersects();
    virtual void BuildFeaMesh();
    virtual void CheckSubSurfBorderIntersect();
    virtual void CheckDuplicateSSIntersects();
    virtual void MergeFeaPartSSEdgeOverlap();
    virtual void RemoveSubSurfFeaTris();
    virtual void TagFeaNodes();

    virtual int GetTotalNumSurfs()
    {
        return m_SurfVec.size();
    }

    virtual void SetFeaMeshStructID( string struct_id )
    {
        if ( m_FeaMeshInProgress )
        {
            return;
        }

        m_FeaStructID = struct_id;
        SetActiveMesh( struct_id );

        if ( struct_id != m_IntersectStructID )
        {
            CleanUp(); // Cleans intersection information, not FeaMesh
            m_IntersectStructID = struct_id;
        }
    }

    virtual string GetFeaMeshStructID()
    {
        return m_FeaStructID;
    }

    virtual string GetIntersectStructID()
    {
        return m_IntersectStructID;
    }

    virtual bool GetIntersectComplete()
    {
        return m_IntersectComplete;
    }

    virtual bool GetFeaMeshInProgress()
    {
        return m_FeaMeshInProgress;
    }
    virtual void SetFeaMeshInProgress( bool progress_flag )
    {
        m_FeaMeshInProgress = progress_flag;
    }

    virtual void SetCADOnlyFlag( bool cad_only_flag )
    {
        m_CADOnlyFlag = cad_only_flag;
    }

    virtual void TransferDrawObjData();

    virtual void UpdateDrawObjs();
    virtual void LoadDrawObjs( vector< DrawObj* > & draw_obj_vec );

    virtual void UpdateDisplaySettings();
    virtual void UpdateAssemblyDisplaySettings( const string &assembly_id );

    virtual const vector < SimpleFeaProperty >& GetSimplePropertyVec()
    {
        return m_SimplePropertyVec;
    }

    virtual const vector < SimpleFeaMaterial >& GetSimpleMaterialVec()
    {
        return m_SimpleMaterialVec;
    }

    virtual void ResetPropMatUse()
    {
        for ( int i = 0; i < m_SimplePropertyVec.size(); i++ )
        {
            m_SimplePropertyVec[ i ].m_Used = false;
        }
    }

    virtual void MarkPropMatUsed( int indx )
    {
        m_SimplePropertyVec[ indx ].m_Used = true;
        m_SimpleMaterialVec[ m_SimplePropertyVec[ indx ].GetSimpFeaMatIndex() ].m_Used = true;
    }

    virtual void RegisterAnalysis();

    virtual Surf* GetFeaSurf( int FeaPartID, int surf_num );

    virtual void MeshUnMeshed( const vector < string > & idvec );
    virtual void CleanupMeshes( const vector < string > & idvec );
    virtual void ExportAssemblyMesh( const string &assembly_id );

    virtual void WriteAssemblyCalculix( const string &assembly_id, const FeaCount &feacount );
    virtual void WriteAssemblyCalculix( FILE* fp, const string &assembly_id, const FeaCount &feacount );
    virtual void WriteConnectionCalculix( FILE* fp, FeaConnection* conn );
    virtual void WriteCalculixMaterials( FILE* fp );

protected:

    virtual void GetMassUnit();

    vector < SimpleFeaProperty > m_SimplePropertyVec;
    vector < SimpleFeaMaterial > m_SimpleMaterialVec;

    bool m_FeaMeshInProgress;
    bool m_CADOnlyFlag; // Indicates that only meshing should be performed, but the surfaces are still exported

    string m_FeaStructID;

    string m_IntersectStructID;
    bool m_IntersectComplete;

    meshmaptype m_MeshPtrMap;

    FeaMesh* m_ActiveMesh;


    SimpleAssemblySettings m_AssemblySettings;
};

#define FeaMeshMgr FeaMeshMgrSingleton::getInstance()

#endif
