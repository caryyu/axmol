/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

https://axmolengine.github.io/

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __CCGLVIEW_H__
#define __CCGLVIEW_H__

#include "base/Types.h"
#include "base/EventTouch.h"

#include <functional>
#include <vector>

#if (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32)
#    include <windows.h>
#endif /* (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) */

#if (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX)
#    define AX_ICON_SET_SUPPORT true
#endif /* (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) || (AX_TARGET_PLATFORM == AX_PLATFORM_LINUX) */

/** There are some Resolution Policy for Adapt to the screen. */
enum class ResolutionPolicy
{
    /** The entire application is visible in the specified area without trying to preserve the original aspect ratio.
     * Distortion can occur, and the application may appear stretched or compressed.
     */
    EXACT_FIT,
    /** The entire application fills the specified area, without distortion but possibly with some cropping,
     * while maintaining the original aspect ratio of the application.
     */
    NO_BORDER,
    /** The entire application is visible in the specified area without distortion while maintaining the original
     * aspect ratio of the application. Borders can appear on two sides of the application.
     */
    SHOW_ALL,
    /** The application takes the height of the design resolution size and modifies the width of the internal
     * canvas so that it fits the aspect ratio of the device.
     * No distortion will occur however you must make sure your application works on different
     * aspect ratios.
     */
    FIXED_HEIGHT,
    /** The application takes the width of the design resolution size and modifies the height of the internal
     * canvas so that it fits the aspect ratio of the device.
     * No distortion will occur however you must make sure your application works on different
     * aspect ratios.
     */
    FIXED_WIDTH,

    UNKNOWN,
};

/** @struct GLContextAttrs
 *
 * There are six opengl Context Attrs.
 */
struct GLContextAttrs
{
    int redBits;
    int greenBits;
    int blueBits;
    int alphaBits;
    int depthBits;
    int stencilBits;
    int multisamplingCount;
    bool visible   = true;
    bool decorated = true;
    bool vsync       = false;
#if defined(_WIN32)
    void* viewParent = nullptr;
#endif
};

NS_AX_BEGIN

class Scene;
class Renderer;
class Director;

/**
 * @addtogroup platform
 * @{
 */
/**
 * @brief By GLView you can operate the frame information of EGL view through some function.
 */
class AX_DLL GLView : public Object
{
    friend class Director;
public:
    /**
     * @js ctor
     */
    GLView();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~GLView();

    /** Force destroying EGL view, subclass must implement this method.
     *
     * @lua endToLua
     */
    virtual void end() = 0;

    /** Get whether opengl render system is ready, subclass must implement this method. */
    virtual bool isOpenGLReady() = 0;

    /** Exchanges the front and back buffers, subclass must implement this method. */
    virtual void swapBuffers() = 0;

    /** Open or close IME keyboard , subclass must implement this method.
     *
     * @param open Open or close IME keyboard.
     */
    virtual void setIMEKeyboardState(bool open) = 0;

    /** When the window is closed, it will return false if the platforms is Ios or Android.
     * If the platforms is windows or Mac,it will return true.
     *
     * @return In ios and android it will return false,if in windows or Mac it will return true.
     */
    virtual bool windowShouldClose() { return false; };

    /** Static method and member so that we can modify it on all platforms before create OpenGL context.
     *
     * @param glContextAttrs The OpenGL context attrs.
     */
    static void setGLContextAttrs(GLContextAttrs& glContextAttrs);

    /** Return the OpenGL context attrs.
     *
     * @return Return the OpenGL context attrs.
     */
    static GLContextAttrs getGLContextAttrs();

    /** The OpenGL context attrs. */
    static GLContextAttrs _glContextAttrs;

    /** Polls the events. */
    virtual void pollEvents();

    /**
     * Get the frame size of EGL view.
     * In general, it returns the screen size since the EGL view is a fullscreen view.
     *
     * @return The frame size of EGL view.
     */
    virtual Vec2 getFrameSize() const;

    /**
     * Set the frame size of EGL view.
     *
     * @param width The width of the fram size.
     * @param height The height of the fram size.
     */
    virtual void setFrameSize(float width, float height);

    /** Set zoom factor for frame. This methods are for
     * debugging big resolution (e.g.new ipad) app on desktop.
     *
     * @param zoomFactor The zoom factor for frame.
     */
    virtual void setFrameZoomFactor(float /*zoomFactor*/) {}

    /** Get zoom factor for frame. This methods are for
     * debugging big resolution (e.g.new ipad) app on desktop.
     *
     * @return The zoom factor for frame.
     */
    virtual float getFrameZoomFactor() const { return 1.0; }

    /**
     * Hide or Show the mouse cursor if there is one.
     *
     * @param isVisible Hide or Show the mouse cursor if there is one.
     */
    virtual void setCursorVisible(bool /*isVisible*/) {}

    /** Get retina factor.
     *
     * @return The retina factor.
     */
    virtual int getRetinaFactor() const { return 1; }

    /** Only works on ios platform. Set Content Scale of the Factor. */
    virtual bool setContentScaleFactor(float /*scaleFactor*/) { return false; }

    /** Only works on ios platform. Get Content Scale of the Factor. */
    virtual float getContentScaleFactor() const { return 1.0; }

    /** Returns whether or not the view is in Retina Display mode.
     *
     * @return Returns whether or not the view is in Retina Display mode.
     */
    virtual bool isRetinaDisplay() const { return false; }

#if (AX_TARGET_PLATFORM == AX_PLATFORM_IOS)
    virtual void* getEAGLView() const { return nullptr; }
#endif /* (AX_TARGET_PLATFORM == AX_PLATFORM_IOS) */

    /**
     * Get the visible area size of opengl viewport.
     *
     * @return The visible area size of opengl viewport.
     */
    virtual Vec2 getVisibleSize() const;

    /**
     * Get the visible origin point of opengl viewport.
     *
     * @return The visible origin point of opengl viewport.
     */
    virtual Vec2 getVisibleOrigin() const;

    /**
     * Get the visible rectangle of opengl viewport.
     *
     * @return The visible rectangle of opengl viewport.
     */
    virtual Rect getVisibleRect() const;

    /**
     * Gets safe area rectangle
     */
    virtual Rect getSafeAreaRect() const;

    /**
     * Set the design resolution size.
     * @param width Design resolution width.
     * @param height Design resolution height.
     * @param resolutionPolicy The resolution policy desired, you may choose:
     *                         [1] EXACT_FIT Fill screen by stretch-to-fit: if the design resolution ratio of width to
     * height is different from the screen resolution ratio, your game view will be stretched. [2] NO_BORDER Full screen
     * without black border: if the design resolution ratio of width to height is different from the screen resolution
     * ratio, two areas of your game view will be cut. [3] SHOW_ALL  Full screen with black border: if the design
     * resolution ratio of width to height is different from the screen resolution ratio, two black borders will be
     * shown.
     */
    virtual void setDesignResolutionSize(float width, float height, ResolutionPolicy resolutionPolicy);

    /** Get design resolution size.
     *  Default resolution size is the same as 'getFrameSize'.
     *
     * @return The design resolution size.
     */
    virtual const Vec2& getDesignResolutionSize() const;

    /**
     * Set opengl view port rectangle with points.
     *
     * @param x Set the points of x.
     * @param y Set the points of y.
     * @param w Set the width of  the view port
     * @param h Set the Height of the view port.
     */
    virtual void setViewPortInPoints(float x, float y, float w, float h);

    /**
     * Set Scissor rectangle with points.
     *
     * @param x Set the points of x.
     * @param y Set the points of y.
     * @param w Set the width of  the view port
     * @param h Set the Height of the view port.
     */
    virtual void setScissorInPoints(float x, float y, float w, float h);

    /**
     * Get whether GL_SCISSOR_TEST is enable.
     *
     * @return Whether GL_SCISSOR_TEST is enable.
     */
    virtual bool isScissorEnabled();

    /**
     * Get the current scissor rectangle.
     *
     * @return The current scissor rectangle.
     */
    virtual Rect getScissorRect() const;

    /** Set the view name.
     *
     * @param viewname A string will be set to the view as name.
     */
    virtual void setViewName(std::string_view viewname);

    /** Get the view name.
     *
     * @return The view name.
     */
    std::string_view getViewName() const;

    /** Touch events are handled by default; if you want to customize your handlers, please override this function.
     *
     * @param num The number of touch.
     * @param ids The identity of the touch.
     * @param xs The points of x.
     * @param ys The points of y.
     */
    virtual void handleTouchesBegin(int num, intptr_t ids[], float xs[], float ys[]);

    /** Touch events are handled by default; if you want to customize your handlers, please override this function.
     *
     * @param num The number of touch.
     * @param ids The identity of the touch.
     * @param xs The points of x.
     * @param ys The points of y.
     */
    virtual void handleTouchesMove(int num, intptr_t ids[], float xs[], float ys[]);

    /** Touch events are handled by default; if you want to customize your handlers, please override this function.
     *
     * @param num The number of touch.
     * @param ids The identity of the touch.
     * @param xs The points of x.
     * @param ys The points of y.
     * @param fs The force of 3d touches.
     # @param ms The maximum force of 3d touches
     */
    virtual void handleTouchesMove(int num, intptr_t ids[], float xs[], float ys[], float fs[], float ms[]);

    /** Touch events are handled by default; if you want to customize your handlers, please override this function.
     *
     * @param num The number of touch.
     * @param ids The identity of the touch.
     * @param xs The points of x.
     * @param ys The points of y.
     */
    virtual void handleTouchesEnd(int num, intptr_t ids[], float xs[], float ys[]);

    /** Touch events are handled by default; if you want to customize your handlers, please override this function.
     *
     * @param num The number of touch.
     * @param ids The identity of the touch.
     * @param xs The points of x.
     * @param ys The points of y.
     */
    virtual void handleTouchesCancel(int num, intptr_t ids[], float xs[], float ys[]);

    /** Set window icon (implemented for windows and linux).
     *
     * @param filename A path to image file, e.g., "icons/cusom.png".
     */
    virtual void setIcon(std::string_view filename) const {};

    /** Set window icon (implemented for windows and linux).
     * Best icon (based on size) will be auto selected.
     *
     * @param filelist The array contains icons.
     */
    virtual void setIcon(const std::vector<std::string_view>& filelist) const {};

    /** Set default window icon (implemented for windows and linux).
     * On windows it will use icon from .exe file (if included).
     * On linux it will use default window icon.
     */
    virtual void setDefaultIcon() const {};

    /**
     * Get the opengl view port rectangle.
     *
     * @return Return the opengl view port rectangle.
     */
    const Rect& getViewPortRect() const;

    /**
     * Get list of all active touches.
     *
     * @return A list of all active touches.
     */
    std::vector<Touch*> getAllTouches() const;

    /**
     * Get scale factor of the horizontal direction.
     *
     * @return Scale factor of the horizontal direction.
     */
    float getScaleX() const;

    /**
     * Get scale factor of the vertical direction.
     *
     * @return Scale factor of the vertical direction.
     */
    float getScaleY() const;

    /** Returns the current Resolution policy.
     *
     * @return The current Resolution policy.
     */
    ResolutionPolicy getResolutionPolicy() const { return _resolutionPolicy; }

#if (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32)
    virtual HWND getWin32Window() = 0;
#endif /* (AX_TARGET_PLATFORM == AX_PLATFORM_WIN32) */

#if (AX_TARGET_PLATFORM == AX_PLATFORM_MAC)
    virtual void* getCocoaWindow() = 0;
    virtual void* getNSGLContext() = 0;  // stevetranby: added
#endif                                /* (AX_TARGET_PLATFORM == AX_PLATFORM_MAC) */

    /**
     * Renders a Scene with a Renderer
     * This method is called directly by the Director
     */
    void renderScene(Scene* scene, Renderer* renderer);

protected:
    /**
    * queue a priority operation in render thread for non-PC platforms, even through app in background
    * invoked by Director
    */
    virtual void queueOperation(AsyncOperation op, void* param = nullptr);

    void updateDesignResolutionSize();

    void handleTouchesOfEndOrCancel(EventTouch::EventCode eventCode, int num, intptr_t ids[], float xs[], float ys[]);

    // real screen size
    Vec2 _screenSize;
    // resolution size, it is the size appropriate for the app resources.
    Vec2 _designResolutionSize;
    // the view port size
    Rect _viewPortRect;
    // the view name
    std::string _viewName;

    float _scaleX;
    float _scaleY;
    ResolutionPolicy _resolutionPolicy;
};

// end of platform group
/// @}

NS_AX_END

#endif /* __CCGLVIEW_H__ */
