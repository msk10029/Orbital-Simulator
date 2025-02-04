#include <GL/glut.h>
#include <vector>
#include <cmath>
#include "utils.hpp"
#include "opengl_visualizer.hpp"
#include "texture_loader.hpp"


std::vector<Vector3D> orbit_points;
int satelliteIndex = 0;

// Camera Controls
float cameraDistance = 5.0f;  // Initial distance from Earth
float cameraAngleX = 0.0f;    // Horizontal rotation angle
float cameraAngleY = 0.0f;    // Vertical rotation angle


float zoomLevel = 1.0;  // Zoom scale
float panX = 0.0, panY = 0.0;

void setOrbitData(std::vector<Vector3D> points) {
    orbit_points = points;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear both color & depth buffers
    glLoadIdentity();

    // Position the camera
    gluLookAt(cameraDistance * cos(cameraAngleX) * cos(cameraAngleY),
          cameraDistance * sin(cameraAngleY),
          cameraDistance * sin(cameraAngleX) * cos(cameraAngleY),
          0.0, 0.0, 0.0,  // Look at the origin
          0.0, 1.0, 0.0); // Up vector // Up vector (y-axis)

    // Draw Earth
    glColor3f(0.0, 0.0, 1.0);
    glutSolidSphere(0.6, 50, 50);  // Earth (radius 0.6, detailed with 50 slices)

    // Path
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for (auto& point : orbit_points) {
        glVertex3f(point.x / 10000.0, point.y / 10000.0, point.z / 10000.0);
    }
    glEnd();

    // Draw Moving Satellite
    if (!orbit_points.empty()) {
        glColor3f(1.0, 0.0, 0.0);
        glPointSize(5.0);
        glBegin(GL_POINTS);
        glVertex3f(orbit_points[satelliteIndex].x / 10000.0,
                   orbit_points[satelliteIndex].y / 10000.0,
                   orbit_points[satelliteIndex].z / 10000.0);
        glEnd();
    }

    glutSwapBuffers();  // Swap buffers for smooth animation
}


void initOpenGL(int argc, char** argv) {
    // glutInit(&argc, argv);
    // glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  // Enable depth buffer
    // glutInitWindowSize(800, 800);
    // glutCreateWindow("3D Orbital Path Visualization");

    // glEnable(GL_DEPTH_TEST);  // Enable depth testing for 3D rendering

    // glClearColor(0.0, 0.0, 0.0, 1.0);  // Black background
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // gluPerspective(45.0, 1.0, 0.1, 100.0);  // Set 3D perspective
    // glMatrixMode(GL_MODELVIEW);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("3D Orbital Path Visualization");

    glEnable(GL_DEPTH_TEST);  // Enable depth buffering for proper 3D rendering
    glEnable(GL_LIGHTING);    // Enable OpenGL lighting system
    glEnable(GL_LIGHT0);      // Enable the first light source
    glEnable(GL_COLOR_MATERIAL);  // Allow color and lighting to interact

    // Set Light Position (Simulating the Sun)
    GLfloat lightPos[] = {5.0f, 5.0f, 5.0f, 1.0f};  // Light positioned at (5,5,5)
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    // Set Light Properties
    GLfloat ambientLight[]  = {0.2f, 0.2f, 0.2f, 1.0f};  // Dim ambient light
    GLfloat diffuseLight[]  = {0.8f, 0.8f, 0.8f, 1.0f};  // Bright white light
    GLfloat specularLight[] = {1.0f, 1.0f, 1.0f, 1.0f};  // Specular highlight

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

    // Set Material Properties for Objects
    GLfloat matSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};  // Bright specular highlights
    GLfloat matShininess[] = {50.0f};  // Shininess factor

    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void handleKeys(unsigned char key, int x, int y) {
    switch (key) {
        case '+': cameraDistance -= 0.2f; break;
        case '-': cameraDistance += 0.2f; break;
        case 'w': cameraAngleY += 0.1f; break;
        case 's': cameraAngleY -= 0.1f; break;
        case 'a': cameraAngleX -= 0.1f; break;
        case 'd': cameraAngleX += 0.1f; break;
    }
    glutPostRedisplay();
}

void update(int value) {
    satelliteIndex = (satelliteIndex + 1) % orbit_points.size();  // Move satellite forward
    glutPostRedisplay();  // Redraw the screen
    glutTimerFunc(50, update, 0);  // Call again after 50ms
}

void startRendering() {
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeys);
    glutTimerFunc(50, update, 0);
    glutMainLoop();
}