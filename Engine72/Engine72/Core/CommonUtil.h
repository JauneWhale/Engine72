#pragma once

#include <windows.h>
#include <cassert>
#include <string>
#include <memory>
#include <algorithm>
#include <vector>
#include <array>
#include <unordered_map>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <sstream>
#include <wrl.h>
#include "CRTDebugDefines.h"

inline float GetAspectRatio(int width, int height)
{
	return static_cast<float>(width) / height;
}