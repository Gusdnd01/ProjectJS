#include "pch.h"
#include "BaseWindow.h"
#include "Resource.h"
#include "Core.h"

BaseWindow::BaseWindow(POINT _ptResolution)
	: m_hWnd(0)
	, m_hInst(0)
    , m_ptResolution(_ptResolution)
{
}

BaseWindow::~BaseWindow()
{
}
//�Լ��� ���� ���� �Ǿ��ֱ⶧���� ��밡��
//:: = ���� ���� ������
int BaseWindow::Run(HINSTANCE _hInst, LPWSTR _lpCmdline, int _nCmdShow)
{
    m_hInst = _hInst;

    MyRegisterClass();
    WindowCreate();
    WindowShow(_nCmdShow);
    WindowUpdate();

    if (!Core::GetInst()->Init(m_hWnd, m_ptResolution)) {
        MessageBox(m_hWnd, L"Core �ʱ�ȭ ����", L"Fail", MB_OK);
    }

    return MessageLoop();//�����Ǿ����� �̰� this��� Ű���尡 �տ� ����
}

ATOM BaseWindow::MyRegisterClass()
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = m_hInst;
    wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_PROJECTJS));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = WINDOW_CLASS_NAME;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

void BaseWindow::WindowCreate()
{
    int iWinposx = GetSystemMetrics(SM_CXSCREEN) / 2 - m_ptResolution.x/ 2;
    int iWinposy = GetSystemMetrics(SM_CYSCREEN) / 2 - m_ptResolution.y/ 2;

    m_hWnd = CreateWindowW(WINDOW_CLASS_NAME, L"Hyun Framework", WS_OVERLAPPEDWINDOW,
        iWinposx, iWinposy, m_ptResolution.x, m_ptResolution.y, nullptr, nullptr, m_hInst, nullptr);

    RECT rt = { iWinposx, iWinposy, iWinposx + m_ptResolution.x, iWinposy + m_ptResolution.y };
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
    MoveWindow(m_hWnd, iWinposx, iWinposy, rt.right - rt.left, rt.bottom - rt.top, true);
}

void BaseWindow::WindowShow(int _nCmdShow)
{
    ShowWindow(m_hWnd, _nCmdShow);
}

void BaseWindow::WindowUpdate()
{
    UpdateWindow(m_hWnd);
}

LRESULT BaseWindow::WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
    switch (_message)
    {
    //    // �츮�� PAINT�� ����..?
    //case WM_PAINT:
    //{
    //    PAINTSTRUCT ps;
    //    HDC hdc = BeginPaint(_hWnd, &ps);
    //    // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�...
    //    EndPaint(_hWnd, &ps);
    //}
    //break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(_hWnd, _message, _wParam, _lParam);
    }
    return 0;
}

int BaseWindow::MessageLoop()
{

    MSG msg;
    // �⺻ �޽��� �����Դϴ�:
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            Core::GetInst()->GameLoop();
        }
    }
    Core::GetInst()->Release();
    return (int)msg.wParam;
}
