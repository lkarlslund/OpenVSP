#ifndef _VSP_COMMON_FUNCTIONALITIES_H
#define _VSP_COMMON_FUNCTIONALITIES_H

namespace VSPGraphic
{
namespace Common
{
enum VSPenum
{
    VSP_TRIANGLES,
    VSP_QUADS,
    VSP_LINES,
    VSP_LINE_LOOP,
    VSP_LINE_STRIP,
    VSP_POINTS,
    VSP_DRAW_SOLID,
    VSP_DRAW_MAPPED,
    VSP_DRAW_SHADED,
    VSP_DRAW_TEXTURED,
    VSP_DRAW_WIRE_FRAME,
    VSP_DRAW_WIRE_FRAME_SOLID,
    VSP_DRAW_WIRE_FRAME_MAPPED,
    VSP_DRAW_WIRE_FRAME_SHADED,
    VSP_DRAW_WIRE_FRAME_TRANSPARENT_BACK,
    VSP_CAM_ORTHO,
    VSP_CAM_PERSPECTIVE,
    VSP_CAM_TOP,
    VSP_CAM_FRONT,
    VSP_CAM_FRONT_YUP,
    VSP_CAM_LEFT,
    VSP_CAM_LEFT_ISO,
    VSP_CAM_BOTTOM,
    VSP_CAM_REAR,
    VSP_CAM_RIGHT,
    VSP_CAM_RIGHT_ISO,
    VSP_CAM_CENTER,
    VSP_OBJECT_MARKER,
    VSP_OBJECT_ENTITY,
    VSP_OBJECT_CFD_ENTITY,
    VSP_OBJECT_PROTRACTOR,
    VSP_OBJECT_RULER,
    VSP_OBJECT_PROBE,
    VSP_OBJECT_PICK_VERTEX,
    VSP_OBJECT_PICK_GEOM,
    VSP_OBJECT_PICK_LOCATION,
    VSP_TEXTURE_BLENDED,
    VSP_TEXTURE_LAYERED,
    VSP_BACKGROUND_COLOR,
    VSP_BACKGROUND_IMAGE,
};
}
}
#endif
