// This is the header file to be included by ever other project that uses the Dyson engine
#pragma once

#include "core.h"

#include "graphics/window.h"
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "graphics/sprite.h"
#include "graphics/tilemap.h"
#include "graphics/batch_renderer.h"
#include "graphics/text.h"
#include "graphics/data_buffers/vertex_array.h"
#include "graphics/data_buffers/vertex_buffer.h"
#include "graphics/data_buffers/index_buffer.h"

#include "maths/vec/vec2.h"
#include "maths/vec/vec3.h"
#include "maths/vec/vec4.h"
#include "maths/mat/mat4.h"
#include "maths/constants.h"

#include "util/error_handling.h"
#include "util/input.h"
#include "util/timer.h"
#include "util/orthographic_camera.h"
#include "util/audio.h"