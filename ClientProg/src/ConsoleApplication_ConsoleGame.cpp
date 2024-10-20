#include "MyUtil.h"
#include <cwchar>
#define _USE_MATH_DEFINES
#include <cmath>
#include <complex>
#include <Windows.h>
#include <WinUser.h>
#include <strsafe.h>
#include "KInput.h"
#include <vector>
#include "Client.hxx"
#include <iostream>
#include <thread>
#include <conio.h>
#include <array>
#include <mutex>


std::array<char, 128> buffer = {""};
std::array<char, 128> receiveBuffer = {""};

std::mutex g_m;

double g_drawScale = 1.0;

class KVector2
{
public:
    double x;
    double y;
};

KVector2 g_pos{ 10, 10 };

void DrawLine(double x, double y, double x2, double y2, char ch)
{
    KVector2 center{ g_width / 2.0, g_height / 2.0 };
    ScanLine(int(x * g_drawScale + center.x), int(-y * g_drawScale + center.y)
        , int(x2 * g_drawScale + center.x), int(-y2 * g_drawScale + center.y), ch);
}

void Update(double elapsedTime)
{
    if (Input.GetKeyDown(VK_LEFT)) {
        g_pos.x -= 1;
        
    }
    if (Input.GetKeyDown(VK_RIGHT)) {
        g_pos.x += 1;
        
    }
    if (Input.GetKeyDown(VK_DOWN)) {
        g_pos.y += 1;
        
    }
    if (Input.GetKeyDown(VK_UP)) {
        g_pos.y -= 1;
        
    }
}

void DrawGameWorld(double elapsedTime) {
    g_drawScale = 1.0;
    DrawLine(-g_width / 2, 0, g_width / 2, 0, '.');
    DrawLine(0, -g_height / 2, 0, g_height / 2, '.');

    PutTextf(0, 0, "%g", elapsedTime);

    float h = Input.GetAxis("Horizontal");
    float v = Input.GetAxis("Vertical");
    PutTextf(1, 1, "Simultaneous Key Processing:");
    PutTextf(1, 2, "h = %g", h);
    PutTextf(1, 3, "v = %g", v);
    PutText(g_pos.x, g_pos.y, "P");
    PutTextf(1, g_height - 3, "Chat: %s", buffer.data());
    PutTextf(1, g_height - 2, "Server: %s", receiveBuffer.data());
    DrawBuffer();
}

void chatting(bool& isChatting, const network::ConnectionHandler& connHandl)
{
    isChatting = true;
    int index = 0;

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    while (true)
    {
        int ch = _getch();

        if (ch == 224) {
            int arrowKey = _getch();
            switch (arrowKey) {
            case 75:
            case 77:
            case 72:
            case 80:
                continue;
            default:
                break;
            }
        }

        
        if (ch == '\r') {
            buffer[index] = '\0'; 
            break;
        }

        if (ch == '\b' && index > 0) {
            index--;
            buffer[index] = '\0';
            continue;
        }

        if (index < sizeof(buffer) - 1 && ch >= 32 && ch <= 126) {
            buffer[index++] = ch;
        }
    }

    connHandl.SendData(buffer.data(), buffer.size());
    fflush(stdin);
    buffer.fill('\0');

    connHandl.ReceiveData(receiveBuffer.data(), receiveBuffer.size());

    isChatting = false;
}

int main(void)
{
    g_hwndConsole = GetConsoleWindow();
    g_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ShowCursor(false);

    bool isGameLoop = true;
    clock_t prevClock = clock();
    clock_t currClock = prevClock;
    int i = 1;

    network::ConnectionHandler connectionHandl{};
    if (!connectionHandl.Initialize())
    {
        printf("Failed to initialize client\n");
        return 1;
    }

    if (!connectionHandl.Connect())
    {
        printf("Failed to connect to server\n");
        return 2;
    }

    bool isChattingMode = false;
    while (isGameLoop)
    {
        if (Input.GetKeyDown(VK_ESCAPE)) {
            isGameLoop = false;
        }
        if (Input.GetKeyDown(VK_SPACE) && !isChattingMode)
        {
            std::thread chatting_thread(chatting, std::ref(isChattingMode), std::cref(connectionHandl));

            chatting_thread.detach();
        }
        prevClock = currClock;
        currClock = clock();
        const double elapsedTime = ((double)currClock - (double)prevClock) / CLOCKS_PER_SEC;
        ClearBuffer();
        Input.Update(elapsedTime);
        Update(elapsedTime);
        Sleep(10);
        DrawGameWorld(elapsedTime);
       
    }

    connectionHandl.Disconect();
}