/* Notes to self while implimenting code:
 *
 * Function to send input:
 * SendInput(1, &ip, sizeof(INPUT));
 * Where ip is an INPUT object
 *
 * However, ip has to have the properties you
 * Want below in order for it to function properly:
 *
 * INPUT.ki.wVk = [ascii character] --> Sets which ascii character to print
 * INPUT.ki.dwFlags = [0 OR KEYEVENTF_KEYUP] --> 0 means a key press, and KEYEVENTF_KEYUP means a key release
 *
 * GetAsyncKeyState(VK_NUMPAD2) returns true if numpad 2 is pressed and false otherwise
 *
 * https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes?redirectedfrom=MSDN
 * ^
 * Source to all key presses (microsoft codes)
 *
 *http://doc.51windows.net/Directx9_SDK/input/tuts/directinputcctutorials.htm
 *^
 *directx
 */

#include <iostream>
#include <windows.h>
#include <vector>
#include <string>

 //takes in a properly set up INPUT and presses the "key" key on the keyboard

int setKey(char key)
{
    if (key == ' ')
        return  VK_SPACE;
    else if (key == ':' || key == ';')
        return  VK_OEM_1;
    else if (key == '-' || key == '_')
        return  VK_OEM_MINUS;
    else if (key == '/' || key == '?')
        return  VK_OEM_2;
    else if (key == '.' || key == '>')
        return  VK_OEM_PERIOD;
    else if (key == ',' || key == '<')
        return  VK_OEM_COMMA;
    else if (key == '/' || key == '?')
        return  VK_OEM_2;
    else if (key == '`' || key == '~')
        return  VK_OEM_3;
    else if (key == '[' || key == '{')
        return  VK_OEM_4;
    else if (key == '\\' || key == '|')
        return  VK_OEM_5;
    else if (key == ']' || key == '}')
        return  VK_OEM_6;
    else if (key == '\'' || key == '\"')
        return  VK_OEM_7;
    else if (key == '+' || key == '=')
        return  VK_OEM_PLUS;
    else if (key == '\t')
        return VK_TAB;
    else if (key == '1' || key == '!')
        return static_cast<int>('1');
    else if (key == '2' || key == '@')
        return static_cast<int>('2');
    else if (key == '3' || key == '#')
        return static_cast<int>('3');
    else if (key == '4' || key == '$')
        return static_cast<int>('4');
    else if (key == '5' || key == '%')
        return static_cast<int>('5');
    else if (key == '6' || key == '^')
        return static_cast<int>('6');
    else if (key == '7' || key == '&')
        return static_cast<int>('7');
    else if (key == '8' || key == '*')
        return static_cast<int>('8');
    else if (key == '9' || key == '(')
        return static_cast<int>('9');
    else if (key == '0' || key == ')')
        return static_cast<int>('0');
    

    else if (std::isalpha(key))
        return static_cast<int>(std::toupper(key));

}

int setKey(std::string key)
{
    if (key == "ENTER")
        return VK_RETURN;
    if (key == "BACKSPACE" || key == "BACK")
        return VK_BACK;
    if (key == "SHIFT")
        return VK_SHIFT;
    if (key == "CONTROL" || key == "CTRL")
        return VK_CONTROL;
    if (key == "TAB")
        return VK_TAB;
}

template <typename T>
void release(T key)
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; 
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.dwFlags = KEYEVENTF_KEYUP; //release
    ip.ki.wVk = setKey(key);
    SendInput(1, &ip, sizeof(INPUT));
}

void hold(std::string key)
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; 
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.dwFlags = 0; //press
    ip.ki.wVk = setKey(key);
    SendInput(1, &ip, sizeof(INPUT));
}

void hold(char key)
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; 
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.dwFlags = 0;
    ip.ki.wVk = setKey(key);
    bool requireShift = false;

    std::string shifts = "!@#$%^&*()_+{}:\"<>?|~";
    if (shifts.find(key) != std::string::npos || std::isupper(key))
        requireShift = true;

    if (requireShift)
    {
        hold("SHIFT");
        SendInput(1, &ip, sizeof(INPUT));
        release("SHIFT");
    }

    else
        SendInput(1, &ip, sizeof(INPUT));
}

template<typename T>
void press(T key)
{
    hold(key);
    release(key);
}

//sends the message in all lower-case
void sendMessage(std::string message)
{
    for (int i{ 0 }; i < message.length(); ++i)
    {
        press(message[i]);
    }
    press("ENTER");
}

//params: inital time, final time
//does: waits the amount of time in between
void wait(int Hi, int Mi, int Si, int Hf, int Mf, int Sf)
{
    int dH = 0;
    int dM = 0;
    int dS = 0;
    if (Si > Sf)
    {
        Mf--;
        Sf += 60;
    }
    dS = Sf - Si;
    if (Mi > Mf)
    {
        Hf--;
        Mf += 60;
    }
    dM = Mf - Mi;
    if (Hi > Hf)
    {
        Hf += 24;
    }
    dH = Hf - Hi;

    std::cout << dH << " " << dM << " " << dS << " ";

    //There are 3,600,000ms in 1h, 60,000ms in 1m, and 1000ms in 1s
    Sleep(dH * 3600000);
    Sleep(dM * 60000);
    Sleep(dS * 1000);
}

//-------------------------------------------------------------------------------------------------------

int main()
{
    
    // Exit normally
    return 0;
}
