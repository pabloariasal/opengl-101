#pragma once

#include<QGLWidget>

class MyGlWindow : public QGLWidget
{

public:

protected:
    void initializeGL();
    void paintGL();

};
