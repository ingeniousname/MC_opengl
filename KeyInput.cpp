#include "KeyInput.h"
#include <algorithm>

std::vector<KeyInput*> KeyInput::_instances;


KeyInput::KeyInput(std::vector<int> keysToListen, std::vector<int> keysToListenRelease)
{

    // add keys, which press is listened
    for (int x : keysToListen)
        keymap.insert(std::make_pair(x, false));

    // add keys, which release is listened
    for (int x : keysToListenRelease)
        releasemap.insert(std::make_pair(x, false));

    KeyInput::_instances.push_back(this);
}

KeyInput::~KeyInput()
{
    _instances.erase(std::remove(_instances.begin(), _instances.end(), this), _instances.end());
}

void KeyInput::setupKeyCallback(GLFWwindow* window)
{
    // set key callbacks
    glfwSetKeyCallback(window, KeyInput::key_callback);
    glfwSetMouseButtonCallback(window, KeyInput::mouse_button_callback);
}

void KeyInput::setKeyDown(int key, bool flag)
{
    // find a key and then set a flag
    auto it = keymap.find(key);
    if (it != keymap.end())
        keymap[key] = flag;
}

bool KeyInput::getKeyDown(int key)
{
    //find a key and check if it is down
    bool result;
    auto it = keymap.find(key);
    if (it != keymap.end())
        result = keymap[key];
    return result;
}

bool KeyInput::getMouseButtonDown(int key)
{
    // we want the mouse button to be pressed only once per action
    bool result = getKeyDown(key);
    if (result)
    {
        // if the key is held and released, set it to not released and get a true output (key has just been pressed)
        if (getKeyReleased(key))
        {
            setKeyReleased(key, false);
            return true;
        }
        // if the key is not released - do not repeat the action
        return false;
    }
    else
    {
        // if it is not released - release it, you do not hold it now
        if (!getKeyReleased(key))
            setKeyReleased(key, true);
        return false;
    }
}

void KeyInput::setKeyReleased(int key, bool flag)
{
    // set key released / or else
    auto it = releasemap.find(key);
    if (it != releasemap.end())
        releasemap[key] = flag;
}

bool KeyInput::getKeyReleased(int key)
{
    // check if a key is released
    bool result;
    auto it = releasemap.find(key);
    if (it != releasemap.end())
        result = releasemap[key];
    return result;
}

void KeyInput::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    for (KeyInput* instance : _instances)
        instance->setKeyDown(key, action != GLFW_RELEASE);
}

void KeyInput::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    for (KeyInput* instance : _instances)
            instance->setKeyDown(button, action == GLFW_PRESS);
     
        
    
}
