#ifndef OPENGL_VISUALIZER_HPP
#define OPENGP_VISUALIZER_HPP

#include "utils.hpp"
#include "texture_loader.hpp"
#include<vector>

extern std::vector<Vector3D> orbit_points;

void initOpenGL(int argc, char** argv);
void setOrbitData(std::vector<Vector3D> orbit_points);
void startRendering();
void display();
#endif