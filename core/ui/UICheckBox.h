/****************************************************************************
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

#ifndef __UICHECKBOX_H__
#define __UICHECKBOX_H__

#include "ui/UIAbstractCheckButton.h"
#include "ui/GUIExport.h"

/**
 * @addtogroup ui
 * @{
 */
NS_AX_BEGIN

namespace ui
{

/**
 *  Checkbox is a specific type of two-states button that can be either checked or unchecked.
 */
class AX_GUI_DLL CheckBox : public AbstractCheckButton
{

    DECLARE_CLASS_GUI_INFO

public:
    /**
     * CheckBox event type, currently only "selected" and "unselected" event are cared.
     */
    enum class EventType
    {
        SELECTED,
        UNSELECTED
    };

    /**
     * A callback which will be called after certain CheckBox event issue.
     * @see `CheckBox::EventType`
     */
    typedef std::function<void(Object*, CheckBox::EventType)> ccCheckBoxCallback;

    /**
     * Default constructor.
     *
     * @lua new
     */
    CheckBox();

    /**
     * Default destructor.
     *
     * @lua NA
     */
    virtual ~CheckBox();

    /**
     * Create and return a empty CheckBox instance pointer.
     */
    static CheckBox* create();

    /**
     * Create an checkbox with various images.
     *
     * @param backGround    backGround texture.
     * @param backGroundSelected    backGround selected state texture.
     * @param cross    cross texture.
     * @param backGroundDisabled    backGround disabled state texture.
     * @param frontCrossDisabled    cross dark state texture.
     * @param texType    @see `Widget::TextureResType`
     *
     * @return A CheckBox instance pointer.
     */
    static CheckBox* create(std::string_view backGround,
                            std::string_view backGroundSelected,
                            std::string_view cross,
                            std::string_view backGroundDisabled,
                            std::string_view frontCrossDisabled,
                            TextureResType texType = TextureResType::LOCAL);

    /**
     * Another factory method to create a CheckBox instance.
     * This method uses less resource to create a CheckBox.
     * @param backGround The background image name in `std::string`.
     * @param cross The cross image name in `std::string`.
     * @param texType  The texture's resource type in `Widget::TextureResType`.
     * @return A CheckBox instance pointer
     */
    static CheckBox* create(std::string_view backGround,
                            std::string_view cross,
                            TextureResType texType = TextureResType::LOCAL);

    /**
     *Add a callback function which would be called when checkbox is selected or unselected.
     *@param callback A std::function with type @see `ccCheckBoxCallback`
     */
    void addEventListener(const ccCheckBoxCallback& callback);

    // override functions
    virtual std::string getDescription() const override;

    virtual void onTouchEnded(Touch* touch, Event* unusedEvent) override;

protected:
    virtual void dispatchSelectChangedEvent(bool selected) override;

    virtual Widget* createCloneInstance() override;
    virtual void copySpecialProperties(Widget* model) override;

protected:
    // if you use the old event callback, it will retain the _checkBoxEventListener
    Object* _checkBoxEventListener;

    ccCheckBoxCallback _checkBoxEventCallback;
};

}  // namespace ui

NS_AX_END
// end of ui group
/// @}

#endif /* defined(__CocoGUI__CheckBox__) */
