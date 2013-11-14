#pragma once

class SystemClass : Uncopyable
{
private:
    const HINSTANCE instanceHandle;
    HWND windowHandle;

    const bool isFullScreen;
    const double freq;
    double last;

    function<bool(double)> idle;
    function<void(HDC)> draw;

public:
    // HINSTANCE : ������ �����찡 ���ӵ� ���α׷��� �ν��Ͻ�
    // Width : ������ �������� �ʱ� ���α���
    // Height : ������ �������� �ʱ� ���α���
    // FullScreen : ��üȭ�� ����
    SystemClass(HINSTANCE InstanceHandle, size_t Width, size_t Height, bool FullScreen);

    ~SystemClass();

    // �� ���޽ð����� ȣ��� �ݹ��Լ��� ���Ѵ�
    // bool Callback(double elapsed) : �� ���޽ð����� ȣ��� �ݹ��Լ�
    //     elapsed : ������ �־��� ȣ��κ��� �帥 �ð�
    //     ��ȯ�� : true to receive more idle processing time; false if no more idle time is needed.
    void onIdle(const decltype(idle)& Callback) { idle = Callback; }

    // �׸��⸦ ������ �ݹ��Լ��� ���Ѵ�
    // void Callback(HDC hdc) : �� ������ �������� ȣ��� �ݹ��Լ�
    //     hdc : �������� ���� DC �ڵ�
    void onDraw(const decltype(draw)& Callback) { draw = Callback; }

    // ������� ������ �ν��Ͻ��� ȭ��� ǥ���ϰ�, �޼��������� �����Ѵ�
    // ShowCommand : �����찡 �����Ǿ����� �������� ����(�ʱ�ȭ����, ��üȭ��, ��..)
    void Run(int ShowCommand);

private:
    static LRESULT CALLBACK wndProc_temp(HWND, UINT, WPARAM, LPARAM);
    static LRESULT CALLBACK wndProc(HWND, UINT, WPARAM, LPARAM);
    LRESULT CALLBACK messageHandler(HWND, UINT, WPARAM, LPARAM);
};
