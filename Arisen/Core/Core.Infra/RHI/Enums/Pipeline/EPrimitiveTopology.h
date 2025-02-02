#pragma once

namespace ArisenEngine::RHI
{
    typedef enum EPrimitiveTopology {
        PRIMITIVE_TOPOLOGY_POINT_LIST = 0,
        PRIMITIVE_TOPOLOGY_LINE_LIST = 1,
        PRIMITIVE_TOPOLOGY_LINE_STRIP = 2,
        PRIMITIVE_TOPOLOGY_TRIANGLE_LIST = 3,
        PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP = 4,
        PRIMITIVE_TOPOLOGY_TRIANGLE_FAN = 5,
        PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY = 6,
        PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY = 7,
        PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY = 8,
        PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY = 9,
        PRIMITIVE_TOPOLOGY_PATCH_LIST = 10,
        PRIMITIVE_TOPOLOGY_MAX_ENUM = 0x7FFFFFFF
    } EPrimitiveTopology;
}
