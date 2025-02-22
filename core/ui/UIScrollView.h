/****************************************************************************
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
Copyright (c) 2019-present Axmol Engine contributors (see AUTHORS.md).

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

#ifndef __UISCROLLVIEW_H__
#define __UISCROLLVIEW_H__

#include "ui/UILayout.h"
#include "ui/GUIExport.h"
#include <list>

NS_AX_BEGIN
/**
 * @addtogroup ui
 * @{
 */

class EventFocusListener;

namespace ui
{

class ScrollViewBar;

/**
 * Layout container for a view hierarchy that can be scrolled by the user, allowing it to be larger than the physical
 * display. It holds a inner `Layout` container for storing child items horizontally or vertically.
 */
class AX_GUI_DLL ScrollView : public Layout
{

    DECLARE_CLASS_GUI_INFO

public:
    /**
     * ScrollView scroll direction type.
     */
    enum class Direction
    {
        NONE,
        VERTICAL,
        HORIZONTAL,
        BOTH
    };

    /**
     * Scrollview scroll event type.
     */
    enum class EventType
    {
        SCROLL_TO_TOP,
        SCROLL_TO_BOTTOM,
        SCROLL_TO_LEFT,
        SCROLL_TO_RIGHT,
        SCROLLING,
        BOUNCE_TOP,
        BOUNCE_BOTTOM,
        BOUNCE_LEFT,
        BOUNCE_RIGHT,
        CONTAINER_MOVED,
        SCROLLING_BEGAN,
        SCROLLING_ENDED,
        AUTOSCROLL_ENDED
    };

    /**
     * A callback which would be called when a ScrollView is scrolling.
     */
    typedef std::function<void(Object*, EventType)> ccScrollViewCallback;

    /**
     * Default constructor
     * @js ctor
     * @lua new
     */
    ScrollView();

    /**
     * Default destructor
     * @js NA
     * @lua NA
     */
    ~ScrollView() override;

    /**
     * Create an empty ScrollView.
     * @return A ScrollView instance.
     */
    static ScrollView* create();

    /**
     * Changes scroll direction of scrollview.
     *
     * @see `Direction`
     * @param dir Scroll direction enum.
     */
    virtual void setDirection(Direction dir);

    /**
     * Query scroll direction of scrollview.
     *
     * @see `Direction`      Direction::VERTICAL means vertical scroll, Direction::HORIZONTAL means horizontal scroll
     *
     * @return Scrollview scroll direction.
     */
    Direction getDirection() const;

    /**
     * Get inner container of scrollview.
     *
     * Inner container is a child of scrollview.
     *
     * @return Inner container pointer.
     */
    Layout* getInnerContainer() const;

    /**
     * Immediately stops inner container scroll (auto scrolling is not affected).
     */
    virtual void stopScroll();

    /**
     * Immediately stops inner container scroll initiated by any of the "scrollTo*" member functions
     */
    virtual void stopAutoScroll();

    /**
     * Immediately stops inner container scroll if any.
     */
    virtual void stopOverallScroll();

    /**
     * Scroll inner container to bottom boundary of scrollview.
     * @param timeInSec Time in seconds.
     * @param attenuated Whether scroll speed attenuate or not.
     */
    virtual void scrollToBottom(float timeInSec, bool attenuated);

    /**
     * Scroll inner container to top boundary of scrollview.
     * @param timeInSec Time in seconds.
     * @param attenuated Whether scroll speed attenuate or not.
     */
    virtual void scrollToTop(float timeInSec, bool attenuated);

    /**
     * Scroll inner container to left boundary of scrollview.
     * @param timeInSec Time in seconds.
     * @param attenuated Whether scroll speed attenuate or not.
     */
    virtual void scrollToLeft(float timeInSec, bool attenuated);

    /**
     * Scroll inner container to right boundary of scrollview.
     * @param timeInSec Time in seconds.
     * @param attenuated Whether scroll speed attenuate or not.
     */
    virtual void scrollToRight(float timeInSec, bool attenuated);

    /**
     * Scroll inner container to top and left boundary of scrollview.
     * @param timeInSec Time in seconds.
     * @param attenuated Whether scroll speed attenuate or not.
     */
    virtual void scrollToTopLeft(float timeInSec, bool attenuated);

    /**
     * Scroll inner container to top and right boundary of scrollview.
     * @param timeInSec Time in seconds.
     * @param attenuated Whether scroll speed attenuate or not.
     */
    virtual void scrollToTopRight(float timeInSec, bool attenuated);

    /**
     * Scroll inner container to bottom and left boundary of scrollview.
     * @param timeInSec Time in seconds.
     * @param attenuated Whether scroll speed attenuate or not.
     */
    virtual void scrollToBottomLeft(float timeInSec, bool attenuated);

    /**
     * Scroll inner container to bottom and right boundary of scrollview.
     * @param timeInSec Time in seconds
     * @param attenuated Whether scroll speed attenuate or not.
     */
    virtual void scrollToBottomRight(float timeInSec, bool attenuated);

    /**
     * Scroll inner container to vertical percent position of scrollview.
     * @param percent A value between 0 and 100.
     * @param timeInSec Time in seconds.
     * @param attenuated Whether scroll speed attenuate or not.
     */
    virtual void scrollToPercentVertical(float percent, float timeInSec, bool attenuated);

    /**
     * Scroll inner container to horizontal percent position of scrollview.
     * @param percent A value between 0 and 100.
     * @param timeInSec Time in seconds.
     * @param attenuated Whether scroll speed attenuate or not.
     */
    virtual void scrollToPercentHorizontal(float percent, float timeInSec, bool attenuated);

    /**
     * Scroll inner container to both direction percent position of scrollview.
     * @param percent A value between 0 and 100.
     * @param timeInSec Time in seconds.
     * @param attenuated Whether scroll speed attenuate or not.
     */
    virtual void scrollToPercentBothDirection(const Vec2& percent, float timeInSec, bool attenuated);

    /**
     * @return How far the scroll view is scrolled in the vertical axis
     */
    float getScrolledPercentVertical() const;
    /**
     * @return How far the scroll view is scrolled in the horizontal axis
     */
    float getScrolledPercentHorizontal() const;
    /**
     * @return How far the scroll view is scrolled in both axes, combined as a Vec2
     */
    Vec2 getScrolledPercentBothDirection() const;

    /**
     * Move inner container to bottom boundary of scrollview.
     */
    virtual void jumpToBottom();

    /**
     * Move inner container to top boundary of scrollview.
     */
    virtual void jumpToTop();

    /**
     * Move inner container to left boundary of scrollview.
     */
    virtual void jumpToLeft();

    /**
     * Move inner container to right boundary of scrollview.
     */
    virtual void jumpToRight();

    /**
     * Move inner container to top and left boundary of scrollview.
     */
    virtual void jumpToTopLeft();

    /**
     * Move inner container to top and right boundary of scrollview.
     */
    virtual void jumpToTopRight();

    /**
     * Move inner container to bottom and left boundary of scrollview.
     */
    virtual void jumpToBottomLeft();

    /**
     * Move inner container to bottom and right boundary of scrollview.
     */
    virtual void jumpToBottomRight();

    /**
     * Move inner container to vertical percent position of scrollview.
     * @param percent A value between 0 and 100.
     */
    virtual void jumpToPercentVertical(float percent);

    /**
     * Move inner container to horizontal percent position of scrollview.
     * @param percent   A value between 0 and 100.
     */
    virtual void jumpToPercentHorizontal(float percent);

    /**
     * Move inner container to both direction percent position of scrollview.
     * @param percent   A value between 0 and 100.
     */
    virtual void jumpToPercentBothDirection(const Vec2& percent);

    /**
     * Change inner container size of scrollview.
     *
     * Inner container size must be larger than or equal scrollview's size.
     *
     * @param size Inner container size.
     */
    void setInnerContainerSize(const Vec2& size);

    /**
     * Get inner container size of scrollview.
     *
     * Inner container size must be larger than or equal scrollview's size.
     *
     * @return The inner container size.
     */
    const Vec2& getInnerContainerSize() const;

    /**
     * Set inner container position
     *
     * @param pos Inner container position.
     */
    void setInnerContainerPosition(const Vec2& pos);

    /**
     * Get inner container position
     *
     * @return The inner container position.
     */
    const Vec2& getInnerContainerPosition() const;

    /**
     * Add callback function which will be called  when scrollview event triggered.
     * @param callback A callback function with type of `ccScrollViewCallback`.
     */
    virtual void addEventListener(const ccScrollViewCallback& callback);

    // override functions
    void addChild(Node* child) override;
    void addChild(Node* child, int localZOrder) override;
    void addChild(Node* child, int localZOrder, int tag) override;
    void addChild(Node* child, int localZOrder, std::string_view name) override;
    void removeAllChildren() override;
    void removeAllChildrenWithCleanup(bool cleanup) override;
    void removeChild(Node* child, bool cleanup = true) override;
    Vector<Node*>& getChildren() override;
    const Vector<Node*>& getChildren() const override;
    ssize_t getChildrenCount() const override;
    Node* getChildByTag(int tag) const override;
    Node* getChildByName(std::string_view name) const override;
    // touch event callback
    bool onTouchBegan(Touch* touch, Event* unusedEvent) override;
    void onTouchMoved(Touch* touch, Event* unusedEvent) override;
    void onTouchEnded(Touch* touch, Event* unusedEvent) override;
    void onTouchCancelled(Touch* touch, Event* unusedEvent) override;
    void update(float dt) override;

    /**
     * @brief Toggle bounce enabled when scroll to the edge.
     *
     * @param enabled True if enable bounce, false otherwise.
     */
    void setBounceEnabled(bool enabled);

    /**
     * @brief Query bounce state.
     *
     * @return True if bounce is enabled, false otherwise.
     */
    bool isBounceEnabled() const;

    /**
     * @brief Toggle whether enable scroll inertia while scrolling.
     *
     * @param enabled True if enable inertia, false otherwise.
     */
    void setInertiaScrollEnabled(bool enabled);

    /**
     * @brief Query inertia scroll state.
     *
     * @return True if inertia is enabled, false otherwise.
     */
    bool isInertiaScrollEnabled() const;

    /**
     * @brief Toggle scroll bar enabled.
     *
     * @param enabled True if enable scroll bar, false otherwise.
     */
    void setScrollBarEnabled(bool enabled);

    /**
     * @brief Query scroll bar state.
     *
     * @return True if scroll bar is enabled, false otherwise.
     */
    bool isScrollBarEnabled() const;

    /**
     * @brief Set the scroll bar positions from the left-bottom corner (horizontal) and right-top corner (vertical).
     *
     * @param positionFromCorner The position from the left-bottom corner (horizontal) and right-top corner (vertical).
     */
    void setScrollBarPositionFromCorner(const Vec2& positionFromCorner);

    /**
     * @brief Set the vertical scroll bar position from right-top corner.
     *
     * @param positionFromCorner The position from right-top corner
     */
    void setScrollBarPositionFromCornerForVertical(const Vec2& positionFromCorner);

    /**
     * @brief Get the vertical scroll bar's position from right-top corner.
     *
     * @return positionFromCorner
     */
    Vec2 getScrollBarPositionFromCornerForVertical() const;

    /**
     * @brief Set the horizontal scroll bar position from left-bottom corner.
     *
     * @param positionFromCorner The position from left-bottom corner
     */
    void setScrollBarPositionFromCornerForHorizontal(const Vec2& positionFromCorner);

    /**
     * @brief Get the horizontal scroll bar's position from right-top corner.
     *
     * @return positionFromCorner
     */
    Vec2 getScrollBarPositionFromCornerForHorizontal() const;

    /**
     * @brief Set the scroll bar's width
     *
     * @param width The scroll bar's width
     */
    void setScrollBarWidth(float width);

    /**
     * @brief Get the scroll bar's width
     *
     * @return the scroll bar's width
     */
    float getScrollBarWidth() const;

    /**
     * @brief Set the scroll bar's color
     *
     * @param color the scroll bar's color
     */
    void setScrollBarColor(const Color3B& color);

    /**
     * @brief Get the scroll bar's color
     *
     * @return the scroll bar's color
     */
    const Color3B& getScrollBarColor() const;

    /**
     * @brief Set the scroll bar's opacity
     *
     * @param opacity the scroll bar's opacity
     */
    void setScrollBarOpacity(uint8_t opacity);

    /**
     * @brief Get the scroll bar's opacity
     *
     * @return the scroll bar's opacity
     */
    uint8_t getScrollBarOpacity() const;

    /**
     * @brief Set scroll bar auto hide state
     *
     * @param autoHideEnabled scroll bar auto hide state
     */
    void setScrollBarAutoHideEnabled(bool autoHideEnabled);

    /**
     * @brief Query scroll bar auto hide state
     *
     * @return True if scroll bar auto hide is enabled, false otherwise.
     */
    bool isScrollBarAutoHideEnabled() const;

    /**
     * @brief Set scroll bar auto hide time
     *
     * @param autoHideTime bar auto hide time
     */
    void setScrollBarAutoHideTime(float autoHideTime);

    /**
     * @brief Get the scroll bar's auto hide time
     *
     * @return the scroll bar's auto hide time
     */
    float getScrollBarAutoHideTime() const;

    /**
     * @brief Set the touch total time threshold
     *
     * @param touchTotalTimeThreshold the touch total time threshold
     */
    void setTouchTotalTimeThreshold(float touchTotalTimeThreshold);

    /**
     * @brief Get the touch total time threshold
     *
     * @return the touch total time threshold
     */
    float getTouchTotalTimeThreshold() const;

    /**
     * Set layout type for scrollview.
     *
     * @see `Layout::Type`
     * @param type  Layout type enum.
     */
    void setLayoutType(Type type) override;

    /**
     * Get the layout type for scrollview.
     *
     * @see `Layout::Type`
     * @return LayoutType
     */
    Type getLayoutType() const override;

    /**
     * Return the "class name" of widget.
     */
    std::string getDescription() const override;

    /**
     * @lua NA
     */
    void onEnter() override;

    /**
     * @lua NA
     */
    void onExit() override;

    /**
     *  When a widget is in a layout, you could call this method to get the next focused widget within a specified
     *direction. If the widget is not in a layout, it will return itself
     *@param direction the direction to look for the next focused widget in a layout
     *@param current  the current focused widget
     *@return the next focused widget in a layout
     */
    Widget* findNextFocusedWidget(FocusDirection direction, Widget* current) override;

    /**
     * Set the time in seconds to scroll between items.
     * Subsequent calls of function 'scrollToItem', will take 'time' seconds for scrolling.
     * @param time The seconds needed to scroll between two items. 'time' must be >= 0
     * @see scrollToItem(ssize_t, const Vec2&, const Vec2&)
     */
    void setScrollDuration(float time);

    /**
     * Get the time in seconds to scroll between items.
     * @return The time in seconds to scroll between items
     * @see setScrollDuration(float)
     */
    float getScrollDuration() const;

    /**
     * @return Whether the user is currently dragging the ScrollView to scroll it
     */
    bool isScrolling() const { return _scrolling; }
    /**
     * @return Whether the ScrollView is currently scrolling because of a bounceback or inertia slowdown.
     */
    bool isAutoScrolling() const { return _autoScrolling; }

    bool init() override;

    /**
     * @brief Scroll to specific item
     * @param item Item to scroll to
     * @param positionRatioInView Specifies the position with ratio in list view's content size.
     * @param itemAnchorPoint Specifies an anchor point of each item for position to calculate distance.
     */
    void scrollToItem(Node* item, const Vec2& positionRatioInView, const Vec2& itemAnchorPoint);

    /**
     * @brief Scroll to specific item
     * @param item Item to scroll to
     * @param positionRatioInView Specifies the position with ratio in list view's content size.
     * @param itemAnchorPoint Specifies an anchor point of each item for position to calculate distance.
     * @param timeInSec Scroll time
     */
    void scrollToItem(Node* item, const Vec2& positionRatioInView, const Vec2& itemAnchorPoint, float timeInSec);

    static Vec2 calculateItemPositionWithAnchor(const Node* node, const Vec2& itemAnchorPoint);

protected:
    enum class MoveDirection
    {
        TOP,
        BOTTOM,
        LEFT,
        RIGHT,
    };

    void initRenderer() override;

    void onSizeChanged() override;
    void doLayout() override;

    Widget* createCloneInstance() override;
    void copySpecialProperties(Widget* model) override;
    void copyClonedWidgetChildren(Widget* model) override;

    virtual void initScrollBar();
    virtual void removeScrollBar();

    Vec2 flattenVectorByDirection(const Vec2& vector);

    virtual Vec2 getHowMuchOutOfBoundary(const Vec2& addition = Vec2::ZERO);
    bool isOutOfBoundary(MoveDirection dir);
    bool isOutOfBoundary();

    virtual void moveInnerContainer(const Vec2& deltaMove, bool canStartBounceBack);

    bool calculateCurrAndPrevTouchPoints(Touch* touch, Vec3* currPt, Vec3* prevPt);
    void gatherTouchMove(const Vec2& delta);
    Vec2 calculateTouchMoveVelocity() const;

    virtual void startAttenuatingAutoScroll(const Vec2& deltaMove, const Vec2& initialVelocity);
    void startAutoScroll(const Vec2& deltaMove, float timeInSec, bool attenuated);
    void startAutoScrollToDestination(const Vec2& des, float timeInSec, bool attenuated);
    bool isNecessaryAutoScrollBrake();
    void processAutoScrolling(float deltaTime);

    void startInertiaScroll(const Vec2& touchMoveVelocity);

    bool startBounceBackIfNeeded();

    void jumpToDestination(const Vec2& des);

    virtual void scrollChildren(const Vec2& deltaMove);

    virtual void handlePressLogic(Touch* touch);
    virtual void handleMoveLogic(Touch* touch);
    virtual void handleReleaseLogic(Touch* touch);

    void interceptTouchEvent(Widget::TouchEventType event, Widget* sender, Touch* touch) override;

    void processScrollEvent(MoveDirection dir, bool bounce);
    void processScrollingEvent();
    void processScrollingEndedEvent();
    void dispatchEvent(EventType eventType);

    void updateScrollBar(const Vec2& outOfBoundary);

    Vec2 calculateItemDestination(const Vec2& positionRatioInView, const Node* item, const Vec2& itemAnchorPoint);

protected:
    virtual float getAutoScrollStopEpsilon() const;
    bool fltEqualZero(const Vec2& point) const;
    Layout* _innerContainer;

    Direction _direction;

    float _topBoundary;
    float _bottomBoundary;
    float _leftBoundary;
    float _rightBoundary;

    bool _bePressed;

    float _childFocusCancelOffsetInInch;

    // Touch move speed
    std::list<Vec2> _touchMoveDisplacements;
    std::list<float> _touchMoveTimeDeltas;
    long long _touchMovePreviousTimestamp;
    float _touchTotalTimeThreshold;

    bool _scrolling;

    bool _autoScrolling;
    bool _autoScrollAttenuate;
    Vec2 _autoScrollStartPosition;
    Vec2 _autoScrollTargetDelta;
    float _autoScrollTotalTime;
    float _autoScrollAccumulatedTime;
    bool _autoScrollCurrentlyOutOfBoundary;
    bool _autoScrollBraking;
    Vec2 _autoScrollBrakingStartPosition;

    bool _inertiaScrollEnabled;

    bool _bounceEnabled;

    Vec2 _outOfBoundaryAmount;
    bool _outOfBoundaryAmountDirty;

    bool _scrollBarEnabled;
    ScrollViewBar* _verticalScrollBar;
    ScrollViewBar* _horizontalScrollBar;

    Object* _scrollViewEventListener;
    ccScrollViewCallback _eventCallback;

    float _scrollTime;
};

}  // namespace ui
// end of ui group
/// @}
NS_AX_END
#endif /* defined(__CocoGUI__ScrollView__) */
