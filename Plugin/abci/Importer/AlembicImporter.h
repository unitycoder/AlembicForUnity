#pragma once

#include <cstdint>

struct  aiConfig;
struct  aiCameraData;
struct  aiXformData;
struct  aiMeshSummary;
struct  aiMeshSampleSummary;
struct  aiPolyMeshData;
struct  aiSubmeshSummary;
struct  aiSubmeshData;
struct  aiFacesets;

class   aiContext;
class   aiObject;
#ifdef abciImpl
    class aiSchemaBase;
    class aiSampleBase;
    class aiXformSample;    // : aiSampleBase
    class aiCameraSample;   // : aiSampleBase
    class aiPolyMeshSample; // : aiSampleBase
    class aiPointsSample;   // : aiSampleBase
    class aiCurvesSample;   // : aiSampleBase
    class aiSubDSample;     // : aiSampleBase
#else
    // force make castable
    using aiSchemaBase     = void;
    using aiSampleBase     = void;
    using aiXformSample    = void;
    using aiCameraSample   = void;
    using aiPolyMeshSample = void;
    using aiPointsSample   = void;
    using aiCurvesSample   = void;
    using aiSubDSample     = void;
#endif

class   aiXform;    // : aiSchemaBase
class   aiCamera;   // : aiSchemaBase
class   aiPolyMesh; // : aiSchemaBase
class   aiPoints;   // : aiSchemaBase
class   aiCurves;   // : aiSchemaBase
class   aiSubD;     // : aiSchemaBase
class   aiProperty;

struct  aiPolyMeshData;
struct  aiPointsData;
struct  aiCurvesSampleData;
struct  aiSubDSampleData;

enum class aiNormalsMode
{
    ReadFromFile,
    ComputeIfMissing,
    AlwaysCompute,
    Ignore
};

enum class aiTangentsMode
{
    None,
    Compute,
};

enum class aiTimeSamplingType
{
    Uniform,
    Cyclic,
    Acyclic,
};

enum class aiTopologyVariance
{
    Constant,
    Homogeneous, // vertices are variant, topology is constant
    Heterogenous, // both vertices and topology are variant
};

enum class aiPropertyType
{
    Unknown,

    // scalar types
    Bool,
    Int,
    UInt,
    Float,
    Float2,
    Float3,
    Float4,
    Float4x4,

    // array types
    BoolArray,
    IntArray,
    UIntArray,
    FloatArray,
    Float2Array,
    Float3Array,
    Float4Array,
    Float4x4Array,

    ScalarTypeBegin  = Bool,
    ScalarTypeEnd    = Float4x4,

    ArrayTypeBegin   = BoolArray,
    ArrayTypeEnd     = Float4x4Array,
};

struct aiConfig
{
    aiNormalsMode normals_mode = aiNormalsMode::ComputeIfMissing;
    aiTangentsMode tangents_mode = aiTangentsMode::None;
    float scale_factor = 1.0f;
    float aspect_ratio = -1.0f;
    float vertex_motion_scale = 1.0f;
    int split_unit = 0x7fffffff;
    bool swap_handedness = true;
    bool swap_face_winding = false;
    bool interpolate_samples = true;
    bool turn_quad_edges = false;
    bool async_load = false;
};

struct aiTimeSamplingData
{
    aiTimeSamplingType type = aiTimeSamplingType::Uniform;
    float start_time = 0.0f;
    float end_time = 0.0f;
    float interval = 1.0f / 30.0f;  // relevant only if type is Uniform or Cyclic
    int numTimes = 0;               // relevant only if type is Acyclic
    double *times = nullptr;        // relevant only if type is Acyclic
};

struct aiXformData
{
    abcV3 translation = { 0.0f, 0.0f, 0.0f };
    abcV4 rotation = { 0.0f, 0.0f, 0.0f, 1.0f }; // quaternion
    abcV3 scale = { 1.0f, 1.0f, 1.0f };
    bool inherits = false;
};

struct aiCameraData
{
    float near_clipping_plane = 0.3f;
    float far_clipping_plane = 1000.0f;
    float field_of_view = 60.0f;      // in degree. vertical one
    float aspect_ratio = 16.0f / 9.0f;

    float focus_distance = 5.0f;     // in cm
    float focal_length = 0.0f;       // in mm
    float aperture = 2.4f;          // in cm. vertical one
};

struct aiMeshSummary
{
    aiTopologyVariance topology_variance = aiTopologyVariance::Constant;
    bool has_velocities = false;
    bool has_normals = false;
    bool has_tangents = false;
    bool has_uv0 = false;
    bool has_uv1 = false;
    bool has_colors = false;
    bool constant_points = false;
    bool constant_velocities = false;
    bool constant_normals = false;
    bool constant_tangents = false;
    bool constant_uv0 = false;
    bool constant_uv1 = false;
    bool constant_colors = false;
};

struct aiMeshSampleSummary
{
    int split_count = 0;
    int submesh_count = 0;
    int vertex_count = 0;
    int index_count = 0;
    bool topology_changed = false;
};

struct aiMeshSplitSummary
{
    int submesh_count = 0;
    int submesh_offset = 0;
    int vertex_count = 0;
    int vertex_offset = 0;
    int index_count = 0;
    int index_offset = 0;
};

struct aiSubmeshSummary
{
    int split_index = 0;
    int submesh_index = 0; // submesh index in split
    int index_count = 0;
};

struct aiPolyMeshData
{
    abcV3 *points = nullptr;
    abcV3 *velocities = nullptr;
    abcV3 *normals = nullptr;
    abcV4 *tangents = nullptr;
    abcV2 *uv0 = nullptr;
    abcV2 *uv1 = nullptr;
    abcV4 *colors = nullptr;
    int *indices = nullptr;

    int vertex_count = 0;
    int index_count = 0;

    abcV3 center = { 0.0f, 0.0f, 0.0f };
    abcV3 size = { 0.0f, 0.0f, 0.0f };
};

struct aiSubmeshData
{
    int *indices = nullptr;

};

struct aiPointsSummary
{
    bool has_velocity = false;
    bool position_is_constant = false;
    bool id_is_constant = false;
    int32_t peak_count = 0;
    uint64_t min_id = 0;
    uint64_t max_id = 0;
    abcV3 bounds_center = { 0.0f, 0.0f, 0.0f };
    abcV3 bounds_extents = { 0.0f, 0.0f, 0.0f };
};

struct aiPointsData
{
    abcV3       *points = nullptr;
    abcV3       *velocities = nullptr;
    uint64_t    *ids = nullptr;
    int32_t     count = 0;

    abcV3       center = { 0.0f, 0.0f, 0.0f };
    abcV3       size = { 0.0f, 0.0f, 0.0f };
};

struct aiPropertyData
{
    void *data = nullptr;
    int size = 0;
    aiPropertyType type = aiPropertyType::Unknown;

    aiPropertyData() {}
    aiPropertyData(void *d, int s, aiPropertyType t) : data(d), size(s), type(t) {}
};


abciAPI abcSampleSelector aiTimeToSampleSelector(float time);
abciAPI abcSampleSelector aiIndexToSampleSelector(int64_t index);
abciAPI void            aiCleanup();
abciAPI void            aiClearContextsWithPath(const char *path);
abciAPI aiContext*      aiCreateContext(int uid);
abciAPI void            aiDestroyContext(aiContext* ctx);

abciAPI bool            aiLoad(aiContext* ctx, const char *path);
abciAPI void            aiSetConfig(aiContext* ctx, const aiConfig* conf);
abciAPI float           aiGetStartTime(aiContext* ctx);
abciAPI float           aiGetEndTime(aiContext* ctx);
abciAPI int             aiGetFrameCount(aiContext* ctx);
abciAPI aiObject*       aiGetTopObject(aiContext* ctx);
abciAPI void            aiUpdateSamples(aiContext* ctx, float time);

abciAPI const char*     aiGetNameS(aiObject* obj);
abciAPI int             aiGetNumChildren(aiObject* obj);
abciAPI aiObject*       aiGetChild(aiObject* obj, int i);
abciAPI void            aiSetEnabled(aiObject* obj, bool v);

abciAPI aiSampleBase*   aiSchemaGetSample(aiSchemaBase* schema);
abciAPI void            aiSchemaUpdateSample(aiSchemaBase* schema, const abcSampleSelector *ss);
abciAPI void            aiSchemaSync(aiSchemaBase* schema);
abciAPI bool            aiSchemaIsConstant(aiSchemaBase* schema);
abciAPI bool            aiSchemaIsDataUpdated(aiSchemaBase* schema);
abciAPI void            aiSchemaMarkForceUpdate(aiSchemaBase* schema);

abciAPI void            aiSampleSync(aiSampleBase* sample);

abciAPI aiXform*        aiGetXform(aiObject* obj);
abciAPI void            aiXformGetData(aiXformSample* sample, aiXformData *dst);

abciAPI aiPolyMesh*     aiGetPolyMesh(aiObject* obj);
abciAPI void            aiPolyMeshGetSummary(aiPolyMesh* schema, aiMeshSummary* dst);
abciAPI void            aiPolyMeshGetSampleSummary(aiPolyMeshSample* sample, aiMeshSampleSummary* dst);
abciAPI void            aiPolyMeshGetSplitSummaries(aiPolyMeshSample* sample, aiMeshSplitSummary *dst);
abciAPI void            aiPolyMeshGetSubmeshSummaries(aiPolyMeshSample* sample, aiSubmeshSummary* dst);
abciAPI void            aiPolyMeshFillVertexBuffer(aiPolyMeshSample* sample, aiPolyMeshData* vbs, aiSubmeshData* ibs);

abciAPI aiCamera*       aiGetCamera(aiObject* obj);
abciAPI void            aiCameraGetData(aiCameraSample* sample, aiCameraData *dst);

abciAPI aiPoints*       aiGetPoints(aiObject* obj);
abciAPI void            aiPointsGetSummary(aiPoints *schema, aiPointsSummary *dst);
abciAPI void            aiPointsSetSort(aiPoints* schema, bool v);
abciAPI void            aiPointsSetSortBasePosition(aiPoints* schema, abcV3 v);
abciAPI void            aiPointsGetDataPointer(aiPointsSample* sample, aiPointsData *dst);
abciAPI void            aiPointsCopyData(aiPointsSample* sample, aiPointsData *dst);

abciAPI int             aiSchemaGetNumProperties(aiSchemaBase* schema);
abciAPI aiProperty*     aiSchemaGetPropertyByIndex(aiSchemaBase* schema, int i);
abciAPI aiProperty*     aiSchemaGetPropertyByName(aiSchemaBase* schema, const char *name);
abciAPI const char*     aiPropertyGetNameS(aiProperty* prop);
abciAPI aiPropertyType  aiPropertyGetType(aiProperty* prop);
abciAPI void            aiPropertyCopyData(aiProperty* prop, const abcSampleSelector *ss, aiPropertyData *dst);
