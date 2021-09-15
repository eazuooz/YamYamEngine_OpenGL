
#include "InputSystem.h"
#include <SDL/SDL.h>
#include <cstring>

bool KeyboardState::GetKeyValue(SDL_Scancode keycode) const
{
    return mCurrState[keycode] == 1;
}

ButtonState KeyboardState::GetKeyState(SDL_Scancode keyCode) const
{
    if (mPrevState[keyCode] == 0)
    {
        if (mCurrState[keyCode] == 0)
        {
            return ENone;
        }
        else
        {
            return EPressed;
        }
    }
    else
    {
        if (mCurrState[keyCode] == 0)
        {
            return EReleased;
        }
        else
        {
            return EHeld;
        }
    }
}

bool MouseState::GetButtonValue(int button) const
{
    return (SDL_BUTTON(button) & mCurrButtons) == 1;
}

ButtonState MouseState::GetButtonState(int button) const
{
    int mask = SDL_BUTTON(button);
    if ((mask & mPrevButtons) == 0)
    {
        if ((mask & mCurrButtons) == 0)
        {
            return ENone;
        }
        else
        {
            return EPressed;
        }
    }
    else
    {
        if ((mask & mCurrButtons) == 0)
        {
            return EReleased;
        }
        else
        {
            return EHeld;
        }
    }
}

bool ControllerState::GetButtonValue(SDL_GameControllerButton button) const
{
    return mCurrButtons[button] == 1;
}

ButtonState ControllerState::GetButtonState(SDL_GameControllerButton button) const
{
    if (mPrevButtons[button] == 0)
    {
        if (mCurrButtons[button] == 0)
        {
            return ENone;
        }
        else
        {
            return EPressed;
        }
    }
    else // Prev state must be 1
    {
        if (mCurrButtons[button] == 0)
        {
            return EReleased;
        }
        else
        {
            return EHeld;
        }
    }
}

bool InputSystem::Initialize()
{
    mState.Keyboard.mCurrState = SDL_GetKeyboardState(NULL);
    memset(mState.Keyboard.mPrevState, 0,
        SDL_NUM_SCANCODES);

    mState.Mouse.mCurrButtons = 0;
    mState.Mouse.mPrevButtons = 0;
    
    mController = SDL_GameControllerOpen(0);
    mState.Controller.mIsConnected = (mController != nullptr);
    memset(mState.Controller.mCurrButtons, 0,
        SDL_CONTROLLER_BUTTON_MAX);
    memset(mState.Controller.mPrevButtons, 0,
        SDL_CONTROLLER_BUTTON_MAX);

    //SDL_ShowCursor(SDL_ENABLE);

    return true;
}

void InputSystem::Shutdown()
{
}

void InputSystem::PrepareForUpdate()
{
    // Copy current state to previous
    // Keyboard
    memcpy(mState.Keyboard.mPrevState,
        mState.Keyboard.mCurrState,
        SDL_NUM_SCANCODES);

    // Mouse
    mState.Mouse.mPrevButtons = mState.Mouse.mCurrButtons;
    mState.Mouse.mIsRelative = false;
    mState.Mouse.mScrollWheel = Vector2::Zero;

    // Controller
    memcpy(mState.Controller.mPrevButtons,
        mState.Controller.mCurrButtons,
        SDL_CONTROLLER_BUTTON_MAX);
}

void InputSystem::Update()
{
    //mouse
    int x = 0; int y = 0;
    if (mState.Mouse.mIsRelative)
    {
        mState.Mouse.mCurrButtons =
            SDL_GetRelativeMouseState(&x, &y);
    }
    else
    {
        mState.Mouse.mCurrButtons =
            SDL_GetMouseState(&x, &y);
    }

    mState.Mouse.mMousePos.x = static_cast<float>(x);
    mState.Mouse.mMousePos.y = static_cast<float>(y);

    // Buttons
    for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++)
    {
        mState.Controller.mCurrButtons[i] =
            SDL_GameControllerGetButton(mController,
                SDL_GameControllerButton(i));
    }

    // Triggers
    mState.Controller.mLeftTrigger =
        Filter1D(SDL_GameControllerGetAxis(mController,
            SDL_CONTROLLER_AXIS_TRIGGERLEFT));
    mState.Controller.mRightTrigger =
        Filter1D(SDL_GameControllerGetAxis(mController,
            SDL_CONTROLLER_AXIS_TRIGGERRIGHT));

    // Sticks
    x = SDL_GameControllerGetAxis(mController,
        SDL_CONTROLLER_AXIS_LEFTX);
    y = -SDL_GameControllerGetAxis(mController,
        SDL_CONTROLLER_AXIS_LEFTY);
    mState.Controller.mLeftStick = Filter2D(x, y);

    x = SDL_GameControllerGetAxis(mController,
        SDL_CONTROLLER_AXIS_RIGHTX);
    y = -SDL_GameControllerGetAxis(mController,
        SDL_CONTROLLER_AXIS_RIGHTY);
    mState.Controller.mRightStick = Filter2D(x, y);
}

void InputSystem::ProcessEvent(SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_MOUSEWHEEL:
        mState.Mouse.mScrollWheel = Vector2(
            static_cast<float>(event.wheel.x),
            static_cast<float>(event.wheel.y));
        break;
    default:
        break;
    }
}

void InputSystem::SetRelativeMouseMode(const bool value)
{
    SDL_bool set = value ? SDL_TRUE : SDL_FALSE;
    SDL_SetRelativeMouseMode(set);

    mState.Mouse.mIsRelative = value;
}

float InputSystem::Filter1D(int input)
{
    const int deadZone = 250;
    const int maxValue = 30000;

    float retVal = 0.0f;

    int absValue = input > 0 ? input : -input;

    if (absValue > deadZone)
    {
        retVal = static_cast<float>(absValue - deadZone) /
        (maxValue - deadZone);
        retVal = input > 0 ? retVal : -1.0f * retVal;
        retVal = Math::Clamp(retVal, -1.0f, 1.0f);
    }

    return retVal;
}

Vector2 InputSystem::Filter2D(int inputX, int inputY)
{
    const float deadZone = 8000.0f;
    const float maxValue = 30000.0f;

    Vector2 dir;
    dir.x = static_cast<float>(inputX);
    dir.y = static_cast<float>(inputY);

    float length = dir.Length();

    if (length < deadZone)
    {
        dir = Vector2::Zero;
    }
    else
    {
        float f = (length - deadZone) / (maxValue - deadZone);
        f = Math::Clamp(f, 0.0f, 1.0f);
        dir *= f / length;
    }

    return dir;
}
