#include "ofMain.h"
#include "ofApp.h"
#include "ControlApp.h"
#include "GLFW/glfw3.h"

//========================================================================
int main( ){
    
    glfwInit();
    
    int monitorCount;
    GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
  
    ofGLFWWindowSettings settings;
    settings.setGLVersion(3,2);

    settings.setSize(600, 960);
    if (monitorCount > 1) {
        settings.monitor = 1;
        settings.windowMode = OF_FULLSCREEN;
    }
    else {
        settings.setPosition(glm::vec2(300,0));
    }
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

    ofGLFWWindowSettings settings2;
    settings2.setGLVersion(3,2);
    settings2.setSize(300, 300);
    if (monitorCount > 1) {
        settings2.setPosition(glm::vec2(300,0));
    }
    else {
        settings2.setPosition(glm::vec2(0,0));
    }
    settings2.resizable = false;
    shared_ptr<ofAppBaseWindow> controlWindow = ofCreateWindow(settings2);

    shared_ptr<ofApp> mainApp(new ofApp);
    shared_ptr<ControlApp> controlApp(new ControlApp);
    controlApp->app = mainApp;
    controlApp->appWindowSize = mainWindow->getWindowSize();

    
    ofRunApp(mainWindow, mainApp);
    ofRunApp(controlWindow, controlApp);
    ofRunMainLoop();

}
