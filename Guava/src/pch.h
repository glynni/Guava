#pragma once

/*Logging*******************************************************/
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

/*OpenGL********************************************************/
#include <glad/glad.h>

/*Window********************************************************/
#include <GLFW/glfw3.h>

/*ImGUI********************************************************/
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

/*Math********************************************************/
#include <glm.hpp>
#include <gtx/transform.hpp>
#include <gtc/matrix_transform.hpp>
using namespace glm;

/*Model importing***********************************************/
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

/*Strings*******************************************************/
#include <string>
using std::string;
using std::string_view;

/*Streams, File IO**********************************************/
#include <fstream>
#include <sstream>
#include <iostream>
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::cin;
using std::cout;

/*Memory******************************************************/
#include <memory>
template<typename T>
using scope = std::unique_ptr<T>;

template<typename T, typename ... Args>
constexpr scope<T> CreateScope(Args&& ... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using ref = std::shared_ptr<T>;

template<typename T, typename ... Args>
constexpr scope<T> CreateRef(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

/*Time********************************************************/
#include <chrono>
using namespace		std::chrono_literals;
using hr_clock =	std::chrono::high_resolution_clock;
using time_point =	std::chrono::high_resolution_clock::time_point;
using duration =	std::chrono::duration<double>;

/*Threads******************************************************/
#include <thread>
#include <future>
using std::thread;
using std::mutex;
using std::future;
using std::scoped_lock;

/*Utility******************************************************/
#include <utility>

/*Algorithms***************************************************/
#include <algorithm>
#include <execution>

/*Data structures***********************************************/
#include <unordered_map>
#include <map>
#include <set>
#include <queue>
#include <unordered_set>
#include <vector>
template<typename T, typename U>
using u_map = std::unordered_map<T, U>;

template<typename T>
using u_set = std::unordered_set<T>;

using std::vector;
using std::map;
using std::set;

/*Engine********************************************************/
#include "Engine/Core/Core.h"
#include "Engine/Core/Log.h"
using Byte = unsigned char;