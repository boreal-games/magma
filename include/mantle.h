#ifndef _MANTLE_H
#define _MANTLE_H

#include <stdint.h>

#ifndef MAGMA_EXTERN
#define MAGMA_EXTERN extern
#endif

#define GR_STDCALL

#ifdef __cplusplus
extern "C" {
#endif



// constants (some guessed)
#define GR_API_VERSION           1
#define GR_MAX_MEMORY_HEAPS      8
#define GR_MAX_PHYSICAL_GPU_NAME 256
#define GR_MAX_PHYSICAL_GPUS     4
#define GR_NULL_HANDLE           0



// type aliases
typedef void     GR_VOID;
typedef int32_t  GR_BOOL;
typedef char     GR_CHAR;
typedef uint32_t GR_UINT;
typedef uint32_t GR_UINT32;
typedef uint64_t GR_UINT64;
typedef int32_t  GR_INT;
typedef float    GR_FLOAT;

typedef size_t   GR_SIZE;
typedef uint64_t GR_GPU_SIZE;

typedef int32_t  GR_ENUM;
typedef int32_t  GR_FLAGS;
typedef int32_t  GR_RESULT;

typedef uint64_t GR_BASE_OBJECT;
typedef uint64_t GR_CMD_BUFFER;
typedef uint64_t GR_DEVICE;
typedef uint64_t GR_FENCE;
typedef uint64_t GR_IMAGE;
typedef uint64_t GR_GPU_MEMORY;
typedef uint64_t GR_OBJECT;
typedef uint64_t GR_PHYSICAL_GPU;
typedef uint64_t GR_QUEUE;
typedef uint64_t GR_QUEUE_SEMAPHORE;



// callbacks
typedef GR_VOID *(GR_STDCALL *GR_ALLOC_FUNCTION)(
    GR_SIZE size,
    GR_SIZE alignment,
    GR_ENUM allocType
);

typedef GR_VOID (GR_STDCALL *GR_FREE_FUNCTION)(
    GR_VOID *pMem
);



// forward declarations
typedef struct _GR_ALLOC_CALLBACKS                GR_ALLOC_CALLBACKS;
typedef struct _GR_APPLICATION_INFO               GR_APPLICATION_INFO;
typedef struct _GR_CMD_BUFFER_CREATE_INFO         GR_CMD_BUFFER_CREATE_INFO;
typedef struct _GR_DEVICE_CREATE_INFO             GR_DEVICE_CREATE_INFO;
typedef struct _GR_DEVICE_QUEUE_CREATE_INFO       GR_DEVICE_QUEUE_CREATE_INFO;
typedef struct _GR_EXTENT2D                       GR_EXTENT2D;
typedef struct _GR_EXTENT3D                       GR_EXTENT3D;
typedef struct _GR_FORMAT                         GR_FORMAT;
typedef struct _GR_IMAGE_STATE_TRANSITION         GR_IMAGE_STATE_TRANSITION;
typedef struct _GR_IMAGE_SUBRESOURCE_RANGE        GR_IMAGE_SUBRESOURCE_RANGE;
typedef struct _GR_MEMORY_ALLOC_INFO              GR_MEMORY_ALLOC_INFO;
typedef struct _GR_MEMORY_REF                     GR_MEMORY_REF;
typedef struct _GR_MEMORY_STATE_TRANSITION        GR_MEMORY_STATE_TRANSITION;
typedef struct _GR_OFFSET2D                       GR_OFFSET2D;
typedef struct _GR_OFFSET3D                       GR_OFFSET3D;
typedef struct _GR_PHYSICAL_GPU_IMAGE_PROPERTIES  GR_PHYSICAL_GPU_IMAGE_PROPERTIES;
typedef struct _GR_PHYSICAL_GPU_MEMORY_PROPERTIES GR_PHYSICAL_GPU_MEMORY_PROPERTIES;
typedef struct _GR_PHYSICAL_GPU_PERFORMANCE       GR_PHYSICAL_GPU_PERFORMANCE;
typedef struct _GR_PHYSICAL_GPU_PROPERTIES        GR_PHYSICAL_GPU_PROPERTIES;
typedef struct _GR_RECT                           GR_RECT;
typedef struct _GR_VIRTUAL_MEMORY_REMAP_RANGE     GR_VIRTUAL_MEMORY_REMAP_RANGE;



// initialization and device functions
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grInitAndEnumerateGpus)(
    const GR_APPLICATION_INFO *pAppInfo,
    const GR_ALLOC_CALLBACKS  *pAllocCb,
    GR_UINT                   *pGpuCount,
    GR_PHYSICAL_GPU            gpus[GR_MAX_PHYSICAL_GPUS]
);
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grGetGpuInfo)(
    GR_PHYSICAL_GPU gpu,
    GR_ENUM         infoType,
    GR_SIZE        *pDataSize,
    GR_VOID        *pData
);
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grCreateDevice)(
    GR_PHYSICAL_GPU              gpu,
    const GR_DEVICE_CREATE_INFO *pCreateInfo,
    GR_DEVICE                   *pDevice
);
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grDestroyDevice)(
    GR_DEVICE device
);

// extension discovery functions
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grGetExtensionSupport)(
    GR_PHYSICAL_GPU gpu,
    const GR_CHAR  *pExtName
);

// queue functions
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grGetDeviceQueue)(
    GR_DEVICE device,
    GR_ENUM   queueType,
    GR_UINT   queueId,
    GR_QUEUE *pQueue
);
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grQueueWaitIdle)(
    GR_QUEUE queue
);
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grDeviceWaitIdle)(
    GR_DEVICE device
);
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grQueueSubmit)(
    GR_QUEUE             queue,
    GR_UINT              cmdBufferCount,
    const GR_CMD_BUFFER *pCmdBuffers,
    GR_UINT              memRefCount,
    const GR_MEMORY_REF *pMemRefs,
    GR_FENCE             fence
);
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grQueueSetGlobalMemReferences)(
    GR_QUEUE             queue,
    GR_UINT              memRefCount,
    const GR_MEMORY_REF *pMemRefs
);

// memory management functions
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grGetMemoryHeapCount)(
    GR_DEVICE device,
    GR_UINT  *pCount
);
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grGetMemoryHeapInfo)(
    GR_DEVICE device,
    GR_UINT   heapId,
    GR_ENUM   infoType,
    GR_SIZE  *pDataSize,
    GR_VOID  *pData
);
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grAllocMemory)(
    GR_DEVICE                   device,
    const GR_MEMORY_ALLOC_INFO *pAllocInfo,
    GR_GPU_MEMORY              *pMem
);
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grFreeMemory)(
    GR_GPU_MEMORY mem
);
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grSetMemoryPriority)(
    GR_GPU_MEMORY mem,
    GR_ENUM       priority
);
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grMapMemory)(
    GR_GPU_MEMORY mem,
    GR_FLAGS      flags,
    GR_VOID     **ppData
);
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grUnmapMemory)(
    GR_GPU_MEMORY mem
);
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grRemapVirtualMemoryPages)(
    GR_DEVICE                            device,
    GR_UINT                              rangeCount,
    const GR_VIRTUAL_MEMORY_REMAP_RANGE *pRanges,
    GR_UINT                              preWaitSemaphoreCount,
    const GR_QUEUE_SEMAPHORE            *pPreWaitSemaphores,
    GR_UINT                              postSignalSemaphoreCount,
    const GR_QUEUE_SEMAPHORE            *pPostSignalSemaphores
);
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grPinSystemMemory)(
    GR_DEVICE      device,
    const GR_VOID *pSystem,
    GR_SIZE        memSize,
    GR_GPU_MEMORY *pMem
);

// generic API object management functions
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grDestroyObject)(
    GR_OBJECT object
);
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grGetObjectInfo)(
    GR_BASE_OBJECT object,
    GR_ENUM        infoType,
    GR_SIZE       *pDataSize,
    GR_VOID       *pData
);
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grBindObjectMemory)(
    GR_OBJECT     object,
    GR_GPU_MEMORY mem,
    GR_GPU_SIZE   offset
);

// command buffer management functions
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grCreateCommandBuffer)(
    GR_DEVICE                        device,
    const GR_CMD_BUFFER_CREATE_INFO *pCreateInfo,
    GR_CMD_BUFFER                   *pCmdBuffer
);
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grBeginCommandBuffer)(
    GR_CMD_BUFFER cmdBuffer,
    GR_FLAGS      flags
);
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grEndCommandBuffer)(
    GR_CMD_BUFFER cmdBuffer
);
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grResetCommandBuffer)(
    GR_CMD_BUFFER cmdBuffer
);

// command buffer building functions
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grCmdClearColorImage)(
    GR_CMD_BUFFER cmdBuffer,
    GR_IMAGE image,
    const GR_FLOAT color[4],
    GR_UINT rangeCount,
    const GR_IMAGE_SUBRESOURCE_RANGE *pRanges
);
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grCmdClearColorImageRaw)(
    GR_CMD_BUFFER cmdBuffer,
    GR_IMAGE image,
    const GR_UINT32 color[4],
    GR_UINT rangeCount,
    const GR_IMAGE_SUBRESOURCE_RANGE *pRanges
);
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grCmdPrepareImages)(
    GR_CMD_BUFFER                    cmdBuffer,
    GR_UINT                          transitionCount,
    const GR_IMAGE_STATE_TRANSITION *pStateTransitions
);
MAGMA_EXTERN GR_RESULT (GR_STDCALL *grCmdPrepareMemoryRegions)(
    GR_CMD_BUFFER                     cmdBuffer,
    GR_UINT                           transitionCount,
    const GR_MEMORY_STATE_TRANSITION *pStateTransitions
);



// enumerations
typedef enum _GR_CHANNEL_FORMAT {
    GR_CH_FMT_UNDEFINED,
    GR_CH_FMT_R4G4,
    GR_CH_FMT_R4G4B4A4,
    GR_CH_FMT_R5G6B5,
    GR_CH_FMT_B5G6R5,
    GR_CH_FMT_R5G5B5A1,
    GR_CH_FMT_R8,
    GR_CH_FMT_R8G8,
    GR_CH_FMT_R8G8B8A8,
    GR_CH_FMT_B8G8R8A8,
    GR_CH_FMT_R10G11B11,
    GR_CH_FMT_R11G11B10,
    GR_CH_FMT_R10G10B10A2,
    GR_CH_FMT_R16,
    GR_CH_FMT_R16G16,
    GR_CH_FMT_R16G16B16A16,
    GR_CH_FMT_R32,
    GR_CH_FMT_R32G32,
    GR_CH_FMT_R32G32B32,
    GR_CH_FMT_R32G32B32A32,
    GR_CH_FMT_R16G8,
    GR_CH_FMT_R32G8,
    GR_CH_FMT_R9G9B9E5,
    GR_CH_FMT_BC1,
    GR_CH_FMT_BC2,
    GR_CH_FMT_BC3,
    GR_CH_FMT_BC4,
    GR_CH_FMT_BC5,
    GR_CH_FMT_BC6U,
    GR_CH_FMT_BC6S,
    GR_CH_FMT_BC7
} GR_CHANNEL_FORMAT;

typedef enum _GR_IMAGE_ASPECT {
    GR_IMAGE_ASPECT_COLOR = 0x1700,
    GR_IMAGE_ASPECT_DEPTH,
    GR_IMAGE_ASPECT_STENCIL
} GR_IMAGE_ASPECT;

typedef enum _GR_IMAGE_STATE {
    GR_IMAGE_STATE_DATA_TRANSFER = 0x1300,
    GR_IMAGE_STATE_GRAPHICS_SHADER_READ_ONLY,
    GR_IMAGE_STATE_GRAPHICS_SHADER_WRITE_ONLY,
    GR_IMAGE_STATE_GRAPHICS_SHADER_READ_WRITE,
    GR_IMAGE_STATE_COMPUTE_SHADER_READ_ONLY,
    GR_IMAGE_STATE_COMPUTE_SHADER_WRITE_ONLY,
    GR_IMAGE_STATE_COMPUTE_SHADER_READ_WRITE,
    GR_IMAGE_STATE_MULTI_SHADER_READ_ONLY,
    GR_IMAGE_STATE_TARGET_AND_SHADER_READ_ONLY,
    GR_IMAGE_STATE_UNINITIALIZED,
    GR_IMAGE_STATE_TARGET_RENDER_ACCESS_OPTIMAL,
    GR_IMAGE_STATE_TARGET_SHADER_ACCESS_OPTIMAL,
    GR_IMAGE_STATE_CLEAR,
    GR_IMAGE_STATE_RESOLVE_SOURCE,
    GR_IMAGE_STATE_RESOLVE_DESTINATION,
    GR_IMAGE_STATE_DISCARD,
    GR_IMAGE_STATE_DATA_TRANSFER_SOURCE,
    GR_IMAGE_STATE_DATA_TRANSFER_DESTINATION
} GR_IMAGE_STATE;

typedef enum _GR_INFO_TYPE {
    GR_INFO_TYPE_PHYSICAL_GPU_PROPERTIES = 0x6100,
    GR_INFO_TYPE_PHYSICAL_GPU_PERFORMANCE,
    GR_INFO_TYPE_PHYSICAL_GPU_QUEUE_PROPERTIES,
    GR_INFO_TYPE_PHYSICAL_GPU_MEMORY_PROPERTIES,
    GR_INFO_TYPE_PHYSICAL_GPU_IMAGE_PROPERTIES,

    GR_INFO_TYPE_MEMORY_HEAP_PROPERTIES = 0x6200,

    GR_INFO_TYPE_FORMAT_PROPERTIES = 0x6300,

    GR_INFO_TYPE_SUBRESOURCE_LAYOUT = 0x6400,

    GR_INFO_TYPE_MEMORY_REQUIREMENTS = 0x6800,
    GR_INFO_TYPE_PARENT_DEVICE,
    GR_INFO_TYPE_PARENT_PHYSICAL_GPU
} GR_INFO_TYPE;

typedef enum _GR_MEMORY_STATE {
    GR_MEMORY_STATE_DATA_TRANSFER = 0x1200,
    GR_MEMORY_STATE_GRAPHICS_SHADER_READ_ONLY,
    GR_MEMORY_STATE_GRAPHICS_SHADER_WRITE_ONLY,
    GR_MEMORY_STATE_GRAPHICS_SHADER_READ_WRITE,
    GR_MEMORY_STATE_COMPUTE_SHADER_READ_ONLY,
    GR_MEMORY_STATE_COMPUTE_SHADER_WRITE_ONLY,
    GR_MEMORY_STATE_COMPUTE_SHADER_READ_WRITE,
    GR_MEMORY_STATE_MULTI_USE_READ_ONLY,
    GR_MEMORY_STATE_INDEX_DATA,
    GR_MEMORY_STATE_INDIRECT_ARG,
    GR_MEMORY_STATE_WRITE_TIMESTAMP,
    GR_MEMORY_STATE_QUEUE_ATOMIC,
    GR_MEMORY_STATE_DISCARD,
    GR_MEMORY_STATE_DATA_TRANSFER_SOURCE,
    GR_MEMORY_STATE_DATA_TRANSFER_DESTINATION
} GR_MEMORY_STATE;

typedef enum _GR_NUM_FORMAT {
    GR_NUM_FMT_UNDEFINED,
    GR_NUM_FMT_UNORM,
    GR_NUM_FMT_SNORM,
    GR_NUM_FMT_UINT,
    GR_NUM_FMT_SINT,
    GR_NUM_FMT_FLOAT,
    GR_NUM_FMT_SRGB,
    GR_NUM_FMT_DS
} GR_NUM_FORMAT;

typedef enum _GR_PHYSICAL_GPU_TYPE {
    GR_GPU_TYPE_OTHER = 0x3000,
    GR_GPU_TYPE_INTEGRATED,
    GR_GPU_TYPE_DISCRETE,
    GR_GPU_TYPE_VIRTUAL
} GR_PHYSICAL_GPU_TYPE;

typedef enum _GR_QUEUE_TYPE {
    GR_QUEUE_UNIVERSAL = 0x1000,
    GR_QUEUE_COMPUTE
} GR_QUEUE_TYPE;

typedef enum _GR_RETURN_CODE {
    GR_SUCCESS = 0x10000,
    GR_UNSUPPORTED,
    GR_NOT_READY,
    GR_TIMEOUT,
    GR_EVENT_SET,
    GR_EVENT_RESET,

    GR_ERROR_UNKNOWN = 0x11000,
    GR_ERROR_UNAVAILABLE,
    GR_ERROR_INITIALIZATION_FAILED,
    GR_ERROR_OUT_OF_MEMORY,
    GR_ERROR_OUT_OF_GPU_MEMORY,
    GR_ERROR_DEVICE_ALREADY_CREATED,
    GR_ERROR_DEVICE_LOST,
    GR_ERROR_INVALID_POINTER,
    GR_ERROR_INVALID_VALUE,
    GR_ERROR_INVALID_HANDLE,
    GR_ERROR_INVALID_ORDINAL,
    GR_ERROR_INVALID_MEMORY_SIZE,
    GR_ERROR_INVALID_EXTENSION,
    GR_ERROR_INVALID_FLAGS,
    GR_ERROR_INVALID_ALIGNMENT,
    GR_ERROR_INVALID_FORMAT,
    GR_ERROR_INVALID_IMAGE,
    GR_ERROR_INVALID_DESCRIPTOR_SET_DATA,
    GR_ERROR_INVALID_QUEUE_TYPE,
    GR_ERROR_INVALID_OBJECT_TYPE,
    GR_ERROR_UNSUPPORTED_SHADER_IL_VERSION,
    GR_ERROR_BAD_SHADER_CODE,
    GR_ERROR_BAD_PIPELINE_DATA,
    GR_ERROR_TOO_MANY_MEMORY_REFERENCES,
    GR_ERROR_NOT_MAPPABLE,
    GR_ERROR_MEMORY_MAP_FAILED,
    GR_ERROR_MEMORY_UNMAP_FAILED,
    GR_ERROR_INCOMPATIBLE_DEVICE,
    GR_ERROR_INCOMPATIBLE_DRIVER,
    GR_ERROR_INCOMPLETE_COMMAND_BUFFER,
    GR_ERROR_BUILDING_COMMAND_BUFFER,
    GR_ERROR_MEMORY_NOT_BOUND,
    GR_ERROR_INCOMPATIBLE_QUEUE,
    GR_ERROR_NOT_SHAREABLE
} GR_RETURN_CODE;

typedef enum _GR_SYSTEM_ALLOC_TYPE {
    GR_SYSTEM_ALLOC_API_OBJECT = 0x2e00,
    GR_SYSTEM_ALLOC_INTERNAL,
    GR_SYSTEM_ALLOC_INTERNAL_TEMP,
    GR_SYSTEM_ALLOC_INTERNAL_SHADER,
    GR_SYSTEM_ALLOC_DEBUG
} GR_SYSTEM_ALLOC_TYPE;

typedef enum _GR_VALIDATION_LEVEL {
    GR_VALIDATION_LEVEL_0 = 0x8000,
    GR_VALIDATION_LEVEL_1,
    GR_VALIDATION_LEVEL_2,
    GR_VALIDATION_LEVEL_3,
    GR_VALIDATION_LEVEL_4
} _GR_VALIDATION_LEVEL;



// flags
typedef enum _GR_CMD_BUFFER_BUILD_FLAGS {
    GR_CMD_BUFFER_OPTIMIZE_GPU_SMALL_BATCH       = 1 << 0,
    GR_CMD_BUFFER_OPTIMIZE_PIPELINE_SWITCH       = 1 << 1,
    GR_CMD_BUFFER_OPTIMIZE_ONE_TIME_SUBMIT       = 1 << 2,
    GR_CMD_BUFFER_OPTIMIZE_DESCRIPTOR_SET_SWITCH = 1 << 3
} GR_CMD_BUFFER_BUILD_FLAGS;

typedef enum _GR_DEVICE_CREATE_FLAGS {
    GR_DEVICE_CREATE_VALIDATION = 1 << 0
} GR_DEVICE_CREATE_FLAGS;

typedef enum _GR_IMAGE_USAGE_FLAGS {
    GR_IMAGE_USAGE_SHADER_ACCESS_READ  = 1 << 0,
    GR_IMAGE_USAGE_SHADER_ACCESS_WRITE = 1 << 1,
    GR_IMAGE_USAGE_COLOR_TARGET        = 1 << 2,
    GR_IMAGE_USAGE_DEPTH_STENCIL       = 1 << 3
} GR_IMAGE_USAGE_FLAGS;

typedef enum _GR_MEMORY_PROPERTY_FLAGS {
    GR_MEMORY_MIGRATION_SUPPORT         = 1 << 0,
    GR_MEMORY_VIRTUAL_REMAPPING_SUPPORT = 1 << 1,
    GR_MEMORY_PINNING_SUPPORT           = 1 << 2,
    GR_MEMORY_PREFER_GLOBAL_REFS        = 1 << 3
} GR_MEMORY_PROPERTY_FLAGS;

typedef enum _GR_MEMORY_REF_FLAGS {
    GR_MEMORY_REF_READ_ONLY = 1 << 0
} GR_MEMORY_REF_FLAGS;



// structures
struct _GR_ALLOC_CALLBACKS {
    GR_ALLOC_FUNCTION pfnAlloc;
    GR_FREE_FUNCTION  pfnFree;
};

struct _GR_APPLICATION_INFO {
    const GR_CHAR *pAppName;
    GR_UINT32      appVersion;
    const GR_CHAR *pEngineName;
    GR_UINT32      engineVersion;
    GR_UINT32      apiVersion;
};

struct _GR_CMD_BUFFER_CREATE_INFO {
    GR_ENUM  queueType;
    GR_FLAGS flags;
};

struct _GR_DEVICE_CREATE_INFO {
    GR_UINT                            queueRecordCount;
    const GR_DEVICE_QUEUE_CREATE_INFO *pRequestedQueues;
    GR_UINT                            extensionCount;
    const GR_CHAR *const              *ppEnabledExtensionNames;
    GR_ENUM                            maxValidationLevel;
    GR_FLAGS                           flags;
};

struct _GR_DEVICE_QUEUE_CREATE_INFO {
    GR_ENUM queueType;
    GR_UINT queueCount;
};

struct _GR_EXTENT2D {
    GR_INT width;
    GR_INT height;
};

struct _GR_EXTENT3D {
    GR_INT width;
    GR_INT height;
    GR_INT depth;
};

struct _GR_FORMAT {
    GR_UINT32 channelFormat : 16;
    GR_UINT32 numericFormat : 16;
};

struct _GR_IMAGE_SUBRESOURCE_RANGE {
    GR_ENUM aspect;
    GR_UINT baseMipLevel;
    GR_UINT mipLevels;
    GR_UINT baseArraySlice;
    GR_UINT arraySize;
};

struct _GR_IMAGE_STATE_TRANSITION {
    GR_IMAGE                   image;
    GR_ENUM                    oldState;
    GR_ENUM                    newState;
    GR_IMAGE_SUBRESOURCE_RANGE subresourceRange;
};

struct _GR_MEMORY_ALLOC_INFO {
    GR_GPU_SIZE size;
    GR_GPU_SIZE alignment;
    GR_FLAGS    flags;
    GR_UINT     heapCount;
    GR_UINT     heaps[GR_MAX_MEMORY_HEAPS];
    GR_ENUM     memPriority;
};

struct _GR_MEMORY_REF {
    GR_GPU_MEMORY mem;
    GR_FLAGS      flags;
};

struct _GR_MEMORY_STATE_TRANSITION {
    GR_GPU_MEMORY mem;
    GR_ENUM       oldState;
    GR_ENUM       newState;
    GR_GPU_SIZE   offset;
    GR_GPU_SIZE   regionSize;
};

struct _GR_OFFSET2D {
    GR_INT x;
    GR_INT y;
};

struct _GR_OFFSET3D {
    GR_INT x;
    GR_INT y;
    GR_INT z;
};

struct _GR_PHYSICAL_GPU_IMAGE_PROPERTIES {
    GR_UINT     maxSliceWidth;
    GR_UINT     maxSliceHeight;
    GR_UINT     maxDepth;
    GR_UINT     maxArraySlices;
    GR_UINT     reserved1;
    GR_UINT     reserved2;
    GR_GPU_SIZE maxMemoryAlignment;
    GR_UINT32   sparseImageSupportLevel;
    GR_FLAGS    flags;
};

struct _GR_PHYSICAL_GPU_MEMORY_PROPERTIES {
    GR_FLAGS    flags;
    GR_GPU_SIZE virtualMemPageSize;
    GR_GPU_SIZE maxVirtualMemSize;
    GR_GPU_SIZE maxPhysicalMemSize;
};

struct _GR_PHYSICAL_GPU_PERFORMANCE {
    GR_FLOAT maxGpuClock;
    GR_FLOAT aluPerClock;
    GR_FLOAT texPerClock;
    GR_FLOAT primsPerClock;
    GR_FLOAT pixelsPerClock;
};

struct _GR_PHYSICAL_GPU_PROPERTIES {
    GR_UINT32   apiVersion;
    GR_UINT32   driverVersion;
    GR_UINT32   vendorId;
    GR_UINT32   deviceId;
    GR_ENUM     gpuType;
    GR_CHAR     gpuName[GR_MAX_PHYSICAL_GPU_NAME];
    GR_UINT     maxMemRefsPerSubmission;
    GR_GPU_SIZE reserved;
    GR_GPU_SIZE maxInlineMemoryUpdateSize;
    GR_UINT     maxBoundDescriptorSets;
    GR_UINT     maxThreadGroupSize;
    GR_UINT64   timestampFrequency;
    GR_BOOL     multiColorTargetClears;
};

struct _GR_RECT {
    GR_OFFSET2D offset;
    GR_EXTENT2D extent;
};

struct _GR_VIRTUAL_MEMORY_REMAP_RANGE {
    GR_GPU_MEMORY virtualMem;
    GR_GPU_SIZE   virtualStartPage;
    GR_GPU_MEMORY realMem;
    GR_GPU_SIZE   realStartPage;
    GR_GPU_SIZE   pageCount;
};



#ifdef __cplusplus
}
#endif

#endif
